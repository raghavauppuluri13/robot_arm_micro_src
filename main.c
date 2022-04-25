/**
  ******************************************************************************
  * @file    main.c
  * @author  Raghava Uppuluri
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f0xx.h"
#include "inc/servo.h"
#include "inc/ik.h"
#include "inc/stdout.h"
#include "inc/joy.h"
#include "inc/utils.h"
#include "inc/break_beam.h"

struct Joy joys[JOY_CNT] = {
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
};

void TIM15_IRQHandler() {
    TIM15->SR &= ~TIM_SR_UIF;

    for(int id = 0; id < JOY_CNT; id++) {
        ADC1->CHSELR = 0;
        ADC1->CHSELR |= 1 << joy_specs[id].ch;
        while(!(ADC1->ISR & ADC_ISR_ADRDY));
        ADC1->CR |= ADC_CR_ADSTART;
        while(!(ADC1->ISR & ADC_ISR_EOC));
        joys[id].bcsum -= joys[id].boxcar[joys[id].bcn];
        joys[id].bcsum += joys[id].boxcar[joys[id].bcn] = ADC1->DR;
        joys[id].bcn += 1;
        if (joys[id].bcn >= BCSIZE) {
            joys[id].bcn = 0;
        }
        joys[id].val = joys[id].bcsum / BCSIZE;
    }
}


void test_servo() {
    pwm_gpio_init();
    for(int id = 0; id < SERVO_CNT; id++ ) {
        servo_init(id);
    }

    servo_write(5,100);

    int wait = 100000000; // ns ~ 100hz pub rate TODO: tune

    for(;;) {
        ;
//        for(int i = 45; i < 75; i++) {
//            servo_write(5,i);
//
//            smintf("Angle: %d\n", i);
//            nano_wait(wait);
//        }
//        for(int i = 75; i >= 45; i--) {
//            servo_write(5,i);
//
//            smintf("Angle: %d\n", i);
//            nano_wait(wait);
//        }
    }

}

void test_ik() {
    init_inv_kin();
    for(;;) {
        for(int i = 0; i < 20; i++) {
            inv_kin();
            smintf("{ ");
            for(int i = 0; i < SERVO_CNT; i++) {
                print_float(ang[i]);
                smintf(", ", i);
            }
            smintf("}\n");
            z -= 1;
            nano_wait(100000000);
        }
        for(int i = 0; i < 20; i++) {
            inv_kin();
            smintf("{ ");
            for(int i = 0; i < SERVO_CNT; i++) {
                print_float(ang[i]);
                smintf(", ");
            }
            smintf("}\n");
            z += 1;
            nano_wait(100000000);
        }
    }
}

void test_break_beam() {
    init_break_beam();
    for(;;) {
        smintf("Score: %d\n", score);
        nano_wait(10000000);
    }

}

void test_joys() {
    init_joys();
    start_joys();

    for(;;) {
        smintf("Joy 0: %d, Joy 1: %d, Joy 2: %d \n", joys[0].val,joys[1].val,joys[2].val);
        nano_wait(10000000);
    }

}

void inc_axis(float* axis, int joy_ind, int lower, int upper) {

    if(joys[joy_ind].val > UPPER_JOY_MID) {
       (*axis) = (*axis) + AXIS_STEP;
       clamp(axis,upper,lower);
    }
    else if(joys[joy_ind].val < LOWER_JOY_MID) {
       (*axis) = (*axis) - AXIS_STEP;
       clamp(axis,upper,lower);
    }
}

void test_main() {
    init_joys();
    start_joys();
    init_inv_kin();
    //nano_wait(1000000000); // joy
    pwm_gpio_init();
    init_break_beam();
    for(int id = 0; id < SERVO_CNT; id++ ) {
        servo_init(id);
    }

    for(;;) {
        inc_axis(&x,0,X_MIN,X_MAX);
        inc_axis(&y,1,Y_MIN,Y_MAX);
        inc_axis(&z,2,Z_MIN,Z_MAX);
        inc_axis(&grip,3,GRIP_MIN,GRIP_MAX);
        smintf("XYZ: ");
        print_float(x);
        smintf(" ");
        print_float(y);
        smintf(" ");
        print_float(z);
        smintf("\n");

        inv_kin();
        smintf("{ ");
        for(int i = 0; i < SERVO_CNT; i++) {
            print_float(ang[i]);
            smintf(", ", i);
        }
        smintf("}\n");
        servo_write(0, ang[0]);
        servo_write(1, ang[1]);
        servo_write(2, ang[2]);
        servo_write(3,90);
        servo_write(4, ang[4]);
        servo_write(5,grip);
        nano_wait(10000000); // speed and frequency of arm
//        for(int id = 0; id < SERVO_CNT; id++ ) {
//            servo_write(id,0);
//        }
    }
}

int main(void)
{
    init_usart(); // printf with serial protocol
    test_main();
    //test_joys();
    //test_servo();
    //test_break_beam();
    //test_ik();
}

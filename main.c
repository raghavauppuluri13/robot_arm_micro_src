/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "inc/servo.h"
#include "inc/stdout.h"
#include "inc/joy.h"

struct Joy joys[JOY_CNT] = {
  {.val = 2048, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 2048, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 2048, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 2048, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 2048, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 2048, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
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

void nano_wait(unsigned int n) {
    asm(    "        mov r0,%0\n"
            "repeat: sub r0,#83\n"
            "        bgt repeat\n" : : "r"(n) : "r0", "cc");
}

int main(void)
{
//    pwm_gpio_init();
//
//    for(int id = 0; id < SERVO_CNT; id++ ) {
//        servo_init(id);
//    }
//    servo_write(5,180);

    init_usart();
    init_joys();
    start_joys();

    for(;;) {
        smintf("Joy 2: %d, Joy 3: %d\n", joys[0].val,joys[1].val);
        nano_wait(10000000);
    }
}

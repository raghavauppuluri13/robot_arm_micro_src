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

int main(void)
{
    uint8_t id = 5;
    pwm_gpio_init();
    servo_init(id);
    enable_servo_timers();
    servo_write(id,0);

    for(;;);
}

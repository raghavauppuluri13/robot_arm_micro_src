#ifndef __SERVO_H__
#define __SERVO_H__
#include "stm32f0xx.h"

// Pulse width lim ts in microseconds for servo


// PWM period=20ms
#define PWM_PSC 16
#define PWM_ARR 60000

#define MIN_DEG 0
#define MAX_DEG 180

// 0.0272 duty cycle - 0 deg
// min pulse width = 544ns
#define MIN_CCR 1632

// 90 deg
#define MID_CCR 4416

// 0.12s duty cycle - 180 deg
// max pulse width = 2400ns
#define MAX_CCR 7200
#define SERVO_CNT 6
/* Valid servo pin map:
 * TIM2_CH2: PA1, AF2  SERVO ID #0
 * TIM2_CH3: PA2, AF2, SERVO ID #1
 * TIM2_CH4: PA3, AF2, SERVO ID #2
 *
 * TIM3_CH4: PB1, AF1, SERVO ID #3
 * TIM3_CH1: PB4, AF1, SERVO ID #4
 * TIM3_CH2: PB5, AF1, SERVO ID #5
 */
struct ServoSpec {
    uint8_t pin;
    TIM_TypeDef* tim;
    GPIO_TypeDef* gpio;
    uint8_t af;
    __IO uint16_t* ccmr;
    __IO uint16_t* ccr;
    uint16_t mode_preload;
};

const struct ServoSpec srv_specs[SERVO_CNT] = {
        /****************************** ID 0 **********************************/
        { .pin = 1, .gpio = GPIOA, .tim=TIM2, .af = 2,
          .ccmr = &(TIM2->CCMR1), .ccr = &(TIM2->CCR1),
          .mode_preload = TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE
        },
        /****************************** ID 1 **********************************/
        { .pin = 2, .gpio = GPIOA, .tim=TIM2, .af = 2,
          .ccmr = &(TIM2->CCMR2), .ccr = &(TIM2->CCR1),
          .mode_preload = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE
        },
        /****************************** ID 2 **********************************/
        { .pin = 3, .gpio = GPIOA, .tim=TIM2, .af = 2,
          .ccmr = &(TIM2->CCMR2), .ccr = &(TIM2->CCR1),
          .mode_preload = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE
        },
        /****************************** ID 3 **********************************/
        { .pin = 1, .gpio = GPIOB, .tim=TIM3, .af = 1,
          .ccmr = &(TIM2->CCMR2), .ccr = &(TIM2->CCR1),
          .mode_preload = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE
        },
        /****************************** ID 4 **********************************/
        { .pin = 4, .gpio = GPIOB, .tim=TIM3, .af = 1,
          .ccmr = &(TIM2->CCMR1), .ccr = &(TIM2->CCR1),
          .mode_preload = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE
        },
        /****************************** ID 5 **********************************/
        { .pin = 5, .gpio = GPIOB, .tim=TIM3, .af = 1,
          .ccmr = &(TIM2->CCMR1), .ccr = &(TIM2->CCR1),
          .mode_preload = TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE
        },
};

// servo and pwm inits
static void pwm_gpio_init();
static void srv_init(uint8_t id);

// writes a degree value to a servo
void servo_write(uint8_t id, float deg); //

// maps a degree value to CCR value
static uint16_t map_(uint16_t in, uint16_t from_high, uint16_t from_low,
                                  uint16_t to_high,   uint16_t to_low);

// PWM Timers

#endif

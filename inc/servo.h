#include "stm32f0xx.h"

#ifndef __SERVO_H__
#define __SERVO_H__

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
    __IO uint32_t* ccmr;
    __IO uint32_t* ccr;
    uint16_t mode_preload;
    uint16_t ccer_en;
    uint8_t max_ang;
    uint8_t init_ang;
    uint8_t min_ang;
};

static const struct ServoSpec srv_specs[SERVO_CNT] = {
        /****************************** ID 0 **********************************/
        { .pin = 1, .gpio = GPIOA, .tim=TIM2, .af = 2,
          .ccmr = &(TIM2->CCMR1), .ccr = &(TIM2->CCR2), .ccer_en = TIM_CCER_CC2E,
          .mode_preload = TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1| TIM_CCMR1_OC2PE,
          .min_ang = 0, .max_ang = 180, .init_ang = 90
        },
        /****************************** ID 1 **********************************/
        { .pin = 2, .gpio = GPIOA, .tim=TIM2, .af = 2,
          .ccmr = &(TIM2->CCMR2), .ccr = &(TIM2->CCR3),.ccer_en = TIM_CCER_CC3E,
          .mode_preload = TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE,
          .min_ang = 0, .max_ang = 180, .init_ang = 90
        },
        /****************************** ID 2 **********************************/
        { .pin = 3, .gpio = GPIOA, .tim=TIM2, .af = 2,
          .ccmr = &(TIM2->CCMR2), .ccr = &(TIM2->CCR4),.ccer_en = TIM_CCER_CC4E,
          .mode_preload = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE,
          .min_ang = 75, .max_ang = 105, .init_ang = 90
        },
        /****************************** ID 3 **********************************/
        { .pin = 1, .gpio = GPIOB, .tim=TIM3, .af = 1,
          .ccmr = &(TIM3->CCMR2), .ccr = &(TIM3->CCR4),.ccer_en = TIM_CCER_CC4E,
          .mode_preload = TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE,
          .min_ang = 15, .max_ang = 160, .init_ang = 90
        },
        /****************************** ID 4 **********************************/
        { .pin = 4, .gpio = GPIOB, .tim=TIM3, .af = 1,
          .ccmr = &(TIM3->CCMR1), .ccr = &(TIM3->CCR1),.ccer_en = TIM_CCER_CC1E,
          .mode_preload = TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE,
          .min_ang = 0, .max_ang = 180, .init_ang = 90
        },
        /****************************** ID 5 **********************************/
        { .pin = 5, .gpio = GPIOB, .tim=TIM3, .af = 1,
          .ccmr = &(TIM3->CCMR1), .ccr = &(TIM3->CCR2),.ccer_en = TIM_CCER_CC2E,
          .mode_preload = TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE,
          .min_ang = 0, .max_ang = 180, .init_ang = 100
        },
};

// servo and pwm inits
void pwm_gpio_init();

void servo_init(uint8_t id);

// clamps a value
void clamp(float* val, int max, int min);

// writes a degree value to a servo
void servo_write(uint8_t id, float deg);

// maps a degree value to CCR value
static uint32_t map(uint32_t in, uint32_t from_high, uint32_t from_low,
                                  uint32_t to_high,   uint32_t to_low);

void servos_enable();

void servos_disable();

#endif

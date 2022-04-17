#include "inc/servo.h"

static

// PWM
void pwm_gpio_init()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB1ENR |= RCC_APB2ENR_TIM1EN;

    TIM2->ARR = PWM_ARR;
    TIM2->PSC = PWM_PSC;
    TIM2->CR1 |= TIM_CR1_ARPE;
    TIM2->CR1 |= TIM_CR1_CEN;

    TIM3->ARR = PWM_ARR;
    TIM3->PSC = PWM_PSC;
    TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->CR1 |= TIM_CR1_CEN;

}

void srv_init(uint8_t id) {
    srv_specs[id].gpio->MODER &= ~(3 << (2 * srv_specs[id].pin));
    srv_specs[id].gpio->MODER |= 2 << (2 * srv_specs[id].pin);
    srv_specs[id].gpio->AFR[0] |= srv_specs[id].af << (4 * srv_specs[id].pin);
    // Enable PWM 1 mode and preload register
    *(srv_specs[id].ccmr) |= srv_specs[id].mode_preload;
}

// writes a degree value to a servo
void servo_write(uint8_t id, float deg) {
   *(srv_specs[id].ccr) = map_(deg, MAX_DEG, MIN_DEG, MAX_CCR, MIN_CCR);
}

// IN/MAX_IN = OUT/MAX_OUT, OUT = (IN/MAX_IN)*MAX_OUT
static uint16_t map_(uint16_t in, uint16_t from_high, uint16_t from_low,
                                  uint16_t to_high,   uint16_t to_low) {
    return ((in-from_low) * (to_high - to_low)) / (from_high - from_low) + to_low;
}

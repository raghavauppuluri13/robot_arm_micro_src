#include "inc/servo.h"
#include "assert.h"
// PWM
void pwm_gpio_init()
{
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM2->ARR = PWM_ARR-1;
    TIM2->PSC = PWM_PSC-1;

    TIM3->ARR = PWM_ARR-1;
    TIM3->PSC = PWM_PSC-1;
}

void servos_enable() {
    TIM2->CR1 |= TIM_CR1_CEN;
    TIM3->CR1 |= TIM_CR1_CEN;
}

void servos_disable() {
    TIM2->CR1 &= ~TIM_CR1_CEN;
    TIM3->CR1 &= ~TIM_CR1_CEN;
}

void servo_init(uint8_t id) {
    srv_specs[id].gpio->MODER &= ~(3 << (2 * srv_specs[id].pin));
    srv_specs[id].gpio->MODER |= 2 << (2 * srv_specs[id].pin);
    srv_specs[id].gpio->AFR[0] |= srv_specs[id].af << (4 * srv_specs[id].pin);
    // Enable PWM 1 mode and preload register
    *(srv_specs[id].ccmr) |= srv_specs[id].mode_preload;
    srv_specs[id].tim->CCER |= srv_specs[id].ccer_en;
    *(srv_specs[id].ccr) = map(srv_specs[id].init_ang,MAX_DEG,MIN_DEG,MAX_CCR,MIN_CCR);
}

void clamp(float* val, int max, int min) {
    if (*val > max) {
       *val = max;
    }
    else if(*val < min) {
       *val = min;
    }
}

// writes a degree value to a servo
void servo_write(uint8_t id, float deg) {
   //assert(deg >= 0 && deg <= 180);
   clamp(&deg,srv_specs[id].max_ang,srv_specs[id].min_ang);
   *(srv_specs[id].ccr) = map(deg,MAX_DEG,MIN_DEG,MAX_CCR,MIN_CCR);
}

// IN/MAX_IN = OUT/MAX_OUT, OUT = (IN/MAX_IN)*MAX_OUT
uint32_t map(uint32_t in, uint32_t from_high, uint32_t from_low,
                                  uint32_t to_high,   uint32_t to_low) {
    return ((in-from_low) * (to_high - to_low)) / (from_high - from_low) + to_low;
}

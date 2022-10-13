#include "inc/joy.h"


void init_joy(uint8_t id) {
    GPIOC->MODER |= 3 << (2 * joy_specs[id].pin);
}

void init_joys() {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    for(int i = 0; i < JOY_CNT; i++) {
        init_joy(i);
    }

    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
    RCC->CR2 |= RCC_CR2_HSI14ON;
    while(!(RCC->CR2 & RCC_CR2_HSI14RDY));
    ADC1->CR |= ADC_CR_ADEN;
    while(!(ADC1->ISR & ADC_ISR_ADRDY));
    while((ADC1->CR & ADC_CR_ADSTART));

    init_tim15();
}


void start_joys(void) {
    TIM15->CR1 |= 1;
}

void init_tim15(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
    TIM15->PSC = 4800-1;
    TIM15->ARR = 100-1;
    TIM15->DIER |= 1;
    NVIC->ISER[0] |= 1<<TIM15_IRQn;
    NVIC_SetPriority(TIM15_IRQn,0);
}

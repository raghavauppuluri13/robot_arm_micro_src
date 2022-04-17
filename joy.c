#include "inc/joy.h"


void init_joy(uint8_t id) {
    GPIOC->MODER |= 3 << (2 * joys[id].pin);
}

void init_adc_gpio() {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
    RCC->CR2 |= RCC_CR2_HSI14ON;
    while(!(RCC->CR2 & RCC_CR2_HSI14RDY));
    ADC1->CR |= ADC_CR_ADEN;
    while(!(ADC1->ISR & ADC_ISR_ADRDY));
    while((ADC1->CR & ADC_CR_ADSTART));
}

void TIM15_IRQHandler() {
    TIM15->SR &= ~TIM_SR_UIF;

    for(int id = 0; id < JOY_CNT; id++) {
        ADC1->CHSELR = 0;
        ADC1->CHSELR |= 1 << joys[id].ch;
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

void init_tim15(void)
{
    RCC->APB1ENR |= 1;
    TIM15->PSC = 48000-1;
    TIM15->ARR = 100-1;
    TIM15->DIER |= 1;
    TIM15->CR1 |= 1;

    NVIC_EnableIRQ(TIM15_IRQn);
    NVIC_SetPriority(TIM15_IRQn,3)
}

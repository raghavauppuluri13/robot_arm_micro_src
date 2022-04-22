/* Break Beam Sensor */
#include "stm32f0xx.h"

#ifndef __BREAK_BEAM_H__
#define __BREAK_BEAM_H__

/* Break Beam sensor EXTI on PA0 */
#define BB_PIN 0
int score = 0;

void init_break_beam() {
   RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
   RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

   GPIOA->MODER &= ~(3 << (BB_PIN * 2));
   GPIOA->PUPDR &= ~(3 << (BB_PIN * 2));
   GPIOA->PUPDR |= 1 << (BB_PIN * 2);

   SYSCFG->EXTICR[0] &= ~(0xf << BB_PIN * 4);
   EXTI->FTSR |= 1 << BB_PIN;
   EXTI->IMR |= 1 << BB_PIN;
   NVIC->ISER[0] |= 1<<EXTI0_1_IRQn;
   NVIC_EnableIRQ(EXTI0_1_IRQn);
   NVIC_SetPriority(EXTI0_1_IRQn,0);
}

void EXTI0_1_IRQHandler() {
    score++;
    EXTI->PR |= 1 << BB_PIN;
}

#endif

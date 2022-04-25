/* Break Beam Sensor */
#include "stm32f0xx.h"

#ifndef __BREAK_BEAM_H__
#define __BREAK_BEAM_H__

/* Break Beam sensor EXTI on PC10 */
#define BB_PIN 10
int score = 0;

void init_break_beam() {
   RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
   RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;

   GPIOC->MODER &= ~(3 << (BB_PIN * 2));
   GPIOC->PUPDR &= ~(3 << (BB_PIN * 2));
   GPIOC->PUPDR |= 1 << (BB_PIN * 2);

   SYSCFG->EXTICR[2] &= ~(0xf << ((BB_PIN % 4) * 4));
   SYSCFG->EXTICR[2] |= (2 << ((BB_PIN % 4) * 4));
   EXTI->FTSR |= 1 << BB_PIN;
   EXTI->IMR |= 1 << BB_PIN;
   NVIC->ISER[0] |= 1<<EXTI4_15_IRQn;
   NVIC_EnableIRQ(EXTI4_15_IRQn);
   NVIC_SetPriority(EXTI4_15_IRQn,0);
}

void EXTI4_15_IRQHandler() {
    score++;
    EXTI->PR |= 1 << BB_PIN;
}

#endif

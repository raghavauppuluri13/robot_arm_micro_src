#include <stdio.h>
#include "stm32f0xx.h"
#include "lcd.h"
#include "midi.h"
#include "midiplay.h"

// PIR SENSOR RISING EDGE GPIO;
// TFT LCD DISPLAY (USE LCD FUNCTIONS FROM HW8 lcd.c)
    // HOOK UP MUSIC COMPONENTS
    // OTHER STUFF (LIKE BACKGROUND) WHEN GAME IS OVER

static char print_score[4], print_countdown[5];
static int total_seconds_left = (5*60+0), score = 0;

void timer_debug(void)
{
    // ENABLE PC8 BLINKING OUTPUT
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER &= ~GPIO_MODER_MODER8;
    GPIOC->MODER |= GPIO_MODER_MODER8_0;

    // TIMER DEBUG DEMO (PLACE IN INTERRUPT)
    /*
    if ((GPIOC->ODR & GPIO_ODR_8) != 0) {
        GPIOC->BRR |= GPIO_BRR_BR_8;
    } else {
        GPIOC->BSRR |= GPIO_BSRR_BS_8;
    }
    */

}

void init_lcd_spi(void)
{
    // ENABLE GPIO OUTPUTS FOR LCD
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER11 |
                        GPIO_MODER_MODER14);
    GPIOB->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER11_0 |
                        GPIO_MODER_MODER14_0);
    GPIOB->BSRR |= (GPIO_BSRR_BS_8 | GPIO_BSRR_BS_11 | GPIO_BSRR_BS_14);
    GPIOB->MODER &= ~(GPIO_MODER_MODER3 | GPIO_MODER_MODER5);
    GPIOB->MODER |= (GPIO_MODER_MODER3_1 | GPIO_MODER_MODER5_1);
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFR3 | GPIO_AFRL_AFR5);

    // CONFIGURE SPI CONTROLS AND ENABLE
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    SPI1->CR1 &= ~(SPI_CR1_SPE | SPI_CR1_BR);
    SPI1->CR1 |= (SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI);
    SPI1->CR2 |= (SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0);
    SPI1->CR1 |= SPI_CR1_SPE;
}

void setup_ports(void)
{
    // SETUP PC10 FOR PIR SENSOR RISING EDGE
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    GPIOC->MODER &= ~GPIO_MODER_MODER10;

    // SETUP KEYPAD
    GPIOC->MODER &= ~(0xffff);
    GPIOC->MODER |= (0x5500);
    GPIOC->OTYPER |= 0xf0;
    GPIOC->PUPDR &= ~(0xff);
    GPIOC->PUPDR |= (GPIO_PUPDR_PUPDR3_0 | GPIO_PUPDR_PUPDR2_0 |
                     GPIO_PUPDR_PUPDR1_0| GPIO_PUPDR_PUPDR0_0);
}

void TIM7_IRQHandler(void)
{
    TIM7->SR &= ~TIM_SR_UIF;
    if (total_seconds_left > 0)
        total_seconds_left--;
}

void EXTI4_15_IRQHandler(void)
{
    EXTI->PR |= EXTI_PR_PR10;
    if (total_seconds_left > 0)
        score++;
}

void countdown_timer(void)
{
    // GENERATE 1HZ COUNTDOWN WITH TIMER 7
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    TIM7->ARR = 48000 - 1;
    TIM7->PSC = 1000 - 1;
    TIM7->DIER |= TIM_DIER_UIE;
    TIM7->CR1 |= TIM_CR1_CEN;
    NVIC_SetPriority(TIM7_IRQn, 0);
    NVIC->ISER[0] |= (1<<TIM7_IRQn);
}

void score_increment(void)
{
    // USE PC10 AS INPUT TO TRIGGER GPIO INTERRUPT
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
    SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI10;
    SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PC;
    EXTI->RTSR |= EXTI_RTSR_TR10;
    EXTI->IMR |= EXTI_IMR_MR10;
    NVIC_SetPriority(EXTI4_15_IRQn, 1);
    NVIC->ISER[0] |= (1<<EXTI4_15_IRQn);
}

void num_to_string(void)
{
    // CONVERT INTEGER TIME AND SCORE TO PRINTABLE STRINGS
    int minutes = total_seconds_left / 60;
    int seconds = total_seconds_left % 60;
    print_countdown[0] = minutes + '0';
    print_countdown[1] = ':';
    print_countdown[2] = (seconds / 10) + '0';
    print_countdown[3] = (seconds % 10) + '0';
    sprintf(print_score, "%d", score);
}

void game_logic(void)
{
    countdown_timer();
    score_increment();
}

void initialize_lcd_contents(void)
{
    // Instantiate LCD Display
    LCD_Clear(WHITE);
    LCD_DrawString(40, 40, BLACK, WHITE, "COUNTDOWN", 16, 0);
    LCD_DrawString(40, 180, BLACK, WHITE, "SCORE", 16, 0);
    total_seconds_left++; //start at the correct time
}

void continuous_display_music(void)
{
    MIDI_Player *mp = midi_init(scale);
    // The default rate for a MIDI file is 2 beats per second
    // with 48 ticks per beat.  That's 500000/48 microseconds.
    init_tim2(10417);
    int shift = 0;
    while (1)
    {
        // Redraw Count Down Timer and Score for Every Frame
        num_to_string();
        if (total_seconds_left > 10)
            LCD_DrawString(80, 90, BLACK, WHITE, print_countdown, 16, 0);
        else
            LCD_DrawString(80, 90, RED, WHITE, print_countdown, 16, 0);
        LCD_DrawString(80, 230, BLACK, WHITE, print_score, 16, 0);

        // Loop and Shift Music According to Time Remaining
            // how to turn off one song?
            // how to blend songs together?
        if (total_seconds_left > 60) {
            asm("wfi");
            if (mp->nexttick == MAXTICKS)
                mp = midi_init(scale);
        } else if ((total_seconds_left == 60) && (!shift)) {
            mp = midi_init(tiger);
            shift = 1;
        } else {
            asm("wfi");
            if (mp->nexttick == MAXTICKS)
                mp = midi_init(tiger);
        }
    }
}

int main(void)
{
    LCD_Setup(); // sets up LCD and SPI
    setup_ports(); // sets up PC10 or other GPIO input (PIR rising edge)
    game_logic(); // calculate time and increment score
    initialize_lcd_contents(); // display contents of LCD
    initialize_music(); // integrate music functions and components
    continuous_display_music();
}

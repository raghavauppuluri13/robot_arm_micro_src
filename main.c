#include "stm32f0xx.h"
#include "lcd.h"
#include "inc/servo.h"
#include "inc/ik.h"
#include "inc/stdout.h"
#include "inc/joy.h"
#include "inc/utils.h"
#include "inc/break_beam.h"
#include "midi.h"
#include "midiplay.h"

#define TOTAL_SECONDS_RESET_VALUE 3*60

static char print_score[4], print_countdown[5];
static int total_seconds_left = (TOTAL_SECONDS_RESET_VALUE);
//static int score = 0;
struct Joy joys[JOY_CNT] = {
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
  {.val = 1950, .bcsum = 0, .boxcar = {0}, .bcn = 0 },
};

//Menu Related variables
#define NUM_OF_MENU_OPTIONS 4
const char * words[NUM_OF_MENU_OPTIONS] = {"GAME", "Free Mode", "Hard Mode", "Leaderboard"};
int leaderboard[5] = {0, 0, 0, 0, 0};
int optionSelected = 0;
int gameMode = 0;

int mainMenuCount = 10;
int updateMenu = 0;
enum stateOfNum {MAINMENU, GAMEOVER, GAME, FREEMODE, HARDMODE, LEADERBOARD, INITMAINMENU, INITLEADERBOARD, GAMEINIT, INITFREEMODE, INITHARDMODE};
void init_lcd_spi(void)
{
    // ENABLE GPIO OUTPUTS FOR LCD
     /*  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
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
       SPI1->CR1 |= SPI_CR1_SPE; */
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
           GPIOB->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER11 |
                               GPIO_MODER_MODER14);
           GPIOB->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER11_0 |
                               GPIO_MODER_MODER14_0);
           GPIOB->BSRR |= (GPIO_BSRR_BS_8 | GPIO_BSRR_BS_11 | GPIO_BSRR_BS_14);
           GPIOB->MODER &= ~(GPIO_MODER_MODER13 | GPIO_MODER_MODER15);
           GPIOB->MODER |= (GPIO_MODER_MODER13_1 | GPIO_MODER_MODER15_1);
           GPIOB->AFR[1] &= ~(GPIO_AFRL_AFR5 | GPIO_AFRL_AFR7);

           // CONFIGURE SPI CONTROLS AND ENABLE
           RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
           SPI1->CR1 &= ~(SPI_CR1_SPE | SPI_CR1_BR);
           SPI1->CR1 |= (SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI);
           SPI1->CR2 |= (SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0);
           SPI1->CR1 |= SPI_CR1_SPE;
}


/* drawMenuOption
 * const char * words - string to output
 * int baseModeAlignmentX - the X base alignment of the first output on the menu
 * int baseModeAlignmentY - the Y base alignment of the first output on the menu
 * int menuOptionNum - the # menu option that is being output. 0 for the main menu title, >0 for menu options
 * u16 fc - the font color
 * u16 bc - the background color
 * u16 rc - the rectangle color
 *
 */
int drawMenuOption(const char * words, int baseModeAlignmentX, int baseModeAlignmentY, int menuOptionNum, u16 fc, u16 bc, u16 rc)
{
    int baseModeAlignmentYFixed = baseModeAlignmentY + 50 * menuOptionNum;
    int rectX1Spacing = baseModeAlignmentX - 5;
    int rectY1Spacing = baseModeAlignmentYFixed - 5;
    int rectX2Spacing = rectX1Spacing + 125;
    int rectY2Spacing = rectY1Spacing + 30;

    if(menuOptionNum == 0)
    {
        int lineX1 = baseModeAlignmentX;
        int lineX2 = baseModeAlignmentX + 80;
        int lineY12 = baseModeAlignmentYFixed + 20;

        LCD_DrawLine(lineX1, lineY12 , lineX2, lineY12, fc);
        LCD_DrawString(baseModeAlignmentX, baseModeAlignmentY, fc, bc, words, 16, 1); // opaque background
    }
    else
    {
        LCD_DrawRectangle(rectX1Spacing, rectY1Spacing, rectX2Spacing, rectY2Spacing, rc);
        LCD_DrawString(baseModeAlignmentX, baseModeAlignmentYFixed, fc, bc, words, 16, 1); // opaque background
    }
    menuOptionNum++;
    return menuOptionNum;
}


/*drawMainMenu
 * countDown: the current count down of the timer in seconds
 * optionSelected: the current option that is selected
 */
void drawMainMenu(int optionSelected, int countDown)
{
    int selectModeAlignmentX = 70;
    int selectModeAlignmentY = 10;
    int menuOptionItr = 0;



    LCD_Clear(0);
    LCD_DrawFillRectangle(0, 0, 440, 440, BLUE);
    menuOptionItr = drawMenuOption("Select Mode. ", selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, YELLOW, BLUE, BLACK);
    for(int i = 0; i < NUM_OF_MENU_OPTIONS; i++)
    {
        if (i == optionSelected)
            menuOptionItr = drawMenuOption(words[i], selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, RED, RED, RED);
        else
            menuOptionItr = drawMenuOption(words[i], selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, YELLOW, BLUE, BLACK);
    }
    LCD_DrawString(15, 250, YELLOW, BLUE, "Time until option is kept: " , 16, 1);

    char converted[2];
    sprintf(converted, "%d", countDown);
    LCD_DrawString(140, 280, YELLOW, BLUE, converted, 16, 1);//converted[0]
}
void drawMainMenuNoBKGND(int optionSelected, int countDown)
{
    int selectModeAlignmentX = 70;
    int selectModeAlignmentY = 10;
    int menuOptionItr = 0;



    //LCD_Clear(0);
    //LCD_DrawFillRectangle(0, 0, 440, 440, BLUE);
    menuOptionItr = drawMenuOption("Select Mode. ", selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, YELLOW, BLUE, BLACK);
    for(int i = 0; i < NUM_OF_MENU_OPTIONS; i++)
    {
        if (i == optionSelected)
            menuOptionItr = drawMenuOption(words[i], selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, RED, RED, RED);
        else
            menuOptionItr = drawMenuOption(words[i], selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, YELLOW, BLUE, BLACK);
    }
    LCD_DrawString(15, 250, YELLOW, BLUE, "Time until option is kept: " , 16, 1);

    char converted[2];
    sprintf(converted, "%d", countDown);
    LCD_DrawString(140, 280, YELLOW, BLUE, converted, 16, 1);//converted[0]
}


void doCoolColorEffect(int x4, int y4, const char * stringToOutput, int fontSize, int opaque)
{

    LCD_DrawString(x4, y4, YELLOW, BLUE, stringToOutput, fontSize, opaque);
    for(int i = 0; i < 3; i++)
    {
        for(int v = 0; v < 100; v++)
        {
            LCD_DrawString(x4, y4, RED, BLUE, stringToOutput, fontSize, opaque);
        }
        for(int v = 0; v < 100; v++)
        {
            LCD_DrawString(x4, y4, GREEN, BLUE, stringToOutput, fontSize, opaque);
        }
        for(int v = 0; v < 100; v++)
        {
            LCD_DrawString(x4, y4, BLACK, BLUE, stringToOutput, fontSize, opaque);
        }
        for(int v = 0; v < 100; v++)
        {
            LCD_DrawString(x4, y4, YELLOW, BLUE, stringToOutput, fontSize, opaque);
        }
        for(int v = 0; v < 100; v++)
        {
            LCD_DrawString(x4, y4, WHITE, BLUE, stringToOutput, fontSize, opaque);
        }
    }

}


void drawGameOver()
{
    LCD_Clear(0);
    if(score > leaderboard[0])
    {
        LCD_DrawFillRectangle(0, 0, 440, 440, BLUE);
        doCoolColorEffect(60, 150,"NEW HIGH SCORE!!!", 16, 1);

        leaderboard[1] = leaderboard[0];
        leaderboard[2] = leaderboard[1];
        leaderboard[3] = leaderboard[2];

        leaderboard[0] = score;
    }
    else if ((score > leaderboard[4]) | (score > leaderboard[3]) | (score > leaderboard[2]) | (score > leaderboard[1]))
    {
        LCD_DrawFillRectangle(0, 0, 440, 440, BLUE);
        doCoolColorEffect(60, 150,"G o o d  j o b !", 16, 1);
        if(score > leaderboard[1])
        {
            leaderboard[3] = leaderboard[2];
            leaderboard[2] = leaderboard[1];
            leaderboard[1] = score;
        }
        else if(score > leaderboard[2])
        {
            leaderboard[3] = leaderboard[2];
            leaderboard[2] = score;
        }
        else if(score > leaderboard[3])
        {
            leaderboard[3] = score;
        }
        /*if(score > leaderboard[4])
        {
            leaderboard[4] = score;
        }
        else if(score > leaderboard[3])
        {

            leaderboard[3] = score;
        }
        else if(score > leaderboard[2])
        {
            leaderboard[3] = leaderboard[2];
            leaderboard[2] = score;
        }
        else
        {
            leaderboard[2] = leaderboard[1];
            leaderboard[3] = leaderboard[2];
            leaderboard[1] = score;
        }*/
    }
    else
    {
        LCD_DrawFillRectangle(0, 0, 440, 440, BLUE);
        doCoolColorEffect(60, 150,"G A M E   O V E R", 16, 1);
    }
    gameMode = INITMAINMENU;

}



void drawLeaderBoard(int countDown)
{
    int selectModeAlignmentX = 70;
       int selectModeAlignmentY = 10;
       int menuOptionItr = 0;



       LCD_Clear(0);
       LCD_DrawFillRectangle(0, 0, 440, 440, BLUE);
       menuOptionItr = drawMenuOption("Leaderboard", selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, YELLOW, BLUE, BLACK);
       for(int i = 1; i < 5; i++)
       {
           if (i == 1)
           {
               menuOptionItr = drawMenuOption("#1", selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, YELLOW, BLUE, YELLOW);
               char scoreString[3];
               sprintf(scoreString, "%d", leaderboard[0]);
               LCD_DrawString(selectModeAlignmentX + 50, selectModeAlignmentY + 50, YELLOW, BLUE, scoreString, 16, 1);//converted[0]
           }
           else if(i == 2)
           {
               menuOptionItr = drawMenuOption("#2", selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, GRAY, BLUE, GRAY);
               char scoreString[3];
               sprintf(scoreString, "%d", leaderboard[1]);
               LCD_DrawString(selectModeAlignmentX + 50, selectModeAlignmentY + 100, YELLOW, BLUE, scoreString, 16, 1);//converted[0]
           }
           else if(i == 3)
           {
               menuOptionItr = drawMenuOption("#3", selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, BROWN, BLUE, BROWN);
               char scoreString[3];
               sprintf(scoreString, "%d", leaderboard[2]);
               LCD_DrawString(selectModeAlignmentX + 50, selectModeAlignmentY + 150, YELLOW, BLUE, scoreString, 16, 1);//converted[0]
           }
           else
           {
               menuOptionItr = drawMenuOption("#4", selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, WHITE, BLUE, WHITE);
               char scoreString[3];
               sprintf(scoreString, "%d", leaderboard[3]);
               LCD_DrawString(selectModeAlignmentX + 50, selectModeAlignmentY + 200, YELLOW, BLUE, scoreString, 16, 1);//converted[0]
           }
       }
       LCD_DrawString(15, 250, YELLOW, BLUE, "Time until menu return " , 16, 1);

       char converted[2];
       sprintf(converted, "%d", countDown);
       LCD_DrawString(140, 280, YELLOW, BLUE, converted, 16, 1);//converted[0]
}
void inc_axis(float* axis, int joy_ind, int lower, int upper) {

    if(joys[joy_ind].val > UPPER_JOY_MID) {
       (*axis) = (*axis) + AXIS_STEP;
       clamp(axis,upper,lower);
    }
    else if(joys[joy_ind].val < LOWER_JOY_MID) {
       (*axis) = (*axis) - AXIS_STEP;
       clamp(axis,upper,lower);
    }
}
void TIM15_IRQHandler() {
    TIM15->SR &= ~TIM_SR_UIF;

    for(int id = 0; id < JOY_CNT; id++) {
        ADC1->CHSELR = 0;
        ADC1->CHSELR |= 1 << joy_specs[id].ch;
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


void TIM14_IRQHandler()
{
    TIM14->SR &= ~TIM_SR_UIF;

    if(mainMenuCount == 0)
    {

        RCC->APB1ENR &= ~RCC_APB1ENR_TIM14EN;
        if(optionSelected == 0)
        {
            gameMode = GAMEINIT;
        }
        else if(optionSelected == 1)
        {
            gameMode = INITFREEMODE;
        }
        else if(optionSelected == 2)
        {
            gameMode = INITHARDMODE;
        }
        else if(optionSelected == 3)
         {
            gameMode = INITLEADERBOARD;
         }
    }
    else if (mainMenuCount != 0)
    {
        mainMenuCount--;
        updateMenu = 1;
        if((optionSelected > 0) &&((joys[1].val  < 1024) | (joys[2].val  < 1024)))
        {
            optionSelected--;
        }
        else if((optionSelected < 3) &&((joys[1].val  > 3072) | (joys[2].val  > 3072)))
        {
            optionSelected++;
        }

        //drawMainMenu(optionSelected, mainMenuCount);
    }

}

void enableTIM14()
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
    TIM14->ARR = 48000 - 1;
    TIM14->PSC = 1000 - 1;
    TIM14->DIER |= TIM_DIER_UIE;
    TIM14->CR1 |= TIM_CR1_CEN;
    NVIC_SetPriority(TIM14_IRQn, 0);
    NVIC->ISER[0] |= (1<<TIM14_IRQn);

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
    if(gameMode == GAMEINIT)
    {
        LCD_Clear(BLUE);
        LCD_DrawString(40, 40, YELLOW, BLUE, "COUNTDOWN", 16, 0);
        LCD_DrawString(40, 180, YELLOW, BLUE, "SCORE", 16, 0);
    }
    else if(gameMode == INITFREEMODE)
    {
            LCD_Clear(GREEN);
            LCD_DrawString(40, 40, BLACK, GREEN, "Time", 16, 0);
            LCD_DrawString(40, 180, BLACK, GREEN, "In Box:", 16, 0);
    }
    else if(gameMode == INITHARDMODE)
    {
                LCD_Clear(RED);
                LCD_DrawString(40, 40, WHITE, RED, "T I M E L E F T", 16, 0);
                LCD_DrawString(40, 180, WHITE, RED, "S C O R E", 16, 0);
    }


    total_seconds_left++; //start at the correct time
}
void loop_robot()
{
    inc_axis(&x,0,X_MIN,X_MAX);
    inc_axis(&y,1,Y_MIN,Y_MAX);
    inc_axis(&z,2,Z_MIN,Z_MAX);
    inc_axis(&grip,3,GRIP_MIN,GRIP_MAX);
    smintf("XYZ: ");
    print_float(x);
    smintf(" ");
    print_float(y);
    smintf(" ");
    print_float(z);
    smintf("\n");

    inv_kin();
    smintf("{ ");
    for(int i = 0; i < SERVO_CNT; i++) {
        print_float(ang[i]);
        smintf(", ", i);
    }
    smintf("}\n");
    servo_write(0, ang[0]);
    servo_write(1, ang[1]);
    servo_write(2, ang[2]);
    servo_write(3,90);
    servo_write(4, ang[4]);
    servo_write(5,grip);
    nano_wait(10000000); // speed and frequency of arm
}
void continuous_display_music(void)
{
    reset_voices();
    MIDI_Player *mp = midi_init(nocaution);


    // The default rate for a MIDI file is 2 beats per second
    // with 48 ticks per beat.  That's 500000/48 microseconds.
    init_tim2(10417);
    //int shift = 0;
    while (1)
    {
        // Redraw Count Down Timer and Score for Every Frame
        num_to_string();
        if(total_seconds_left == 0)
        {
            break;
        }
        if(total_seconds_left == 60)
        {
            reset_voices();
            mp = midi_init(tiger);
        }
        loop_robot();
        if(gameMode == GAMEINIT)
        {
            if (total_seconds_left > 10)
                LCD_DrawString(80, 90, YELLOW, BLUE, print_countdown, 16, 0);
            else
                LCD_DrawString(80, 90, RED, BLUE, print_countdown, 16, 0);
            LCD_DrawString(80, 230, YELLOW, BLUE, print_score, 16, 0);
        }
        else if(gameMode == INITFREEMODE)
        {
            LCD_DrawString(80, 90, BLACK, GREEN, print_countdown, 16, 0);
            LCD_DrawString(80, 230, BLACK, GREEN, print_score, 16, 0);
        }
        else if(gameMode == INITHARDMODE)
        {
                   if (total_seconds_left > 10)
                       LCD_DrawString(80, 90, WHITE, RED, print_countdown, 16, 0);
                   else
                       LCD_DrawString(80, 90, BLACK, RED, print_countdown, 16, 0);
                   LCD_DrawString(80, 230, WHITE, RED, print_score, 16, 0);
        }
        // Loop and Shift Music According to Time Remaining
            // how to turn off one song?
            // how to blend songs together?
       /* if (total_seconds_left > 60) {
            asm("wfi");
            if (mp->nexttick == MAXTICKS)
                mp = midi_init(scale);
        } else if ((total_seconds_left == 60) && (!shift)) {
            mp = midi_init(tiger);
            shift = 1;
        } else {
            asm("wfi");
            if (mp->nexttick == MAXTICKS)
                //mp = midi_init(tiger);
                mp = midi_init(0);
        }*/
    }
    /*
     * struct {
    uint8_t in_use;
    uint8_t note;
    uint8_t chan;
    uint8_t volume;
    int     step;
    int     offset;
    int     last_sample;
}    voice[VOICES];
     */  //(int time, int chan, int key, int velo)

}

int main(void)
{
    enableTIM14();
    init_joys();
    start_joys();
    init_joys();
    start_joys();
    init_inv_kin();
    //nano_wait(1000000000); // joy
    pwm_gpio_init();
    init_break_beam();
    for(int id = 0; id < SERVO_CNT; id++ ) {
        servo_init(id);
    }
    char newStr[2];

    LCD_Setup(); // this will call init_lcd_spi()
    gameMode = INITMAINMENU;
    for(;;)
    {
        switch (gameMode)
        {
        case INITMAINMENU:
            enableTIM14();
            mainMenuCount = 9;
            drawMainMenu(optionSelected, mainMenuCount);
            gameMode = MAINMENU;
            break;
        case MAINMENU:
                if(updateMenu == 1)
                {
                    char converted[2];
                    sprintf(converted, "%d", mainMenuCount);
                    drawMainMenuNoBKGND(optionSelected,mainMenuCount);
                    LCD_DrawString(140, 280, YELLOW, BLUE, converted, 16, 0);//converted[0]
                    updateMenu = 0;
                }
                break;
        case GAMEINIT:
            setup_ports(); // sets up PC10 or other GPIO input (PIR rising edge)
            score = 0;
            total_seconds_left = (TOTAL_SECONDS_RESET_VALUE);
            game_logic(); // calculate time and increment score
            initialize_lcd_contents(); // display contents of LCD
            initialize_music(); // integrate music functions and components
            continuous_display_music();
            gameMode = GAME;
            break;
        case GAME:
                reset_voices();
                TIM6->CR1 &= ~TIM_CR1_CEN;
                TIM2->CR1 &= ~TIM_CR1_CEN;

                DAC->CR &= ~DAC_CR_EN1;
                RCC->APB1ENR &= ~RCC_APB1ENR_DACEN;
                gameMode = GAMEOVER;
                break;
        case GAMEOVER:
                drawGameOver();
                break;
        case INITLEADERBOARD:
                enableTIM14();
                mainMenuCount = 9;
                drawLeaderBoard(mainMenuCount);
                gameMode = LEADERBOARD;
                break;
        case LEADERBOARD:

            sprintf(newStr, "%d", mainMenuCount);
            LCD_DrawString(140, 280, YELLOW, BLUE, newStr, 16, 0);//converted[0]
            if(mainMenuCount == 0)
                gameMode = INITMAINMENU;
            break;

        case INITFREEMODE:
            setup_ports(); // sets up PC10 or other GPIO input (PIR rising edge)
                        score = 0;
                        total_seconds_left = (TOTAL_SECONDS_RESET_VALUE + 2*60);
                        game_logic(); // calculate time and increment score
                        initialize_lcd_contents(); // display contents of LCD
                        initialize_music(); // integrate music functions and components
                        continuous_display_music();
                        gameMode = FREEMODE;
            break;
        case FREEMODE:
            reset_voices();
            TIM6->CR1 &= ~TIM_CR1_CEN;
            TIM2->CR1 &= ~TIM_CR1_CEN;

            DAC->CR &= ~DAC_CR_EN1;
            RCC->APB1ENR &= ~RCC_APB1ENR_DACEN;
            gameMode = INITMAINMENU;

            break;
        case INITHARDMODE:
            setup_ports(); // sets up PC10 or other GPIO input (PIR rising edge)
                                   score = 0;
                                   total_seconds_left = (TOTAL_SECONDS_RESET_VALUE);
                                   game_logic(); // calculate time and increment score
                                   initialize_lcd_contents(); // display contents of LCD
                                   initialize_music(); // integrate music functions and components
                                   continuous_display_music();
                                   gameMode = HARDMODE;
            break;
        case HARDMODE:
            reset_voices();
                       TIM6->CR1 &= ~TIM_CR1_CEN;
                       TIM2->CR1 &= ~TIM_CR1_CEN;

                       DAC->CR &= ~DAC_CR_EN1;
                       RCC->APB1ENR &= ~RCC_APB1ENR_DACEN;
                       gameMode = GAMEOVER;
            break;
        default:
                gameMode = 0;
                break;

        };
    }
}

/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f0xx.h"
#include "lcd.h"

			
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
void drawMainMenu(int optionSelected)
{
    int selectModeAlignmentX = 70;
    int selectModeAlignmentY = 10;
    int menuOptionItr = 0;

    const char * words[NUM_OF_MENU_OPTIONS] = {"GAME", "Free Mode", "Play-back Mode", "Leader Board"};


    LCD_Clear(0);
    LCD_DrawFillRectangle(0, 0, 440, 440, BLUE);
    menuOptionItr = drawMenuOption("Select Mode. ", selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, YELLOW, BLUE, BLACK);
    for(int i = 0; i < NUM_OF_MENU_OPTIONS; i++)
    {
        if(i == optionSelected)
            menuOptionItr = drawMenuOption(words[i], selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, RED, RED, RED);
        else
            menuOptionItr = drawMenuOption(words[i], selectModeAlignmentX, selectModeAlignmentY, menuOptionItr, YELLOW, BLUE, BLACK);
    }
    LCD_DrawString(15, 300, YELLOW, BLUE, "2/8 to select, 5 to choose", 16, 1);
}


int main(void)
{
    enable_ports();
    LCD_Setup(); // this will call init_lcd_spi()
    drawMainMenu(0);
    
    

	for(;;);
}

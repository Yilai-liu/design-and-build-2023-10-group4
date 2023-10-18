#include "LCD1602.h"
#include "interface.h"
#include "stm32f10x.h"
#include <stdio.h>

// Global variable definitions
unsigned char const table1[] = "Distance: ";
unsigned char const table2[] = "Command:";

/*******************************************************************************
* Function Name: LcdBusy
* Function Description: Check the LCD busy status. When LcdBusy is 1, it's busy and waiting.
*                      When LcdBusy is 0, it's idle and can accept commands and data.
* Input: None
* Output: Status
*******************************************************************************/
//bit LcdBusy()
// {                          
//    bit result;
//    LCDRS_RESET;
//    LCDWR_SET;
//    LCDEN_SET;
//    Delay_us(1);
//    result = (bit)(P0&0x80);
//    LCDEN_RESET;
//    return(result); 
//}
 
/*******************************************************************************
* Function Name: LcdWriteCom
* Function Description: Write a command to the LCD1602
* Input: None
* Output: None
*******************************************************************************/
void LcdWriteCom(unsigned char com)
{
    //while(LcdBusy());
    Delay_us(20);
    LCDWRITE_DATA(com);
    LCDRS_RESET;
    LCDWR_RESET;
    LCDEN_RESET;
    Delay_us(10);
    LCDEN_SET;
    Delay_us(10);
    LCDEN_RESET;
    Delay_us(10);
}

/*******************************************************************************
* Function Name: LcdWriteDate
* Function Description: Write data to the LCD1602
* Input: None
* Output: None
*******************************************************************************/
void LcdWriteDate(unsigned char date)
{
    //while(LcdBusy());
    Delay_us(20);
    LCDWRITE_DATA(date);
    LCDRS_SET;
    LCDWR_RESET;
    LCDEN_RESET;
    Delay_us(10);
    LCDEN_SET;
    Delay_us(10);
    LCDEN_RESET;
    Delay_us(10);
}

void LCD1602PortInit()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = LCDRS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCDRS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCDWR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCDWR_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCDEN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCDEN_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_PORT;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_GPIO, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name: LCD1602Init
* Function Description: Initialize the LCD1602
* Input: None
* Output: None
*******************************************************************************/
void LCD1602Init()
{
    char index = 0;
    LCD1602PortInit();
    Delayms(100);
    LcdWriteCom(0x38);  // Set 16x2 display, 8-bit data interface
    LcdWriteCom(0x0c);  // Turn on display, show cursor, and blink
    LcdWriteCom(0x06);  // Automatically increment pointer after each write
    LcdWriteCom(0x01);  // Clear the screen
    Delayms(100);  // Delay for LCD1602 to stabilize

    LcdWriteCom(0x80);  // Set data address pointer for the first line
    for (index = 0; index < 10; index++)
    {
        LcdWriteDate(table1[index]);  // Write data             
    }

    LcdWriteCom(0xc0);  // Set data address pointer for the second line
    for (index = 0; index < 8; index++)
    {
        LcdWriteDate(table2[index]);  // Write data             
    }
}

/*******************************************************************************
* Function Name: LCD1602WriteCommand
* Function Description: Display a command on the screen (U - Up, D - Down, L - Left, R - Right, S - Stop)
* Input: comm - Character format
* Output: None
*******************************************************************************/
void LCD1602WriteCommand(char comm)
{
    LcdWriteCom(0xc0 + 9);
    LcdWriteDate(comm);  // Write data   
}

void LCD1602WriteDistance(unsigned int distance)
{
    char data_buf[4];
    int index = 0;

    data_buf[3] = 0;
    sprintf(data_buf, "%03d", (int)distance);
    LcdWriteCom(0x80 + 10);  // Set data address pointer for the first line
    for (index = 0; index < 3; index++)
    {
        LcdWriteDate(data_buf[index]);  // Write data             
    }
}


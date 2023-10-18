#include "LCD12864.h"
#include "charcode.h"
#include "interface.h"
#include <stdio.h>

unsigned char const table1[] = "Hantech MCU";
unsigned char const table2[] = "Command:";

// Delay n microseconds
void delay_nus(unsigned long n)
{
    unsigned long j;
    while (n--)
    {
        j = 8;
        while (j--);
    }
}

// GPIO configuration function
void LCDGPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = LCDCS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCDCS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCDRST_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCDRST_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCDRS_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCDRS_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCDSCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCDSCL_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCDSID_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LCDSID_GPIO, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name: LcdWriteCmd
* Function Description: Write a command to the LCD12864
* Input: cmd
* Output: None
*******************************************************************************/
void LcdWriteCmd(u8 cmd)
{
    char i;
    LCDCS_RESET;
    LCDRS_RESET;
    for (i = 0; i < 8; i++) {
        LCDSCL_RESET;
        if (cmd & 0x80) LCDSID_SET;  // Set data line
        else       LCDSID_RESET;
        LCDSCL_SET;  // Generate clock rising edge
        cmd <<= 1;
    }
    LCDCS_SET;
}

/*******************************************************************************
* Function Name: LcdWriteData
* Function Description: Write data to the LCD12864
* Input: dat
* Output: None
*******************************************************************************/
void LcdWriteData(u8 dat)
{
    char i;
    LCDCS_RESET;
    LCDRS_SET;
    for (i = 0; i < 8; i++) {
        LCDSCL_RESET;
        if (dat & 0x80) LCDSID_SET;  // Set data line
        else       LCDSID_RESET;
        LCDSCL_SET;  // Generate clock rising edge
        dat <<= 1;
    }
    LCDCS_SET;
}

/*******************************************************************************
* Function Name: LCD12864Init
* Function Description: Initialize the LCD12864
* Input: None
* Output: None
*******************************************************************************/
void LCD12864Init(void)
{
    const unsigned char con_d2 = 0x16; // Default fine-tuned contrast value, can be set in the range 0x00-0x3f

    LCDGPIO_Configuration();

    LCDRST_RESET;
    Delay_us(3000);  // Low-level reset
    LCDRST_SET;
    Delay_us(50);   // Reset completed

    LcdWriteCmd(0xe2);
    Delay_us(15);  // Software reset

    LcdWriteCmd(0x2c);
    Delay_us(15);  // Boost ON
    LcdWriteCmd(0x2e);
    Delay_us(15);  // Voltage Regular ON
    LcdWriteCmd(0x2f);
    Delay_us(15);  // Voltage Follower ON

    LcdWriteCmd(0x24);  // Coarse contrast adjustment, can be set in the range 0x20-0x27
    LcdWriteCmd(0x81);  // Fine contrast adjustment, following line should immediately follow
    LcdWriteCmd(con_d2);  // 0x1a, fine contrast adjustment value, can be set in the range 0x00-0x3f

    LcdWriteCmd(0xa2);  // 1/9 bias set
    LcdWriteCmd(0xc8);  // Row scan sequence: 0xc8 from top to bottom, 0xc0 from bottom to top
    LcdWriteCmd(0xa0);  // Column scan sequence: 0xa0 from left to right, 0xa1 from right to left

    LcdWriteCmd(0x40);  // Starting row: start from the first row
    LcdWriteCmd(0xaf);  // Turn on the display

    LcdClearScreen();
    LcdWriteString(0, 0, "Hantech MCU");
    ShowEnString(0, 2, "Command:");
    ShowEnString(0, 4, "Left:    cm/s");
    ShowEnString(0, 6, "Right:   cm/s");
    LCD12864WriteCommand(' ');
}

/*******************************************************************************
* Function Name: LcdClearScreen
* Function Description: Clear the LCD12864 screen
* Input: None
* Output: None
*******************************************************************************/
void LcdClearScreen(void)
{
    unsigned char i, j;

    for (i = 0; i < 8; i++) {
        LcdWriteCmd(0xB0 + i);  // Y-axis address

        // After writing data, the X-coordinate will automatically increment, but we initialize it with 0x00
        // The X-axis coordinates start at 0x10, 0x00
        LcdWriteCmd(0x10);
        LcdWriteCmd(0x00);

        // X has 128 bits, so a total of 128 cycles, the X-coordinate will automatically increment, so we don't need to set the coordinate again
        for (j = 0; j < 128; j++) {
            LcdWriteData(0x00);
        }
    }
}

/*******************************************************************************
* Function Name: LcdWriteString
* Function Description: Write 16x16 Chinese characters on the LCD12864
* Input: x, y, cn
* Output: None
* Explanation: This function can directly write strings
*******************************************************************************/
unsigned char LcdWriteString(unsigned char x, unsigned char y, unsigned char *cn)
{
    unsigned char j, x1, x2, wordNum;
    y = y * 2;

    // Y's coordinate can range from 0 to 7, return if greater
    if (y > 7) {
        return 0;
    }

    // X's coordinate can range from 0 to 128, return if greater
    if (x > 128) {
        return 0;
    }

    y += 0xB0;
    LcdWriteCmd(y);
    while (*cn != '\0') {
        LcdWriteCmd(y);

        x


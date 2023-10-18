#include "uart.h"
#include "interface.h"

// UART function
// UART1 TxD GPIOA9 RxD GPIOA10
void USART3Conf(uint32_t baudRate)
{
    USART_InitTypeDef USART_InitStruct; // Define the USART1 initialization structure

    GPIO_InitTypeDef GPIO_InitStruct; // Define the GPIO pins structure for the USART

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); // Enable the clock for USART1 and GPIOA

    // USART1_Tx_Pin Configure
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9; // Output pin
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz; // Set maximum speed to 2MHz
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // Push-pull output mode with alternate function
    GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize the GPIO pin

    // USART1_Rx_Pin Configure
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // GPIO input mode with floating input
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10; // Input pin
    GPIO_Init(GPIOA, &GPIO_InitStruct); // Initialize the GPIO pin

    // USART1 Configure
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); // Enable USART1 clock
    USART_InitStruct.USART_BaudRate = baudRate; // Baud rate 19200
    USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 8-bit data
    USART_InitStruct.USART_StopBits = USART_StopBits_1; // 1 stop bit
    USART_InitStruct.USART_Parity = USART_Parity_No; // No parity
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // Enable both transmission and reception
    USART_Init(USART1, &USART_InitStruct); // Initialize USART1
    // USART1_INT Configure
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // Enable receive interrupt
    // USART_ITConfig(USART1 , USART_IT_TXE , ENABLE);
    USART_Cmd(USART1, ENABLE); // Enable USART
    USART_ClearFlag(USART1, USART_FLAG_TC); // Clear the transmission complete flag to resolve the first data send failure issue
}

void PutChar(uint8_t Data)
{
    USART_SendData(USART1, Data);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); // Wait for transmission to complete
}

void PutStr(char *str) // Send a string
{
    while (*str != '\0')
    {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); // Wait for transmission to complete
    }
}

void PutNChar(uint8_t *buf, uint16_t size)
{
    uint8_t i;
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); // Prevent the loss of the first byte
    for (i = 0; i < size; i++)
    {
        USART_SendData(USART1, buf[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); // Wait for transmission to complete
    }
}


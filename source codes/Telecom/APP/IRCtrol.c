#include "IRCtrol.h"
#include "interface.h"

unsigned char ir_rec_flag = 0; // Receive data flag, 1 for new data, 0 for none
unsigned char IRCOM[4];

// Use Timer3 for delay (systick is already in use in the main function and cannot be reused in interrupts)
void Time3Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 1;
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1); // 72M / 72 = 1us
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

// 1us delay
void DelayUs(vu32 nCount)
{
    u16 TIMCounter = nCount;
    TIM_Cmd(TIM3, ENABLE);
    TIM_SetCounter(TIM3, TIMCounter);
    while (TIMCounter > 1)
    {
        TIMCounter = TIM_GetCounter(TIM3);
    }
    TIM_Cmd(TIM3, DISABLE);
}

// External interrupt configuration for infrared remote control
void IRCtrolInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure; // External interrupt structure
    NVIC_InitTypeDef NVIC_InitStructure; // Interrupt structure

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);

    GPIO_InitStructure.GPIO_Pin = IRIN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IRIN_GPIO , &GPIO_InitStructure);

    GPIO_EXTILineConfig(IRIN_PORTSOURCE , IRIN_PINSOURCE);

    EXTI_InitStructure.EXTI_Line = IRIN_EXITLINE;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = IRIN_IRQCH;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    Time3Init();
}

// Delay function for 0.14ms
void DelayIr(unsigned char x)
{
    while(x--)
    {
        DelayUs(140);
    }
}

void IRIntIsr(void)
{
    unsigned char j, k, N = 0;
    DelayIr(15);
    if (IRIN == 1)
    {
        return;
    }
    continue_time = 40; // Continuous transmission signal, indicating that the command lasts for 40*5 = 200ms, no command stops
    // Confirm IR signal appearance
    while (!IRIN) // Wait for IR to go high, skipping the 9ms leading low-level signal.
    {
        DelayIr(1);
    }

    for (j = 0; j < 4; j++) // Collect four sets of data
    {
        for (k = 0; k < 8; k++) // Each set of data has 8 bits
        {
            while (IRIN) // Wait for IR to go low, skipping the 4.5ms leading high-level signal.
            {
                DelayIr(1);
            }
            while (!IRIN) // Wait for IR to go high
            {
                DelayIr(1);
            }
            while (IRIN) // Calculate the duration of the IR high level
            {
                DelayIr(1);
                N++;
                if (N >= 30)
                {
                    return; // The 0.14ms count is too long, automatically exit.
                }
            } // High level count complete
            IRCOM[j] = IRCOM[j] >> 1; // Fill the highest bit with "0"
            if (N >= 8)
            {
                IRCOM[j] = IRCOM[j] | 0x80; // Fill the highest bit with "1"
            }
            N = 0;
        } // end for k
    } // end for j

    k = ~IRCOM[3];
    if (IRCOM[2] != k)
    {
        return;
    }

    // Command conversion
    switch (IRCOM[2])
    {
        case 0x46: ctrl_comm = COMM_UP; break;
        case 0x15: ctrl_comm = COMM_DOWN; break;
        case 0x44: ctrl_comm = COMM_LEFT; break;
        case 0x43: ctrl_comm = COMM_RIGHT; break;
        case 0x40: ctrl_comm = COMM_STOP; break;
        default:

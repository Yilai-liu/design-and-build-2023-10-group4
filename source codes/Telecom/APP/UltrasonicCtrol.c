#include "UltrasonicCtrol.h"
#include "interface.h"
#include "stm32f10x.h"

volatile unsigned char status = 0; // Current program status: 0 for idle, 1 for sending trigger signal, 2 for waiting for signal return, 3 for ...
unsigned int dis_count = 0;        // Pulse width duration measurement
volatile unsigned int distance_cm = 0; // Current distance in centimeters
unsigned char t2_full_count = 0;       // Counter for times the timer is filled up
static unsigned int ultick_5ms = 0;    // 5ms counter

void Time4Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1); // 72M / 72 = 1us
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

// External interrupt configuration for ultrasonic sensor (not used in the code)
void UltraSoundInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure; // Define a structure for external interrupts
    NVIC_InitTypeDef NVIC_InitStructure; // Define an interrupt structure

    GPIO_InitStructure.GPIO_Pin = Echo_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Echo_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = Trig_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(Trig_GPIO, &GPIO_InitStructure);

    GPIO_EXTILineConfig(Echo_PORTSOURCE, Echo_PINSOURCE);
    EXTI_InitStructure.EXTI_Line = Echo_EXITLINE;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel = Echo_IRQCH;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    Time4Init();
    Trig_RESET;
}

void Distance(void)
{
    ultick_5ms++;
    if (ultick_5ms >= 15)
    {
        ultick_5ms = 0;
        GetDistanceDelay();
    }
}

// Reading distance value using a delay
void GetDistanceDelay(void)
{
    // Send a trigger signal
    Trig_SET;
    status = 1;
    TIM_SetCounter(TIM4, 0);
    TIM_Cmd(TIM4, ENABLE);

    while (TIM_GetCounter(TIM4) < 11); // Wait for a delay of more than 10us
    status = 2;
    Trig_RESET;
    TIM_SetCounter(TIM4, 0);

    while (Echo == 0) // Wait for the return signal to start
    {
        if (TIM_GetCounter(TIM4) > 60000) // Response time exceeds the normal range
        {
            status = 0;
            distance_cm = 0; // Move backward in case of failure
            TIM_Cmd(TIM4, DISABLE); // Turn off the timer
            return; // This attempt failed
        }
    }

    TIM_SetCounter(TIM4, 0);
    while (Echo == 1) // Start measuring length
    {
        int count = TIM_GetCounter(TIM4);
        if (count > 60000) // Response time exceeds the normal range
        {
            status = 0;
            distance_cm = 0; // Move backward in case of failure
            TIM_Cmd(TIM4, DISABLE); // Turn off the timer
            return; // This attempt failed
        }
    }

    dis_count = TIM_GetCounter(TIM4);
    TIM_Cmd(TIM4, DISABLE); // Turn off the timer
    distance_cm = (unsigned int)(((long)(dis_count)*34) / 2000); // Speed of sound is 340 m/s
    status = 0; // Ready for the next transmission
}


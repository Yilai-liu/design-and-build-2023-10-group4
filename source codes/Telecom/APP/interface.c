#include "interface.h"

void UserLEDInit(void) // Function to light up the PB0 LED
{
  GPIO_InitTypeDef  GPIO_InitStructure; // Define a structure variable

  GPIO_InitStructure.GPIO_Pin = LED_PIN; // Select the IO port you want to configure
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // Set push-pull output mode
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Configure GPIO port speed
  GPIO_Init(LED_GPIO, &GPIO_InitStructure); // Initialize GPIO

  LED_SET; // High level turns off the LED
}

void delay_init(void)
{
   SysTick->CTRL &= 0xfffffffb; // Control register, select external clock, which is one-eighth of the system clock (HCLK/8; 72M/8 = 9M)
}

// 1us delay function
void Delay_us(u32 Nus)
{
  SysTick->LOAD = Nus * 9; // Time load at 72M main frequency
  SysTick->CTRL |= 0x01; // Start the countdown
  while (!(SysTick->CTRL & (1 << 16))); // Wait for the time to reach
  SysTick->CTRL = 0X00000000; // Turn off the counter
  SysTick->VAL = 0X00000000; // Clear the counter
}

void Delayms(u32 Nms)
{
  while (Nms--)
  {
    Delay_us(1000);
  }
}

// Enable all GPIO clocks
void GPIOCLKInit(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
}

// Infrared phototransistor initialization
void RedRayInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = SEARCH_M_PIN; // Configure enable GPIO pin
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Configure GPIO mode, input pull-up
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Configure GPIO port speed
  GPIO_Init(SEARCH_M_GPIO, &GPIO_InitStructure);

  // Repeat similar configurations for other pins

}

void ServoInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = Servo_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Configure GPIO port speed
  GPIO_Init(Servo_GPIO, &GPIO_InitStructure);

  Servo_SET; // Default to high level
}

/**
  * @function NVIC_TIM5Configuration
  * @brief Configure TIM5 interrupt vector parameters
  * @param None
  * @return None
**/
static void NVIC_TIM2Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);
}

void TIM2_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* Time base configuration */
  // This is the auto-reload count value, and the period is 100us
  TIM_TimeBaseStructure.TIM_Period = (100 - 1); // 10kHz
  // This is the prescaler factor, subtract 1 when dividing by 0 to indicate no prescaling
  TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1); // 1MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Clear TIM2 update pending flag */
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

  /* TIM IT enable */ // Enable overflow interrupt
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);

  /* Interrupt parameter configuration */
  NVIC_TIM2Configuration();
}

void LEDToggle(uint16_t Led)
{
  /* XOR 1 with the specified pin to toggle the corresponding LED indicator state */
  LED_GPIO->ODR ^= Led;
}

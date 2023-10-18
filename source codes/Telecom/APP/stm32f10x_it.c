/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides a template for all exception handlers and 
  *          peripheral interrupt service routines.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "interface.h"
#include "IRCtrol.h"
#include "motor.h"

/**
  * @brief   This function handles the NMI (Non-Maskable Interrupt) exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles the Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go into an infinite loop when a Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles the Memory Management exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go into an infinite loop when a Memory Management exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles the Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go into an infinite loop when a Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles the Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go into an infinite loop when a Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles the SVCall (System Service Call) exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles the Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles the PendSVC (Pendable Service Call) exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles the SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/**
  * @brief  This function handles external interrupts on lines 10 to 15 (EXTI15_10).
  */
void EXTI15_10_IRQHandler()
{
	if (EXTI_GetITStatus(IRIN_EXITLINE) != RESET) // Infrared interrupt
	{
		EXTI_ClearITPendingBit(IRIN_EXITLINE); // Clear the interrupt flag
		IRIntIsr();
	}

	// Add other external interrupt handling here if needed
}

/**
  * @brief  This function handles the TIM2 (Timer 2) interrupt.
  */
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		tick_1ms++;
		if (tick_1ms >= 10)
		{


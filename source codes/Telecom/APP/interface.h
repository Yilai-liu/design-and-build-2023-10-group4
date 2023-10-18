#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#include "stm32f10x.h"
// User LED PB0 IO configuration
#define LED_PIN         GPIO_Pin_0
#define LED_GPIO        GPIOB
#define LED_SET         GPIO_SetBits(LED_GPIO , LED_PIN)  // High level
#define LED_RESET       GPIO_ResetBits(LED_GPIO , LED_PIN) // Low level

// Infrared remote control, infrared receiver data line, external interrupt PD10
#define IRIN_PIN         GPIO_Pin_10
#define IRIN_GPIO        GPIOD
#define IRIN_PORTSOURCE  GPIO_PortSourceGPIOD
#define IRIN_PINSOURCE   GPIO_PinSource10
#define IRIN_EXITLINE    EXTI_Line10
#define IRIN_IRQCH       EXTI15_10_IRQn
#define IRIN             GPIO_ReadInputDataBit(IRIN_GPIO, IRIN_PIN)

// Ultrasonic control, external interrupt return PB14
#define Echo_PIN         GPIO_Pin_14
#define Echo_GPIO        GPIOB
#define Echo_PORTSOURCE  GPIO_PortSourceGPIOB
#define Echo_PINSOURCE   GPIO_PinSource14
#define Echo_EXITLINE    EXTI_Line14
#define Echo_IRQCH       EXTI15_10_IRQn
#define Echo             GPIO_ReadInputDataBit(Echo_GPIO, Echo_PIN)
// Trigger IO PD8
#define Trig_PIN         GPIO_Pin_8
#define Trig_GPIO        GPIOD
#define Trig_RESET       GPIO_SetBits(Trig_GPIO , Trig_PIN)
#define Trig_SET         GPIO_ResetBits(Trig_GPIO , Trig_PIN) // Inverted from 5V to 3.3V, modified by LC 2015.09.20 10:18

// Servo control IO PA0
#define Servo_PIN         GPIO_Pin_0
#define Servo_GPIO        GPIOA
#define Servo_SET         GPIO_SetBits(Servo_GPIO , Servo_PIN)
#define Servo_RESET       GPIO_ResetBits(Servo_GPIO , Servo_PIN)

// LCD1602 IO
// LCDRS PC13
#define LCDRS_PIN         GPIO_Pin_13
#define LCDRS_GPIO        GPIOC
#define LCDRS_SET         GPIO_SetBits(LCDRS_GPIO , LCDRS_PIN)
#define LCDRS_RESET       GPIO_ResetBits(LCDRS_GPIO , LCDRS_PIN)

// LCDWR PC14
#define LCDWR_PIN         GPIO_Pin_14
#define LCDWR_GPIO        GPIOC
#define LCDWR_SET         GPIO_SetBits(LCDWR_GPIO , LCDWR_PIN)
#define LCDWR_RESET       GPIO_ResetBits(LCDWR_GPIO , LCDWR_PIN)

// LCDEN PC15
#define LCDEN_PIN         GPIO_Pin_15
#define LCDEN_GPIO        GPIOC
#define LCDEN_SET         GPIO_SetBits(LCDEN_GPIO , LCDEN_PIN)
#define LCDEN_RESET       GPIO_ResetBits(LCDEN_GPIO , LCDEN_PIN)

// LCDPORT PF0-PF7
#define LCD_PORT        0x00ff
#define LCD_GPIO        GPIOF
#define LCDWRITE_DATA(data)   LCD_GPIO->BSRR = 0x00ff0000; LCD_GPIO->BSRR = (data)

// 4-wheel small car motor drive IO definition Left front and rear parallel, right front and rear parallel, L left, R right
/* 
EN1 PD4
EN2 PD2
IN1 PC11
IN2 PD0
IN3 PD6
IN4 PG9
EN1=1 EN2=1 High level

IN1=1 IN2=0 Left reverse
IN1=0 IN2=1 Left forward

IN3=1 IN4=1 Right reverse
IN3=0 IN4=1 Right forward

Note: The left and right sides can be determined by the motor wiring. If it does not match the actual situation, you can adjust the position of the wiring for the 4 motors accordingly.

The following is for reference
FRONT_LEFT_F_PIN	PG13	Left front forward IO //Not used
FRONT_LEFT_B_PIN	PG11	Left front reverse IO //Not used

FRONT_RIGHT_F_PIN	PC11	Right front forward IO IN1 New definition of left front forward control
FRONT_RIGHT_B_PIN	PD0	  Right front reverse IO IN2 New definition of left front forward control

BEHIND_LEFT_F_PIN	PD6	    Left rear forward IO IN3 New definition of right
BEHIND_LEFT_B_PIN	PG9	    Left rear reverse IO IN4 New definition of reverse control

The two control IOs of the right rear motor have been changed to two enable EN1 and EN2, and the high level is effective
BEHIND_RIGHT_F_PIN	PD4	    Right motor enable IO EN1
BEHIND_RIGHT_B_PIN	PD2	    Left motor enable IO EN2
 */
 
// Not used, reserved
#define FRONT_LEFT_F_PIN         GPIO_Pin_13
#define FRONT_LEFT_F_GPIO        GPIOG
#define FRONT_LEFT_F_SET         GPIO_SetBits(FRONT_LEFT_F_GPIO , FRONT_LEFT_F_PIN)
#define FRONT_LEFT_F_RESET       GPIO_ResetBits(FRONT_LEFT_F_GPIO , FRONT_LEFT_F_PIN)
// Not used, reserved
#define FRONT_LEFT_B_PIN         GPIO_Pin_11
#define FRONT_LEFT_B_GPIO        GPIOG
#define FRONT_LEFT_B_SET         GPIO_SetBits(FRONT_LEFT_B_GPIO , FRONT_LEFT_B_PIN)
#define FRONT_LEFT_B_RESET       GPIO_ResetBits(FRONT_LEFT_B_GPIO , FRONT_LEFT_B_PIN)

// IN1 PC11 IO definition
#define FRONT_RIGHT_F_PIN         GPIO_Pin_11
#define FRONT_RIGHT_F_GPIO        GPIOC
#define FRONT_RIGHT_F_SET         GPIO_SetBits(FRONT_RIGHT_F_GPIO , FRONT_RIGHT_F_PIN) // High level
#define FRONT_RIGHT_F_RESET       GPIO_ResetBits(FRONT_RIGHT_F_GPIO , FRONT_RIGHT_F_PIN) // Low level
// IN2 PD0 IO definition
#define FRONT_RIGHT_B_PIN         GPIO_Pin_0
#define FRONT_RIGHT_B_GPIO        GPIOD
#define FRONT_RIGHT_B_SET         GPIO_SetBits(FRONT_RIGHT_B_GPIO , FRONT_RIGHT_B_PIN) // High level
#define FRONT_RIGHT_B_RESET       GPIO_ResetBits(FRONT_RIGHT_B_GPIO , FRONT_RIGHT_B_PIN) // Low level
// IN3 PD6 IO definition
#define BEHIND_LEFT_F_PIN         GPIO_Pin_6
#define BEHIND_LEFT_F_GPIO        GPIOD
#define BEHIND_LEFT_F_SET         GPIO_SetBits(BEHIND_LEFT_F_GPIO , BEHIND_LEFT_F_PIN) // High level
#define BEHIND_LEFT_F_RESET       GPIO_ResetBits(BEHIND_LEFT_F_GPIO , BEHIND_LEFT_F_PIN) // Low level
// IN4 PG9 IO definition
#define BEHIND_LEFT_B_PIN         GPIO_Pin_9
#define BEHIND_LEFT_B_GPIO        GPIOG
#define BEHIND_LEFT_B_SET         GPIO_SetBits(BEHIND_LEFT_B_GPIO , BEHIND_LEFT_B_PIN) // High level
#define BEHIND_LEFT_B_RESET       GPIO_ResetBits(BEHIND_LEFT_B_GPIO , BEHIND_LEFT_B_PIN) // Low level
// EN1 PD4
#define BEHIND_RIGHT_F_PIN         GPIO_Pin_4
#define BEHIND_RIGHT_F_GPIO        GPIOD
#define BEHIND_RIGHT_F_SET         GPIO_SetBits(BEHIND_RIGHT_F_GPIO , BEHIND_RIGHT_F_PIN)
#define BEHIND

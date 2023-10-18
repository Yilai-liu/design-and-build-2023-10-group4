#include "motor.h"
#include "interface.h"
#include "stm32f10x.h"

// GPIO configuration function
void MotorGPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_F_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(FRONT_LEFT_F_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_B_PIN;
    GPIO_Init(FRONT_LEFT_B_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_F_PIN;
    GPIO_Init(FRONT_RIGHT_F_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_B_PIN;
    GPIO_Init(FRONT_RIGHT_B_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_F_PIN;
    GPIO_Init(BEHIND_LEFT_F_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_B_PIN;
    GPIO_Init(BEHIND_LEFT_B_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_F_PIN;
    GPIO_Init(BEHIND_RIGHT_F_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_B_PIN;
    GPIO_Init(BEHIND_RIGHT_B_GPIO, &GPIO_InitStructure);
}

// Drive the motor to move based on the duty cycle
void CarMove(void)
{
    BEHIND_RIGHT_EN;

    // Right wheel
    if (front_right_speed_duty > 0)  // Forward
    {
        if (speed_count < front_right_speed_duty)
        {
            FRONT_RIGHT_GO;
        }
        else  // Stop
        {
            FRONT_RIGHT_STOP;
        }
    }
    else if (front_right_speed_duty < 0)  // Backward
    {
        if (speed_count < (-1) * front_right_speed_duty)
        {
            FRONT_RIGHT_BACK;
        }
        else  // Stop
        {
            FRONT_RIGHT_STOP;
        }
    }
    else  // Stop
    {
        FRONT_RIGHT_STOP;
    }

    // Left wheel
    if (behind_left_speed_duty > 0)  // Forward
    {
        if (speed_count < behind_left_speed_duty)
        {
            BEHIND_LEFT_GO;
        }
        else  // Stop
        {
            BEHIND_LEFT_STOP;
        }
    }
    else if (behind_left_speed_duty < 0)  // Backward
    {
        if (speed_count < (-1) * behind_left_speed_duty)
        {
            BEHIND_LEFT_BACK;
        }
        else  // Stop
        {
            BEHIND_LEFT_STOP;
        }
    }
    else  // Stop
    {
        BEHIND_LEFT_STOP;
    }
}

// Move forward
void CarGo(void)
{
    front_right_speed_duty = 30;  // Right forward
    behind_left_speed_duty = 30;  // Left forward
}

// Move backward
void CarBack(void)
{
    front_right_speed_duty = -SPEED_DUTY;  // Right backward
    behind_left_speed_duty = -SPEED_DUTY;  // Left backward
}

// Move left
void CarLeft(void)
{
    front_right_speed_duty = SPEED_DUTY + 10;  // Right forward
    behind_left_speed_duty = -20;  // Left backward
}

// Move right
void CarRight(void)
{
    front_right_speed_duty = -20;  // Right backward
    behind_left_speed_duty = SPEED_DUTY + 10;  // Increase rear-wheel driving force, left forward
}

// Stop
void CarStop(void)
{
    front_right_speed_duty = 0;
    behind_left_speed_duty = 0;
}

void MotorInit(void)
{
    MotorGPIO_Configuration();
    CarStop();
}


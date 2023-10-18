// Connection method: Please refer to the interface.h file
// Some source code is from the internet - please delete after 24 hours

#include "stm32f10x.h"
#include "interface.h"
#include "LCD1602.h"
#include "IRCtrol.h"
#include "motor.h"
#include "UltrasonicCtrol.h"
#include "redvoid.h"
#include "uart.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_it.h"

// Global variable definitions
unsigned int speed_count = 0; // Duty cycle counter (50 times per cycle)
// char front_left_speed_duty = SPEED_DUTY;
char front_right_speed_duty = SPEED_DUTY;
char behind_left_speed_duty = SPEED_DUTY;
// char behind_right_speed_duty = SPEED_DUTY;

unsigned char tick_5ms = 0; // 5ms counter, as the basic period of the main function
unsigned char tick_1ms = 0; // 1ms counter, as the basic counter for the motors
unsigned char tick_200ms = 0; // Refresh display

char ctrl_comm = COMM_STOP; // Control command
char ctrl_comm_last = COMM_STOP; // Last command
unsigned char continue_time = 0;
unsigned char bt_rec_flag = 0; // Bluetooth control flag

int main(void)
{
    delay_init();
    GPIOCLKInit();
    UserLEDInit();
    LCD1602Init();
    // IRCtrolInit();
    TIM2_Init();
    MotorInit();
    // UltraSoundInit();
    RedRayInit();
    ServoInit();
    USART3Conf(9600);

    while (1)
    {
        if (tick_5ms >= 5)
        {
            tick_5ms = 0;
            tick_200ms++;
            if (tick_200ms >= 40)
            {
                tick_200ms = 0;
                LEDToggle(LED_PIN);
            }

            VoidRun();
        }
    }
}


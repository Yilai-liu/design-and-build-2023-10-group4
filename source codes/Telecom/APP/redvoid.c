#include "redvoid.h"
#include "interface.h"
#include "motor.h"

extern char ctrl_comm;

// Get the status of the infrared obstacle avoidance module
char GetVoidStatus(void)
{
    char left = 0, right = 0;
    char count;
    if (VOID_L_IO == BARRIER_Y)
    {
        count = 2;
        while (--count)  // Collect information about front obstacles twice with a 10ms interval
        {
            if (VOID_L_IO == BARRIER_N)
                break;
            Delayms(1);
        }
        if (count == 0)
            left = 1;
    }

    if (VOID_R_IO == BARRIER_Y)
    {
        count = 2;
        while (--count)  // Collect information about front obstacles twice with a 10ms interval
        {
            if (VOID_R_IO == BARRIER_N)
                break;
            Delayms(1);
        }
        if (count == 0)
            right = 2;
    }

    return left + right;
}

// Delay while checking infrared; stop and exit the delay if an obstacle occurs
void DelayCheck(int ms)
{
    while (ms--)
    {
        Delayms(1);
        if (VOID_NONE != GetVoidStatus())
        {
            CarStop();
            return;
        }
    }
}

// Infrared obstacle avoidance processing
// Handling method:
// - Left obstacle: Reverse for 500ms, then turn right for 500ms
// - Right obstacle: Reverse for 500ms, then turn left for 500ms
// - Obstacles on both sides: Stop for 700ms, then turn right for 500ms
// - No obstacles: Move forward
void VoidRun(void)
{
    char status;
    status = GetVoidStatus();

    switch (status)
    {
        case VOID_LEFT:
            ctrl_comm = COMM_RIGHT;
            CarBack();
            Delayms(100);
            CarStop();
            Delayms(300);
            CarRight();
            Delayms(350);
            break;
        case VOID_RIGHT:
            ctrl_comm = COMM_LEFT;
            CarBack();
            Delayms(100);
            CarStop();
            Delayms(300);
            CarLeft();
            Delayms(350);
            break;
        case VOID_BOTH:
            ctrl_comm = COMM_RIGHT;
            CarStop();
            Delayms(300);
            CarRight();
            Delayms(1000);
            break;
        case VOID_NONE:
            ctrl_comm = COMM_UP;
            CarGo();
            break;
        default:
            break;
    }
}
 

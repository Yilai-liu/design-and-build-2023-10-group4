#ifndef __ULTRASONICCTROL_H_
#define __ULTRASONICCTROL_H_
#include "stm32f10x.h"

extern volatile unsigned int distance_cm;
void UltraSoundInit(void);
void GetDistanceDelay(void);
void Distance(void);
void LCD12864WriteDistance(unsigned int distance);
#endif

#ifndef __IRCTROL_H_
#define __IRCTROL_H_

#include "stm32f10x.h"

extern unsigned char ir_rec_flag; // Receive data flag, 1 for new data, 0 for none
extern char ctrl_comm; // Control command
extern unsigned char continue_time;

void IRCtrolInit(void);
void IRIntIsr(void);

#endif

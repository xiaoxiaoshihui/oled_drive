#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f10x.h"

void delay(uint16_t time);    // delay(1000)—”≥Ÿ“ª√Î
void initSysTick(void);
void delay_us(u32 xus);
void delay_ms(u32 xms);



#endif




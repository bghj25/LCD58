#ifndef IT_CONFIG_H
#define IT_CONFIG_H
#include "init.h"

volatile static uint32_t	delay_dec = 0; // ?????????? ?????????? delay_dec

void SysTick_Handler(void);
void delay_ms(uint32_t delay_ms);
void SysTickInit(void);
#endif

#include "it_config.h"

void SysTickInit(void)
{
	SysTick->LOAD |= (16000)-1;
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Pos;
	SysTick->CTRL |= SysTick_CTRL_COUNTFLAG_Pos;
	SysTick->CTRL |= ~SysTick_CTRL_ENABLE_Pos;
}



void SysTick_Handler(void)
{
	if (delay_dec !=0)
			delay_dec--;
}

void delay_ms(uint32_t delay_ms)
{
	  delay_dec = delay_ms;//????????? delay_dec ???????? delay_ms
		
		while (delay_dec)
		{
					
		}; // ????????? ??????? ???? delay_dec ?? ?????? ?????? 0
}

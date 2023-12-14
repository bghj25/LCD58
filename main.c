#include "init.h"

int main(void)
{
	Init();
	char str[] = "Ento комарик";
	PrintLine(str, 1, first_line);
	uint8_t picture[8] = {0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x0E, 0x1F, 0x1F};
	AddCustomChar(0, picture); 
	PrintTableChar(secnond_line, 5, 0, 0x0);
	/*
	01110
	01110
	01110
	01110
	01110
	01110
	11111
	11111
	*/
	
	while(1)
	{
		
	}
}

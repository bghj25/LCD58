#include "init.h"

int main(void)
{
	Init();
	PrintTableChar(first_line, 2, 0, 'b');
	char str[] = "Ento  ŒÃ¿–";
	uint8_t len = sizeof(str)/sizeof(char);
	PrintLine(str, 1, first_line, sizeof(str)/sizeof(char) - 1);
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

#include "init.h"
#include "it_config.h"


void LCD(uint8_t val, uint8_t cmd)
{
	BitAction data;
	PORT_WriteBit(MDR_PORTF, LCD_A0, (BitAction)cmd);
	// set RS (A0) = cmd; cmd = 0 -> Command, cmd = 1 -> Data
	data = (BitAction)(val & 0x01);
	PORT_WriteBit(LCD_DB0_PORT, LCD_DB0, data);
	data = (BitAction)((val >> 1) & 0x01);
	PORT_WriteBit(LCD_DB1_PORT, LCD_DB1, data);
	data = (BitAction)((val >> 2) & 0x01);
	PORT_WriteBit(LCD_DB2_PORT, LCD_DB2, data);
	data = (BitAction)((val >> 3) & 0x01);
	PORT_WriteBit(LCD_DB3_PORT, LCD_DB3, data);
	data = (BitAction)((val >> 4) & 0x01);
	PORT_WriteBit(LCD_DB4_PORT, LCD_DB4, data);
	data = (BitAction)((val >> 5) & 0x01);
	PORT_WriteBit(LCD_DB5_PORT, LCD_DB5, data);
	data = (BitAction)((val >> 6) & 0x01);
	PORT_WriteBit(LCD_DB6_PORT, LCD_DB6, data);
	data = (BitAction)((val >> 7) & 0x01);
	PORT_WriteBit(LCD_DB7_PORT, LCD_DB7, data);
	E_SET;
	delay_ms(5);
	E_RESET;
}


void Init(void)
{
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
	
	PORT_InitTypeDef PORT_InitStruct;

	PORT_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_InitStruct.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStruct.PORT_OE = PORT_OE_OUT;
	PORT_InitStruct.PORT_Pin = LCD_DB0 + LCD_DB1 + LCD_DB2;  // Aiaaauoa a?oaea ieiu, anee iaiaoiaeii
	PORT_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORT_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;

	PORT_Init(MDR_PORTA, &PORT_InitStruct);
	
	PORT_InitStruct.PORT_Pin = LCD_DB3 + LCD_DB4 + LCD_DB5 + LCD_DB6 + LCD_DB7;
	PORT_Init(MDR_PORTB, &PORT_InitStruct);
	
	PORT_InitStruct.PORT_Pin = PORT_Pin_1 + PORT_Pin_3 + LCD_A0;
	PORT_Init(MDR_PORTF, &PORT_InitStruct);
	
	PORT_InitStruct.PORT_Pin = PORT_Pin_1 + PORT_Pin_0;
	PORT_Init(MDR_PORTC, &PORT_InitStruct);
	
	PSB_SET;
	RW_RESET;
	delay_ms(10);
	XRES_RESET;
	delay_ms(40);
	XRES_SET; //
	delay_ms(40);
	LCD((uint8_t)0x0E, 0x0); //D = 1; C = 1; P = 0
	LCD(0x06, 0); //Сдвиг курсора вправо
	LCD(0x00, 0); 
			
}


void PrintTableChar(display_line line, uint8_t pos, uint8_t page, char sym)
{
	if(line == secnond_line)
		pos += 0x40;
	if(page == 0)
		LCD(0x0E, 0);
	else
		LCD(0x0F, 1);
	LCD(128 + pos, 0);
	LCD(sym, 1);
}


void PrintLine(char* str, uint8_t start_pos, display_line line)
{
	unsigned char mask[] = {65, 189, 66, 190, 191, 69, 192, 193, 194, 195, 196, 197, 77, 
        72, 79, 134, 80, 67, 84, 199, 200, 88, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210}; 
	uint8_t len = sizeof(str)/sizeof(char) - 1;
	uint8_t i;
	char translit;
	for(i = 0; i < len; i++)
	{
		if(str[i] < 128)
		{
			PrintTableChar(line, start_pos + i, 0, str[i]);
		}
		else
		{
			translit = mask[str[i] - 192];
			if(translit < 128)
				PrintTableChar(line, start_pos + i, 0, translit);
			else
				PrintTableChar(line, start_pos + i, 1, translit);
		}
	}
}	


void AddCustomChar(uint8_t code, uint8_t* dots)
{
	uint8_t adr = code << 3;
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		LCD((0x1 << 6) + adr + i, 0);
		LCD(dots[i], 1);
	}
}
/*
Индикатор инициализируется в начальное состояние при подаче питания, а также по входу XRES с активным уровнем лог.0:
память индикатора очищается,
DL=1 (8-ми битный интерфейс),
D=0 (индикатор выключен), C=0 (курсор выключен),
P=0 (нулевая страница знакогенератора),
ID=0 (инкремент),
SH=0 (сдвиг экрана запрещён),
EXT=0 (основной набор команд).
*/


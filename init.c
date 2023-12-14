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
	DELAY_MS(5);
	E_RESET;
	DELAY_MS(1);
}



void Init(void)
{
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
	
	PORT_InitTypeDef PORTA_InitStruct;
	
	PORTA_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORTA_InitStruct.PORT_FUNC = PORT_FUNC_PORT;
	PORTA_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTA_InitStruct.PORT_OE = PORT_OE_OUT;
	PORTA_InitStruct.PORT_Pin = PORT_Pin_1 | PORT_Pin_2   | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_7;
	PORTA_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORTA_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	
	PORT_Init(MDR_PORTA, &PORTA_InitStruct);
	
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	
	PORT_InitTypeDef PORTB_InitStruct;
	
	PORTB_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORTB_InitStruct.PORT_FUNC = PORT_FUNC_PORT;
	PORTB_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTB_InitStruct.PORT_OE = PORT_OE_OUT;
	PORTB_InitStruct.PORT_Pin = PORT_Pin_0 | PORT_Pin_1   | PORT_Pin_2 | PORT_Pin_5 | PORT_Pin_6;
	PORTB_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORTB_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	
	PORT_Init(MDR_PORTB, &PORTB_InitStruct);
	
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
	
	PORT_InitTypeDef PORTC_InitStruct;
	
	PORTC_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORTC_InitStruct.PORT_FUNC = PORT_FUNC_PORT;
	PORTC_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTC_InitStruct.PORT_OE = PORT_OE_OUT;
	PORTC_InitStruct.PORT_Pin = PORT_Pin_0 | PORT_Pin_1;
	PORTC_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PORTC_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	
	PORT_Init(MDR_PORTC, &PORTC_InitStruct);
	
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);
	
	PORT_InitTypeDef PORTF_InitStruct;
	
	PORTF_InitStruct.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORTF_InitStruct.PORT_FUNC = PORT_FUNC_PORT;
	PORTF_InitStruct.PORT_MODE = PORT_MODE_DIGITAL;
	PORTF_InitStruct.PORT_OE = PORT_OE_OUT;
	PORTF_InitStruct.PORT_Pin = PORT_Pin_1 | PORT_Pin_3;
	PORTF_InitStruct.PORT_PULL_UP = PORT_PULL_UP_OFF;
	PORTF_InitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	
	PORT_Init(MDR_PORTF, &PORTF_InitStruct);


	
	RW_RESET;
	PSB_SET;
	XRES_SET;
	LCD(0x38, 0); 
	LCD(0x38, 0); 
	LCD(0x38, 0); // init
	LCD(0x38, 0); // 2 lines 5*7 matrix
	LCD(0x0C, 0); // Display on, cursor off, 0 page
	LCD(0x01, 0); // Clear display
	LCD(0x06, 0); // Increment cursor (shift right)

//	LCD(0x00, 0); 
			
}


void PrintTableChar(display_line line, uint8_t pos, uint8_t page, char sym)
{
	if(line == secnond_line)
		pos += 0xC0;
	else
		pos += 0x80;
	if(page == 0)
		LCD(0x0E, 0);
	else
		LCD(0x0F, 0);
	LCD(pos, 0);
	LCD(sym, 1);
}


void PrintLine(char* str, uint8_t start_pos, display_line line, uint8_t len)
{
	unsigned char mask[] = {65, 189, 66, 190, 191, 69, 192, 193, 194, 195, 196, 197, 77, 
        72, 79, 134, 80, 67, 84, 199, 200, 88, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210}; 
	uint8_t i;
	char translit;
	for(i = 0; i < len; i++)
	{
		PrintTableChar(line, start_pos + i, 0, str[i]);
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


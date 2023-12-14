#ifndef INIT_H
#define INIT_H


#include "MDR32Fx.h"                    // Device header
#include "MDR32F9Qx_config.h"           // Keil::Device:Startup
#include "MDR32F9Qx_rst_clk.h"          // Keil::Drivers:RST_CLK
#include "MDR32F9Qx_port.h"             // Keil::Drivers:PORT


#define A0_SET 			PORT_SetBits(MDR_PORTF, PORT_Pin_1)
#define A0_RESET 		PORT_ResetBits(MDR_PORTF, PORT_Pin_1)
#define RW_SET 			PORT_SetBits(MDR_PORTC, PORT_Pin_1)
#define RW_RESET 		PORT_ResetBits(MDR_PORTC, PORT_Pin_1)
#define E_SET 			PORT_SetBits(MDR_PORTC, PORT_Pin_0)
#define E_RESET 		PORT_ResetBits(MDR_PORTC, PORT_Pin_0)
#define XRES_SET 		PORT_SetBits(MDR_PORTA, PORT_Pin_1)
#define XRES_RESET 	PORT_ResetBits(MDR_PORTA, PORT_Pin_1)
#define PSB_SET 		PORT_SetBits(MDR_PORTF, PORT_Pin_3)
#define PSB_RESET 	PORT_ResetBits(MDR_PORTF, PORT_Pin_3)
#define LED_SET 		PORT_SetBits(MDR_PORTA, PORT_Pin_2)
#define LED_RESET 	PORT_ResetBits(MDR_PORTA, PORT_Pin_2)

#define LCD_DB0_PORT MDR_PORTA
#define LCD_DB1_PORT MDR_PORTA
#define LCD_DB2_PORT MDR_PORTA
#define LCD_DB3_PORT MDR_PORTB
#define LCD_DB4_PORT MDR_PORTB
#define LCD_DB5_PORT MDR_PORTB
#define LCD_DB6_PORT MDR_PORTB
#define LCD_DB7_PORT MDR_PORTB

#define LCD_DB0 	PORT_Pin_7
#define LCD_DB1 	PORT_Pin_4
#define LCD_DB2 	PORT_Pin_5
#define LCD_DB3 	PORT_Pin_0
#define LCD_DB4 	PORT_Pin_2
#define LCD_DB5 	PORT_Pin_1
#define LCD_DB6 	PORT_Pin_5
#define LCD_DB7 	PORT_Pin_6
#define LCD_A0 		PORT_Pin_1

#define DELAY_US(x)    for(int i = 0; i < x; i++)
#define DELAY_MS(x)    for(int i = 0; i < 1333*x; i++)


typedef enum
{
	first_line = 0,
	secnond_line
} display_line;


void LCD(uint8_t val, uint8_t cmd);
void Init(void);
void PrintTableChar(uint8_t line, uint8_t pos, uint8_t page, char sym);
void PrintLine(char* str, uint8_t start_pos, display_line line);
void AddCustomChar(uint8_t code, uint8_t* dots);

#endif

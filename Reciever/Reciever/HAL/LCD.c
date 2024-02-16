/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/
#define F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "LCD.h"


u8* itoa(s32 num, u8* str, s32 base) {
	s32 i = 0;
	s32 isNegative = 0;

	// Handle 0 explicitly
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// Handle negative numbers
	if (num < 0 && base == 10) {
		isNegative = 1;
		num = -num;
	}

	// Convert the number to string in reverse order
	while (num != 0) {
		s32 rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		num = num / base;
	}

	// If the number is negative, append '-'
	if (isNegative)
	str[i++] = '-';

	// Append the null terminator
	str[i] = '\0';

	// Reverse the string
	s32 start = 0;
	s32 end = i - 1;
	while (start < end) {
		s8 temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}

	return str;
}


/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_voidInit(void)
{
	/*
	 *delay to wait the VDD rises
	 *Turn on 2 lines_8 bits mode
	 *Turn off cursor
	 *Clear command
	*/
	GPIO_setupPortDirection(LCD_CTRL_PORT,0xFF);
	GPIO_setupPortDirection(LCD_DATA_PORT,0xFF);
	_delay_ms(40);
	LCD_voidSendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);
	LCD_voidSendCommand(LCD_CURSOR_OFF);
	LCD_voidSendCommand(LCD_CLEAR_COMMAND);
}

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_voidSendCommand(u8 u8CommandCopy)
{
	/*
	 *Clear RS & RW PINS
	 *Send command on data port
	 *Turn on the enable pin 
	 *delay to read the command (1ms more for init function)
	 *Turn off the enable pin
	*/
	GPIO_writePin(LCD_CTRL_PORT,LCD_RS_PIN,LOGIC_LOW);
	GPIO_writePin(LCD_CTRL_PORT,LCD_RW_PIN,LOGIC_LOW);
	GPIO_writePort(LCD_DATA_PORT,u8CommandCopy);
	GPIO_writePin(LCD_CTRL_PORT,LCD_E_PIN,LOGIC_HIGH);
	_delay_ms(2);
	GPIO_writePin(LCD_CTRL_PORT,LCD_E_PIN,LOGIC_LOW);
}

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_voidSendData(u8 u8DataCopy)
{
	
	/*
	 *Clear RW pin
	 *Set RS pin
	 *Send command on data port
	 *Turn on the enable pin 
	 *delay to read the command
	 *Turn off the enable pin
	*/
	GPIO_writePin(LCD_CTRL_PORT,LCD_RS_PIN,LOGIC_HIGH);
	GPIO_writePin(LCD_CTRL_PORT,LCD_RW_PIN,LOGIC_LOW);
	GPIO_writePort(LCD_DATA_PORT,u8DataCopy);
	GPIO_writePin(LCD_CTRL_PORT,LCD_E_PIN,LOGIC_HIGH);
	_delay_ms(2);
	GPIO_writePin(LCD_CTRL_PORT,LCD_E_PIN,LOGIC_LOW);
}

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_voidSendString(const u8 *Str)
{
	u8 i=0;
	while(Str[i] != '\0')
	{
		if(i == 16){
			LCD_voidSendCommand(LCD_NEW_LINE);
		}
		LCD_voidSendData(Str[i]);
		i++;
	}
}

/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(u8 row,u8 col)
{
	u8 address=LCD_SET_CURSOR_LOCATION;
	switch(row)
	{
		case 0: address+=col; break;
		case 1: address+=col+0x40; break;
	}
	LCD_voidSendCommand(address);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
//void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_voidIntgerToString(u32 data)
{
	u8 buff[16];
	itoa(data,buff,10);
	LCD_voidSendString(buff);
}

/*
 * Description :
 * Send the clear screen command
 */
void LCD_voidClearScreen(void)
{
	LCD_voidSendCommand(LCD_CLEAR_COMMAND);
}






/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Mohamed Khaled
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "../LIB/std_types.h"
#include "../MCAL/gpio.h"
#include "../LIB/common_macros.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD HW Ports and Pins Ids */
#define LCD_CTRL_PORT               PORTD_ID
#define LCD_DATA_PORT               PORTC_ID


#define LCD_RS_PIN                  0
#define LCD_RW_PIN                  1
#define LCD_E_PIN                   5



#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/* LCD Commands */
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80
#define LCD_BLINK_CURSOR                     0x0F
#define LCD_NEW_LINE                         0xC0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

u8* itoa(s32 num, u8* str, s32 base);
/*
 * Description :
 * Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 */
void LCD_voidInit(void);

/*
 * Description :
 * Send the required command to the screen
 */
void LCD_voidSendCommand(u8 u8CommandCopy);

/*
 * Description :
 * Display the required character on the screen
 */
void LCD_voidSendData(u8 u8DataCopy);

/*
 * Description :
 * Display the required string on the screen
 */
void LCD_voidSendString(const u8 *Str);
/*
 * Description :
 * Move the cursor to a specified row and column index on the screen
 */
void LCD_moveCursor(u8 row,u8 col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
//void LCD_displayStringRowColumn(u8 row,u8 col,const char *Str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_voidIntgerToString(u32 data);
/*
 * Description :
 * Send the clear screen command
 */
void LCD_voidClearScreen(void);

#endif /* LCD_H_ */ 





#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "../LIB/types.h"
#include "../LIB/bitwise_operation.h"
#include "../MCAL/DIO.h"
#include "../MCAL/UART.h"

#define BL_PORT PORT_E


void bluetooth_Init(void); // Initialize UART5 module for HC-05
uint8 bluetooth_Read(void); //Read data from Rx5 pin of TM4C123
void bluetooth_Write(uint8 data); // Transmit a character to HC-05 over Tx5 pin 
void bluetooth_Write_String(uint8 *str);

/*
Note:
Till Now this is not 100% generic
You must connect the bluetooth module to port E !!!!!!!
*/

#endif
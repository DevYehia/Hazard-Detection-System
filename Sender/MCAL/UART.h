#ifndef UART_H
#define UART_H

#include "../LIB/types.h"
#include "../LIB/tm4c123gh6pm.h"
#include "../LIB/bitwise_operation.h"
#define UART0 0 
#define UART1 1 
#define UART2 2 
#define UART3 3 
#define UART4 4 
#define UART5 5 
#define UART6 6 
#define UART7 7 

//Function: Initialize the UART CLock and the corresponding GPIO pins
//Till now the only supported UART is UART5
//Input: UART number 
//Output:None
void UART_Init(uint8 uart_num);
//Function: Sets the baud rate in the IBRD and FBRD registers
//Till now the only supported baud rate is 9600 b/sec
//Input: None
//Output: None
void UART_setBaudRate();


#endif 
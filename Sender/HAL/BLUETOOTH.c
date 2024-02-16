#include "BLUETOOTH.h"

void bluetooth_Init(void)
{
    UART_Init(UART5);
}

uint8 bluetooth_Read(void)  
{
    while(Get_Bit(UART5_FR_R,4) != 0); /* wait until Rx buffer is not full */
    return  UART5_DR_R; 
}

void bluetooth_Write(uint8 data)  
{
    while(Get_Bit(UART5_FR_R,5) != 0); /* wait until Tx buffer not full */
    UART5_DR_R = data;                 /* before giving it another byte */
}

void bluetooth_Write_String(uint8 *str)
{
  while(*str)
	{
		bluetooth_Write(*(str++));
	}
}
#include "UART.h"



void UART_Init(uint8 uart_num){
  switch(uart_num){
    
  case UART5:{
    Set_Bit(SYSCTL_RCGCUART_R, 5);  /* enable clock to UART5 */
    Set_Bit(SYSCTL_RCGCGPIO_R, 4);  /* enable clock to PORTE for PE4/Rx and RE5/Tx */
    while((SYSCTL_PRGPIO_R&0x00000010) == 0){};  //wait till clock is initialized
    
    /* UART0 initialization */
    UART5_CTL_R = 0;         /* UART5 module disbable */
    UART_setBaudRate();
    UART5_CC_R = 0;          /*select system clock*/
    UART5_LCRH_R = 0x60;     /* data length 8-bit, not parity bit, no FIFO */
    UART5_CTL_R = 0x301;     /* Enable UART5 module, Rx and Tx */

    /* UART5 TX5 and RX5 use PE4 and PE5. Configure them digital and enable alternate function */
    GPIO_PORTE_DEN_R = 0xFF;
    GPIO_PORTE_AFSEL_R |= 0x30;    /* Use PE4,PE5 alternate function */
    GPIO_PORTE_AMSEL_R = 0;    /* Turn off analog function*/
    GPIO_PORTE_PCTL_R = 0x00110000;     /* configure PE4 and PE5 for UART */
    
  }
    break;
  
    
  }
  
}


void UART_setBaudRate(){
    UART5_IBRD_R = 104;      /* for 9600 baud rate, integer = 104 */
    UART5_FBRD_R = 11;       /* for 9600 baud rate, fractional = 11*/
  
  
}
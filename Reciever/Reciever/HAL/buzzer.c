/*
 * buzzer.c
 *
 * Created: 12/28/2023 5:51:18 PM
 *  Author: user
 */ 
#include "buzzer.h"

void buzzerInit(uint8 port, uint8 pin){
	GPIO_setupPinDirection(port,pin,PIN_OUTPUT);
}

void buzzerON(uint8 port, uint8 pin){
	GPIO_writePin(port,pin,LOGIC_HIGH);
}

void buzzerOFF(uint8 port, uint8 pin){
	GPIO_writePin(port,pin,LOGIC_LOW);
}
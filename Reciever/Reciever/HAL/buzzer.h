/*
 * buzzer.h
 *
 * Created: 12/28/2023 5:51:40 PM
 *  Author: user
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../MCAL/gpio.h"


void buzzerInit(uint8 port, uint8 pin);
void buzzerON(uint8 port,uint8 pin);
void buzzerOFF(uint8 port,uint8 pin);



#endif /* BUZZER_H_ */
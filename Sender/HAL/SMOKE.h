#ifndef SMOKE_H
#define SMOKE_H

#include "../MCAL/DIO.h"


#define ANALOG_PORT PORT_E
#define ANALOG_PIN  PIN3


void smoke_Init(void);
void smoke_Start_Sampling(void);
void smoke_Enable_Interrupt(void);
void smoke_Disable_Interrupt(void);
void smokePriority(void);
#endif
#ifndef SWITCH_H
#define SWITCH_H

#include "../LIB/types.h"
#include "../MCAL/DIO.h"
#include "../MCAL/INTERRUPT.h"
 
#define SWITCH_PORT PORT_E
#define SWITCH_PIN  PIN2
void switchInit(void);
void switchPriority(void);

#endif 
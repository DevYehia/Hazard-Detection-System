#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "../MCAL/DIO.h"
#include "../MCAL/TIMERS.h"
#include "../MCAL/SYSTICKTimer.h"

#define ECHO_PORT PORT_B
#define ECHO_PIN  PIN6

#define TRIGGER_PORT PORT_A
#define TRIGGER_PIN  PIN4


void ultrasonic_Init(void);
//uint32 Measure_distance(void);
void Delay(unsigned long counter);
//void ultrasonic_Enable_Interrupt(void);


#endif
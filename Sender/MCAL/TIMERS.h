#ifndef TIMER_H
#define TIMER_H

#include "../MCAL/DIO.h"

void Timer0ACapture_init(void);


void Timer1_init(void);

void Timer1_setDelay(void);

void Timer1_start(void);

void Timer1_stop(void);

void Timer1_enableInterrupt(void);




void Timer2_init(void);

void Timer2_setDelay(void);

void Timer2_start(void);

void Timer2_stop(void);

void Timer2_enableInterrupt(void);

#endif // TIMER_H

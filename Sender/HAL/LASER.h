#ifndef LASER_H
#define LASER_H
#include "../LIB/types.h"
#include "../MCAL/DIO.h"

void LASER_Init(uint8 PORT,uint8 pin);
void LASER_On(uint8 PORT,uint8 pin);
void LASER_Off(uint8 PORT,uint8 pin);


#endif
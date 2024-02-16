#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "../LIB/tm4c123gh6pm.h"
#include "../LIB/bitwise_operation.h"
#include "../LIB/types.h"

#define FALLING_EDGE 0
#define RISING_EDGE  1
#define HIGH_LEVEL   2
#define LOW_LEVEL    3


void interrupt_init(uint8 mode);

void interrupt_enable_pin(uint8 pin_num);
void interrupt_disable_pin(uint8 pin_num);

#endif
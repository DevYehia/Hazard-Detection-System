#include "switch.h"
#include "BLUETOOTH.h"
#include "../MCAL/TIMERS.h"
void switchInit(void){
    DIO_Init(SWITCH_PORT);
    DIO_SetupDirection(SWITCH_PORT,IN,SWITCH_PIN,PDR);
    interrupt_init(RISING_EDGE);
    interrupt_enable_pin(SWITCH_PIN);
    Timer2_init();
    Timer2_setDelay();
}


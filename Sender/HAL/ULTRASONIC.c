#include "ULTRASONIC.h"

void ultrasonic_Init(void){
  Timer0ACapture_init();  /*initialize Timer0A in edge edge time */
  DIO_Init(PORT_F);
  DIO_SetupDirection(PORT_F,OUT,PIN1,NO_PR);
  DIO_SetupDirection(PORT_F,OUT,PIN3,NO_PR);
}
//int lastEdge, thisEdge;




void Delay(unsigned long counter)
{
	unsigned long i = 0;
	
	for(i=0; i< counter*1000; i++);
}
/* This function is called by the startup assembly code to perform system specific initialization tasks. */





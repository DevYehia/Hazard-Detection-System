#include "LASER.h"


void LASER_Init(uint8 PORT,uint8 pin){
   DIO_Init(PORT);
   DIO_SetupDirection(PORT,OUT,pin,NO_PR);
}
void LASER_On(uint8 PORT,uint8 pin){
  DIO_WritePin(PORT,LOGIC_HIGH,pin);
}
void LASER_Off(uint8 PORT,uint8 pin){
  DIO_WritePin(PORT,LOGIC_LOW,pin);
}
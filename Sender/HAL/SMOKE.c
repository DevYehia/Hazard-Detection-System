#include "SMOKE.h"



void smoke_Init(void){
  Set_Bit(SYSCTL_RCGCADC_R,0); //enable clock of ADC 0
  Set_Bit(SYSCTL_RCGCGPIO_R,4);
  Set_Bit(GPIO_PORTE_AFSEL_R,3);    /* Use PE3 alternate function */
  Clear_Bit(GPIO_PORTE_DEN_R,3);
  Set_Bit(GPIO_PORTE_AMSEL_R,3);    /* Turn on analog function*/
  Clear_Bit(ADC0_ACTSS_R,3);
  ADC0_EMUX_R |= 0xF000;
  ADC0_SSMUX3_R = 0;
  ADC0_PC_R = 0x03;
  Set_Bit(ADC0_SSCTL3_R,2);
  Set_Bit(ADC0_SSCTL3_R,1);
  Set_Bit(ADC0_ACTSS_R,3);
  
  
  
}
void smokePriority(void){

}

void smoke_Start_Sampling(void){
  Set_Bit(ADC0_PSSI_R,3);
}

void smoke_Enable_Interrupt(void){
  
  Set_Bit(NVIC_EN0_R,17);
  Set_Bit(ADC0_IM_R,3);
  
}

void smoke_Disable_Interrupt(void){
  Clear_Bit(NVIC_EN0_R,17);
  Clear_Bit(ADC0_IM_R,3);
}
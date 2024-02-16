#include "INTERRUPT.h"

void interrupt_init(uint8 mode){
  switch(mode){
  case FALLING_EDGE:
    {
      Clear_Bit(GPIO_PORTF_IS_R , 0);
      Clear_Bit(GPIO_PORTF_IS_R , 4);
      
      Clear_Bit(GPIO_PORTF_IBE_R, 0);
      Clear_Bit(GPIO_PORTF_IBE_R, 4);
      
      Clear_Bit(GPIO_PORTF_IEV_R, 0);
      Clear_Bit(GPIO_PORTF_IEV_R, 4);
      
          //clear prior interrupts
    Set_Bit(GPIO_PORTF_ICR_R,0);
    Set_Bit(GPIO_PORTF_ICR_R,4);
    
      Set_Bit(NVIC_EN0_R,30);
    }
    break;
  case RISING_EDGE:
    {
      Clear_Bit(GPIO_PORTE_IS_R , 2);
     // Clear_Bit(GPIO_PORTF_IS_R , 4);
      
      Clear_Bit(GPIO_PORTE_IBE_R, 2);
      //Clear_Bit(GPIO_PORTF_IBE_R, 4);
      
      Set_Bit(GPIO_PORTE_IEV_R, 2);
     // Set_Bit(GPIO_PORTF_IEV_R, 4);
      
          //clear prior interrupts
      Set_Bit(GPIO_PORTE_ICR_R,2);
      
          //enable interrupt
    Set_Bit(NVIC_EN0_R,4);
    }
    break;
  case HIGH_LEVEL:
    {
      Set_Bit(GPIO_PORTF_IS_R , 0);
      Set_Bit(GPIO_PORTF_IS_R , 4);
      
      Clear_Bit(GPIO_PORTF_IBE_R, 0);
      Clear_Bit(GPIO_PORTF_IBE_R, 4);
      
      Set_Bit(GPIO_PORTF_IEV_R, 0);
      Set_Bit(GPIO_PORTF_IEV_R, 4);
    }
    break;
  case LOW_LEVEL:
    {
      Set_Bit(GPIO_PORTF_IS_R , 0);
      Set_Bit(GPIO_PORTF_IS_R , 4);
      
      Clear_Bit(GPIO_PORTF_IBE_R, 0);
      Clear_Bit(GPIO_PORTF_IBE_R, 4);
      
      Clear_Bit(GPIO_PORTF_IEV_R, 0);
      Clear_Bit(GPIO_PORTF_IEV_R, 4);
    }
    break;    
  default:{
    
  }
    
  }  //end of switch
  

    //Set_Bit(GPIO_PORTE_ICR_R,4);
    
    //set priority
    //NVIC_PRI7_R |= 3 << 21;
    

 
} //end of function

void interrupt_enable_pin(uint8 pin_num){
  /*if(pin_num > 7){
  }*/
  
  Set_Bit(GPIO_PORTE_IM_R, pin_num);

}


void interrupt_disable_pin(uint8 pin_num){
  /*if(pin_num > 7){
  }*/
  
  Clear_Bit(GPIO_PORTE_IM_R, pin_num);

}
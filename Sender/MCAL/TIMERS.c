#include "TIMERS.h"

void Timer0ACapture_init(void){
    SYSCTL_RCGCTIMER_R |= 0x01;     /* enable clock to Timer Block 0 */
    
    DIO_Init(PORT_B);
    DIO_SetupDirection(PORT_B,IN,PIN6,NO_PR);
    
    GPIO_PORTB_AFSEL_R |= 0x40;       /* use PB6 alternate function */
    GPIO_PORTB_PCTL_R &= ~0x0F000000; /* configure PB6 for T0CCP0 */
    GPIO_PORTB_PCTL_R |= 0x07000000;
    
	  /* PA4 as a digital output signal to provide trigger signal */
    DIO_Init(PORT_A);      /* enable clock to PORTA */
          
    DIO_SetupDirection(PORT_A,OUT,PIN4,NO_PR);         /* set PA4 as a digial output pin */
    
    
    TIMER0_CTL_R = 0;           /* disable Timer before initialization */
    TIMER0_CFG_R= 0x04;         /* 16-bit timer mode */ 
    TIMER0_TAMR_R = 0x17;        /* up-count, edge-time, capture mode  */
    TIMER0_CTL_R |= 0x0E;       /* capture the both edges and enable STALL for debugging */
    TIMER0_CTL_R |= 0x01;     /* enable Timer A after initialization */  
    //TIMER0_IMR_R |= 0x04;
    //Set_Bit(NVIC_EN0_R,19); //Enable the timer interrupt
}


void Timer1_init(void){
  Set_Bit(SYSCTL_RCGCTIMER_R,1);
  TIMER1_CTL_R = 0;
  TIMER1_CFG_R = 0x0;
  Set_Bit(TIMER1_TAMR_R,1);
  Clear_Bit(TIMER1_TAMR_R,4);
  TIMER1_TAPR_R = 0;
  TIMER1_ICR_R = 0x01;

  
  
}

void Timer1_setDelay(void){
  TIMER1_TAILR_R =0x1869FF;
  TIMER1_TBILR_R = 0x18;
}


void Timer1_start(void){
  
    TIMER1_CTL_R=0x01;
}

void Timer1_stop(void){
      TIMER1_CTL_R=0;
}

void Timer1_enableInterrupt(void){
  Set_Bit(TIMER1_IMR_R,0);
  Set_Bit(NVIC_EN0_R,21);
}



void Timer2_init(void){
  Set_Bit(SYSCTL_RCGCTIMER_R,2);
  TIMER2_CTL_R = 0;
  TIMER2_CFG_R = 0x0;
  Set_Bit(TIMER2_TAMR_R,1);
  Clear_Bit(TIMER2_TAMR_R,4);
  TIMER2_TAPR_R = 0;
  TIMER2_ICR_R = 0x01;

  
  
}

void Timer2_setDelay(void){
  TIMER2_TAILR_R =0xF423FF;
  TIMER2_TBILR_R = 0xF4;
}


void Timer2_start(void){
  
    TIMER2_CTL_R=0x01;
}

void Timer2_stop(void){
      TIMER2_CTL_R=0;
}

void Timer2_enableInterrupt(void){
  Set_Bit(TIMER2_IMR_R,0);
  Set_Bit(NVIC_EN0_R,23);
}
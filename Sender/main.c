#include "HAL/BLUETOOTH.h"
#include "HAL/SMOKE.h"
#include "MCAL/DIO.h"
#include "HAL/switch.h"
#include "HAL/ULTRASONIC.h"
#include "HAL/LASER.h"
uint8 fire[] = "Smoke Detected\n";
uint8 ultra[] = "Object is Near\n";
uint8 Ourswitch[] = "Switched On\n"; 
uint8* itoa(int32,uint8*,int32);

/* global variables to store and display distance in cm */
uint32 time; /*stores pulse on time */
uint32 distance; /* stores measured distance value */


uint8 lastedgeIn_flag =0;
int lastEdge, thisEdge;
unsigned long i = 0;

uint8 systick_done_flag =0;
//uint8 counter;

int main() {
//counter=0;



  //DIO_Init(PORT_F);
//DIO_SetupDirection(PORT_F,OUT,PIN1,NO_PR);
  //DIO_SetupDirection(PORT_F,OUT,PIN3,NO_PR);
  //DIO_SetupDirection(PORT_F,OUT,PIN3,NO_PR);
  DIO_Init(PORT_F);
  DIO_SetupDirection(PORT_F,IN,PIN0,PUR);
  DIO_SetupDirection(PORT_F,IN,PIN4,PUR);
  interrupt_init(FALLING_EDGE);
  Set_Bit(GPIO_PORTF_IM_R, PIN0); //Enable interrupt
  Set_Bit(GPIO_PORTF_IM_R, PIN4); //Enable interrupt


  
  
  while(1){
   

    
  
  }
  
  
}

uint8* itoa(int32 num, uint8* str, int32 base) {
	int32 i = 0;
	int32 isNegative = 0;

	// Handle 0 explicitly
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// Handle negative numbers
	if (num < 0 && base == 10) {
		isNegative = 1;
		num = -num;
	}

	// Convert the number to string in reverse order
	while (num != 0) {
		int32 rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		num = num / base;
	}

	// If the number is negative, append '-'
	if (isNegative)
	str[i++] = '-';

	// Append the null terminator
	str[i] = '\0';

	// Reverse the string
	int32 start = 0;
	int32 end = i - 1;
	while (start < end) {
		int8 temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}

	return str;
}
void ADCHandler(void){
  if(ADC0_SSFIFO3_R > 1000){
     Clear_Bit(NVIC_EN0_R,17);
    //DIO_WritePin(PORT_F,LOGIC_HIGH,PIN3);
    Timer2_start();
    for(int i=0;i<100000;i++);
    LASER_Off(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    LASER_On(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    LASER_Off(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    
    LASER_On(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    LASER_Off(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    while(Get_Bit(TIMER2_RIS_R,0)==0);
    TIMER2_ICR_R = 0x01;
    Timer2_stop();
    bluetooth_Write_String(fire);
    
    Set_Bit(NVIC_EN0_R,17);
  }
  else{
  }
  Set_Bit(ADC0_PSSI_R,3);
  Set_Bit(ADC0_ISC_R, 3);
  
  
}

void SystickHandler(void){

  
  uint32 i=0;
  i=NVIC_ST_CTRL_R; //No need to read for clearing the interrupt in systick!!
  DIO_WritePin(PORT_A,LOGIC_LOW,PIN4);
  SysTickDisable();
  Timer1_start();
  systick_done_flag=1;
 

}

void TIMER0_HANDLER(void){
  
  if(Get_Bit(GPIO_PORTB_DATA_R,PIN6))
  {
    lastEdge = TIMER0_TAR_R;     /* save the timestamp */
	lastedgeIn_flag =1;
  }     
      /* detect falling edge */
  else if((!(Get_Bit(GPIO_PORTB_DATA_R,PIN6))) && lastedgeIn_flag)     
  {
    thisEdge = TIMER0_TAR_R;     /* save the timestamp */
    time=(thisEdge - lastEdge); /* return the time difference */
    distance = (time * 10625)/10000000;
     if (distance >5)
      {
        DIO_WritePin(PORT_F,LOGIC_HIGH,PIN1);
        DIO_WritePin(PORT_F,LOGIC_LOW,PIN3);
      }
      else
      {
        DIO_WritePin(PORT_F,LOGIC_HIGH,PIN3);
        DIO_WritePin(PORT_F,LOGIC_LOW,PIN1);
        Clear_Bit(NVIC_EN0_R,19);
        Timer2_start();
        for(int i=0;i<100000;i++);
        LASER_Off(PORT_A,PIN3);
        for(int i=0;i<100000;i++);
        LASER_On(PORT_A,PIN3);
        for(int i=0;i<100000;i++);
        LASER_Off(PORT_A,PIN3);
        
        while(Get_Bit(TIMER2_RIS_R,0)==0);
        TIMER2_ICR_R = 0x01;
        Timer2_stop();
        Set_Bit(NVIC_EN0_R,19);
        bluetooth_Write_String(ultra);
      }
   }
    TIMER0_ICR_R = 0x04;            /* clear timer0A capture flag */
}


void TIMER1_HANDLER(void){
  
  DIO_WritePin(PORT_A,LOGIC_HIGH,PIN4);
  Timer1_stop();
  SysTickEnable(WITH_INTERRUPT);

  
  TIMER1_ICR_R = 0x01;
}

void SwitchHandler(void){
  //bluetooth_Init();
  interrupt_disable_pin(SWITCH_PIN);
  Set_Bit(GPIO_PORTE_ICR_R,2);
  Timer2_start();
    for(int i=0;i<100000;i++);
    LASER_Off(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    LASER_On(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    LASER_Off(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    
    LASER_On(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    LASER_Off(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    
    LASER_On(PORT_A,PIN3);
    for(int i=0;i<100000;i++);
    LASER_Off(PORT_A,PIN3);
    while(Get_Bit(TIMER2_RIS_R,0)==0);
    TIMER2_ICR_R = 0x01;
    Timer2_stop();
    Set_Bit(GPIO_PORTE_ICR_R,2);
    interrupt_enable_pin(SWITCH_PIN);
    bluetooth_Write_String(Ourswitch);
}


void PortF_Handler(void){
  //Start button
  if(Get_Bit(GPIO_PORTF_MIS_R,PIN0)){
    //Ultrasonic configs

    ultrasonic_Init();

    SysTickDisable();
    SysTickPeriodSet(PERIOD_DELAY_10us,uS_UNIT);
    //SysTickEnable(WITH_INTERRUPT);

    Timer1_init();
    Timer1_setDelay();
    //Timer1_enableInterrupt();

    //enableInterruptToProcessor(); 
    
    
      //ultrasonic_Init();
    //DIO_WritePin(PORT_F,LOGIC_HIGH,PIN3);
    Timer2_init();
    Timer2_setDelay();
    bluetooth_Init();
    smoke_Init();
    //smoke_Enable_Interrupt();
    smoke_Start_Sampling();
    LASER_Init(PORT_A,PIN3);
  
    switchInit();
  
  
  
    enableInterruptToProcessor();
    TIMER0_IMR_R |= 0x04;//Enable the timer0 interrupt 
    Set_Bit(NVIC_EN0_R,19); //Enable the timer0 interrupt 
    
    Timer1_enableInterrupt(); //Enable the timer1 interrupt  
    SysTickEnable(WITH_INTERRUPT);
    interrupt_enable_pin(SWITCH_PIN);
    //Set_Bit(NVIC_EN0_R,17); //Enable the ADC0 interrupt
    smoke_Enable_Interrupt();
    DIO_WritePin(PORT_A,LOGIC_HIGH,PIN4);
  }
  //Stop button
  else if(Get_Bit(GPIO_PORTF_MIS_R,PIN4)){
    TIMER0_IMR_R &= ~(0x04);//Enable the timer0 interrupt 
    Clear_Bit(NVIC_EN0_R,19); //Disable the timer0 interrupt 
    
    Clear_Bit(TIMER1_IMR_R,0);
    Clear_Bit(NVIC_EN0_R,21); //Disable the timer1 interrupt 
 
    SysTickDisable();
    interrupt_disable_pin(SWITCH_PIN);
    //Clear_Bit(NVIC_EN0_R,17); //Disable the ADC0 interrupt
    smoke_Disable_Interrupt();
    DIO_WritePin(PORT_F,LOGIC_LOW,PIN1);
  }

  GPIO_PORTF_ICR_R |= 0x11;
  
}
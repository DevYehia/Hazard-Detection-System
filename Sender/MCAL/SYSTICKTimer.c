#include "SYSTICKTimer.h"
//int Reload_Value=((PERIOD_DELAY_500ms)*(SYS_CLOCK_FREQUENCY))-1;
void enableInterruptToProcessor(void) {
__asm("CPSIE I");  
}

void waitForInterrupt(void) {
  __asm("       wfi\n");
}

void SysTickDisable (void){
  
  NVIC_ST_CTRL_R=0;
  NVIC_ST_CURRENT_R =NVIC_ST_RELOAD_R;
}
void SysTickEnable (uint8 interruptChoice){
  if(interruptChoice ==WITH_NO_INTERRUPT)
    NVIC_ST_CTRL_R=SYSTICK_TIMER_ENABLE_CLOCK;
  else
    NVIC_ST_CTRL_R=SYSTICK_TIMER_ENABLE_INTERRUPT_CLOCK;
}
uint32 SysTickPeriodGet (void){
 return NVIC_ST_RELOAD_R;
}

void SysTickPeriodSet (uint32 ui32Period,uint8 unit){
  if(unit == uS_UNIT)
  {
    NVIC_ST_RELOAD_R=((ui32Period)*(SYS_CLOCK_FREQUENCY_uS))-1;
  }
  else if(unit ==mS_UNIT) 
  {
    NVIC_ST_RELOAD_R=((ui32Period)*(SYS_CLOCK_FREQUENCY_mS))-1;
  
  }
}

uint32 SysTickValueGet (void){
  return NVIC_ST_CURRENT_R;
}

uint8 SysTick_Is_Time_out(void){
  while((NVIC_ST_CTRL_R&0x10000)==0);
  return TIMER_OUT;
}
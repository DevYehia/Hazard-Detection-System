#include "DIO.h"
#define TIMER_OUT 1
#define SYSTICK_TIMER_ENABLE_CLOCK 5
#define SYSTICK_TIMER_ENABLE_INTERRUPT_CLOCK 7

#define WITH_NO_INTERRUPT 0
#define WITH_INTERRUPT 1

#define SYS_CLOCK_FREQUENCY_uS 16 //To make the delay in milliseconds
#define SYS_CLOCK_FREQUENCY_mS 16000
#define SYS_CLOCK_FREQUENCY_S 16000000

#define mS_UNIT 0
#define uS_UNIT 1

/*
Frequency = 16
*/
#define PERIOD_DELAY_10us 10



/* with frequency =16000
#define PERIOD_DELAY_200ms 200
#define PERIOD_DELAY_500ms 500
#define PERIOD_DELAY_1000ms 1000
#define PERIOD_DELAY_2000ms 2000 //Max is 1s bec systick timer is 24 bit and cannot count to that!!
*/

void enableInterruptToProcessor(void);
void waitForInterrupt(void);
void SysTickDisable (void);
void SysTickEnable (uint8 interruptChoice);
uint32 SysTickPeriodGet (void); 

void SysTickPeriodSet (uint32 ui32Period,uint8 unit); 

uint32 SysTickValueGet (void);

uint8 SysTick_Is_Time_out(void);
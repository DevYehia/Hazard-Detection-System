

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_


#include "../LIB/std_types.h"
#include "../LIB/common_macros.h"

#define F_CPU 1000000UL
#define NULL (void *)0

//for enabling global interrupts
#define SREG  *((volatile u8*)0x5F)
#define SREG_GIE    7

//Timer 0
#define TCCR0          *((volatile u8*)0x53)  /**/
#define TCCR0_WGM00          6                /**/
#define TCCR0_WGM01          3                /**/ 
#define TCCR0_CS02           2                /**/  
#define TCCR0_CS01           1                /**/
#define TCCR0_CS00           0                /**/
#define TCCR0_COM00          4                /**/
#define TCCR0_COM01          5                /**/

//Timer 1
#define TCCR1A          *((volatile u8*)0x4F)  /**/
#define TCCR1A_WGM10          0               /**/
#define TCCR1A_WGM11          1                /**/


#define TCCR1B          *((volatile u8*)0x4E)  /**/
#define TCCR1B_WGM12          3                /**/
#define TCCR1B_WGM13          4                /**/
#define TCCR1B_CS02           2                /**/
#define TCCR1B_CS01           1                /**/
#define TCCR1B_CS00           0                /**/

#define TCCR2        *((volatile u8*)0x45)  /**/
#define TCCR2_CS00            0
#define TCCR2_CS01            1
#define TCCR2_CS02            2
#define TCCR2_WGM00          6                /**/
#define TCCR2_WGM01          3                /**/

#define TCNT2        *((volatile u8*)0x44)  /**/
#define OCR0           *((volatile u8*)0x5C)   /**/    

#define TIMSK          *((volatile u8*)0x59)   /**/
#define TIMSK_TOIE_ONE      2
#define TIMSK_OCIE          1                  /**/
#define TIMSK_TOIE          0                  /**/

#define  TCNT0           *((volatile u8*)0x52) /**/
#define  TCNT1L          *((volatile u8*)0x4C) /**/ 
#define  TCNT1H          *((volatile u8*)0x4D) /**/ 

/*Define TIMER0 Mode Options */

#define TIMER0_Normal            1
#define TIMER0_CTC               2 
#define TIMER0_Fast_PWM          3
#define TIMER0_correct_PWM       4



/**/

#define  OCR0_valu_CTC   50
#define  OCR0_valu_PWM   200




/**/
#define  TIMER0_SET_CTC_INITIAL_VALUE


#define CLK_FREQ_MODE    0
#define CLK_FREQ_MODE_OVER_8   1
#define CLK_FREQ_MODE_OVER_64   2
#define CLK_FREQ_MODE_OVER_256   3
#define CLK_FREQ_MODE_OVER_1024   4

#define TIMER0_PRESCALER    CLK_FREQ_MODE
#define TIMER1_PRESCALER    CLK_FREQ_MODE
#define TIMER2_PRESCALER    CLK_FREQ_MODE

#define  TIMER0_Mode   TIMER0_Normal
#define  TIMER1_MODE    TIMER0_Normal


/*Interrupt Vectors for TIPMERS0*/
#define TIMERS_U8_CMP_MTH_INTRPT			11	/*Timer Counter0 Output Compare Match Interrupt Enable*/
#define TIMERS_U8_OVF_INTRPT				12	/*Timer Counter0 Overflow Interrupt Enable*/


#define TIMERS_U8_OVF_INTRPT_ENB_PIN			0	/*Timer Counter0 Overflow Interrupt Enable*/
#define TIMERS_U8_CMP_MTH_INTRPT_ENB_PIN		1	/*Timer Counter0 Output Compare Match Interrupt Enable*/


/* 1. The No of overflow you want to get the required time delay.
 * 2. The preload value to make sure you set the exact time.
 */
#define TIMERS_U8_NORMAL_NO_OF_OVF					1
#define TIMERS_U8_PRELOAD_INITIAL_VALUE				24

#define TIMER1H_PRELOAD  0xB4
#define TIMER1L_PRELOAD  0xC0

#define TIMER_INTEGER_OVERFLOWS                     1
/* 1. The No of overflow you want to get required time delay.
 * 2. The Initial value you want to make the timer start from, this value ranges from 0 to 2^n(max).
 */
#define TIMERS_U8_CTC_NO_OF_OVF						10000
#define TIMERS_U8_SET_CTC_INITIAL_VALUE				100

#define OVERFLOW_MODE 0
#define COMPARE_MODE  1

void timer0_voidInit(void);

void timer0Stop(void);

void timer0_voidSetDuty(u8 Copy_u8DutyCycle);

void timer0_voidSetCallBack(void (*Copy_pvCallBackFunc)(void),u8 index);

void timer1_voidInit(void);

void timer1_voidSetDuty(u8 Copy_u8DutyCycle);

void timer1_voidSetCallBack(void (*Copy_pvCallBackFunc)(void),u8 index);

void timer1Start(void);
void timer1Stop(void);


void timer2_voidInit(void);

void timer2_voidSetCallBack(void (*Copy_pvCallBackFunc)(void),u8 index);

void timer2Stop(void);




#endif








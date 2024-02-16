/*
 * main.c
 *
 * Created: 12/25/2023 8:47:38 PM
 *  Author: user
 */ 

#include <xc.h>
#include <util/delay.h>
#include "MCAL/interrupt.h"
#include "HAL/LCD.h"
#include "MCAL/gpio.h"
#include "HAL/buzzer.h"
#include "MCAL/timer.h"

uint8 countRisings = 0;
uint8 cleared = 1;

void mute(void){
	LCD_voidSendCommand(LCD_CLEAR_COMMAND);
	buzzerOFF(PORTD_ID,PIN4_ID);
	timer1Stop();
	timer2Stop();
	GPIO_writePin(PORTA_ID,PIN0_ID,0);
	cleared = 1;
}
void countInterrupts(void){
	countRisings++;
	if(countRisings == 1){
		timer0_voidInit();
	}
}
void warn(void){
	char fire[] = "Smoke has been detected";
	char ultra[] = "An Object is near";
	char magnetic[] = "Switched On";
	char arr[3] = {0}; 
	if(countRisings == 1 && cleared){
	    LCD_voidSendString(ultra);
		cleared = 0;
	}
	else if(countRisings == 2 && cleared){
		LCD_voidSendString(fire);
		cleared = 0;
	}
	else if(countRisings == 3 && cleared){
		LCD_voidSendString(magnetic);
		cleared = 0;
	}
	//LCD_voidSendString(itoa(countRisings,arr,10));
	buzzerON(PORTD_ID,PIN4_ID);
	timer0Stop();
	timer2_voidInit();
	countRisings = 0;
}
void toggle_led(void){
	GPIO_togglePin(PORTA_ID,0);
}

int main(void)
{
	GPIO_setupPinDirection(PORTD_ID,PIN2_ID,0);
	GPIO_setupPinDirection(PORTD_ID,PIN3_ID,0);
	GPIO_setupPinDirection(PORTB_ID,PIN2_ID,0);
	GPIO_setupPinDirection(PORTA_ID,PIN0_ID,1);
	LCD_voidInit();
	timer1_voidSetCallBack(mute,OVERFLOW_MODE);
	EXTI_voidSetCallBack(timer1_voidInit,1);
	EXTI_voidSetCallBack(countInterrupts,2);	
	timer0_voidSetCallBack(warn,OVERFLOW_MODE);
	timer2_voidSetCallBack(toggle_led,OVERFLOW_MODE);
	enable_interrupts();
	interrupt_voidInt1Init();
	interrupt_voidInt2Init();
	EXTI_voidEnableInterrupt(GICR_INT1);
	EXTI_voidEnableInterrupt(GICR_INT2);
    while(1)
    {

    }
}
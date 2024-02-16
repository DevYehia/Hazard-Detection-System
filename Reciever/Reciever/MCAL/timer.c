


#include "timer.h"


static void (*Global_Timer0CallBack[2])(void)={NULL,NULL};
static void (*Global_Timer1CallBack[2])(void)={NULL,NULL};
static void (*Global_Timer2CallBack[2])(void)={NULL,NULL};
void timer0_voidInit(void)
{
		/*Prescaler */
		#if   TIMER0_PRESCALER   ==  CLK_FREQ_MODE
		    SET_BIT(TCCR0, TCCR0_CS00);
		    CLEAR_BIT(TCCR0, TCCR0_CS01);
		    CLEAR_BIT(TCCR0, TCCR0_CS02);
		#elif   TIMER0_PRESCALER   ==  CLK_FREQ_MODE_OVER_8
			CLEAR_BIT(TCCR0, TCCR0_CS00);
			SET_BIT(TCCR0, TCCR0_CS01);
			CLEAR_BIT(TCCR0, TCCR0_CS02);
		#elif  TIMER0_PRESCALER   ==  CLK_FREQ_MODE_OVER_64
			SET_BIT(TCCR0, TCCR0_CS00);
			SET_BIT(TCCR0, TCCR0_CS01);
			CLEAR_BIT(TCCR0, TCCR0_CS02);
		#elif  TIMER0_PRESCALER   ==  CLK_FREQ_MODE_OVER_256
			CLEAR_BIT(TCCR0, TCCR0_CS00);
			CLEAR_BIT(TCCR0, TCCR0_CS01);
			SET_BIT(TCCR0, TCCR0_CS02);
		#elif  TIMER0_PRESCALER   ==  CLK_FREQ_MODE_OVER_1024
			SET_BIT(TCCR0, TCCR0_CS00);
			CLEAR_BIT(TCCR0, TCCR0_CS01);
			SET_BIT(TCCR0, TCCR0_CS02);
		#else
			#error "wrong sense conrol config"
		#endif
		
	#if TIMER0_Mode == TIMER0_Normal
	/*Choose Normal Mode*/
	CLEAR_BIT(TCCR0, TCCR0_WGM00);
	CLEAR_BIT(TCCR0, TCCR0_WGM01);
	
	/*Timer Over flow flag Enable*/
	SET_BIT(TIMSK , TIMSK_TOIE);
	SET_BIT(SREG , SREG_GIE);  
	
	/* preload value*/
	TCNT0 =0;
	
	#elif     TIMER0_Mode == TIMER0_CTC
	/*Choose CTC Mode*/
	CLEAR_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
	
	/*Timer compare match flag Enable*/
	SET_BIT(TIMSK , TIMSK_OCIE);
	SET_BIT(SREG , SREG_GIE);
	
	/**/
	OCR0=OCR0_valu_CTC;
	
	/*Prescaler */
	#elif     TIMER0_Mode == TIMER0_Fast_PWM
	
	/*Choose PWM Mode*/
	SET_BIT(TCCR0, TCCR0_WGM00);
	SET_BIT(TCCR0, TCCR0_WGM01);
	
	/*Set OC0 on top Clear OC0 on Compare => Non Inverting*/
	CLEAR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
	
	OCR0=OCR0_valu_PWM;
	
	#elif     TIMER0_Mode == TIMER0_correct_PWM
	
	/*Choose PWM Mode*/
	SET_BIT(TCCR0, TCCR0_WGM00);
	CLEAR_BIT(TCCR0, TCCR0_WGM01);
	
	/*Set OC0 on top Clear OC0 on Compare => Non Inverting*/
	CLEAR_BIT(TCCR0, TCCR0_COM00);
	SET_BIT(TCCR0, TCCR0_COM01);
	
	OCR0=OCR0_valu_PWM;
	#else
		#error "wrong sense conrol config"
	#endif
}

void timer0Stop(void){
	CLEAR_BIT(TCCR0, TCCR0_CS00);
	CLEAR_BIT(TCCR0, TCCR0_CS01);
	CLEAR_BIT(TCCR0, TCCR0_CS02);
}



void timer0_voidSetDuty(u8 Copy_u8DutyCycle )
{
	
	/*Check for mode in PWM*/
	OCR0 = Copy_u8DutyCycle;  /*Sets OCR0 value*/
}
	
	
	
void timer0_voidSetCallBack(void (*callBackFunc)(void),u8 index)
{
	
	if(NULL != callBackFunc)
	{
		switch(index)
		{
		case COMPARE_MODE:
			Global_Timer0CallBack[index] = callBackFunc;
			break;
		case OVERFLOW_MODE:
			Global_Timer0CallBack[index] = callBackFunc;
			break;  /* return error */
		}
	}
	else
	{
		/* return error */
	}
	
}



/*prototype for ISR of TIMER0 CTC*/
void __vector_10(void)	__attribute__((signal));
void __vector_10(void)
{
	static u16 L_u16CounterCTC = 0;
	L_u16CounterCTC++;
	if(L_u16CounterCTC == TIMERS_U8_CTC_NO_OF_OVF)
	{
		/*clear counter*/
		L_u16CounterCTC = 0;
		/*call callback function*/
		if(Global_Timer0CallBack[TIMERS_U8_CMP_MTH_INTRPT_ENB_PIN] != NULL)  /* mistake or more save*/
		{
			Global_Timer0CallBack[TIMERS_U8_CMP_MTH_INTRPT_ENB_PIN]();
		}else{}
	}else{}
}

/*prototype for ISR of TIMER0 OVF*/
void __vector_11(void)	__attribute__((signal));
void __vector_11(void)
{
	static u32 OVcounter = 0;
	OVcounter++;
	if(OVcounter == 3906)
	{
		/*update preload value*/
		TCNT0 = 192;

	}else if(OVcounter == 3907){
				TCNT0 = 0;
				/*clear the OVF counter*/
				OVcounter = 0;
				/*call APP function*/
				if(Global_Timer0CallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN] != NULL)
				{
					Global_Timer0CallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN]();
				}
	}

}

void timer1_voidInit(void){
			/*Prescaler */
			#if   TIMER1_PRESCALER   ==  CLK_FREQ_MODE
			SET_BIT(TCCR1B, TCCR1B_CS00);
			CLEAR_BIT(TCCR1B, TCCR1B_CS01);
			CLEAR_BIT(TCCR1B, TCCR1B_CS02);
			#elif   TIMER1_PRESCALER   ==  CLK_FREQ_MODE_OVER_8
			CLEAR_BIT(TCCR1B, TCCR1B_CS00);
			SET_BIT(TCCR1B, TCCR1B_CS01);
			CLEAR_BIT(TCCR1B, TCCR1B_CS02);
			#elif  TIMER1_PRESCALER   ==  CLK_FREQ_MODE_OVER_64
			SET_BIT(TCCR1B, TCCR1B_CS00);
			SET_BIT(TCCR1B, TCCR1B_CS01);
			CLEAR_BIT(TCCR1B, TCCR1B_CS02);
			#elif  TIMER1_PRESCALER   ==  CLK_FREQ_MODE_OVER_256
			CLEAR_BIT(TCCR1B, TCCR1B_CS00);
			CLEAR_BIT(TCCR1B, TCCR1B_CS01);
			SET_BIT(TCCR1B, TCCR1B_CS02);
			#elif  TIMER1_PRESCALER   ==  CLK_FREQ_MODE_OVER_1024
			SET_BIT(TCCR1B, TCCR1B_CS00);
			CLEAR_BIT(TCCR1B, TCCR1B_CS01);
			SET_BIT(TCCR1B, TCCR1B_CS02);
			#else
			#error "wrong sense conrol config"
			#endif
			
			#if TIMER1_MODE == TIMER0_Normal
			/*Choose Normal Mode*/
			CLEAR_BIT(TCCR1A, TCCR1A_WGM10);
			CLEAR_BIT(TCCR1A, TCCR1A_WGM11);
			CLEAR_BIT(TCCR1B, TCCR1B_WGM12);
			CLEAR_BIT(TCCR1B, TCCR1B_WGM13);
			
			/*Timer Over flow flag Enable*/
			SET_BIT(TIMSK , TIMSK_TOIE_ONE);
			//enable global interrupts
			SET_BIT(SREG , SREG_GIE);
			
			/* preload value*/
			TCNT1H = 0;
			TCNT1L = 0;
			#else
			#error "wrong sense conrol config"
			#endif
}

void timer1_voidSetCallBack(void (*callBackFunc)(void),u8 index){
		if(callBackFunc != NULL)
		{
			switch(index)
			{
				case COMPARE_MODE:
				Global_Timer1CallBack[index] = callBackFunc;
				break;
				case OVERFLOW_MODE:
				Global_Timer1CallBack[index] = callBackFunc;
				break;  /* return error */
			}
		}
		else
		{
			/* return error */
		}
}

void timer1Start(void){
				SET_BIT(TCCR1B, TCCR1B_CS00);
				CLEAR_BIT(TCCR1B, TCCR1B_CS01);
				CLEAR_BIT(TCCR1B, TCCR1B_CS02);
}

void timer1Stop(void){
					CLEAR_BIT(TCCR1B, TCCR1B_CS00);
					CLEAR_BIT(TCCR1B, TCCR1B_CS01);
					CLEAR_BIT(TCCR1B, TCCR1B_CS02);
}

void __vector_9(void)	__attribute__((signal));
void __vector_9(void)
{
	static u8 OVcounter = 0;
	OVcounter++;
	if(OVcounter == 76)
	{
		/*update preload value*/
		TCNT1L = TIMER1L_PRELOAD;
		TCNT1H = TIMER1H_PRELOAD;

		}
	else if(OVcounter == 77){
			TCNT1L = 0;
			TCNT1H = 0;
		/*clear the OVF counter*/
		OVcounter = 0;
		/*call APP function*/
		if(Global_Timer1CallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN] != NULL)
		{
			Global_Timer1CallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN]();
		}
	}

}

void timer2_voidInit(void)
{
	/*Prescaler */
	#if   TIMER2_PRESCALER   ==  CLK_FREQ_MODE
	SET_BIT(TCCR2, TCCR2_CS00);
	CLEAR_BIT(TCCR2, TCCR2_CS01);
	CLEAR_BIT(TCCR2, TCCR2_CS02);
	#elif   TIMER2_PRESCALER   ==  CLK_FREQ_MODE_OVER_8
	CLEAR_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLEAR_BIT(TCCR2, TCCR0_CS02);
	#elif  TIMER2_PRESCALER   ==  CLK_FREQ_MODE_OVER_64
	SET_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLEAR_BIT(TCCR0, TCCR0_CS02);
	#elif  TIMER2_PRESCALER   ==  CLK_FREQ_MODE_OVER_256
	CLEAR_BIT(TCCR0, TCCR0_CS00);
	CLEAR_BIT(TCCR0, TCCR0_CS01);
	SET_BIT(TCCR0, TCCR0_CS02);
	#elif  TIMER2_PRESCALER   ==  CLK_FREQ_MODE_OVER_1024
	SET_BIT(TCCR0, TCCR0_CS00);
	CLEAR_BIT(TCCR0, TCCR0_CS01);
	SET_BIT(TCCR0, TCCR0_CS02);
	#else
	#error "wrong sense conrol config"
	#endif

	/*Choose Normal Mode*/
	CLEAR_BIT(TCCR2, TCCR2_WGM00);
	CLEAR_BIT(TCCR2, TCCR2_WGM01);
	
	/*Timer Over flow flag Enable*/
	SET_BIT(TIMSK , 6);
	SET_BIT(SREG , SREG_GIE);
	
	/* preload value*/
	TCNT2 =0;
	

}

void timer2Stop(void){
	CLEAR_BIT(TCCR2, TCCR2_CS00);
	CLEAR_BIT(TCCR2, TCCR2_CS01);
	CLEAR_BIT(TCCR2, TCCR2_CS02);
}



void timer2_voidSetCallBack(void (*callBackFunc)(void),u8 index)
{
	
	if(NULL != callBackFunc)
	{
		switch(index)
		{
			case COMPARE_MODE:
			Global_Timer2CallBack[index] = callBackFunc;
			break;
			case OVERFLOW_MODE:
			Global_Timer2CallBack[index] = callBackFunc;
			break;  /* return error */
		}
	}
	else
	{
		/* return error */
	}
	
}

void __vector_5(void)	__attribute__((signal));
void __vector_5(void)
{
	static u32 OVcounter = 0;
	OVcounter++;
	if(OVcounter == 1953)
	{
		/*update preload value*/
		TCNT2 = 224;

	}
	else if(OVcounter == 1954){
		TCNT2 = 0;
		/*clear the OVF counter*/
		OVcounter = 0;
		/*call APP function*/
		if(Global_Timer2CallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN] != NULL)
		{
			Global_Timer2CallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN]();
		}
	}

}



#include "interrupt.h"


/* 
	Global Pointer to Function => Carry The Adress of ISR func in the main 
	Hint : I Made an array of pointers to carry EXTI 0,1,2 according to its index
	
*/ 
void (*EXTI_CallBack[3]) (void) = { NULL } ;

void enable_interrupts(){
		SET_BIT(STATUS,7);
}



void interrupt_voidInt0Init(void)
{
	/*check sense control of pin INT0*/
	
	#if      INT0_SENSE==LOW_LEVEL
	CLEAR_BIT(MCUCR,MCUCR_ISC00);
	CLEAR_BIT(MCUCR,MCUCR_ISC01);
	
	#elif    INT0_SENSE==ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLEAR_BIT(MCUCR,MCUCR_ISC01);
	
	#elif    INT0_SENSE==FALLNG_EDGE
	CLEAR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
	
	#elif    INT0_SENSE==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
	
	#else
		#error "wrong sense conrol config"
	
	#endif
	
	/*check perifral Iterrupt Enable for Pin InT0*/
	
	#if INTO_INITAL_STATE == DISABLED
	CLEAR_BIT(GICR,GICR_INT0);
	
	#elif INTO_INITAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
	
	#else
		#error "wrong sense conrol config"
	#endif	
} 



void interrupt_voidInt1Init(void)
{
	/*check control of pin INT1*/
	
	#if      INT1_SENSE==LOW_LEVEL
	CLEAR_BIT(MCUCR,MCUCR_ISC10);
	CLEAR_BIT(MCUCR,MCUCR_ISC11);
	
	#elif    INT1_SENSE==ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLEAR_BIT(MCUCR,MCUCR_ISC11);
	
	#elif    INT1_SENSE==FALLNG_EDGE
	CLEAR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
	
	#elif    INT1_SENSE==RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
	
	#else
		#error "wrong sense control config"
	
	#endif
	
	/*check peripheral Interrupt Enable for Pin INT1*/
	
	#if INT1_INITAL_STATE == DISABLED
	CLEAR_BIT(GICR,GICR_INT1);
	
	#elif INT1_INITAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
	
	#else
		#error "wrong sense conrol config"
	#endif		
	
	
	
	
	
	
	
} 


void interrupt_voidInt2Init(void)
{
	#if INT2_SENSE == RISING_EDGE
	    SET_BIT(MCUCSR,MCUCSR_ISC2);
	#elif INT2_SENSE == FALLING_EDGE
	    CLEAR_BIT(MCUCSR,MCUCSR_ISC2);	    
	#else
		#error "wrong sense conrol config"
	#endif			

	#if INT2_INITAL_STATE == DISABLED
	    CLEAR_BIT(GICR,GICR_INT2);
	
	#elif INT2_INITAL_STATE == ENABLED
	    SET_BIT(GICR,GICR_INT2);
	#endif

}



u8 EXTI_voidDisableInterrupt   ( u8 interruptPin )
{

	u8 Local_u8ErrorState = OK ;
	if ( (interruptPin>=GICR_INT2) && (interruptPin<=GICR_INT1) )  /* Check [5:7] */
	{
		/* Clear The Required BIT */
		CLEAR_BIT( GICR , interruptPin );
	}
	else 
	{
		Local_u8ErrorState = NOK ;
	}
	
	return Local_u8ErrorState ;

}


u8 EXTI_voidEnableInterrupt    ( u8 interruptPin )
{
	u8 Local_u8ErrorState = OK ;
	if ( (interruptPin>=GICR_INT2) && (interruptPin<=GICR_INT1) )  /* Check [5:7] */
	{
		/* Clear The Required BIT */
		SET_BIT( GICR , interruptPin );
	}
	else 
	{
		Local_u8ErrorState = NOK ;
	}
	
	return Local_u8ErrorState ;



}



void EXTI_voidClearFlag ( u8 pinNumber ){

	SET_BIT( GIFR , pinNumber );

}

u8 EXTI_u8GetFlag( u8 pinNumber ){

	return GET_BIT( GIFR , pinNumber );

}




/*
 * Brief : This Function Init THE EXTI
 * Parameters : 
				=> The Adress of ISR Func (its name)
				=> EXTI Line --> [INT0 , INT1 , INT2]
 * return : Nothing
 */
void EXTI_voidSetCallBack( void (*callBackFunc)(void) , u8 interruptNo )
{

	if( callBackFunc != NULL ){

		EXTI_CallBack[interruptNo] = callBackFunc ;

	}

}


/*attribute is used to inform the compiler that the function is an interrupt handler or signal handler. 
It allows the compiler to generate the appropriate code for handling interrupts and 
perform any necessary setup or cleanup operations.*/


/* ISR --> Implementation */
void __vector_1(void) __attribute__((signal)); 
void __vector_1(void)
{

	if( EXTI_CallBack[0] != NULL ){

		EXTI_CallBack[0](); /*  Call The Global Pointer to Func   */
		EXTI_voidClearFlag( INT0 );

	}

}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{

	if( EXTI_CallBack[1] != NULL ){

		EXTI_CallBack[1]();
		EXTI_voidClearFlag( INT1 );

	}

}

//isr for External Interrupt 2
void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{

	if( EXTI_CallBack[2] != NULL ){

		EXTI_CallBack[2]();
		EXTI_voidClearFlag( INT2 );

	}

}

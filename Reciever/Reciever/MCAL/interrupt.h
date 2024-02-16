
#ifndef INTERRUPT_INTERFACE_H_
#define INTERRUPT_INTERFACE_H_

#include "../LIB/std_types.h"
#include "../LIB/common_macros.h"
#define STATUS (*(volatile uint8*)0x5F)


#define GICR    *((volatile u8*)0x5B)
#define GICR_INT1     7
#define GICR_INT0     6
#define GICR_INT2     5

#define GIFR    *((volatile u8*)0x5A)
#define GIFR_INT1     7
#define GIFR_INT0     6
#define GIFR_INT2     5

#define MCUCR    *((volatile u8*)0x55)
#define MCUCR_ISC00     0
#define MCUCR_ISC01     1
#define MCUCR_ISC10     2
#define MCUCR_ISC11     3

#define MCUCSR    *((volatile u8*)0x54)
#define MCUCSR_ISC2     6

#define      LOW_LEVEL       1
#define      ON_CHANGE       2
#define      RISING_EDGE     3
#define      FALLNG_EDGE     4
/* Copy_u8INT_Number */
#define INT1     7
#define INT0     6
#define INT2     5


/* Copy_u8EXTILine */
#define EXTI1     1
#define EXTI0     0
#define EXTI2     2

#define      ENABLED         1
#define      DISABLED        0

#define     NULL             0

/*   options:
       1-LOW_LEVEL
       2-ON_CHANGE
       3-RISING_EDGE
       4-FALLNG_EDGE
             */

#define     INT0_SENSE  RISING_EDGE
#define     INT1_SENSE  RISING_EDGE
#define     INT2_SENSE  3
/*   options:
       1-ENABLED
       2-DISABLED
             */

#define INTO_INITAL_STATE   1
#define INT1_INITIAL_STATE  1
#define INT2_INITIAL_STATE  1

enum errorStates{
OK,
NOK
};

void enable_interrupts(void);

void interrupt_voidInt0Init(void);

void interrupt_voidInt1Init(void);

void interrupt_voidInt2Init(void);

u8 EXTI_voidDisableInterrupt   ( u8 Copy_u8INT_Number );

u8 EXTI_voidEnableInterrupt    ( u8 Copy_u8INT_Number );


void EXTI_voidClearFlag ( u8 Copy_u8INT_Number );

u8 EXTI_u8GetFlag( u8 Copy_u8INT_Number );

void EXTI_voidSetCallBack( void (*Copy_pvoidCallBack)(void) , u8 Copy_u8INT_Number );


#endif
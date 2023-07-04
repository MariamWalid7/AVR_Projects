/*
 * TIMER_program.c
 *
 * Created: 4/17/2023 10:14:32 AM
 *  Author: maria
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"

#include <avr/io.h>

/* Global pointer to array of function */
static void (*TIMERS_pvCallBackFunc[16])(void) = {NULL} ; 

void TIMER0_voidInit (void){
	
/* Selecting mode of timer */
#if TIMER0_MODE == TIMER0_OVERFLOW_MODE

/* load TCNT0 with preload value */
TCNT0 = TCNT0_INITIAL_VALUE;

/* Adjust wave generation bits to normal mode */
CLR_BIT (TCCR0,TCCR0_WGM00);
CLR_BIT (TCCR0,TCCR0_WGM01);

/* OVERFLOW INT enabling */
#if TIMER0_INT_OVF == ENABLED

SET_BIT (SREG, SREG_Ibit);
SET_BIT (TIMSK, TIMSK_TOIE0); 

#else

 CLR_BIT (TIMSK, TIMSK_TOIE0);
 #endif
 
 /* Select OC0 non pwm mode */
 #if TIMER0_OC0_MODE == TIMER0_DISCONNECT_OC0
  CLR_BIT(TCCR0, TCCR0_COM00);
  CLR_BIT(TCCR0, TCCR0_COM01);
  
  #elif TIMER0_OC0_MODE == TIMER0_TOGGLE_OC0
 SET_BIT(TCCR0, TCCR0_COM00);
 CLR_BIT(TCCR0, TCCR0_COM01);
 
  #elif TIMER0_OC0_MODE == TIMER0_CLEAR_OC0
  CLR_BIT(TCCR0, TCCR0_COM00);
  SET_BIT(TCCR0, TCCR0_COM01);
  
  #elif TIMER0_OC0_MODE == TIMER0_SET_OC0
  SET_BIT(TCCR0, TCCR0_COM00);
  SET_BIT(TCCR0, TCCR0_COM01);
  
  #endif 
 

#elif  TIMER0_MODE == TIMER0_CTC_MODE

/* Load OCR0 with value */
OCR0 = TIMER0_OCR0_VALUE;

/* Adjust wave generation bits to CTC mode */
CLR_BIT (TCCR0,TCCR0_WGM00);
SET_BIT (TCCR0,TCCR0_WGM01);

/* CTC INT enabling */
#if TIMER0_CTC_INT == ENABLED

SET_BIT (SREG, SREG_Ibit);
SET_BIT (TIMSK, TIMSK_OCIE0);

#else

CLR_BIT (TIMSK, TIMSK_OCIE0);
#endif

 /* Select OC0 non pwm mode */
 #if TIMER0_OC0_MODE == TIMER0_DISCONNECT_OC0
 CLR_BIT(TCCR0, TCCR0_COM00);
 CLR_BIT(TCCR0, TCCR0_COM01);
 
 #elif TIMER0_OC0_MODE == TIMER0_TOGGLE_OC0
 SET_BIT(TCCR0, TCCR0_COM00);
 CLR_BIT(TCCR0, TCCR0_COM01);
 
 #elif TIMER0_OC0_MODE == TIMER0_CLEAR_OC0
 CLR_BIT(TCCR0, TCCR0_COM00);
 SET_BIT(TCCR0, TCCR0_COM01);
 
 #elif TIMER0_OC0_MODE == TIMER0_SET_OC0
 SET_BIT(TCCR0, TCCR0_COM00);
 SET_BIT(TCCR0, TCCR0_COM01);
 
 #endif
  /* Load OCR0 with value */
  OCR0 = TIMER0_OCR0_VALUE;

#elif  TIMER0_MODE == TIMER0_PWM_FAST_MODE

/* Adjust wave generation bits to fast pwm mode */
SET_BIT (TCCR0,TCCR0_WGM00);
SET_BIT (TCCR0,TCCR0_WGM01);

/* Select pwm oc0 mode */
#if TIMER0_OC0_MODE == TIMER0_DISCONNECT_OC0
CLR_BIT(TCCR0, TCCR0_COM00);
CLR_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_OC0_MODE == TIMER0_CLEAR_OC0
CLR_BIT(TCCR0, TCCR0_COM00);
SET_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_OC0_MODE == TIMER0_SET_OC0
SET_BIT(TCCR0, TCCR0_COM00);
SET_BIT(TCCR0, TCCR0_COM01);

#endif

/* Load OCR0 with value */
OCR0 = TIMER0_OCR0_VALUE;

#elif  TIMER0_MODE == TIMER0_PWM_PHCORRECT_MODE

/* Adjust wave generation bits to phase correct pwm mode */
SET_BIT (TCCR0,TCCR0_WGM00);
CLR_BIT (TCCR0,TCCR0_WGM01);

/* Select pwm oc0 mode */
#if TIMER0_OC0_MODE == TIMER0_DISCONNECT_OC0
CLR_BIT(TCCR0, TCCR0_COM00);
CLR_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_OC0_MODE == TIMER0_CLEAR_OC0
CLR_BIT(TCCR0, TCCR0_COM00);
SET_BIT(TCCR0, TCCR0_COM01);

#elif TIMER0_OC0_MODE == TIMER0_SET_OC0
SET_BIT(TCCR0, TCCR0_COM00);
SET_BIT(TCCR0, TCCR0_COM01);

#endif

#endif


/* Set clock Prescaler */
#if CLK_SOURCE_CONFIG == NO_CLK_SOURCE
 CLR_BIT (TCCR0, TCCR0_CS00);
 CLR_BIT (TCCR0, TCCR0_CS01);
 CLR_BIT (TCCR0, TCCR0_CS02);
 
 #elif  CLK_SOURCE_CONFIG == NO_PRESCALLER
 SET_BIT (TCCR0, TCCR0_CS00);
 CLR_BIT (TCCR0, TCCR0_CS01);
 CLR_BIT (TCCR0, TCCR0_CS02);
 
 #elif  CLK_SOURCE_CONFIG == PRESCALLER_8
 CLR_BIT (TCCR0, TCCR0_CS00);
 SET_BIT (TCCR0, TCCR0_CS01);
 CLR_BIT (TCCR0, TCCR0_CS02);
  
 #elif  CLK_SOURCE_CONFIG == PRESCALLER_64
 SET_BIT (TCCR0, TCCR0_CS00);
 SET_BIT (TCCR0, TCCR0_CS01);
 CLR_BIT (TCCR0, TCCR0_CS02);
 
 #elif  CLK_SOURCE_CONFIG == PRESCALLER_256
 CLR_BIT (TCCR0, TCCR0_CS00);
 CLR_BIT (TCCR0, TCCR0_CS01);
 SET_BIT (TCCR0, TCCR0_CS02);
 
 #elif  CLK_SOURCE_CONFIG == PRESCALLER_1024
 SET_BIT (TCCR0, TCCR0_CS00);
 CLR_BIT (TCCR0, TCCR0_CS01);
 SET_BIT (TCCR0, TCCR0_CS02);
 
 #elif  CLK_SOURCE_CONFIG == EXTERNAL_CLK_FALLING_EDGE
 CLR_BIT (TCCR0, TCCR0_CS00);
 SET_BIT (TCCR0, TCCR0_CS01);
 SET_BIT (TCCR0, TCCR0_CS02);
 
 #elif  CLK_SOURCE_CONFIG == EXTERNAL_CLK_RISING_EDGE
 SET_BIT (TCCR0, TCCR0_CS00);
 SET_BIT (TCCR0, TCCR0_CS01);
 SET_BIT (TCCR0, TCCR0_CS02);
 #endif 
}


void TIMER2_voidInit (void){
	
	/* Selecting mode of timer */
	#if TIMER2_MODE == TIMER2_OVERFLOW_MODE

	/* load TCNT2 with preload value */
	TCNT2 = TCNT2_INITIAL_VALUE;

	/* Adjust wave generation bits to normal mode */
	CLR_BIT (TCCR2,TCCR2_WGM20);
	CLR_BIT (TCCR2,TCCR2_WGM21);

	/* OVERFLOW INT enabling */
	#if TIMER2_INT_OVF == ENABLED

	SET_BIT (SREG, SREG_Ibit);
	SET_BIT (TIMSK, TIMSK_TOIE2);

	#else
	
	CLR_BIT (TIMSK, TIMSK_TOIE2);
	#endif
	
	/* Select OC2 non pwm mode */
	#if TIMER2_OC2_MODE == TIMER2_DISCONNECT_OC2
	CLR_BIT(TCCR2, TCCR2_COM20);
	CLR_BIT(TCCR2, TCCR2_COM21);
	
	#elif TIMER2_OC2_MODE == TIMER2_TOGGLE_OC2
	SET_BIT(TCCR2, TCCR2_COM20);
	CLR_BIT(TCCR2, TCCR2_COM21);
	
	#elif TIMER2_OC2_MODE == TIMER2_CLEAR_OC2
	CLR_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
	
	#elif TIMER2_OC2_MODE == TIMER2_SET_OC2
	SET_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
	
	#endif
	

	#elif  TIMER2_MODE == TIMER2_CTC_MODE

	/* Load OCR2 with value */
	OCR2 = TIMER2_OCR2_VALUE;

	/* Adjust wave generation bits to CTC mode */
	CLR_BIT (TCCR2,TCCR2_WGM20);
	SET_BIT (TCCR2,TCCR2_WGM21);

	/* CTC INT enabling */
	#if TIMER2_CTC_INT == ENABLED

	SET_BIT (SREG, SREG_Ibit);
	SET_BIT (TIMSK, TIMSK_OCIE2);

	#else
	
	CLR_BIT (TIMSK, TIMSK_OCIE2);
	#endif

	/* Select OC2 non pwm mode */
	#if TIMER2_OC2_MODE == TIMER2_DISCONNECT_OC2
	CLR_BIT(TCCR2, TCCR2_COM20);
	CLR_BIT(TCCR2, TCCR2_COM21);
	
	#elif TIMER2_OC2_MODE == TIMER2_TOGGLE_OC2
	SET_BIT(TCCR2, TCCR2_COM20);
	CLR_BIT(TCCR2, TCCR2_COM21);
	
	#elif TIMER2_OC2_MODE == TIMER2_CLEAR_OC2
	CLR_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
	
	#elif TIMER2_OC2_MODE == TIMER2_SET_OC2
	SET_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);
	
	#endif


	#elif  TIMER2_MODE == TIMER2_PWM_FAST_MODE

	/* Adjust wave generation bits to fast pwm mode */
	SET_BIT (TCCR2,TCCR2_WGM20);
	SET_BIT (TCCR2,TCCR2_WGM21);

	/* Select pwm oc2 mode */
	#if TIMER2_OC2_MODE == TIMER2_DISCONNECT_OC2
	CLR_BIT(TCCR2, TCCR2_COM20);
	CLR_BIT(TCCR2, TCCR2_COM21);

	#elif TIMER2_OC2_MODE == TIMER2_CLEAR_OC2
	CLR_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);

	#elif TIMER2_OC2_MODE == TIMER2_SET_OC2
	SET_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);

	#endif
	
	/* Set OCR2 value */
	OCR2 = TIMER2_OCR2_VALUE;

	#elif  TIMER2_MODE == TIMER2_PWM_PHCORRECT_MODE

	/* Adjust wave generation bits to phase correct pwm mode */
	SET_BIT (TCCR2,TCCR2_WGM20);
	CLR_BIT (TCCR2,TCCR2_WGM21);

	/* Select pwm oc2 mode */
	#if TIMER2_OC2_MODE == TIMER2_DISCONNECT_OC2
	CLR_BIT(TCCR2, TCCR2_COM20);
	CLR_BIT(TCCR2, TCCR2_COM21);

	#elif TIMER2_OC2_MODE == TIMER2_CLEAR_OC2
	CLR_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);

	#elif TIMER2_OC2_MODE == TIMER2_SET_OC2
	SET_BIT(TCCR2, TCCR2_COM20);
	SET_BIT(TCCR2, TCCR2_COM21);

	#endif
	/* Set OCR2 value */
	OCR2 = TIMER2_OCR2_VALUE;

	#endif
	
	#if ASYNC_STATUS_TIMER2 == EXTERNAL_CLK_CRYSTAL_OSC
	SET_BIT (ASSR, ASSR_AS2);
	
	#else
	CLR_BIT (ASSR, ASSR_AS2);
	#endif 


	/* Set clock Prescaler */
	#if CLK_SOURCE_CONFIG == NO_CLK_SOURCE
	CLR_BIT (TCCR2, TCCR2_CS20);
	CLR_BIT (TCCR2, TCCR2_CS21);
	CLR_BIT (TCCR2, TCCR2_CS22);
	
	#elif  CLK_SOURCE_CONFIG == NO_PRESCALLER
	SET_BIT (TCCR2, TCCR2_CS20);
	CLR_BIT (TCCR2, TCCR2_CS21);
	CLR_BIT (TCCR2, TCCR2_CS22);
	
	#elif  CLK_SOURCE_CONFIG == PRESCALLER_8
	CLR_BIT (TCCR2, TCCR2_CS20);
	SET_BIT (TCCR2, TCCR2_CS21);
	CLR_BIT (TCCR2, TCCR2_CS22);
	
	#elif  CLK_SOURCE_CONFIG == PRESCALLER_64
	CLR_BIT (TCCR2, TCCR2_CS20);
	CLR_BIT (TCCR2, TCCR2_CS21);
	SET_BIT (TCCR2, TCCR2_CS22);
	
	#elif  CLK_SOURCE_CONFIG == PRESCALLER_128
	SET_BIT (TCCR2, TCCR2_CS20);
	CLR_BIT (TCCR2, TCCR2_CS21);
	SET_BIT (TCCR2, TCCR2_CS22);
	
	#elif  CLK_SOURCE_CONFIG == PRESCALLER_256
	CLR_BIT (TCCR0, TCCR0_CS00);
	SET_BIT (TCCR0, TCCR0_CS01);
	SET_BIT (TCCR0, TCCR0_CS02);
	
	#elif  CLK_SOURCE_CONFIG == PRESCALLER_1024
	SET_BIT (TCCR0, TCCR0_CS00);
	SET_BIT (TCCR0, TCCR0_CS01);
	SET_BIT (TCCR0, TCCR0_CS02);
	
	#endif
}

void TIMER0_voidStartTimer(void){
	
	TCNT0 = TCNT0_INITIAL_VALUE;
}



void TIMER0_voidPhaseCorrectPWM(u8 Copy_u8DutyCycle) {

     /* Set OC0 pin as output pin*/
      DIO_enumSetPinDirection(DDRB, DIO_u8_PIN3, DIO_u8_PIN_OUTPUT);
	 /*configure PWM Duty Cycle*/
	 OCR0 = (Copy_u8DutyCycle*(256-1))/100;
	 /*Start PWM*/
	 TIMER0_voidStartTimer();
 
 }
 
void TIMER0_voidFastPWM(u8 Copy_u8DutyCycle){

	/* set OC0 as output pin */
	DIO_enumSetPinDirection(DDRB, DIO_u8_PIN3, DIO_u8_PIN_OUTPUT);
	 /*configure PWM Duty Cycle*/
	 OCR0 = (Copy_u8DutyCycle*256)/100;
	 /*Start PWM*/
	 TIMER0_voidStartTimer();
} 

 void TIMER0_voidSetDesiredTime_ms(u32 Copy_Time_ms){
 
   /*Timer0 calculations*/
	 u32 Local_u32TickTime    = (CLK_SOURCE_CONFIG * 1000000) / F_CPU ;  /*Time in micro second*/
	 u32 Local_u32DesiredTime = Copy_Time_ms * 1000;                                /*Time in micro second*/
	 if (CLK_SOURCE_CONFIG == NO_PRESCALLER)
	 {
		 /*Multiply bu the same value multiplied by prescaller*/
		 Local_u32DesiredTime = Local_u32DesiredTime * (F_CPU/1000000);
	 }
	 
	 /*set OCR0 value*/
	 OCR0    = Local_u32DesiredTime / Local_u32TickTime;
	 
	 /*Start counter by setting TCCR0 value*/
	 TIMER0_voidStartTimer();
	 
 }

void TIMER2_voidStartTimer(void){
	
	TCNT2 = TCNT2_INITIAL_VALUE;
}

void TIMER2_voidFastPWM(u8 Copy_u8DutyCycle){

	/* set OC2 as output pin */
	DIO_enumSetPinDirection(DDRB, DIO_u8_PIN3, DIO_u8_PIN_OUTPUT);
	/*configure PWM Duty Cycle*/
	OCR2 = (Copy_u8DutyCycle*256)/100;
	/*Start PWM*/
	TIMER2_voidStartTimer();
}

void TIMER2_voidPhaseCorrectPWM(u8 Copy_u8DutyCycle) {
     /*Set OC2 as output pin */
	 DIO_enumSetPinDirection(DDRB, DIO_u8_PIN3, DIO_u8_PIN_OUTPUT);
	/*configure PWM Duty Cycle*/
	OCR2 = (Copy_u8DutyCycle*(256-1))/100;
	/*Start PWM*/
	TIMER2_voidStartTimer();	
}

void TIMER2_voidSetDesiredTime_ms(u32 Copy_Time_ms){
	 
	 /*Timer2 calculations*/
	 u32 Local_u32TickTime    = (CLK_SOURCE_CONFIG * 1000000) / F_CPU ;  /*Time in micro second*/
	 u32 Local_u32DesiredTime = Copy_Time_ms * 1000;                                /*Time in micro second*/
	 if (CLK_SOURCE_CONFIG == NO_PRESCALLER)
	 {
		 /*Multiply bu the same value multiplied by prescaller*/
		 Local_u32DesiredTime = Local_u32DesiredTime * (F_CPU/1000000);
	 }
	 
	 /*set OCR0 value*/
	 OCR2    = Local_u32DesiredTime / Local_u32TickTime;
	 
	 /*Start counter by setting TCCR0 value*/
	 TIMER2_voidStartTimer();
	 
 }
 
 
void TIMER1_voidInit(void){
	
		/*Set Configurable Modes*/

		#if TIMER1_MODE == TIMER1_NORMAL_MODE

		/*Set Waveform generation mode as Normal mode */
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);

		/*Set the require Preload Value*/
		TCNT1 = TCNT1_INIT_VALUE ;

		/*Timer1 Overflow Interrupt Enable*/
		#if TIMER1_OVERFLOW_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_TOIE1) ;
		#elif TIMER1_OVERFLOW_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_TOIE1) ;
		
		#endif

		#elif (TIMER1_MODE == TIMER1_CTC_OCR1A_MODE) || (TIMER1_MODE == TIMER1_CTC_ICR1_MODE)

		/*Set Waveform generation mode as CTC modes */
		#if TIMER1_MODE == TIMER1_CTC_ICR1_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_CTC_OCR1A_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		
		#endif

		/*Set the require CTC Values*/
		OCR1A = TIMER1_CTCA_VAL ;
		OCR1B = TIMER1_CTCB_VAL ;

		/*Set ICR1 if TIMER1_CTC_OCR1A_MODE = TIMER1_CTC_ICR1_MODE*/
		#if TIMER1_MODE == TIMER1_CTC_ICR1_MODE
		ICR1 = TIMER1_ICR1_VAL ;

		#if TIMER1_ICR_EDGE == RISING
		SET_BIT(TCCR1B , TCCR1B_ICES1) ;
		#elif TIMER1_ICR_EDGE == FALLING
		CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
		
		#endif

		#endif

		/*Set OCR1A mode*/
		#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
		#elif TIMER1_OCR1A_MODE == TIMER_OC_TOGGLE
		SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
		#elif TIMER1_OCR1A_MODE == TIMER_OC_LOW
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
		#elif TIMER1_OCR1A_MODE == TIMER_OC_HIGH
		SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
		
		#endif

		/*Set OCR1B mode*/
		#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
		#elif TIMER1_OCR1B_MODE == TIMER_OC_TOGGLE
		SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
		#elif TIMER1_OCR1B_MODE == TIMER_OC_LOW
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
		#elif TIMER1_OCR1B_MODE == TIMER_OC_HIGH
		SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
		
		#endif

		/*Timer1 CTC Interrupt Enable*/
		#if TIMER1_CTCA_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
		#elif TIMER1_CTCA_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_OCIE1A) ;
		
		#endif

		#if TIMER1_CTCB_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
		#elif TIMER1_CTCB_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_OCIE1B) ;
		
		#endif

		#elif (TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE) || (TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE) ||(TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE) || (TIMER1_MODE == TIMER1_PWM_10_BIT_MODE) || (TIMER1_MODE == TIMER1_PWM_9_BIT_MODE) || (TIMER1_MODE == TIMER1_PWM_8_BIT_MODE)

		/*Set Waveform generation mode as PWM modes */
		#if TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_PWM_10_BIT_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_PWM_9_BIT_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_PWM_8_BIT_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		CLR_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		
		#endif

		/*Set the require CTC Values*/
		OCR1A = TIMER1_CTCA_VAL ;
		OCR1B = TIMER1_CTCB_VAL ;

		/*Set ICR1*/
		#if ((TIMER1_MODE == TIMER1_PWM_PHASE_CORRECT_ICR1_MODE) || (TIMER1_MODE == TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE))
		ICR1 = TIMER1_ICR1_VAL ;

		#if TIMER1_ICR_EDGE == RISING
		SET_BIT(TCCR1B , TCCR1B_ICES1) ;
		#elif TIMER1_ICR_EDGE == FALLING
		CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
		
		#endif
		
		#endif

		/*Set OCR1A mode*/
		#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
		#elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
		#elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
		SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
		
		#endif

		/*Set OCR1B mode*/
		#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
		#elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
		#elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
		SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
		
		#endif

		/*Timer1 PWM Interrupt Enable*/
		#if TIMER1_OVERFLOW_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_TOIE1) ;
		#elif TIMER1_OVERFLOW_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_TOIE1) ;
		
		#endif

		#if TIMER1_CTCA_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
		#elif TIMER1_CTCA_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_OCIE1A) ;
		
		#endif

		#if TIMER1_CTCB_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
		#elif TIMER1_CTCB_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_OCIE1B) ;
		
		#endif

		#if TIMER1_ICR_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_TICIE1) ;
		#elif TIMER1_ICR_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_TICIE1) ;
		
		#endif


		#elif (TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE) || (TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE) || (TIMER1_MODE == TIMER1_FAST_PWM_10_BIT_MODE) || (TIMER1_MODE == TIMER1_FAST_PWM_9_BIT_MODE) || (TIMER1_MODE == TIMER1_FAST_PWM_8_BIT_MODE)

		/*Set Waveform generation mode as PWM modes */
		#if TIMER1_MODE == TIMER1_FAST_PWM_OCR1A_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		SET_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_FAST_PWM_10_BIT_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_FAST_PWM_9_BIT_MODE
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		SET_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		#elif TIMER1_MODE == TIMER1_FAST_PWM_8_BIT_MODE
		SET_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);
		
		#endif

		/*Set the require CTC Values*/
		OCR1A = TIMER1_CTCA_VAL ;
		OCR1B = TIMER1_CTCB_VAL ;

		/*Set ICR1*/
		#if TIMER1_MODE == TIMER1_FAST_PWM_ICR1_MODE
		ICR1 = TIMER1_ICR1_VAL ;

		#if TIMER1_ICR_EDGE == RISING
		SET_BIT(TCCR1B , TCCR1B_ICES1) ;
		#elif TIMER1_ICR_EDGE == FALLING
		CLR_BIT(TCCR1B , TCCR1B_ICES1) ;
		
		#endif
		
		#endif

		/*Set OCR1A mode*/
		#if TIMER1_OCR1A_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1A1) ;
		#elif TIMER1_OCR1A_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
		CLR_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
		#elif TIMER1_OCR1A_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
		SET_BIT(TCCR1A , TCCR1A_COM1A0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1A1) ;
		
		#endif

		/*Set OCR1B mode*/
		#if TIMER1_OCR1B_MODE == TIMER_OC_DISCONNECTED
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		CLR_BIT(TCCR1A , TCCR1A_COM1B1) ;
		#elif TIMER1_OCR1B_MODE == TIMER_CLR_ON_CTC_SET_ON_TOP
		CLR_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
		#elif TIMER1_OCR1B_MODE == TIMER_SET_ON_CTC_CLR_ON_TOP
		SET_BIT(TCCR1A , TCCR1A_COM1B0) ;
		SET_BIT(TCCR1A , TCCR1A_COM1B1) ;
		
		#endif

		/*Timer1 PWM Interrupt Enable*/
		#if TIMER1_OVERFLOW_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_TOIE1) ;
		#elif TIMER1_OVERFLOW_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_TOIE1) ;
		
		#endif

		#if TIMER1_CTCA_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_OCIE1A) ;
		#elif TIMER1_CTCA_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_OCIE1A) ;
		
		#endif

		#if TIMER1_CTCB_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_OCIE1B) ;
		#elif TIMER1_CTCB_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_OCIE1B) ;
		
		#endif

		#if TIMER1_ICR_INTERRUPT == DISABLED
		CLR_BIT(TIMSK , TIMSK_TICIE1) ;
		#elif TIMER1_ICR_INTERRUPT == ENABLED
		SET_BIT(TIMSK , TIMSK_TICIE1) ;
		
		
		#endif
		
		#endif
} 

void TIMER1_voidStartTimer(void){
	
	TCNT1 = TCNT1_INIT_VALUE;
}

void TIMER1_voidFastPWM(u8 Copy_u8DutyCycle){
	
	/* set OC1A as output pin */
	DIO_enumSetPinDirection(DDRD, DIO_u8_PIN5, DIO_u8_PIN_OUTPUT);
	
	/*configure PWM Duty Cycle*/
	OCR1A = Copy_u8DutyCycle*1000;
	ICR1 = TIMER1_ICR1_VAL;
	
	/*Start PWM*/
	TIMER1_voidStartTimer();
	
}

void timer1_wave_fastPWM_A(double value)
{
	/* set OC1A as output pin */
	SET_BIT(DDRD,5);
	/* select fast PWM mode*/
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	/* load a value in OCR1A,ICR1 */
	OCR1A=value*1000;
	ICR1=19999;
	/* select timer clock, no prescaling */
	SET_BIT(TCCR1B,CS10);
	/* clear OC1A on compare match, set OC1A at BOTTOM,(non inverting mode)*/
	SET_BIT(TCCR1A,COM1A1);
}

void timer1_wave_fastPWM_B(double value)
{
	/* set OC1B as output pin */
	SET_BIT(DDRD,4);
	/* select fast PWM mode*/
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	/* load a value in OCR1B,ICR1 */
	OCR1B=value*1000;
	ICR1=19999;
	/* select timer clock, no prescaling */
	SET_BIT(TCCR1B,CS10);
	/* clear OC1B on compare match, set OC1B at BOTTOM,(non inverting mode)*/
	SET_BIT(TCCR1A,COM1B1);
}



void TIMER_voidSetCallBack(void (*Copy_pvCallBackFunc)(void) , u8 Copy_u8VectorID){
	
 if (Copy_pvCallBackFunc != NULL){
		
	TIMERS_pvCallBackFunc[Copy_u8VectorID] = Copy_pvCallBackFunc ;
		}	
}




/* TIMER0 ISR for normal mode */
void __vector_11(void){

	if (TIMERS_pvCallBackFunc[TIMER0_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER0_OVF_VECTOR_ID]() ;
	}
}

/* TIMER0 ISR for CTC mode */
void __vector_10(void){
	
	if (TIMERS_pvCallBackFunc[TIMER0_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER0_CTC_VECTOR_ID]() ;
	}
}

/* TIMER2 ISR for normal mode */
void __vector_5(void){
	
	if (TIMERS_pvCallBackFunc[TIMER2_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER2_OVF_VECTOR_ID]() ;
	}
}

/* TIMER2 ISR for CTC mode */
void __vector_4(void){
	
	if (TIMERS_pvCallBackFunc[TIMER2_CTC_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER2_CTC_VECTOR_ID]() ;
	}
}

/*TIMER1 Normal Mode ISR*/
void __vector_9(void){
	if (TIMERS_pvCallBackFunc[TIMER1_OVF_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_OVF_VECTOR_ID]() ;
	}
}

/*TIMER1 CTCB Mode ISR*/
void __vector_8(void){
	if (TIMERS_pvCallBackFunc[TIMER1_CTCB_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_CTCB_VECTOR_ID]() ;
	}
}

/*TIMER1 CTCA Mode ISR*/
void __vector_7(void){
	if (TIMERS_pvCallBackFunc[TIMER1_CTCA_VECTOR_ID] != NULL)
	{
		TIMERS_pvCallBackFunc[TIMER1_CTCA_VECTOR_ID]() ;
	}
}
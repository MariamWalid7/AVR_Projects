/*
 * TIMER_config.h
 *
 * Created: 4/23/2023 4:45:56 PM
 *  Author: maria
 */ 


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

/* Choose MCU frequency */ 
#define F_CPU   8000000UL

/* Choose Clk source:
Options: NO_CLK_SOURCE               
 NO_PRESCALLER               
 PRESCALLER_8                
 PRESCALLER_64               
 PRESCALLER_128                //Only available for timer2
 PRESCALLER_256              
 PRESCALLER_1024             
 EXTERNAL_CLK_FALLING_EDGE   
 EXTERNAL_CLK_RISING_EDGE    
*/
#define CLK_SOURCE_CONFIG  NO_PRESCALLER

/****************** TIMER0 config *******************/ //(MODES(4), INT STATUS(OVF/CTC), OC0, OCR0 value)

/* Choose MODE OF TIMER0:
Options:
 TIMER0_OVERFLOW_MODE        
 TIMER0_CTC_MODE             
 TIMER0_PWM_PHCORRECT_MODE   
 TIMER0_PWM_FAST_MODE
*/ 
#define TIMER0_MODE       TIMER0_PWM_FAST_MODE

/*INT status of TIMER0:
Options:
 ENABLED/ DISABLED
*/ 
#define TIMER0_INT_OVF    DISABLED
#define TIMER0_CTC_INT    ENABLED

/* OC0 MODE:
 Options:
 TIMER0_DISCONNECT_OC0      
 TIMER0_TOGGLE_OC0          
 TIMER0_CLEAR_OC0           
 TIMER0_SET_OC0
 */
#define TIMER0_OC0_MODE   TIMER0_DISCONNECT_OC0

/* PWM MODES:
 Options:
 TIMER0_PWM_NONINVERTED_OC0 
 TIMER0_PWM_INVERTED_OC0
*/
#define TIMER0_PWM     TIMER0_PWM_NONINVERTED_OC0 

/*OCR0 Initial Value*/
#define TIMER0_OCR0_VALUE  0

/* TCNT0 Initial value */
#define TCNT0_INITIAL_VALUE 0


/****************** TIMER2 config *******************/ //(MODES(4), INT STATUS(OVF/CTC), OC2, OCR2 value)

/* Choose MODE OF TIMER2:
Options:
 TIMER2_OVERFLOW_MODE        
 TIMER2_CTC_MODE             
 TIMER2_PWM_PHCORRECT_MODE   
 TIMER2_PWM_FAST_MODE
*/ 
#define TIMER2_MODE       TIMER2_CTC_MODE

/*INT status of TIMER2:
Options:
 ENABLED/ DISABLED
*/ 
#define TIMER2_INT_OVF    DISABLED
#define TIMER2_CTC_INT    DISABLED

/* OC2 MODE:
 Options:(non pwm)
 TIMER2_DISCONNECT_OC2      
 TIMER2_TOGGLE_OC2          
 TIMER2_CLEAR_OC2           
 TIMER2_SET_OC0
 */
#define TIMER2_OC2_MODE   TIMER2_DISCONNECT_OC2

/* PWM MODES:
 Options:
 TIMER2_PWM_NONINVERTED_OC2 
 TIMER2_PWM_INVERTED_OC2
*/
//#define TIMER2_PWM     TIMER0_PWM_NONINVERTED_OC2 

/*OCR2 Initial Value*/
#define TIMER2_OCR2_VALUE  78

/* TCNT2 Initial value */
#define TCNT2_INITIAL_VALUE 0

/* Asynchronus status for TIMER2 */
#define ASYNC_STATUS_TIMER2  EXTERNAL_CLK_CRYSTAL_OSC 




/****************** TIMER1 config *******************/ //(MODES, INT STATUS, OC, OCR value)

#define TIMER1_ICR_INTERRUPT      DISABLED
#define TIMER1_CTCB_INTERRUPT     DISABLED
#define TIMER1_CTCA_INTERRUPT     DISABLED
#define TIMER1_OVERFLOW_INTERRUPT DISABLED


#define TIMER1_OCR1B_MODE   TIMER_OC_DISCONNECTED
#define TIMER1_OCR1A_MODE   TIMER_OC_DISCONNECTED

#define TIMER1_MODE   TIMER1_FAST_PWM_ICR1_MODE

#define TCNT1_INIT_VALUE 0

#define TIMER1_ICR1_VAL 20000

#define TIMER1_ICR_EDGE RISING

#define TIMER1_CTCA_VAL 500

#define TIMER1_CTCB_VAL 0

#endif /* TIMER_CONFIG_H_ */
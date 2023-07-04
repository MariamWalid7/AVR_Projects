/*
 * TIMER_interface.h
 *
 * Created: 4/23/2023 4:45:34 PM
 *  Author: maria
 */ 


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

/* Vector indexes for Interrupts */
#define TIMER0_OVF_VECTOR_ID		11
#define TIMER0_CTC_VECTOR_ID		10

#define TIMER1_OVF_VECTOR_ID		9
#define TIMER1_CTCB_VECTOR_ID		8
#define TIMER1_CTCA_VECTOR_ID		7
#define TIMER1_ICU_VECTOR_ID		6

#define TIMER2_OVF_VECTOR_ID		5
#define TIMER2_CTC_VECTOR_ID		4




/* TIMER0 */
void TIMER0_voidInit (void);
void TIMER0_voidStartTimer(void);
void TIMER0_voidPhaseCorrectPWM(u8 Copy_u8DutyCycle);
void TIMER0_voidFastPWM(u8 Copy_u8DutyCycle);
void TIMER0_voidSetDesiredTime_ms(u32 Copy_Time_ms);

/* TIMER1 */
void TIMER1_voidInit(void);
void TIMER1_voidStartTimer(void);
void TIMER1_voidFastPWM(u8 Copy_u8DutyCycle);
void timer1_wave_fastPWM_A(double value);
void timer1_wave_fastPWM_B(double value);

/* TIMER2 */
void TIMER2_voidInit (void);
void TIMER2_voidStartTimer(void);
void TIMER2_voidPhaseCorrectPWM(u8 Copy_u8DutyCycle);
void TIMER2_voidFastPWM(u8 Copy_u8DutyCycle);
void TIMER2_voidSetDesiredTime_ms(u32 Copy_Time_ms);

/* Call back function for ISR */
void TIMER_voidSetCallBack(void (*Copy_pvCallBackFunc)(void) , u8 Copy_u8VectorID);




#endif /* TIMER_INTERFACE_H_ */
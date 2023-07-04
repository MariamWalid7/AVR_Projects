/*
 * TIMER_private.h
 *
 * Created: 4/17/2023 10:14:06 AM
 *  Author: maria
 */ 


#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

/*********** INT registers *************/
#define SREG   (*(volatile u8*)(0x5F))      
#define TIMSK  (*(volatile u8*)(0x59))
#define TIFR   (*(volatile u8*)(0x58))

/*********** TIMER0 registers *************/
#define TCCR0  (*(volatile u8*)(0x53))
#define TCNT0  (*(volatile u8*)(0x52))
#define OCR0   (*(volatile u8*)(0x5C))

/*********** TIMER1 registers *************/
#define TCCR1A			*((volatile u8*)0X4F)
#define TCCR1B			*((volatile u8*)0X4E)
#define TCNT1H          *((volatile u8 *)(0x4D))
#define TCNT1L          *((volatile u8 *)(0x4C))
#define TCNT1			*((volatile u16*)0X4C)    
#define OCR1AL          *((volatile u8 *)(0x4A))
#define OCR1AH          *((volatile u8 *)(0x4B))
#define OCR1A			*((volatile u16*)0X4A)
#define OCR1BL          *((volatile u8 *)(0x48))
#define OCR1BH          *((volatile u8 *)(0x49))
#define OCR1B			*((volatile u16*)0X48)
#define ICR1H           *((volatile u8 *)(0x47))
#define ICR1L           *((volatile u8 *)(0x46))
#define ICR1			*((volatile u16*)0X46)

/*********** TIMER2 registers *************/
#define TCCR2  (*(volatile u8*)(0x45))
#define TCNT2  (*(volatile u8*)(0x44))
#define OCR2   (*(volatile u8*)(0x43))
#define ASSR   (*(volatile u8*)(0x42))

/*********** INT bits *************/
#define SREG_Ibit                   7

#define TIMSK_OCIE2                 7 
#define TIMSK_TOIE2                 6
#define TIMSK_TICIE1                5
#define TIMSK_OCIE1A                4
#define TIMSK_OCIE1B                3
#define TIMSK_TOIE1                 2
#define TIMSK_OCIE0                 1
#define TIMSK_TOIE0                 0

#define TIFR_OCF2                   7
#define TIFR_TOV2                   6
#define TIFR_ICF1                   5
#define TIFR_OCF1A                  4
#define TIFR_OCF1B                  3
#define TIFR_TOV1                   2
#define TIFR_OCF0                   1
#define TIFR_TOV0                   0

/*********** TIMER0 bits *************/

#define TCCR0_FOC0                  7
#define TCCR0_WGM00                 6
#define TCCR0_COM01                 5
#define TCCR0_COM00                 4
#define TCCR0_WGM01                 3
#define TCCR0_CS02                  2
#define TCCR0_CS01                  1
#define TCCR0_CS00                  0

/*********** TIMER1 bits *************/

#define TCCR1A_COM1A1		7
#define TCCR1A_COM1A0		6
#define TCCR1A_COM1B1		5
#define TCCR1A_COM1B0		4
#define TCCR1A_WGM11		1
#define TCCR1A_WGM10		0

#define TCCR1B_ICNC1		7
#define TCCR1B_ICES1		6
#define TCCR1B_WGM13		4
#define TCCR1B_WGM12		3

/*********** TIMER2 bits *************/
#define TCCR2_FOC2                  7
#define TCCR2_WGM20                 6
#define TCCR2_COM21                 5
#define TCCR2_COM20                 4
#define TCCR2_WGM21                 3
#define TCCR2_CS22                  2
#define TCCR2_CS21                  1
#define TCCR2_CS20                  0

#define ASSR_AS2                    3


/* clk Source  */
#define NO_CLK_SOURCE               0
#define NO_PRESCALLER               1
#define PRESCALLER_8                8
#define PRESCALLER_64               64
#define PRESCALLER_128              128  //Only available for timer2
#define PRESCALLER_256              256
#define PRESCALLER_1024             1024
#define EXTERNAL_CLK_FALLING_EDGE   7
#define EXTERNAL_CLK_RISING_EDGE    8

#define EXTERNAL_CLK_CRYSTAL_OSC    9


#define ENABLED                     1
#define DISABLED                    0

#define RISING                      1
#define FALLING                     0

#define NULL                        0

/* TIMER0 MODES */
#define TIMER0_OVERFLOW_MODE        0
#define TIMER0_CTC_MODE             1
#define TIMER0_PWM_PHCORRECT_MODE   2
#define TIMER0_PWM_FAST_MODE        3

/* OC0 MODES */
// NON PWM 
#define TIMER0_DISCONNECT_OC0      0
#define TIMER0_TOGGLE_OC0          1
#define TIMER0_CLEAR_OC0           2
#define TIMER0_SET_OC0             3

//PWM (FAST & PHASECORRECT)
#define TIMER0_PWM_NONINVERTED_OC0 2
#define TIMER0_PWM_INVERTED_OC0    3


/* TIMER2 MODES */
#define TIMER2_OVERFLOW_MODE        0
#define TIMER2_CTC_MODE             1
#define TIMER2_PWM_PHCORRECT_MODE   2
#define TIMER2_PWM_FAST_MODE        3

/* OC0 MODES */
// NON PWM
#define TIMER2_DISCONNECT_OC2      0
#define TIMER2_TOGGLE_OC2          1
#define TIMER2_CLEAR_OC2           2 
#define TIMER2_SET_OC2             3

//PWM (FAST & PHASECORRECT)
#define TIMER2_PWM_NONINVERTED_OC2 2
#define TIMER2_PWM_INVERTED_OC2    3

/* OCR1 MODES */
#define TIMER_OC_DISCONNECTED      0
#define TIMER_CLR_ON_CTC_SET_ON_TOP 1
#define TIMER_SET_ON_CTC_CLR_ON_TOP 2
#define TIMER_OC_LOW                3
#define TIMER_OC_HIGH               4
#define TIMER_OC_TOGGLE             5

/*TIMER1 MODES */
#define TIMER1_NORMAL_MODE								0
#define TIMER1_PWM_8_BIT_MODE							1
#define TIMER1_PWM_9_BIT_MODE							2
#define TIMER1_PWM_10_BIT_MODE							3
#define TIMER1_CTC_OCR1A_MODE							4
#define TIMER1_FAST_PWM_8_BIT_MODE						5
#define TIMER1_FAST_PWM_9_BIT_MODE 						6
#define TIMER1_FAST_PWM_10_BIT_MODE						7
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_ICR1_MODE		8
#define TIMER1_PWM_PHASE_AND_FREQ_CORRECT_OCR1A_MODE	9
#define TIMER1_PWM_PHASE_CORRECT_ICR1_MODE				10
#define TIMER1_PWM_PHASE_CORRECT_OCR1A_MODE				11
#define TIMER1_CTC_ICR1_MODE							12
#define TIMER1_FAST_PWM_ICR1_MODE						14
#define TIMER1_FAST_PWM_OCR1A_MODE						15

 


#endif /* TIMER_PRIVATE_H_ */
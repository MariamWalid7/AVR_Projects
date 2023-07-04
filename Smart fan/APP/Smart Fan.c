/*
 * LM35 with negative.c
 *
 * Created: 3/13/2023 10:41:30 PM
 *  Author: maria
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "ADC_config.h"
#include "ADC_interfaceh.h"
#include "ADC_private.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"

#define F_CPU 8000000UL
#include <util/delay.h>

u16 volt, Temp ;

int main(void)
{
	CLCD_voidInit();
	ADC_voidInit();
	TIMER0_voidInit();
	
	DIO_enumSetPinDirection(DIO_u8_PORTB, DIO_u8_PIN4, DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection(DIO_u8_PORTB, DIO_u8_PIN5, DIO_u8_PIN_OUTPUT);
	
    while(1)
    {
		//DIO_enumSetPinValue(DIO_u8_PORTB, DIO_u8_PIN5, DIO_u8_PIN_HIGH);
		
        volt = (ADC_u16Read()*2.5);
		
        if (volt >= 1000){
			
			Temp = (volt - 1000)/ 10;
			
			if(Temp < 10){
	        
	        CLCD_voidSend_1_Digit (Temp);
			
			DIO_enumSetPinValue(DIO_u8_PORTB, DIO_u8_PIN5, DIO_u8_PIN_LOW);
			TIMER0_voidFastPWM(0);
	        
			}			
        
        else if (Temp < 100){
	        
	        CLCD_voidSend_2_Digits (Temp);
			
			if(Temp >= 25 && Temp <=35){
				
				DIO_enumSetPinValue(DIO_u8_PORTB, DIO_u8_PIN5, DIO_u8_PIN_HIGH);
				TIMER0_voidFastPWM(25);
				_delay_ms(500);
				
			}
			
			else if(Temp >= 35 && Temp <=45){
				
				DIO_enumSetPinValue(DIO_u8_PORTB, DIO_u8_PIN5, DIO_u8_PIN_HIGH);
				TIMER0_voidFastPWM(100);
				_delay_ms(500);
				
			}
			
	        
        } 
		}
		
		else{
		 
		 Temp = (1000 - volt)/ 10;
		 
		 CLCD_voidSendChar('-');
		 
			if(Temp < 10)
			
			CLCD_voidSend_1_Digit (Temp);
			
			
			else if (Temp < 100){
				
				CLCD_voidSend_2_Digits (Temp);
				
			} 			
		 
    }
}
	}
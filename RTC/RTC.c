/*
 * RTC.c
 *
 * Created: 4/29/2023 1:11:33 AM
 *  Author: maria
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "seven segment.h"
#include "LCD.h"
#include "keypad_driver.h"
#include "std_macros.h"
#define F_CPU 8000000UL
#include <util/delay.h>

volatile unsigned char sec_counter = 0;
unsigned char min_counter = 0;
unsigned char hr_counter = 0; 
unsigned char value, FirstDigit, SecondDigit;

int main(void)
{
	
	keypad_vInit();
	LCD_vInit();
	seven_seg_vinit('B');
	
	SET_BIT(DDRC,0);
	SET_BIT(DDRC,1);
	SET_BIT(DDRC,2);
	SET_BIT(DDRC,3);
	SET_BIT(DDRC,4);
	SET_BIT(DDRC,5);
	SET_BIT(DDRC,6);
	SET_BIT(DDRC,7);
	
	LCD_vSend_string("Press 1 to ");
	LCD_movecursor(2,1);
	LCD_vSend_string("Set Clock");
	
	timer2_overflow_init_interrupt();
    while(1)
    {
		value = keypad_u8check_press();
		
        if (value != NOTPRESSED){
			
			if (value == '1'){
				
			LCD_clearscreen();
			LCD_vSend_string("hours=--");
			LCD_movecursor(1,7);
			
			do{
					
				FirstDigit = keypad_u8check_press();
			}while (FirstDigit == NOTPRESSED);
			LCD_vSend_char(FirstDigit);
			_delay_ms(300);
			
			do{
				
				SecondDigit = keypad_u8check_press();
			}while (SecondDigit == NOTPRESSED);
			LCD_vSend_char(SecondDigit);
			_delay_ms(300);
			
			hr_counter = (SecondDigit - 48) + 10*(FirstDigit - 48);
			
			LCD_clearscreen();
			LCD_vSend_string("minutes=--");
			LCD_movecursor(1,9);
			
			do{
				
				FirstDigit = keypad_u8check_press();
			}while (FirstDigit == NOTPRESSED);
			LCD_vSend_char(FirstDigit);
			_delay_ms(300);
			
			do{
				
				SecondDigit = keypad_u8check_press();
			}while (SecondDigit == NOTPRESSED);
			LCD_vSend_char(SecondDigit);
			_delay_ms(300);
			
			min_counter = (SecondDigit - 48) + 10*(FirstDigit - 48);
			
			LCD_clearscreen();
			LCD_vSend_string("sec=--");
			LCD_movecursor(1,5);
			
			do{
				
				FirstDigit = keypad_u8check_press();
			}while (FirstDigit == NOTPRESSED);
			LCD_vSend_char(FirstDigit);
			_delay_ms(300);
			
			do{
				
				SecondDigit = keypad_u8check_press();
			}while (SecondDigit == NOTPRESSED);
			LCD_vSend_char(SecondDigit);
			_delay_ms(300);
			
			sec_counter = (SecondDigit - 48) + 10*(FirstDigit - 48);
			
			LCD_clearscreen();
			LCD_vSend_string("Press 1 to ");
			LCD_movecursor(2,1);
			LCD_vSend_string("Set Clock");
			
		} 
		
		else {
		LCD_vSend_string("Wrong Choice");
		_delay_ms(1000);
		LCD_clearscreen();
		LCD_vSend_string("press 1 to");
		LCD_movecursor(2,1);
		LCD_vSend_string("set clock");
		}
					
    }
	
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,0);
		seven_seg_write('B',sec_counter%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,1);
		seven_seg_write('B',sec_counter/10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,2);
		seven_seg_write('B',min_counter%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,4);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,3);
		seven_seg_write('B',min_counter/10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,5);
		CLR_BIT(PORTC,4);
		seven_seg_write('B',hr_counter%10);
		_delay_ms(5);
		
		SET_BIT(PORTC,0);
		SET_BIT(PORTC,1);
		SET_BIT(PORTC,2);
		SET_BIT(PORTC,3);
		SET_BIT(PORTC,4);
		CLR_BIT(PORTC,5);
		seven_seg_write('B',hr_counter/10);
		_delay_ms(5);
		
		if(sec_counter == 60){
			
			sec_counter = 0;
			min_counter++;
		}
		
		if(min_counter == 60){
			
			min_counter = 0;
			hr_counter++;
		}
		
		if(hr_counter == 24){
			
			hr_counter = 0;
		}
}
			}

ISR(TIMER2_OVF_vect)
{
	sec_counter++;
	
}
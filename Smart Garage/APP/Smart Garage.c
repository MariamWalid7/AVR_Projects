/*
 * Smart_Garage.c
 *
 * Created: 4/29/2023 3:34:24 AM
 *  Author: maria
 */ 


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"

#define F_CPU 1000000UL
#include <util/delay.h>

int main(void)
{
	u8 flag1 = 0;
	u8 flag2 = 0;
	u8 counter = 0;
	u8 *IR1, *IR2;
	//u8 *local_ptr = 0;
	
	CLCD_voidInit();
	
	CLCD_voidSendString("There's 0 cars");
	CLCD_voidMoveCursor(2,1);
	CLCD_voidSendString("There's space");
	
	DIO_enumSetPinDirection(DIO_u8_PORTD, DIO_u8_PIN0, DIO_u8_PIN_INPUT);
	DIO_enumSetPinDirection(DIO_u8_PORTD, DIO_u8_PIN1, DIO_u8_PIN_INPUT);
	
	 
	
	
    while(1)
    {
      DIO_enumGetPinvalue(DIO_u8_PORTD, DIO_u8_PIN0, *IR1);  
	  
	   if(IR1==1 && flag1==0 && counter<3)
	   {
		   counter++;
		   CLCD_voidMoveCursor(1,11);
		   CLCD_voidSendChar(counter+48);
		   flag1=1;
		   if(counter==3)
		   {
			   CLCD_voidClearScreen();
			   CLCD_voidSendString("there are 3 cars");
			   CLCD_voidMoveCursor(2,1);
			   CLCD_voidSendString("garage is full");
		   }
		   timer1_wave_fastPWM_B(0.999999);
		   _delay_ms(1000);
		   timer1_wave_fastPWM_B(1.499999);
	   }
	   else if(IR1==0)
	   {
		   flag1=0;
	   }
	   
	   DIO_enumGetPinvalue(DIO_u8_PORTD, DIO_u8_PIN1, *IR2);
	   
	   if(IR2==1 && flag2==0 && counter<0)
	   {
		   counter--;
		   CLCD_voidMoveCursor(1,11);
		   CLCD_voidSendChar(counter+48);
		   flag2=1;
		   
		   CLCD_voidClearScreen();
		   CLCD_voidSendString("there are ");
		   CLCD_voidSendChar(counter+48);
		   CLCD_voidSendString(" cars");
		   CLCD_voidMoveCursor(2,1);
		   CLCD_voidSendString("garage has space");
		   timer1_wave_fastPWM_A(0.999999);
		   _delay_ms(1000);
		   timer1_wave_fastPWM_A(1.499999);
	   }
	   else if(IR2==0)
	   {
		   flag2=0;
	   }
	   
    }
}
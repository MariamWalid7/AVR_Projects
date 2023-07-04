/*
 * ********************************** CLCD_program.c ************************************
 *  Author: maria
 *  Layer: HAL
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"


void CLCD_voidSendCmd (u8 copy_u8Cmd){
	
	#if CLCD_MODE == 8
	
	DIO_enumSetPortValue(CLCD_DATA_PORT, copy_u8Cmd); 
	
	DIO_enumSetPinValue (CLCD_CONTROL_PORT, CLCD_RS, DIO_u8_PIN_LOW);
	DIO_enumSetPinValue (CLCD_CONTROL_PORT, CLCD_RW, DIO_u8_PIN_LOW);
	
	CLCD_voidSendFallingEdge();
	
	
	#elif CLCD_MODE == 4
	
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_u8_PIN_LOW  );
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_u8_PIN_LOW  );
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,Copy_u8Command>>4);             // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,Copy_u8Command);                // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();	
	
	#endif
	
	_delay_ms(1);
}


void CLCD_voidInit (void){
	
	/* set data and control pins as output */
	DIO_enumSetPortDirection (CLCD_DATA_PORT, DIO_u8_PORT_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_RS, DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_RW, DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_EN, DIO_u8_PIN_OUTPUT);
	
	#if CLCD_MODE == 8
	
	_delay_ms(50); //wait for more than 30ms after power on
	
	CLCD_voidSendCmd (EIGHT_BITS_MODE); //set 8 bit mode
	
	_delay_us(50); //wait more than 39us after function set
	
	CLCD_voidSendCmd (CLCD_DISPLAYON_CURSOROFF); //display on/off control
	
	_delay_us(50); //wait more than 39us 
	
	CLCD_voidSendCmd (CLCD_CLEAR_DISPLAY); //display clear
	
	_delay_ms(5); //wait for more than 1.53ms after display clear
	
	CLCD_voidSendCmd (CLCD_ENTRY_MODE); //entry mode
	
	_delay_ms(1);
	
	#elif CLCD_MODE == 4
	
	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);
	DIO_enumSetPinDirection  (CLCD_DATA_PORT,DIO_u8_PIN4,DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_DATA_PORT,DIO_u8_PIN5,DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_DATA_PORT,DIO_u8_PIN6,DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_DATA_PORT,DIO_u8_PIN7,DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT , CLCD_RS , DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT , CLCD_RW , DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT , CLCD_EN , DIO_u8_PIN_OUTPUT);



	/*return home*/
	CLCD_voidSendCmd(CLCD_RETURN_HOME);
	_delay_ms(30);

	/*FUNCTION SET Command*/
	CLCD_voidSendCmd(FOUR_BITS_MODE); // 4 Bit Mode
	_delay_ms(1);

	/* DISPLAY & Cursor (ON / OFF) Control */
	CLCD_voidSendCmd(CLCD_DISPLAYON_CURSOROFF);
	_delay_ms(1);

	/* DISPLAY CLEAR */
	CLCD_voidSendCmd(CLCD_CLEAR_DISPLAY);

	/* ENTRY MODE  Set*/
	CLCD_voidSendCmd(CLCD_ENTRY_MODE);
	_delay_ms(1);	
   #endif
	
}


void CLCD_voidSendChar (u8 copy_u8Char){
	
   #if CLCD_MODE == 8
		
   DIO_enumSetPortValue(CLCD_DATA_PORT, copy_u8Char);
		
   DIO_enumSetPinValue (CLCD_CONTROL_PORT, CLCD_RS, DIO_u8_PIN_HIGH);
   DIO_enumSetPinValue (CLCD_CONTROL_PORT, CLCD_RW, DIO_u8_PIN_LOW);
		
   CLCD_voidSendFallingEdge();
		
		
	#elif CLCD_MODE == 4
	
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_u8_PIN_HIGH );
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_u8_PIN_LOW  );
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,(Copy_u8Data>>4));            // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,Copy_u8Data);               // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();	
		
  #endif
_delay_ms(1);	
	
}

void CLCD_voidSendString (u8 *copy_u8PtrString){
	
	u8 LOC_u8Counter = 0;
	
	while(copy_u8PtrString[LOC_u8Counter] != '\0'){
		
		CLCD_voidSendChar(copy_u8PtrString[LOC_u8Counter]);
		
		LOC_u8Counter++;
	}
}


void CLCD_voidMoveCursor (u8 copy_u8Row, u8 copy_u8Column){
	
		u8 LOC_u8Data;
		if(copy_u8Row>2 || copy_u8Row<1 || copy_u8Column>16 || copy_u8Column<1){
			LOC_u8Data = 0x80;
		}
		else if(copy_u8Row==1){
			LOC_u8Data = 0x80+copy_u8Column-1;
		}
		else if (copy_u8Row==2){
			LOC_u8Data = 0XC0+copy_u8Column-1;
		}
		CLCD_voidSendCmd(LOC_u8Data);
		_delay_ms(1);
	
	
}

void CLCD_voidSend_1_Digit (u8 copy_u8Digit){ 
	
	CLCD_voidSendChar(copy_u8Digit+48);
	_delay_ms(1);
}

void CLCD_voidSend_2_Digits (u8 copy_u8Digit){ 
	
	CLCD_voidSendChar((copy_u8Digit/10)+48);
	CLCD_voidSendChar((copy_u8Digit%10)+48);
	_delay_ms(1);
}




void CLCD_voidSendFallingEdge (void){
	
	DIO_enumSetPinValue (CLCD_CONTROL_PORT, CLCD_EN, DIO_u8_PIN_HIGH);
	_delay_ms(2);
	DIO_enumSetPinValue (CLCD_CONTROL_PORT, CLCD_EN, DIO_u8_PIN_LOW);
	_delay_ms(2);
	
}
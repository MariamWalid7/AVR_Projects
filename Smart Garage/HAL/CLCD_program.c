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


void CLCD_voidSendCommand (u8 copy_u8Cmd){
	
	#if CLCD_MODE == 8
	
	DIO_enumSetPortValue(CLCD_DATA_PORT, copy_u8Cmd); 
	
	DIO_enumSetPinValue (CLCD_CONTROL_PORT, CLCD_RS, DIO_u8_PIN_LOW);
	DIO_enumSetPinValue (CLCD_CONTROL_PORT, CLCD_RW, DIO_u8_PIN_LOW);
	
	CLCD_voidSendFallingEdge();
	
	
	#elif CLCD_MODE == 4
	
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RS , DIO_u8_PIN_LOW  );
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_RW , DIO_u8_PIN_LOW  );
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,copy_u8Cmd>>4);             // send the most 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,copy_u8Cmd);                // send the least 4 bits of data to high nibbles
	CLCD_voidSendFallingEdge();	
	
	#endif
	
	_delay_ms(1);
}


void CLCD_voidInit (void){
	
	#if   CLCD_MODE == 8

	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);

	// All Pins as OutPut pins
	DIO_enumSetPortDirection (CLCD_DATA_PORT, DIO_u8_PORT_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_RS, DIO_u8_PORT_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_RW, DIO_u8_PORT_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_EN, DIO_u8_PORT_OUTPUT);

	/* Return cursor to the first position on the first line  */
	CLCD_voidSendCommand(lcd_Home);
	_delay_ms(1);

	/*FUNCTION SET Command : 2 lines , 5*8 font size */
	CLCD_voidSendCommand( EIGHT_BITS ); // 8 Bit Mode ==> 0x38
	_delay_ms(1); // wait more than 39 Ms

	/* DISPLAY & Cursor (ON / OFF) Control */
	CLCD_voidSendCommand( lcd_DisplayOn_CursorOff );
	_delay_ms(1);

	/* DISPLAY CLEAR */
	CLCD_voidClearScreen();

	/* ENTRY MODE  SET*/
	CLCD_voidSendCommand( lcd_EntryMode );
	_delay_ms(1);



	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      4 Bits Mode       >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

	#elif   CLCD_MODE == 4

	// 1- must wait more than 30 ms before any action (VDD rises to 4.5 v)
	_delay_ms(50);
	DIO_enumSetPinDirection      (CLCD_DATA_PORT,DIO_u8_PIN4,DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection      (CLCD_DATA_PORT,DIO_u8_PIN5,DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection      (CLCD_DATA_PORT,DIO_u8_PIN6,DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection      (CLCD_DATA_PORT,DIO_u8_PIN7,DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_RS, DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_RW, DIO_u8_PIN_OUTPUT);
	DIO_enumSetPinDirection  (CLCD_CONTROL_PORT, CLCD_EN, DIO_u8_PIN_OUTPUT);



	/*return home*/
	CLCD_voidSendCommand( lcd_Home );
	_delay_ms(30);

	/*FUNCTION SET Command*/
	CLCD_voidSendCommand( FOUR_BITS ); // 4 Bit Mode
	_delay_ms(1);

	/* DISPLAY & Cursor (ON / OFF) Control */
	CLCD_voidSendCommand( lcd_DisplayOn_CursorOff );
	_delay_ms(1);

	/* DISPLAY CLEAR */
	CLCD_voidClearScreen();

	/* ENTRY MODE  Set*/
	CLCD_voidSendCommand( lcd_EntryMode );
	_delay_ms(1);


	#endif
	
}


void CLCD_voidSendChar (u8 copy_u8Char){
	
	#if   CLCD_MODE == 8

	DIO_enumSetPortValue (CLCD_DATA_PORT, copy_u8Char);
	DIO_enumSetPinValue  (CLCD_CONTROL_PORT, CLCD_RS, DIO_u8_PIN_HIGH);
	DIO_enumSetPinValue  (CLCD_CONTROL_PORT, CLCD_RW, DIO_u8_PIN_LOW );
	CLCD_voidSendFallingEdge();

	
	#elif   CLCD_MODE == 4

	DIO_enumSetPinValue  (CLCD_CONTROL_PORT, CLCD_RS, DIO_u8_PIN_HIGH);
	DIO_enumSetPinValue  (CLCD_CONTROL_PORT, CLCD_RW, DIO_u8_PIN_LOW);
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,(copy_u8Char>>4));            
	CLCD_voidSendFallingEdge();
	DIO_voidWriteHighNibbles (CLCD_DATA_PORT ,copy_u8Char);               
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
		CLCD_voidSendCommand(LOC_u8Data);
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




static void CLCD_voidSendFallingEdge (void){
	
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_EN , DIO_u8_PIN_HIGH );
	_delay_ms(1);
	DIO_enumSetPinValue  ( CLCD_CONTROL_PORT , CLCD_EN , DIO_u8_PIN_LOW  );
	_delay_ms(1);
	
}

void CLCD_voidClearScreen(void){
	
		CLCD_voidSendCommand(lcd_Clear);
		_delay_ms(10); //wait more than 1.53 ms
}
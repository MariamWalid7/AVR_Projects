/*
 * ********************************** CLCD_interface.h ************************************
 *  Author: maria
 *  Layer: HAL
 */ 


#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#include "CLCD_config.h"

/*  Defining modes */ 
#if CLCD_MODE == 8
#define EIGHT_BITS_MODE 0x38
#elif CLCD_MODE == 4
#define FOUR_BITS_MODE 0x28 
#endif



/* CLCD Commands */ 
#define CLCD_CLEAR_DISPLAY          0x01
#define CLCD_RETURN_HOME            0x02
#define CLCD_DISPLAYOFF_CURSOROFF   0x08
#define CLCD_DISPLAYON_CURSOROFF    0x0C
#define CLCD_DISPLAYON_CURSORON     0x0E
#define CLCD_DISPLAYON_CURSORBLINK  0x0F
#define CLCD_ENTRY_MODE             0x06



void CLCD_voidSendCmd (u8 copy_u8Cmd);
void CLCD_voidInit (void);
void CLCD_voidSendChar (u8 copy_u8Char);
void CLCD_voidSendString (u8 *copy_u8PtrString);
void CLCD_voidSendFallingEdge (void);
void CLCD_voidMoveCursor (u8 copy_u8Row, u8 copy_u8Column);
void CLCD_voidSend_1_Digit (u8 copy_u8Digit);
void CLCD_voidSend_2_Digits (u8 copy_u8Digit);






#endif /* CLCD_INTERFACE_H_ */
/*
 * ********************************** CLCD_interface.h ************************************
 *  Author: maria
 *  Layer: HAL
 */ 


#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

#include "CLCD_config.h"

/*  Defining modes */ 
#if   CLCD_MODE == 4
#define FOUR_BITS                     0x28          
#elif CLCD_MODE == 8
#define EIGHT_BITS                    0x38          
#endif



/* CLCD Commands */ 
#define lcd_DisplayOn_CursorOff       0x0c          // display on, cursor off, don't blink character
#define lcd_DisplayOn_CursorOn        0x0e          // display on, cursor on, don't blink character
#define lcd_DisplayOff_CursorOff      0x08          // turn display off
#define lcd_Clear                     0x01          //replace all characters with ASCII 'space'
#define lcd_EntryMode                 0x06          // shift cursor from left to right on read/write
#define lcd_Home                      0x02          // return cursor to first position on first line
#define lcd_CGRAM                     0x40          // the first Place/Address at CGRAM
#define lcd_SetCursor                 0x80          // set cursor position
#define lcd_FunctionReset             0x30          // reset the LCD



void CLCD_voidSendCommand (u8 copy_u8Cmd);
void CLCD_voidInit (void);
void CLCD_voidSendChar (u8 copy_u8Char);
void CLCD_voidSendString (u8 *copy_u8PtrString);
void CLCD_voidClearScreen(void);
static void CLCD_voidSendFallingEdge (void);
void CLCD_voidMoveCursor (u8 copy_u8Row, u8 copy_u8Column);
void CLCD_voidSend_1_Digit (u8 copy_u8Digit);
void CLCD_voidSend_2_Digits (u8 copy_u8Digit);






#endif /* CLCD_INTERFACE_H_ */
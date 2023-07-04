/*
 * EEPROM_program.c
 *
 * Created: 9/6/2022 3:08:08 PM
 *  Author: maria
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"

#include <avr/io.h>

void EEPROM_voidWrite(u16 copy_u16Address, u8 copy_u8Data )
{
	/*set up address register*/
	EEARL=(u8)copy_u16Address;
	EEARH=(u8)(copy_u16Address>>8);
	/*set up data register*/
	EEDR=copy_u8Data ;
	/*write logical one to EEMWE*/
	SET_BIT(EECR,EECR_EEMWE);
	/*start EEPROM write by setting EEWE*/
	SET_BIT(EECR,EECR_EEWE);
	/* wait for completion of write operation*/
	while(GET_BIT(EECR,EECR_EEWE)==1);
	
}
u8 EEPROM_u8Read( u16 copy_u16Address )
{
	/*set up address register*/
	EEARL=(u8)copy_u16Address;
	EEARH=(u8)(copy_u16Address>>8);
	/*start EEPROM read by setting EERE*/
	SET_BIT(EECR,EECR_EERE);
	/*return data from data register*/
	return EEDR ;
}

/*u8 EEPROM_u8Read (u16 copy_u16Address){

//set the address
EEARH = (u8)(copy_u16Address>>8);
EEARL = (u8)copy_u16Address;

//set EERE to 1
SET_BIT(EECR, EECR_EERE);

//read data from data register
return EEDR;	
}*/
/*
 * EEPROM_interface.h
 *
 * Created: 9/6/2022 3:07:33 PM
 *  Author: maria
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_
#include "STD_TYPES.h"

/*
 *Function Name : EEPROM_voidWrite
 *Description : write data in specific address in EEPROM
 *Return : void
 *Arguments : u16 Address, u8 Data
 */
void EEPROM_voidWrite (u16 copy_u16Address, u8 copy_u8Data);



/*
 *Function Name : EEPROM_u8Read
 *Description : read data from specific address in EEPROM
 *Return :  u8 Data
 *Arguments : u16 Address
 */
u8 EEPROM_u8Read (u16 copy_u16Address);



#endif /* EEPROM_INTERFACE_H_ */
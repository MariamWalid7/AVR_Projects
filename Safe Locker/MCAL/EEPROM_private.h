/*
 * EEPROM_regs.h
 *
 * Created: 9/6/2022 3:08:54 PM
 *  Author: maria
 */ 


#ifndef EEPROM_REGS_H_
#define EEPROM_REGS_H_

#include "STD_TYPES.h"

/************* registers *****************/
#define EEARH *((volatile u8 *) 0X3F))      
#define EEARL *((volatile u8 *) 0X3E)) 
#define EEDR  *((volatile u8 *) 0X3D)) 
#define EECR  *((volatile u8 *) 0X3C)) 



/***** EECR BITS ******/
#define EECR_EERE  0
#define EECR_EEWE  1
#define EECR_EEMWE 2
#define EECR_EERIE 3









    

#endif /* EEPROM_REGS_H_ */
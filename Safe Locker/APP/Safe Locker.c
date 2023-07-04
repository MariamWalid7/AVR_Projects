/*
 * Safe_Locker.c
 *
 * Created: 4/30/2023 12:00:03 AM
 *  Author: maria
 */ 
#define F_CPU 8000000UL
#include <util/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"

#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

//#include "KPD_config.h"
#include "KPD_interface.h"


#define EEPROM_STATUS_LOCATION 0X20
#define EEEPROM_FIRST_LOCATION 0X21
#define EEPROM_SECOND_LOCATION 0X22
#define EEPROM_THIRD_LOCATION  0X23
#define EEPROM_FOURTH_LOCATION 0X24

#define MAX_TRIES  3

u8 PASSWORD[4];

int main(void)
{
	u8 counter, flag = 0;
	u8 tries = MAX_TRIES;
	u8 KPD_state = NOTPRESSED;
	
	CLCD_voidInit();
	KEYPAD_voidInitialize();
	TIMER0_voidInit();
	
	if(EEPROM_u8Read(EEPROM_STATUS_LOCATION)==NOTPRESSED){
	CLCD_voidSendString("Set pass:");
	for(counter=0; counter<=3; counter++){
		
		do{
			KPD_state = KEYPAD_u8Read();
			
		}while(KPD_state == NOTPRESSED);
		
		CLCD_voidSendChar(KPD_state+48);
		_delay_ms(500);
		CLCD_voidMoveCursor(1,10+counter);
		CLCD_voidSendString("*");
		_delay_ms(500);
		EEPROM_voidWrite(EEEPROM_FIRST_LOCATION+counter,KPD_state);	
	}
	EEPROM_voidWrite(EEPROM_STATUS_LOCATION, 0x00);
	}
	
	while (flag == 0){
		PASSWORD[0] = PASSWORD[1] = PASSWORD[2] = PASSWORD[3] = NOTPRESSED;
		
		CLCD_voidSendCmd(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendString("Check pass:");
		
		for(counter = 0; counter<= 3; counter++){
		do 
		{
			PASSWORD[counter] = KEYPAD_u8Read();
		} while (PASSWORD[counter] == NOTPRESSED);
		 
		CLCD_voidSendChar(PASSWORD[counter]);
		_delay_ms(500);
		CLCD_voidMoveCursor(1,12+counter);
		CLCD_voidSendString("*");
		_delay_ms(500);
		
		}			
	
	
	if(PASSWORD[0]==EEEPROM_FIRST_LOCATION && PASSWORD[1]==EEPROM_SECOND_LOCATION && PASSWORD[2]==EEPROM_THIRD_LOCATION && PASSWORD[3]==EEPROM_FOURTH_LOCATION){
		
		CLCD_voidSendCmd(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendString("Safe is opened");
		TIMER0_voidFastPWM(10);
		
		flag = 1;
	}
	
	else{
		
		tries-=1;
		if(tries > 0){
		CLCD_voidSendCmd(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendString("Wrong password");
		_delay_ms(500);
		CLCD_voidSendCmd(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendString("tries left: ");
		CLCD_voidMoveCursor(1,11);
		CLCD_voidSendChar(tries+48);
		_delay_ms(500);
		}	
		else{
		CLCD_voidSendCmd(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendString("Wrong password");
		CLCD_voidSendCmd(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendString("No tries left:");
		_delay_ms(500);
		CLCD_voidSendCmd(CLCD_CLEAR_DISPLAY);
		CLCD_voidSendString("Safe is closed");
		_delay_ms(500);	
			flag = 1;
		}	
	}
	
		}
	}		
				
	
		

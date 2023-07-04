/*
 * ********************************** CLCD_config.h ************************************
 *  Author: maria
 *  Layer: HAL
 */ 


#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/* Choose LCD mode: ( 8 or 4 bit modes) */

#define CLCD_MODE    4





/* Choose data and control ports */

#define CLCD_DATA_PORT      DIO_u8_PORTA
#define CLCD_CONTROL_PORT   DIO_u8_PORTB




/* Choose control pins */

#define CLCD_RS   DIO_u8_PIN0
#define CLCD_RW   DIO_u8_PIN1
#define CLCD_EN   DIO_u8_PIN2






#endif /* CLCD_CONFIG_H_ */
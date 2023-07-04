/*
 * ***************************************** GPIO_interface.h *****************************************
 *
 * Created: 8/4/2022 1:47:36 AM
 *  Author: maria
 *  Layer: MCAL
 */

typedef enum {
	DIO_NOK,
	DIO_OK
	}DIO_ErrorState;

#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

#define DIO_u8_PORTA 0
#define DIO_u8_PORTB 1
#define DIO_u8_PORTC 2
#define DIO_u8_PORTD 3

#define DIO_u8_PIN0  0
#define DIO_u8_PIN1  1
#define DIO_u8_PIN2  2
#define DIO_u8_PIN3  3
#define DIO_u8_PIN4  4
#define DIO_u8_PIN5  5
#define DIO_u8_PIN6  6
#define DIO_u8_PIN7  7

#define DIO_u8_PIN_OUTPUT 1
#define DIO_u8_PIN_INPUT  0

#define DIO_u8_PIN_HIGH 1
#define DIO_u8_PIN_LOW  0

#define DIO_u8_PORT_OUTPUT  1
#define DIO_u8_PORT_INPUT   0

#define DIO_u8_PORT_HIGH  1
#define DIO_u8_PORT_LOW   0

/* Pins */
DIO_ErrorState DIO_enumSetPinDirection(u8 copy_u8PortName, u8 copy_u8PinNumber, u8 copy_u8Direction);
DIO_ErrorState DIO_enumSetPinValue (u8 copy_u8PortName, u8 copy_u8PinNumber, u8 copy_u8Value);
DIO_ErrorState DIO_enumGetPinvalue(u8 copy_u8PortName, u8 copy_u8PinNumber, u8 *copy_u8PtrData);
DIO_ErrorState DIO_enumTogglePin(u8 copy_u8PortName, u8 copy_u8PinNumber);
void DIO_voidConnectPullup (u8 copy_u8PortName,u8 copy_u8PinNumber, u8 copy_u8Enable);

/* Ports */
DIO_ErrorState DIO_enumSetPortDirection(u8 copy_u8PortName,u8 copy_u8Direction);
DIO_ErrorState DIO_enumSetPortValue (u8 copy_u8PortName,u8 copy_u8Value);
DIO_ErrorState DIO_enumGetPortvalue(u8 copy_u8PortName, u8 *copy_u8PtrData);



#endif /* GPIO_INTERFACE_H_ */
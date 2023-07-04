/* ****************************** GPIO_program.c *************************************
 * Author: maria
 * Layer:  MCAL
 *
 *
 */
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "GPIO_private.h"
#include "GPIO_interface.h"

/*
 * description: function sets the direction of pin (ip/op). 
 * parameters : port name, pin number, direction.
 * return : its state
 *
 */
DIO_ErrorState DIO_enumSetPinDirection( u8 copy_u8PortName, u8 copy_u8PinNumber, u8 copy_u8Direction)
{
	 DIO_ErrorState LOC_enumState = DIO_OK;
	 
	 if((copy_u8PortName <= DIO_u8_PORTD) && (copy_u8PinNumber <= DIO_u8_PIN7)){
	
        switch(copy_u8Direction){
          default : LOC_enumState = DIO_NOK;

          case DIO_u8_PIN_OUTPUT :
           switch(copy_u8PortName){
            case DIO_u8_PORTA : SET_BIT(DDRA, copy_u8PinNumber); break;
            case DIO_u8_PORTB : SET_BIT(DDRB, copy_u8PinNumber); break;
            case DIO_u8_PORTC : SET_BIT(DDRC, copy_u8PinNumber); break;
            case DIO_u8_PORTD : SET_BIT(DDRD, copy_u8PinNumber); break;
            default : break;
   }break;

          case DIO_u8_PIN_INPUT :
           switch (copy_u8PortName){
           case DIO_u8_PORTA : CLR_BIT(DDRA, copy_u8PinNumber); break;
           case DIO_u8_PORTB : CLR_BIT(DDRB, copy_u8PinNumber); break;
           case DIO_u8_PORTC : CLR_BIT(DDRC, copy_u8PinNumber); break;
           case DIO_u8_PORTD : CLR_BIT(DDRD, copy_u8PinNumber); break;
           default : break;
   }break;
  }
	}  
  else {
	 LOC_enumState = DIO_NOK;  
  }
  
  return LOC_enumState;
}


/*
 * description: function sets the value of pin (high/low). 
 * parameters : port name, pin number, value.
 * return : its state
 *
 */
DIO_ErrorState DIO_enumSetPinValue (u8 copy_u8PortName, u8 copy_u8PinNumber, u8 copy_u8Value){
	DIO_ErrorState LOC_enumState = DIO_OK;
	
	if((copy_u8PortName <= DIO_u8_PORTD) && (copy_u8PinNumber <= DIO_u8_PIN7)){
	
       switch(copy_u8Value){
        default: LOC_enumState = DIO_NOK;

        case DIO_u8_PIN_HIGH:
         switch(copy_u8PortName){
          case DIO_u8_PORTA : SET_BIT(PORTA, copy_u8PinNumber); break;
          case DIO_u8_PORTB : SET_BIT(PORTB, copy_u8PinNumber); break;
          case DIO_u8_PORTC : SET_BIT(PORTC, copy_u8PinNumber); break;
          case DIO_u8_PORTD : SET_BIT(PORTD, copy_u8PinNumber); break;
          default : break;
   }break;

       case DIO_u8_PIN_LOW:
        switch(copy_u8PortName){
	      case DIO_u8_PORTA : CLR_BIT(PORTA, copy_u8PinNumber); break;
	      case DIO_u8_PORTB : CLR_BIT(PORTB, copy_u8PinNumber); break;
	      case DIO_u8_PORTC : CLR_BIT(PORTC, copy_u8PinNumber); break;
	      case DIO_u8_PORTD : CLR_BIT(PORTD, copy_u8PinNumber); break;
	      default : break;
  }break;
 }
}
else {
	 LOC_enumState = DIO_NOK;
     } 
return LOC_enumState; 
}


/*
 * description: function reads the value of pin (high,low). 
 * parameters : port name, pin number, pointer to receive the value.
 * return : its state and receives pin value in pointer. 
 *
 */
DIO_ErrorState DIO_enumGetPinvalue(u8 copy_u8PortName, u8 copy_u8PinNumber, u8 *copy_u8PtrData){
     DIO_ErrorState LOC_enumState = DIO_OK;
	 
	 if((copy_u8PortName <= DIO_u8_PORTD) && (copy_u8PinNumber <= DIO_u8_PIN7)){
	 	
       switch (copy_u8PortName){
        case DIO_u8_PORTA : *copy_u8PtrData = GET_BIT(PINA,copy_u8PinNumber); break;
        case DIO_u8_PORTB : *copy_u8PtrData = GET_BIT(PINB,copy_u8PinNumber); break;
        case DIO_u8_PORTC : *copy_u8PtrData = GET_BIT(PINC,copy_u8PinNumber); break;
        case DIO_u8_PORTD : *copy_u8PtrData = GET_BIT(PIND,copy_u8PinNumber); break;
     }
	}	
	else{
	   LOC_enumState = DIO_NOK;	
	} 
return LOC_enumState;
}


/*
 * description: function toggles the value of pin  
 * parameters : port name, pin number
 * return : its state
 *
 */
DIO_ErrorState DIO_enumTogglePin(u8 copy_u8PortName, u8 copy_u8PinNumber){
    DIO_ErrorState LOC_enumState = DIO_OK;	
	
	if(copy_u8PortName <= DIO_u8_PORTD){
		
      switch (copy_u8PortName){  
       case DIO_u8_PORTA : TOG_BIT(PORTA, copy_u8PinNumber); break;
       case DIO_u8_PORTB : TOG_BIT(PORTB, copy_u8PinNumber); break;
       case DIO_u8_PORTC : TOG_BIT(PORTC, copy_u8PinNumber); break;
       case DIO_u8_PORTD : TOG_BIT(PORTD, copy_u8PinNumber); break;
          }
    }
   	else{
	   	LOC_enumState = DIO_NOK;
   	}
   	return LOC_enumState;	
}

/*
 * description: function sets the direction of port (ip/op). 
 * parameters : port name, direction.
 * return : its state
 *
 */
DIO_ErrorState DIO_enumSetPortDirection(u8 copy_u8PortName,u8 copy_u8Direction){
	DIO_ErrorState LOC_enumState = DIO_OK;
	
	if(copy_u8PortName <= DIO_u8_PORTD){
		
       switch(copy_u8Direction){
	    default: LOC_enumState = DIO_NOK;
        case DIO_u8_PORT_OUTPUT:
         switch(copy_u8PortName){
          case DIO_u8_PORTA : DDRA = 0xff; break;
          case DIO_u8_PORTB : DDRB = 0xff; break;
          case DIO_u8_PORTC : DDRC = 0xff; break;
          case DIO_u8_PORTD : DDRD = 0xff; break;
    } break;

       case DIO_u8_PORT_INPUT:
        switch(copy_u8PortName)	{
	     case DIO_u8_PORTA : DDRA = 0x00; break;
	     case DIO_u8_PORTB : DDRB = 0x00; break;
	     case DIO_u8_PORTC : DDRC = 0x00; break;
	     case DIO_u8_PORTD : DDRD = 0x00; break;
   } break;
  }
 } 
 else{
	 LOC_enumState = DIO_NOK;
 }
 return LOC_enumState;
}

/*
 * description: function sets the value of port  
 * parameters : port name, value.
 * return : its state
 *
 */
DIO_ErrorState DIO_enumSetPortValue (u8 copy_u8PortName,u8 copy_u8Value){
	
	DIO_ErrorState LOC_enumState = DIO_OK;
	
     if (copy_u8PortName <= DIO_u8_PORTD){ 
	switch(copy_u8PortName){
		case DIO_u8_PORTA : PORTA = copy_u8Value; break;
		case DIO_u8_PORTB : PORTB = copy_u8Value; break;
		case DIO_u8_PORTC : PORTC = copy_u8Value; break;
		case DIO_u8_PORTD : PORTD = copy_u8Value; break;
	}
 }
 else {
	 LOC_enumState = DIO_NOK;
 }
 return LOC_enumState;
}

/*
 * description: function reads the value of port. 
 * parameters : port name, pointer to receive the value
 * return : its state and receives the value of port
 *
 */
DIO_ErrorState DIO_enumGetPortvalue(u8 copy_u8PortName, u8 *copy_u8PtrData){
  DIO_ErrorState LOC_enumState = DIO_OK;
 
 if(copy_u8PortName <= DIO_u8_PORTD){
 
   switch (copy_u8PortName){
    case DIO_u8_PORTA : *copy_u8PtrData = PINA ; break;
	case DIO_u8_PORTB : *copy_u8PtrData = PINB ; break;
	case DIO_u8_PORTC : *copy_u8PtrData = PINC ; break;
	case DIO_u8_PORTD : *copy_u8PtrData = PIND ; break;
   }
  }
  else{
	  LOC_enumState = DIO_NOK;
  }
  return LOC_enumState;
}


/*
 * description: function enables internal pull up. 
 * parameters : port name, pin number enable
 * return : void
 *
 */
void DIO_voidConnectPullup (u8 copy_u8PortName,u8 copy_u8PinNumber, u8 copy_u8Enable){
	switch (copy_u8Enable){
		default : break;
		case 1 :
		switch (copy_u8PortName){
			default : break;
			case DIO_u8_PORTA : SET_BIT(PORTA,copy_u8PinNumber); break;
			case DIO_u8_PORTB : SET_BIT(PORTB,copy_u8PinNumber); break;
			case DIO_u8_PORTC : SET_BIT(PORTC,copy_u8PinNumber); break;
			case DIO_u8_PORTD : SET_BIT(PORTD,copy_u8PinNumber); break;
		} break;
		case 0 :
		switch (copy_u8PortName){
			default : break;
			case DIO_u8_PORTA : CLR_BIT(PORTA,copy_u8PinNumber); break;
			case DIO_u8_PORTB : CLR_BIT(PORTB,copy_u8PinNumber); break;
			case DIO_u8_PORTC : CLR_BIT(PORTC,copy_u8PinNumber); break;
			case DIO_u8_PORTD : CLR_BIT(PORTD,copy_u8PinNumber); break;
		} break;
	}
}


DIO_ErrorState DIO_voidWriteHighNibbles(u8 Copy_u8PORT,u8 Copy_u8value){


	DIO_ErrorState LOC_enumState = DIO_OK ;

	if ( (Copy_u8PORT <= DIO_u8_PORTD))
	{
		Copy_u8value = (Copy_u8value<<4) ;
		switch(Copy_u8PORT)
		{
			case DIO_u8_PORTA :
			PORTA &= 0x0f;                   // make sure the high bits = 0000
			PORTA |= Copy_u8value;			//Set only the high nibble of the port A by the given value
			break ;
			case DIO_u8_PORTB:
			PORTB &= 0x0f;                 //Set only the high nibble of the port B by the given value
			PORTB |= Copy_u8value;
			break ;
			case DIO_u8_PORTC :
			PORTC &= 0x0f;                 //Set only the high nibble of the port C by the given value
			PORTC |= Copy_u8value;
			break ;
			case DIO_u8_PORTD:
			PORTD &= 0x0f;                 //Set only the high nibble of the port D by the given value
			PORTD |= Copy_u8value;
			break ;
			default: break ;

		}
	}
	else
	{
		LOC_enumState = DIO_NOK;
	}

	return LOC_enumState ;

}


DIO_ErrorState DIO_voidWriteLowNibbles(u8 Copy_u8PORT,u8 Copy_u8value){

	DIO_ErrorState LOC_enumState = DIO_OK ;


	if ( (Copy_u8PORT <= DIO_u8_PORTD))
	{
		Copy_u8value &= 0x0f;
		switch(Copy_u8PORT)
		{
			case DIO_u8_PORTA :
			PORTA &= 0xf0;                 //Set only the high nibble of the port A by the given value
			PORTA |= Copy_u8value;
			break ;
			case DIO_u8_PORTB:
			PORTB &= 0xf0;                 //Set only the high nibble of the port B by the given value
			PORTB |= Copy_u8value;
			break ;
			case DIO_u8_PORTC :
			PORTC &= 0xf0;                 //Set only the high nibble of the port C by the given value
			PORTC |= Copy_u8value;
			break ;
			case DIO_u8_PORTD:
			PORTD &= 0xf0;                 //Set only the high nibble of the port D by the given value
			PORTD |= Copy_u8value;
			break ;
			default: break ;

		}


	}
	else
	{
		LOC_enumState = DIO_NOK;
	}

	return LOC_enumState ;

}
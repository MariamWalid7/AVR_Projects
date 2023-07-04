/*
 * ADC_program.c
 *
 * Created: 3/6/2023 5:05:38 PM
 *  Author: maria
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "ADC_interfaceh.h"
#include "ADC_config.h"
#include "ADC_private.h"


void ADC_voidInit (void){
	
	/* Configure Vref */
	#if ADC_VREF == VREF_2_56
	SET_BIT(ADMUX,REFS0); 
	SET_BIT(ADMUX,REFS1);
	
	#elif ADC_VREF == VREF_AVCC 
	CLR_BIT(ADMUX,REFS1);
	SET_BIT(ADMUX,REFS0);
	
	#elif ADC_VREF == VREF_AREF
	CLR_BIT(ADMUX,REFS1);
	CLR_BIT(ADMUX,REFS0);
	
	#else
	#error "Wrong ADC_VREF config."
	
	#endif
	
	
	
	/* configure adc channel */
	#if ADC_CHANNEL == ADC_PA0 
	CLR_BIT(ADMUX, MUX0); 
	CLR_BIT(ADMUX, MUX1); 
	CLR_BIT(ADMUX, MUX2); 
	CLR_BIT(ADMUX, MUX3); 
	CLR_BIT(ADMUX, MUX4); 
	
	
	#elif ADC_CHANNEL == ADC_PA1
	SET_BIT(ADMUX, MUX0);
	CLR_BIT(ADMUX, MUX1);
	CLR_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX4);
	
	#elif ADC_CHANNEL == ADC_PA2
	SET_BIT(ADMUX, MUX1);
	CLR_BIT(ADMUX, MUX0);
	CLR_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX4);
	
	#elif ADC_CHANNEL == ADC_PA3
	SET_BIT(ADMUX, MUX1);
	SET_BIT(ADMUX, MUX0);
	CLR_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX4);
		
	#elif ADC_CHANNEL == ADC_PA4
	CLR_BIT(ADMUX, MUX1);
	SET_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX0);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX4);
	
	#elif ADC_CHANNEL == ADC_PA5
	SET_BIT(ADMUX, MUX0);
	SET_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX1);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX4);
	
	#elif ADC_CHANNEL == ADC_PA6
	SET_BIT(ADMUX, MUX1);
	SET_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX0);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX4);
	
	#elif ADC_CHANNEL == ADC_PA7
	SET_BIT(ADMUX, MUX1);
	SET_BIT(ADMUX, MUX2);
	SET_BIT(ADMUX, MUX0);
	CLR_BIT(ADMUX, MUX3);
	CLR_BIT(ADMUX, MUX4);
	
	#elif ADC_CHANNEL == ADC_Differential_9
	CLR_BIT(ADMUX, MUX0);
	CLR_BIT(ADMUX, MUX1);
	CLR_BIT(ADMUX, MUX2);
	CLR_BIT(ADMUX, MUX3);
	SET_BIT(ADMUX, MUX4);
	
	#else
	#error "Wrong ADC_CHANNEL config"
	
	#endif				
	  
	/* enable adc */
	#if ADC_ENABLE == ADC_ENABLED
	SET_BIT(ADCSRA, ADEN);
	
	#elif ADC_ENABLE == ADC_DISABLED
	CLR_BIT(ADCSRA, ADEN);
	
	#else
	#error "Wrong ADC_ENABLE config."
	
	#endif

	/* adjust clock prescaler */
	#if ADC_PRESCALER == ADC_PRESCALLER_2
	CLR_BIT(ADCSRA,ADPS0);
	CLR_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
	
	#elif ADC_PRESCALER == ADC_PRESCALLER_4
	CLR_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);
	
	#elif ADC_PRESCALER == ADC_PRESCALLER_8
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	CLR_BIT(ADCSRA,ADPS2);	
	
    #elif ADC_PRESCALER == ADC_PRESCALLER_16
    CLR_BIT(ADCSRA,ADPS0);
    CLR_BIT(ADCSRA,ADPS1);
    SET_BIT(ADCSRA,ADPS2);
	
    #elif ADC_PRESCALER == ADC_PRESCALLER_32
    SET_BIT(ADCSRA,ADPS0);
    CLR_BIT(ADCSRA,ADPS1);
    SET_BIT(ADCSRA,ADPS2);
	
   #elif ADC_PRESCALER == ADC_PRESCALLER_64
   CLR_BIT(ADCSRA,ADPS0);
   SET_BIT(ADCSRA,ADPS1);
   SET_BIT(ADCSRA,ADPS2);
   
   #elif ADC_PRESCALER == ADC_PRESCALLER_128
   SET_BIT(ADCSRA,ADPS0);
   SET_BIT(ADCSRA,ADPS1);
   SET_BIT(ADCSRA,ADPS2);
   
   #else
   #error "Wrong ADC_PRESCALER config."
   
   #endif 
   
   #if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
   CLR_BIT(ADCSRA, ADLAR);
   
   #elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
   SET_BIT(ADCSRA, ADLAR);
   
   #else
   #error "Wrong ADC_ADJUSTMENT config."
   
   #endif
         	
				
}

u16 ADC_u16Read (void){
	
	u16 LOC_u16ReadVal;

	SET_BIT(ADCSRA, ADSC);  //start conversion
	
	while(GET_BIT(ADCSRA,ADIF)==0); //do nothing till ADIF becomes zero
	SET_BIT(ADCSRA, ADIF);//clear flag bit
	
	#if ADC_ADJUSTMENT == RIGHT_ADJUSTMENT
	LOC_u16ReadVal = (ADCL|(ADCH<<8)); 
	
	#elif ADC_ADJUSTMENT == LEFT_ADJUSTMENT
	LOC_u16ReadVal = ADCH; 
	
	#endif
	
	return LOC_u16ReadVal;
}
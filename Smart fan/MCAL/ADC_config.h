/*
 * ADC_config.h
 *
 * Created: 3/6/2023 5:06:32 PM
 *  Author: maria
 */ 


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*
Options:
1- ADC_ENABLED
2- ADC_DISABLED
*/
#define ADC_ENABLE              ADC_ENABLED







/*
Options:
1- ADC_INT_DISABLED
2- ADC_INT_ENABLED
*/
#define ADC_INT_ENABLE          ADC_INT_DISABLED



/*
Options:
1- ADC_PA0
2- ADC_PA1
3- ADC_PA2
4- ADC_PA3
5- ADC_PA4
6- ADC_PA5
7- ADC_PA6
8- ADC_PA7
9- ADC_Differential_9
*/
#define ADC_CHANNEL             ADC_Differential_9





/*
Options:
1- VREF_2_56
2- VREF_AVCC
3- VREF_AREF
*/
#define ADC_VREF                VREF_2_56




/*
Options:
1- ADC_PRESCALLER_2
2- ADC_PRESCALLER_4
3 -ADC_PRESCALLER_8
4- ADC_PRESCALLER_16
5- ADC_PRESCALLER_32
6- ADC_PRESCALLER_64
7- ADC_PRESCALLER_128
*/
#define ADC_PRESCALER           ADC_PRESCALLER_32





/*
Options:
1- RIGHT_ADJUSTMENT
2- LEFT_ADJUSTMENT
*/
#define ADC_ADJUSTMENT          RIGHT_ADJUSTMENT




/*Options:
1- SINGLE_CONVERSION
2- FREE_RUNNING
*/
#define ADC_CONVERSION_MODE     SINGLE_CONVERSION






#endif /* ADC_CONFIG_H_ */
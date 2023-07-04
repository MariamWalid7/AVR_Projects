/*
 * ADC_interfaceh.h
 *
 * Created: 3/6/2023 5:06:05 PM
 *  Author: maria
 */ 


#ifndef ADC_INTERFACEH_H_
#define ADC_INTERFACEH_H_


#define ADC_DISABLED         0
#define ADC_ENABLED          1



#define ADC_INT_DISABLED     0
#define ADC_INT_ENABLED      1




#define  ADC_PA0             0
#define  ADC_PA1             1
#define  ADC_PA2             2
#define  ADC_PA3             3
#define  ADC_PA4             4
#define  ADC_PA5             5
#define  ADC_PA6             6
#define  ADC_PA7             7
#define ADC_Differential_9   8




#define VREF_2_56            0
#define VREF_AVCC            1
#define VREF_AREF            2





#define ADC_PRESCALLER_2     0
#define ADC_PRESCALLER_4     1
#define ADC_PRESCALLER_8     2
#define ADC_PRESCALLER_16    3
#define ADC_PRESCALLER_32    4
#define ADC_PRESCALLER_64    5
#define ADC_PRESCALLER_128   6





#define RIGHT_ADJUSTMENT     0
#define LEFT_ADJUSTMENT      1





#define SINGLE_CONVERSION    0
#define FREE_RUNNING         1





void ADC_voidInit (void);
u16 ADC_u16Read (void);



#endif /* ADC_INTERFACEH_H_ */
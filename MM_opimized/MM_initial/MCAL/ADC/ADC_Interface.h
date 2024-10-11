/*
 * ADC_Interface.h
 *
 * Created: 3/4/2024 11:47:43 PM
 *  Author: oraga
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "ADC_Configuration.h"

void ADC_Initialize(adc_vref voltage , adc_prescaler prescaler);
uint16_t ADC_Read(adc_channel channel);



#endif /* ADC_INTERFACE_H_ */
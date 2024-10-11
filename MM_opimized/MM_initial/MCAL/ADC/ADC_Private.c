/*
 * ADC_Private.c
 *
 * Created: 3/4/2024 11:47:58 PM
 *  Author: oraga
 */ 

#include "ADC_Interface.h"

void ADC_Initialize(adc_vref voltage , adc_prescaler prescaler)
{
	ADMUX |= 0x40;
	ADCSRA |= 0xA7;
}

uint16_t ADC_Read(adc_channel channel)
{
	uint16_t val = 0;

	// Clear the ADC result register by reading it once
	uint16_t dummy = ADC_VAL;

	// Select the ADC channel
	switch (channel)
	{
		case ADC_0:
		ADMUX = (ADMUX & 0xF8) | 0x00; // Clear the channel bits and set ADC0
		break;
		case ADC_1:
		ADMUX = (ADMUX & 0xF8) | 0x01; // Clear the channel bits and set ADC1
		break;
		case ADC_2:
		ADMUX = (ADMUX & 0xF8) | 0x02; // Clear the channel bits and set ADC2
		break;
		case ADC_3:
		ADMUX = (ADMUX & 0xF8) | 0x03; // Clear the channel bits and set ADC3
		break;
		case ADC_4:
		ADMUX = (ADMUX & 0xF8) | 0x04; // Clear the channel bits and set ADC4
		break;
		case ADC_5:
		ADMUX = (ADMUX & 0xF8) | 0x05; // Clear the channel bits and set ADC5
		break;
		case ADC_6:
		ADMUX = (ADMUX & 0xF8) | 0x06; // Clear the channel bits and set ADC6
		break;
		case ADC_7:
		ADMUX = (ADMUX & 0xF8) | 0x07; // Clear the channel bits and set ADC7
		break;
	}

	// Start ADC conversion
	ADCSRA |= (1 << ADSC);

	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));

	// Read the converted value
	val = ADC_VAL;

	return val;
}


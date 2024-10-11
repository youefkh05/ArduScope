/*
 * DIO_Configuration.h
 *
 * Created: 3/4/2024 11:54:33 PM
 *  Author: oraga
 */ 


#ifndef DIO_CONFIGURATION_H_
#define DIO_CONFIGURATION_H_

#include "CPU_CONFIGURATIONS.h"
//#include "DIO_Address.h"
// Renaming PORT
typedef enum
{
	DIO_PORTA = 0,
	DIO_PORTB = 1,
	DIO_PORTC = 2,
	DIO_PORTD = 3
}port;
// Renaming PINS
typedef enum
{
	DIO_PIN0 = 0,
	DIO_PIN1 = 1,
	DIO_PIN2 = 2,
	DIO_PIN3 = 3,
	DIO_PIN4 = 4,
	DIO_PIN5 = 5,
	DIO_PIN6 = 6,
	DIO_PIN7 = 7
}pin;
// Renaming STATE
typedef enum
{
	DIO_INPUT = 0,
	DIO_OUTPUT = 1
}state;
// Renaming STATUS
typedef enum
{
	DIO_LOW = 0,
	DIO_HIGH = 1
}status;

#define DIO_PORT_INPUT  0x00
#define DIO_PORT_OUTPUT 0xFF
#define DIO_PORT_LOW    0x00
#define DIO_PORT_HIGH   0xFF



#endif /* DIO_CONFIGURATION_H_ */
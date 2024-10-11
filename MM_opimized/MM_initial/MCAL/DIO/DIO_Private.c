/*
 * DIO_Private.c
 *
 * Created: 3/4/2024 11:56:34 PM
 *  Author: oraga
 */ 

#include "DIO_Interface.h"

/*------------------------PINS---------------------------*/
void DIO_SetPinDirection(port Port, pin Pin, state State)
{
	switch(State)
	{
		case DIO_INPUT:
		switch (Port)
		{
			case DIO_PORTA:
			CLR_BIT(DDRA, Pin);
			break;
			case DIO_PORTB:
			CLR_BIT(DDRB, Pin);
			break;
			case DIO_PORTC:
			CLR_BIT(DDRC, Pin);
			break;
			case DIO_PORTD:
			CLR_BIT(DDRD, Pin);
			break;
		}
		break;
		case DIO_OUTPUT:
		switch (Port)
		{
			case DIO_PORTA:
			SET_BIT(DDRA, Pin);
			break;
			case DIO_PORTB:
			SET_BIT(DDRB, Pin);
			break;
			case DIO_PORTC:
			SET_BIT(DDRC, Pin);
			break;
			case DIO_PORTD:
			SET_BIT(DDRD, Pin);
			break;
		}
		break;
		default://Error
		break;
	}
}
void DIO_SetPinValue(port Port, pin Pin, status Status)
{
	switch(Status)
	{
		case DIO_LOW:
		switch (Port)
		{
			case DIO_PORTA:
			CLR_BIT(PORTA, Pin);
			break;
			case DIO_PORTB:
			CLR_BIT(PORTB, Pin);
			break;
			case DIO_PORTC:
			CLR_BIT(PORTC, Pin);
			break;
			case DIO_PORTD:
			CLR_BIT(PORTD, Pin);
			break;
		}
		break;
		case DIO_HIGH:
		switch (Port)
		{
			case DIO_PORTA:
			SET_BIT(PORTA, Pin);
			break;
			case DIO_PORTB:
			SET_BIT(PORTB, Pin);
			break;
			case DIO_PORTC:
			SET_BIT(PORTC, Pin);
			break;
			case DIO_PORTD:
			SET_BIT(PORTD, Pin);
			break;
		}
		break;
		default://Error
		break;
	}
}
void DIO_TogglePinValue(port Port, pin Pin)
{
	switch (Port)
	{
		case DIO_PORTA:
		TGL_BIT(PORTA, Pin);
		break;
		case DIO_PORTB:
		TGL_BIT(PORTB, Pin);
		break;
		case DIO_PORTC:
		TGL_BIT(PORTC, Pin);
		break;
		case DIO_PORTD:
		TGL_BIT(PORTD, Pin);
		break;
	}
}
uint8_t DIO_GetPinValue(port Port, pin Pin)
{
	uint8_t data = 0;
	switch(Port)
	{
		case DIO_PORTA:
		data = GET_BIT(PINA, Pin);
		break;
		case DIO_PORTB:
		data = GET_BIT(PINB, Pin);
		break;
		case DIO_PORTC:
		data = GET_BIT(PINC, Pin);
		break;
		case DIO_PORTD:
		data = GET_BIT(PIND, Pin);
		break;
	}
	return data;
}
void DIO_SetPinPullUp(port Port, pin Pin)
{
	switch (Port)
	{
		case DIO_PORTA:
		SET_BIT(PORTA, Pin);
		break;
		case DIO_PORTB:
		SET_BIT(PORTB, Pin);
		break;
		case DIO_PORTC:
		SET_BIT(PORTC, Pin);
		break;
		case DIO_PORTD:
		SET_BIT(PORTD, Pin);
		break;
	}
}
/*------------------------PORT---------------------------*/
void DIO_SetPortDirection(port Port, state State)
{
	switch(State)
	{
		case DIO_INPUT:
		switch (Port)
		{
			case DIO_PORTA:
			DDRA = DIO_PORT_INPUT;
			break;
			case DIO_PORTB:
			DDRB = DIO_PORT_INPUT;
			break;
			case DIO_PORTC:
			DDRC = DIO_PORT_INPUT;
			break;
			case DIO_PORTD:
			DDRD = DIO_PORT_INPUT;
			break;
		}
		break;
		case DIO_OUTPUT:
		switch (Port)
		{
			case DIO_PORTA:
			DDRA = DIO_PORT_OUTPUT;
			break;
			case DIO_PORTB:
			DDRB = DIO_PORT_OUTPUT;
			break;
			case DIO_PORTC:
			DDRC = DIO_PORT_OUTPUT;
			break;
			case DIO_PORTD:
			DDRD = DIO_PORT_OUTPUT;
			break;
		}
		break;
		default://Error
		break;
	}
}
void DIO_SetPortValue(port Port, status Status)
{
	switch(Status)
	{
		case DIO_LOW:
		switch (Port)
		{
			case DIO_PORTA:
			PORTA = DIO_PORT_LOW;
			break;
			case DIO_PORTB:
			PORTB = DIO_PORT_LOW;
			break;
			case DIO_PORTC:
			PORTC = DIO_PORT_LOW;
			break;
			case DIO_PORTD:
			PORTD = DIO_PORT_LOW;
			break;
		}
		break;
		case DIO_HIGH:
		switch (Port)
		{
			case DIO_PORTA:
			PORTA = DIO_PORT_HIGH;
			break;
			case DIO_PORTB:
			PORTB = DIO_PORT_HIGH;
			break;
			case DIO_PORTC:
			PORTC = DIO_PORT_HIGH;
			break;
			case DIO_PORTD:
			PORTD = DIO_PORT_HIGH;
			break;
		}
		break;
		default://Error
		break;
	}
}
void DIO_TogglePortValue(port Port)
{
	switch (Port)
	{
		case DIO_PORTA:
		PORTA ^= DIO_PORT_HIGH;
		break;
		case DIO_PORTB:
		PORTB ^= DIO_PORT_HIGH;
		break;
		case DIO_PORTC:
		PORTC ^= DIO_PORT_HIGH;
		break;
		case DIO_PORTD:
		PORTD ^= DIO_PORT_HIGH;
		break;
	}
}
uint8_t DIO_GetPortValue(port Port)
{
	uint8_t data = 0;
	switch(Port)
	{
		case DIO_PORTA:
		data = PINA;
		break;
		case DIO_PORTB:
		data = PINB;
		break;
		case DIO_PORTC:
		data = PINC;
		break;
		case DIO_PORTD:
		data = PIND;
		break;
	}
	return data;
}
void DIO_SetPortPullUp(port Port)
{
	switch (Port)
	{
		case DIO_PORTA:
		PORTA = DIO_PORT_HIGH;
		break;
		case DIO_PORTB:
		PORTB = DIO_PORT_HIGH;
		break;
		case DIO_PORTC:
		PORTC = DIO_PORT_HIGH;
		break;
		case DIO_PORTD:
		PORTD = DIO_PORT_HIGH;
		break;
	}
}

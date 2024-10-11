/*
 * Interrupt_Private.c
 *
 * Created: 3/4/2024 11:51:33 PM
 *  Author: oraga
 */ 
#include "Interrupt_Interface.h"

void External_Interrupt0_Initalize(int0_sense sense)
{
	// Define interrupt pin INT0 as input ????? ?????
	CLR_BIT(DDRD,2);
	// Disable global interrupt while initialization (Apartment Door) arw2 el 42a
	cli();//Clear interrupt, CLR_BIT(SREG,7);
	// Choose sensing method
	switch(sense)
	{
		case INT0_LOW:
		CLR_BIT(MCUCR, ISC01);CLR_BIT(MCUCR, ISC00);// 0 0
		break;
		case INT0_HIGH:
		CLR_BIT(MCUCR, ISC01);SET_BIT(MCUCR, ISC00);// 0 1
		break;
		case INT0_FALLING:
		SET_BIT(MCUCR, ISC01);CLR_BIT(MCUCR, ISC00);// 1 0
		break;
		case INT0_RISING:
		SET_BIT(MCUCR, ISC01);SET_BIT(MCUCR, ISC00);// 1 1
		break;
		
	}
	// Enable peripheral interrupt (Room door)
	SET_BIT(GICR, INT0);
	// Enable global interrupt after initialization (Apartment Door)
	sei();//Set interrupt, SET_BIT(SREG,7);
}
void External_Interrupt1_Initalize(int1_sense sense)
{
	// Define interrupt pin INT0 as input ????? ?????
	CLR_BIT(DDRD,3);
	// Disable global interrupt while initialization (Apartment Door) arw2 el 42a
	cli();//Clear interrupt, CLR_BIT(SREG,7);
	// Choose sensing method
	switch(sense)
	{
		case INT0_LOW:
		CLR_BIT(MCUCR, ISC11);CLR_BIT(MCUCR, ISC10);// 0 0
		break;
		case INT0_HIGH:
		CLR_BIT(MCUCR, ISC11);SET_BIT(MCUCR, ISC10);// 0 1
		break;
		case INT0_FALLING:
		SET_BIT(MCUCR, ISC11);CLR_BIT(MCUCR, ISC10);// 1 0
		break;
		case INT0_RISING:
		SET_BIT(MCUCR, ISC11);SET_BIT(MCUCR, ISC10);// 1 1
		break;
		
	}
	// Enable peripheral interrupt (Room door)
	SET_BIT(GICR, INT0);
	// Enable global interrupt after initialization (Apartment Door)
	sei();//Set interrupt, SET_BIT(SREG,7);
}
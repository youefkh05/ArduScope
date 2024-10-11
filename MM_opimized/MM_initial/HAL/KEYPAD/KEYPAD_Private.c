/*
 * KEYPAD_Private.c
 *
 * Created: 3/5/2024 12:12:49 AM
 *  Author: oraga
 */ 

#include "KEYPAD_Interface.h"

const uint8_t KEYPAD[4][4]=
{
	{'1','4','7','*'},
	{'2','5','8','0'},
	{'3','6','9','#'},
	{'A','B','C','D'}
};


void KEYPAD_Initialize(void)
{
	//Define direction as output
	DIO_SetPinDirection(KEYPAD_PORT, KEYPAD_PIN_OUT0, KEYPAD_OUTPUT);
	DIO_SetPinDirection(KEYPAD_PORT, KEYPAD_PIN_OUT1, KEYPAD_OUTPUT);
	DIO_SetPinDirection(KEYPAD_PORT, KEYPAD_PIN_OUT2, KEYPAD_OUTPUT);
	DIO_SetPinDirection(KEYPAD_PORT, KEYPAD_PIN_OUT3, KEYPAD_OUTPUT);
	//Ensure that we are in initialize state
	DIO_SetPinValue(KEYPAD_PORT, KEYPAD_PIN_OUT0, KEYPAD_HIGH);
	DIO_SetPinValue(KEYPAD_PORT, KEYPAD_PIN_OUT1, KEYPAD_HIGH);
	DIO_SetPinValue(KEYPAD_PORT, KEYPAD_PIN_OUT2, KEYPAD_HIGH);
	DIO_SetPinValue(KEYPAD_PORT, KEYPAD_PIN_OUT3, KEYPAD_HIGH);
	//Define direction as input
	DIO_SetPinDirection(KEYPAD_PORT, KEYPAD_PIN_INP0, KEYPAD_INPUT);
	DIO_SetPinDirection(KEYPAD_PORT, KEYPAD_PIN_INP1, KEYPAD_INPUT);
	DIO_SetPinDirection(KEYPAD_PORT, KEYPAD_PIN_INP2, KEYPAD_INPUT);
	DIO_SetPinDirection(KEYPAD_PORT, KEYPAD_PIN_INP3, KEYPAD_INPUT);
	//Pull-Up activation
	DIO_SetPinPullUp(KEYPAD_PORT, KEYPAD_PIN_INP0);
	DIO_SetPinPullUp(KEYPAD_PORT, KEYPAD_PIN_INP1);
	DIO_SetPinPullUp(KEYPAD_PORT, KEYPAD_PIN_INP2);
	DIO_SetPinPullUp(KEYPAD_PORT, KEYPAD_PIN_INP3);
	
}
uint8_t KEYPAD_Read(void)
{
	uint8_t Loc_row, Loc_col, val=0, btn='F';
	for(Loc_col = KEYPAD_START_COL; Loc_col <= KEYPAD_END_COL; Loc_col++)//loop on columns
	{
		DIO_SetPinValue(KEYPAD_PORT, Loc_col, KEYPAD_LOW);//low to high pulse
		for (Loc_row = KEYPAD_START_ROW; Loc_row <= KEYPAD_END_ROW; Loc_row++)//loop on rows
		{	
			val = DIO_GetPinValue(KEYPAD_PORT, Loc_row);
			if(val==KEYPAD_PRESSED)
			{   
				btn = KEYPAD[Loc_row-KEYPAD_START_ROW][Loc_col-KEYPAD_START_COL];
				while (val == KEYPAD_PRESSED)
				{
					val = DIO_GetPinValue(KEYPAD_PORT, Loc_row);
				}
				_delay_ms(1);
			}
		}
		DIO_SetPinValue(KEYPAD_PORT, Loc_col, KEYPAD_HIGH);//low to high pulse
	}
	return btn;
}
/*
 * LCD_Configuration.h
 *
 * Created: 3/5/2024 12:14:36 AM
 *  Author: oraga
 */ 


#ifndef LCD_CONFIGURATION_H_
#define LCD_CONFIGURATION_H_

#include "PERIPHERAL_LIBRARY.h"

// Global Variable
extern uint32_t Character_Counter;
// Renaming PORTs
#define LCD                                 PORTD
#define LCD_Control_PORT					DIO_PORTB
#define LCD_Data_PORT						PORTD
// Renaming PINs
#define LCD_RS_PIN							DIO_PIN1
#define LCD_RW_PIN							DIO_PIN2
#define LCD_EN_PIN							DIO_PIN3
#define LCD_PIN_D4							DIO_PIN4
#define LCD_PIN_D5							DIO_PIN5
#define LCD_PIN_D6							DIO_PIN6
#define LCD_PIN_D7							DIO_PIN7
// Renaming States
#define LCD_Output							DIO_OUTPUT
#define LCD_Control_PORT_Output				0x0E
#define LCD_Data_PORT_Output				0xF0
#define LCD_Data_PORT_Input					0x00
// Renaming Status
#define LCD_High							DIO_HIGH
#define LCD_Low								DIO_LOW
// Renaming Commands
#define LCD_Command_ClearScreen				0x01
#define LCD_Command_ReturnHome				0x02
#define LCD_Command_DecrementCursor			0x04
#define LCD_Command_DisplayRight			0x1C
#define LCD_Command_IncrementCursor			0x06
#define LCD_Command_DisplayLeft				0x18
#define LCD_Command_DisplayOffCursorOff		0x08
#define LCD_Command_DisplayOffCursorOn		0x0A
#define LCD_Command_DisplayOnCursorOff		0x0C
#define LCD_Command_DisplayOnCursorBlink	0x0E
#define LCD_Command_DisplayOnCursorOn		0x0F
#define LCD_Command_ShiftLeft				0x10
#define LCD_Command_ShiftRight				0x14
#define LCD_Command_2ndLine					0xC0
#define LCD_Command_4Bit2Line				0x28
#define LCD_Command_8BitInitialize			0x33
#define LCD_Command_4BitInitialize			0x32
#define LCD_Command_CGRAM					0x40
#define LCD_Command_1stLine                 0x80

// Renaming Port
#define LCD               PORTD
//#define LCD_Control_PORT  DIO_PORTB
//#define LCD_Data_PORT     DIO_PORTD
// Renaming Pin
#define LCD_RS            DIO_PIN1
#define LCD_RW            DIO_PIN2
#define LCD_EN            DIO_PIN3
#define LCD_D4            DIO_PIN4
#define LCD_D5            DIO_PIN5
#define LCD_D6            DIO_PIN6
#define LCD_D7            DIO_PIN7
// Renaming State
#define LCD_OUTPUT        DIO_OUTPUT
// Renaming Status
#define LCD_HIGH          DIO_HIGH
#define LCD_LOW           DIO_LOW


#endif /* LCD_CONFIGURATION_H_ */
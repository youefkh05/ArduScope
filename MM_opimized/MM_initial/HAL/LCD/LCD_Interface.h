/*
 * LCD_Interface.h
 *
 * Created: 3/5/2024 12:15:11 AM
 *  Author: oraga
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

#include "LCD_Configuration.h"

uint32_t Character_Counter;
Bool CursorDirection;

/*
uint32_t Character_Counter;
Bool CursorDirection;
void LCD_Enable(void);
void LCD_Send_Command(uint8_t Command);
void LCD_HomeScreen(void);
void LCD_ClearScreen(void);
void LCD_Initialize(void);
void LCD_Display_Character(uint8_t Character);
void LCD_Display_String(uint8_t String[]);
void LCD_Reverse_String(uint8_t String[], uint8_t Length);
uint8_t LCD_IntToString(uint32_t Number, uint8_t String[], uint8_t Length);
void LCD_Display_Number(uint32_t Number);
void LCD_FloatToString(fint32_t Number, uint8_t String[], uint8_t AfterPoint);
void LCD_Display_FloatNumber(fint32_t Number, uint8_t AfterPoint);
void LCD_Display_Location(uint8_t xAxis, uint8_t yAxis);
void LCD_Send_Special(uint8_t Character);
void LCD_Store_Special(uint8_t Character[], uint8_t Address);
*/

void LCD_Enable(void);
void LCD_Send_Command(uint8_t Command);
void LCD_Initialize(void);
void LCD_4BITMode(void);
void LCD_8BITMode(void);
void LCD_ClearScreen(void);
void LCD_HomeScreen(void);
void LCD_INcrementCursorRight(void);
void LCD_DecrementCursorLeft(void);
void LCD_DisplayONCursorOFF(void);
void LCD_Write_Command(uint8_t command);
void LCD_Display_Character(uint8_t character);
void LCD_Display_String(uint8_t* str);
void LCD_Display_Number(uint32_t number);
void LCD_Display_FloatNumber(fint32_t Number, uint8_t AfterPoint);
void LCD_Display_Location(uint32_t xAxis, uint32_t yAxis);
void LCD_Write_SpecialCharacter(uint8_t sCharacter);
void LCD_Write_SpecialString(uint8_t* sStr);
void reverse(char* str, int len);
int intToStr(int x, char str[], int d);
void ftoa(float n, char* res, int afterpoint);
void LCD_FloatToString(fint32_t Number, uint8_t String[], uint8_t AfterPoint);
uint8_t LCD_IntToString(uint32_t Number, uint8_t String[], uint8_t Length);
void LCD_Reverse_String(uint8_t String[], uint8_t Length);


#endif /* LCD_INTERFACE_H_ */
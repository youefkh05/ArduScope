/*
 * LCD_Private.c
 *
 * Created: 3/5/2024 12:15:24 AM
 *  Author: oraga
 */ 

#include "LCD_Interface.h"

/*
void LCD_Enable(void)
{
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_High);
	_delay_ms(1);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_Low);
}

void LCD_Send_Command(uint8_t Command)
{
	DIO_SetPinValue(LCD_Control_PORT, LCD_RS_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_RW_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_Low);
	LCD_Data_PORT= (Command & 0xF0);
	LCD_Enable();
	LCD_Data_PORT = ((Command & 0x0F) << 4);
	LCD_Enable();
	_delay_us(100);
	if(Command == LCD_Command_IncrementCursor || Command == LCD_Command_DisplayLeft)
	CursorDirection = Fasle;
	if(Command == LCD_Command_DecrementCursor || Command == LCD_Command_DisplayRight)
	CursorDirection = True;
}

void LCD_HomeScreen(void)
{
	LCD_Send_Command(0x02);
	_delay_us(1900);
	Character_Counter = 0;
}

void LCD_ClearScreen(void)
{
	LCD_Write_Command(0x01);
	LCD_HomeScreen();
	_delay_us(1900);
}

void LCD_Initialize(void)
{
	static Bool Initialized = Fasle;
	if(!Initialized)
	{
		DIO_SetPinDirection(LCD_Control_PORT,LCD_RS_PIN,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_RW_PIN,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_RS_PIN,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_EN_PIN,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_PIN_D4,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_PIN_D5,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_PIN_D6,DIO_OUTPUT );
		//DIO_SetPortDirection(LCD_Control_PORTLCD_PIN_D7, LCD_Control_PORT_Output);
		//DIO_SetPortDirection(LCD_Data_PORT, LCD_Data_PORT_Output);
		_delay_ms(15);
		LCD_Write_Command(0x33);
		LCD_Write_Command(0x32);
		LCD_Write_Command(0x28);
		LCD_Write_Command(0x01);
		LCD_Write_Command(0x02);
		LCD_Write_Command(0x0C);
		LCD_Write_Command(0x06);
		LCD_ClearScreen();
		Initialized = True;
	}
}

void LCD_LineCheck(void)
{
	if(Character_Counter % 32 == 0)
	{
		LCD_ClearScreen();
		LCD_Send_Command(LCD_Command_1stLine);
	}
	else if(Character_Counter % 16 == 0)
	LCD_Send_Command(LCD_Command_2ndLine);
}
void LCD_Display_Character(uint8_t Character)
{
	LCD_Initialize();
	LCD_LineCheck();
	DIO_SetPinValue(LCD_Control_PORT, LCD_RS_PIN, LCD_High);
	DIO_SetPinValue(LCD_Control_PORT, LCD_RW_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_Low);
	LCD_Data_PORT = (Character & 0xF0);
	LCD_Enable();
	LCD_Data_PORT = ((Character & 0x0F) << 4);
	LCD_Enable();
	_delay_us(100);
	if(CursorDirection)
	Character_Counter--;
	else
	Character_Counter++;
}

void LCD_Display_String(uint8_t String[])
{
	uint8_t Counter = 0;
	while(String[Counter] != '\0')
	LCD_Display_Character(String[Counter++]);
}

void LCD_Reverse_String(uint8_t String[], uint8_t Length)
{
	uint8_t Counter = 0, temp;
	Length--;
	while(Counter < Length)
	{
		temp = String[Counter];
		String[Counter++] = String[Length];
		String[Length--] = temp;
	}
}

uint8_t LCD_IntToString(uint32_t Number, uint8_t String[], uint8_t Length)
{	if (Number==0)
	{String[0]='0';
	 String[1]='\0';
	 return 1;
	}
	uint8_t Counter = 0;
	while (Number)
	{
		String[Counter++] = (Number % 10) + '0';
		Number /= 10;
	}
	while (Counter < Length)
	String[Counter++] = '0';
	LCD_Reverse_String(String, Counter);
	String[Counter] = '\0';
	return Counter;
}

void LCD_Display_Number(uint32_t Number)
{
	uint8_t String[33];
	LCD_IntToString(Number, String, 0);
	LCD_Display_String(String);
}
void LCD_FloatToString(fint32_t Number, uint8_t String[], uint8_t AfterPoint)
{	if(Number>=1){
	uint32_t int_part = (uint32_t)Number;
	fint32_t float_part = Number - (fint32_t)int_part;
	uint8_t Counter = LCD_IntToString(int_part, String, 0);
	String[Counter] = '.';
	float_part *= pow(10, AfterPoint);
	LCD_IntToString((uint64_t)float_part, String + Counter + 1, AfterPoint);
	}
	else if(Number>=0){
		String[0]='0';
		String[1]='.';
		fint32_t float_part = Number;
		float_part *= pow(10, AfterPoint);
		LCD_IntToString((uint64_t)float_part, String + 2, AfterPoint);
	}
	else if(-1.0*Number>=1){//negative with int
		String[0]='-';
		LCD_Display_String((uint8_t*)"-");
		Number=-1.0*Number;
		uint32_t int_part = (uint32_t)Number;
		fint32_t float_part = Number - (fint32_t)int_part;
		uint8_t Counter = LCD_IntToString(int_part, String, 0);
		String[Counter] = '.';
		float_part *= pow(10, AfterPoint);
		LCD_IntToString((uint64_t)float_part, String + Counter +1, AfterPoint);
	}
	else{//negative with no int
		String[0]='-';
		String[1]='0';
		String[2]='.';
		//LCD_Display_String((uint8_t*)"-");
		Number=-1.0*Number;
		fint32_t float_part = Number;
		float_part *= pow(10, AfterPoint);
		LCD_IntToString((uint64_t)float_part, String + 3, AfterPoint);
	}
}
void LCD_Display_FloatNumber(fint32_t Number, uint8_t AfterPoint)
{
	uint8_t String[33];
	LCD_FloatToString(Number, String, AfterPoint);
	LCD_Display_String(String);
}


void LCD_Display_Location(uint32_t xAxis, uint32_t yAxis) 
{
	LCD_Initialize();
	uint8_t RowAddress[2] = {0x80, 0xC0};
	LCD_Send_Command(RowAddress[yAxis] + xAxis);
	Character_Counter = (yAxis * 16) + (xAxis);
}
void LCD_Send_Special(uint8_t Character)
{
	LCD_Initialize();
	DIO_SetPinValue(LCD_Control_PORT, LCD_RS_PIN, LCD_High);
	DIO_SetPinValue(LCD_Control_PORT, LCD_RW_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_Low);
	LCD_Data_PORT = (Character & 0xF0);
	LCD_Enable();
	LCD_Data_PORT = ((Character & 0x0F) << 4);
	LCD_Enable();
	_delay_us(100);
}
void LCD_Store_Special(uint8_t Character[], uint8_t Address)
{
	LCD_Send_Command(LCD_Command_CGRAM + (Address*8));
	for(int i = 0; i < 8; i++)
	LCD_Send_Special(Character[i]);
	LCD_Display_Location(Character_Counter % 16, Character_Counter / 16);
}

void LCD_Send_Command(uint8_t Command)
{
	DIO_SetPinValue(LCD_Control_PORT, LCD_RS_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_RW_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_Low);
	LCD_Data_PORT= (Command & 0xF0);
	LCD_Enable();
	LCD_Data_PORT = ((Command & 0x0F) << 4);
	LCD_Enable();
	_delay_us(100);
	if(Command == LCD_Command_IncrementCursor || Command == LCD_Command_DisplayLeft)
	CursorDirection = Fasle;
	if(Command == LCD_Command_DecrementCursor || Command == LCD_Command_DisplayRight)
	CursorDirection = True;
}
*/

void LCD_Enable(void)
{
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_High);
	_delay_ms(1);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_Low);
}

void LCD_HomeScreen(void)
{
	LCD_Write_Command(0x02);
	_delay_us(1900);
	Character_Counter = 0;
}

void LCD_ClearScreen(void)
{
	LCD_Write_Command(0x01);
	LCD_HomeScreen();
	_delay_us(1900);
}

void LCD_Write_Command(uint8_t command)
{
	//Register Select will be logic(0) because it's a command
	DIO_SetPinValue(LCD_Control_PORT, LCD_RS, LCD_LOW);
	//R/W will be logic(0) because we will write on the screen
	DIO_SetPinValue(LCD_Control_PORT, LCD_RW, LCD_LOW);
	//Ensure that enable is in logic(0)
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_LOW);
	//Get high nibble of the command
	LCD = (command & 0xF0);
	//Send high to low pulse of the enable
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_LOW);
	//Get low nibble of the command
	LCD = ((command & 0x0F)<<4);
	//Send high to low pulse of the enable
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_LOW);
	_delay_ms(2);
}

void LCD_Initialize(void)
{
	static Bool Initialized = Fasle;
	if(!Initialized)
	{
		DIO_SetPinDirection(LCD_Control_PORT,LCD_RS_PIN,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_RW_PIN,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_RS_PIN,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_EN_PIN,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_PIN_D4,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_PIN_D5,DIO_OUTPUT );
		DIO_SetPinDirection(LCD_Control_PORT,LCD_PIN_D6,DIO_OUTPUT );
		//DIO_SetPortDirection(LCD_Control_PORTLCD_PIN_D7, LCD_Control_PORT_Output);
		//DIO_SetPortDirection(LCD_Data_PORT, LCD_Data_PORT_Output);
		_delay_ms(15);
		LCD_Write_Command(0x33);
		LCD_Write_Command(0x32);
		LCD_Write_Command(0x28);
		LCD_Write_Command(0x01);
		LCD_Write_Command(0x02);
		LCD_Write_Command(0x0C);
		LCD_Write_Command(0x06);
		LCD_ClearScreen();
		Initialized = True;
	}
}

void LCD_LineCheck(void)
{
	if(Character_Counter % 32 == 0)
	{
		LCD_ClearScreen();
		LCD_Send_Command(LCD_Command_1stLine);
	}
	else if(Character_Counter % 16 == 0)
	LCD_Send_Command(LCD_Command_2ndLine);
}
void LCD_Display_Character(uint8_t character)
{
	//Register Select will be logic(1) because it's a data
	DIO_SetPinValue(LCD_Control_PORT, LCD_RS, LCD_HIGH);
	//R/W will be logic(0) because we will write on the screen
	DIO_SetPinValue(LCD_Control_PORT, LCD_RW, LCD_LOW);
	//Ensure that enable is in logic(0)
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_LOW);
	//Get high nibble of the character
	LCD = (character & 0xF0);
	//Send high to low pulse of the enable
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_LOW);
	//Get low nibble of the character
	LCD = ((character & 0x0F)<<4);
	//Send high to low pulse of the enable
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN, LCD_LOW);
	_delay_ms(2);
}

void LCD_Display_String(uint8_t* str)
{
	while (*str != '\0')
	{
		LCD_Display_Character(*str);
		_delay_ms(5);
		str++;
	}
}

void LCD_Reverse_String(uint8_t String[], uint8_t Length)
{
	uint8_t Counter = 0, temp;
	Length--;
	while(Counter < Length)
	{
		temp = String[Counter];
		String[Counter++] = String[Length];
		String[Length--] = temp;
	}
}

uint8_t LCD_IntToString(uint32_t Number, uint8_t String[], uint8_t Length)
{	if (Number==0)
	{String[0]='0';
		String[1]='\0';
		return 1;
	}
	uint8_t Counter = 0;
	while (Number)
	{
		String[Counter++] = (Number % 10) + '0';
		Number /= 10;
	}
	while (Counter < Length)
	String[Counter++] = '0';
	LCD_Reverse_String(String, Counter);
	String[Counter] = '\0';
	return Counter;
}

void LCD_Display_Number(uint32_t Number)
{
	uint8_t String[33];
	LCD_IntToString(Number, String, 0);
	LCD_Display_String(String);
}
void LCD_FloatToString(fint32_t Number, uint8_t String[], uint8_t AfterPoint)
{	if(Number>=1){
	uint32_t int_part = (uint32_t)Number;
	fint32_t float_part = Number - (fint32_t)int_part;
	uint8_t Counter = LCD_IntToString(int_part, String, 0);
	String[Counter] = '.';
	float_part *= pow(10, AfterPoint);
	LCD_IntToString((uint64_t)float_part, String + Counter + 1, AfterPoint);
}
else if(Number>=0){
	String[0]='0';
	String[1]='.';
	fint32_t float_part = Number;
	float_part *= pow(10, AfterPoint);
	LCD_IntToString((uint64_t)float_part, String + 2, AfterPoint);
}
else if(-1.0*Number>=1){//negative with int
	String[0]='-';
	LCD_Display_String((uint8_t*)"-");
	Number=-1.0*Number;
	uint32_t int_part = (uint32_t)Number;
	fint32_t float_part = Number - (fint32_t)int_part;
	uint8_t Counter = LCD_IntToString(int_part, String, 0);
	String[Counter] = '.';
	float_part *= pow(10, AfterPoint);
	LCD_IntToString((uint64_t)float_part, String + Counter +1, AfterPoint);
}
else{//negative with no int
	String[0]='-';
	String[1]='0';
	String[2]='.';
	//LCD_Display_String((uint8_t*)"-");
	Number=-1.0*Number;
	fint32_t float_part = Number;
	float_part *= pow(10, AfterPoint);
	LCD_IntToString((uint64_t)float_part, String + 3, AfterPoint);
}
}
void LCD_Display_FloatNumber(fint32_t Number, uint8_t AfterPoint)
{
	uint8_t String[33];
	LCD_FloatToString(Number, String, AfterPoint);
	LCD_Display_String(String);
}

void LCD_Display_Location(uint32_t xAxis, uint32_t yAxis)
{
	LCD_Initialize();
	uint8_t RowAddress[2] = {0x80, 0xC0};
	LCD_Send_Command(RowAddress[yAxis] + xAxis);
	Character_Counter = (yAxis * 16) + (xAxis);
}
void LCD_Send_Special(uint8_t Character)
{
	LCD_Initialize();
	DIO_SetPinValue(LCD_Control_PORT, LCD_RS_PIN, LCD_High);
	DIO_SetPinValue(LCD_Control_PORT, LCD_RW_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_Low);
	LCD_Data_PORT = (Character & 0xF0);
	LCD_Enable();
	LCD_Data_PORT = ((Character & 0x0F) << 4);
	LCD_Enable();
	_delay_us(100);
}
void LCD_Store_Special(uint8_t Character[], uint8_t Address)
{
	LCD_Send_Command(LCD_Command_CGRAM + (Address*8));
	for(int i = 0; i < 8; i++)
	LCD_Send_Special(Character[i]);
	LCD_Display_Location(Character_Counter % 16, Character_Counter / 16);
}

void LCD_Send_Command(uint8_t Command)
{
	DIO_SetPinValue(LCD_Control_PORT, LCD_RS_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_RW_PIN, LCD_Low);
	DIO_SetPinValue(LCD_Control_PORT, LCD_EN_PIN, LCD_Low);
	LCD_Data_PORT= (Command & 0xF0);
	LCD_Enable();
	LCD_Data_PORT = ((Command & 0x0F) << 4);
	LCD_Enable();
	_delay_us(100);
	if(Command == LCD_Command_IncrementCursor || Command == LCD_Command_DisplayLeft)
	CursorDirection = Fasle;
	if(Command == LCD_Command_DecrementCursor || Command == LCD_Command_DisplayRight)
	CursorDirection = True;
}
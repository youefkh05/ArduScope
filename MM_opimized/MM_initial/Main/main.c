/*
 * MM_initial.c
 *
 * Created: 3/4/2024 11:23:47 PM
 * Author : oragab
 */ 

#include "main.h"
#define Rpin ADC_7
#define VDCpin ADC_6
#define Vtotpin ADC_4
#define IDCpin ADC_6
#define Itotpin ADC_4


int main(void)
{
	//intialize
	DIO_SetPinDirection(DIO_PORTB,A_MUX_2,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB,B_MUX_2,DIO_OUTPUT);
	_delay_ms(100);
	DIO_SetPinDirection(DIO_PORTB,A_MUX_3,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTB,B_MUX_3,DIO_OUTPUT);
	DIO_SetPinDirection(DIO_PORTA,IDCpin,DIO_INPUT);
	DIO_SetPinDirection(DIO_PORTA,Vtotpin,DIO_INPUT);
	DIO_SetPinDirection(DIO_PORTA,VDCpin,DIO_INPUT);
	DIO_SetPinDirection(DIO_PORTA,Rpin,DIO_INPUT);
	LCD_Initialize();
	_delay_ms(5);
	KEYPAD_Initialize();
	_delay_ms(5);
	ADC_Initialize(5,1024);
	_delay_ms(5);
	uint8_t device=0; //1: ohm  2:Ameter	3:Volt
	uint8_t range;
	uint8_t exit_range;
	uint8_t mode;	//1:AC 2:DC
	mode=0;
	//start
	_delay_ms(5);
	while(1){
		range='0';		//device range
		exit_range=0;	//device exit
		_delay_ms(100);
		device=select_LCD("Which Device? ;)","1Ohm 2Amt 3Volt",3,'f'); //select device
		_delay_ms(100);
		LCD_ClearScreen();
		LCD_HomeScreen();
		//use the selected device
		switch(device)
			{
				case '1': //ohm
					//stay till you want to change the device
					while(exit_range==0){
						//default for caution
						select_mux(device,'3');
						
						//ask to return
						exit_range=ask_to_return('#');
						if(exit_range ==1){
							break;
						}
						//select range
						range=select_LCD("range? 1:10k","2:100k 3:1M",3,'#');
						_delay_ms(1);
						
						if(range=='#'){
							break;
						}
						
						_delay_ms(1);
						//select the mux
						select_mux(device,range);
						_delay_ms(10);
						
						//read the input
						uint16_t x;
						x=ADC_Read(Rpin);
						LCD_ClearScreen();
						LCD_HomeScreen();
						//display the input volt
						LCD_Display_Number(x);
						_delay_ms(1000);
						
						//display the resistor
						display_ohm(range,x);
						range='0';
					}
				break;
				case '2'://Ameter
					//default for caution
					select_mux(device,'4');
					
					//stay till you want to change the device
					while(exit_range==0){
						//ask to return
						exit_range=ask_to_return('#');
						if(exit_range ==1){
							break;
						}
						
						//mechanical
						LCD_ClearScreen();
						LCD_HomeScreen();
						LCD_Display_String("Chose ranges :)");
						LCD_Display_Location(0,1);
						LCD_Display_String("From switches!");
						_delay_ms(2000);
						
						//select range
						range=select_LCD("range? 1:2m 4:1A","2:20m 3:200m :0",4,'#');
						_delay_ms(1);
						
						if(range=='#'){
							break;
						}
						_delay_ms(1);
						
						//select mode
						mode=select_LCD("mode? 1:AC 2:DC","Be careful!",2,'#');
						_delay_ms(1);
						if(mode=='#'){
							break;
						}
						_delay_ms(1);
						select_mux(device,range);
						_delay_ms(10);
						
						//read the input
						uint16_t x;
						x=ADC_Read(IDCpin);
						LCD_ClearScreen();
						LCD_HomeScreen();
						//display the input volt
						LCD_Display_Number(x);
						_delay_ms(1000);
						

						display_Amp(range,x,mode);
						range='0';
						}
				break;
				case '3'://volt
				//default for caution
				select_mux(device,'4');
				
				//stay till you want to change the device
				while(exit_range==0){
					//ask to return
					exit_range=ask_to_return('#');
					if(exit_range ==1){
						break;
					}
					
					//mechanical
					LCD_ClearScreen();
					LCD_HomeScreen();
					LCD_Display_String("Chose ranges :)");
					LCD_Display_Location(0,1);
					LCD_Display_String("From switches!");
					_delay_ms(2000);
					
					//select range
					range=select_LCD("range? 1:300m","2:3V 3:30V 4:400",4,'#');
					_delay_ms(1);
					if(range=='#'){
						break;
					}
					_delay_ms(1);
					
					//select mode
					mode=select_LCD("mode? 1:AC 2:DC","Be careful!",2,'#');
					_delay_ms(1);
					if(mode=='#'){
						break;
					}
					_delay_ms(1);
					
					select_mux(device,range);
					_delay_ms(10);
					
					//read the input AC+DC
					uint16_t xtot;
					xtot=ADC_Read(Vtotpin);
					/*
					LCD_ClearScreen();
					LCD_HomeScreen();
					LCD_Display_String("Xtot Ac = ");
					//display the AC+DC input volt
					LCD_Display_Number(xtot);
					_delay_ms(1000);
					*/
					
					//read the input
					uint16_t x;
					x=ADC_Read(VDCpin);
					LCD_ClearScreen();
					LCD_HomeScreen();
					//display the input volt
					LCD_Display_Number(x);
					_delay_ms(1000);
					
					display_volt(range,xtot,x,mode);

					range='0';
					
					}
				break;
			}
		
		range='0';
		exit_range=0;
		
	}
	_delay_ms(100);
}



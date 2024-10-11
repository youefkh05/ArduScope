
/*
 * APP.c
 *
 * Created: 4/1/2024 10:14:53 AM
 *  Author: AZidan
 */ 

#include "APP.h"
#define Rpin ADC_7
#define VDCpin ADC_6
#define Vtotpin ADC_4
#define IDCpin ADC_6
#define Itotpin ADC_4

fint32_t Read_Volt(uint16_t Vout,uint16_t Vtot, uint8_t Vrange,uint8_t mode)
{
	//check if it didn't exceed the max range (positive or negative)
	if(1003<=Vout || Vout<=206){
		return 999.99;
	}
	//check if it was too small
	if(518<=Vout && Vout <=524){
		return 0.0;
	}
	
	fint32_t Vdivider;
	Vdivider = -1;
	fint32_t Vconst;
	Vconst  = -1;
	switch(Vrange)
	{
		case '1'://300mV
		Vdivider = 5.984;
		Vconst = 2.47859;
		break;
		case '2'://3V
		Vdivider = 0.59884;
		Vconst = 2.5418;
		break;
		case '3'://30V
		Vdivider = 0.0587325;
		Vconst = 2.5144325;
		break;
		case '4'://400V
		Vdivider = 0.0047988;
		Vconst = 2.545246;
		break;
	}
	
	switch(mode){
		case '2':{ //DC
		fint32_t Val = Vout*5.0/1024.0;
		Val = ((Val-Vconst)/(Vdivider)); //equation
		_delay_ms(5);/*
		LCD_ClearScreen();
		LCD_HomeScreen();
		LCD_Display_String("Volt = ");
		LCD_Display_FloatNumber(Val,4);
		_delay_ms(5000);
		*/
		return Val;
		}
		case '1':{ //AC
			/*
			LCD_ClearScreen();
			LCD_HomeScreen();
			LCD_Display_String("Vtot Ac = ");
			LCD_Display_FloatNumber(Vtot,3);
			_delay_ms(1000);
			LCD_Display_Location(0,1);
			LCD_Display_String("Vout Ac = ");
			LCD_Display_FloatNumber(Vout,3);
			_delay_ms(1000);
			*/		
			if(Vtot<=(Vout+2)){ //AC is zero
				return 0.0;
				}
			switch(Vrange)
			{
				case '1'://300mV
				Vout=Vtot-Vout+506;
				break;
				case '2'://3V
				Vout=Vtot-Vout+520;
				break;
				case '3'://30V
				Vout=Vtot-Vout+516;
				break;
				case '4'://400V
				Vout=Vtot-Vout+522;
				break;
			}					
			fint32_t Val;
			Val = Vout*5.0/1024.0;
			Val = ((Val-Vconst)/(Vdivider)); //equation
			/*
			LCD_ClearScreen();
			LCD_HomeScreen();
			LCD_Display_String("V Ac = ");
			LCD_Display_FloatNumber(Val,3);
			_delay_ms(1000);
			LCD_ClearScreen();
			LCD_HomeScreen();
			*/
			_delay_ms(5);
			
			return Val;
		}
	}
	
}

fint32_t Read_Amp(uint16_t x,uint16_t Itot, uint8_t Irange,uint8_t mode)
{	
	//check if it didn't exceed the max range (positive or negative)
	if(810<=x || x<=200){
		return 999.99;
	}
	//check if it was too small
	if(406<=x && x <=414){
		return 0.0;
	}
	
	// I_TO_V_OUT_MCU = I_Slope * I_input + I_intercept
	fint32_t I_input = -1;
	fint32_t I_TO_V_OUT_MCU = 0;
	switch(mode){
		case '1': //AC
			I_TO_V_OUT_MCU = (Itot * 5.0) / 1024.0;
		case '2': //DC
			I_TO_V_OUT_MCU = (x * 5.0) / 1024.0;	
	}
	fint32_t I_Slope     = -1;
	fint32_t I_intercept = -1;
	switch(Irange)
	{
		case '1'://2mA
		I_Slope     = 0.86857;
		I_intercept = 2.263;
		break;
		case '2'://20mA
		I_Slope     = 0.09;
		I_intercept = 2.31;
		break;
		case '3'://200mA
		I_Slope     = 0.0124;
		I_intercept = 2.01;
		break;
		case '4'://1A
		I_Slope     = 2.517;
		I_intercept = 2.012;
		break;
		default:
		LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
		break;
	}
	I_input = (I_TO_V_OUT_MCU - I_intercept) / I_Slope;
	_delay_ms(5);
	// display_Amp(Irange, I_input);
	return I_input;
	
}

void display_ohm(uint8_t range,uint16_t volt){
	// range 1:10k 2:100k 3: 1M
	if (range >'5' || range <'1'){
		LCD_ClearScreen();
		LCD_HomeScreen();
		LCD_Display_String((uint8_t*)"Wrong Range :(");
		return;
	}
	#define R 100 //we will use it to normalize
	fint32_t Rin;
	uint8_t exit_R;
	exit_R=0;
	uint16_t count;
	count=0;
	//if you want to return
	LCD_ClearScreen();
	LCD_HomeScreen();
	LCD_Display_String((uint8_t*)"To Return press:");
	LCD_Display_Location(0,1);
	LCD_Display_String((uint8_t*)"*  ;)");
	//check of yo want to return
	while(exit_R!='*'){
		exit_R =KEYPAD_Read();
		_delay_ms(5);
		count++;
		if(count>=200){
			count=0;
			break;
		}
	}
	if(exit_R=='*'){
		return;
	}
	count=0;
	uint16_t old_volt;
	old_volt=volt;
	while(exit_R != '*'){
		LCD_ClearScreen();
		LCD_HomeScreen();
		//display with the chosen range
		switch (range){
			case '1':
			//we will need to map
			if(volt >=1015){//wrong range
				LCD_Display_String((uint8_t*)"error(big R) :(");
				LCD_Display_Location(0,1);
				LCD_Display_String((uint8_t*)"need big range;)");
				_delay_ms(1000);
				return;
			}
			if(volt<707){	//less than 1k
				Rin=(450.0*volt)/(1024.0-volt);
				LCD_Display_String((uint8_t*)"Resistor (Ohm)");
				LCD_Display_Location(0,1);
				LCD_Display_FloatNumber(Rin,3);
				_delay_ms(1000);
				LCD_Display_Location(11,1);
				LCD_Display_String((uint8_t*)"*:ext");
				//if the resistor value changed
				while(volt<707 && exit_R != '*'){
					if(old_volt!=volt){
						LCD_Display_Location(0,1);
						old_volt=volt;
						LCD_Display_String((uint8_t*)"       ");
						Rin=(450.0*volt)/(1024.0-volt);
						LCD_Display_Location(0,1);
						LCD_Display_FloatNumber(Rin,3);
						_delay_ms(1);
					}
					volt=ADC_Read(Rpin);
					exit_R=KEYPAD_Read();
				}
			}
			else{	//from 1k to 10k
				Rin=(0.450*volt)/(1024.0-volt);	//it will be from 1:10
				LCD_Display_String((uint8_t*)"Resistor (kOhm)");
				LCD_Display_Location(0,1);
				LCD_Display_FloatNumber(Rin,3);
				_delay_ms(1);
				LCD_Display_Location(11,1);
				LCD_Display_String((uint8_t*)"*:ext");
				//if the resistor value changed
				while(volt <1015 && volt>=707 && exit_R != '*'){
					if(old_volt!=volt){
						old_volt=volt;
						LCD_Display_Location(0,1);
						LCD_Display_String((uint8_t*)"     ");
						Rin=(0.450*volt)/(1024.0-volt);
						LCD_Display_Location(0,1);
						LCD_Display_FloatNumber(Rin,3);
						_delay_ms(1);
					}
					volt=ADC_Read(Rpin);
					exit_R=KEYPAD_Read();
				}
			}
			break;
			case '2':
			//we will need to map
			if(volt >=1015){// big range
				LCD_Display_String((uint8_t*)"error(big R) :(");
				LCD_Display_Location(0,1);
				LCD_Display_String((uint8_t*)"need big range;)");
				_delay_ms(1000);
				return;
			}
			if(volt<931){	//small range
				LCD_Display_String((uint8_t*)"caution(smal R)");
				LCD_Display_Location(0,1);
				LCD_Display_String((uint8_t*)"ned smal range;)");
				_delay_ms(1000);
				LCD_ClearScreen();
				LCD_HomeScreen();
			}
			if(volt>=436){
				Rin=(1.35*volt)/(1024.0-volt);	//it will be from 10:100
				LCD_Display_String((uint8_t*)"Resistor (kOhm)");
				LCD_Display_Location(0,1);
				LCD_Display_FloatNumber(Rin,3);
				_delay_ms(1);
				LCD_Display_Location(11,1);
				LCD_Display_String((uint8_t*)"*:ext");
				//if the resistor value changed
				while(volt <1015 && volt>=436 && exit_R != '*'){
					if(old_volt!=volt){
						old_volt=volt;
						LCD_Display_Location(0,1);
						LCD_Display_String((uint8_t*)"       ");
						Rin=(1.35*volt)/(1024.0-volt);
						LCD_Display_Location(0,1);
						LCD_Display_FloatNumber(Rin,3);
						_delay_ms(1);
					}
					volt=ADC_Read(Rpin);
					exit_R=KEYPAD_Read();
				}
			}
			else{	//less than 1k
				Rin=(1350.0*volt)/(1024.0-volt);
				LCD_Display_String((uint8_t*)"Resistor (Ohm)");
				LCD_Display_Location(0,1);
				LCD_Display_FloatNumber(Rin,3);
				_delay_ms(1);
				LCD_Display_Location(11,1);
				LCD_Display_String((uint8_t*)"*:ext");
				//if the resistor value changed
				while(volt<436 && exit_R != '*'){
					if(old_volt!=volt){
						old_volt=volt;
						LCD_Display_Location(0,1);
						LCD_Display_String((uint8_t*)"     ");
						Rin=(1350.0*volt)/(1024.0-volt);
						LCD_Display_Location(0,1);
						LCD_Display_FloatNumber(Rin,3);
						_delay_ms(1);
					}
					volt=ADC_Read(Rpin);
					exit_R=KEYPAD_Read();
				}
			}
			break;
			case '3':
			//we will need to map
			if(volt >=1020){// big range
				LCD_Display_String((uint8_t*)"error(big R) :(");
				LCD_Display_Location(0,1);
				LCD_Display_String((uint8_t*)"need big range;)");
				_delay_ms(1000);
				return;
			}
			if(volt<930){	//small range
				LCD_Display_String((uint8_t*)"caution(smal R)");
				LCD_Display_Location(0,1);
				LCD_Display_String((uint8_t*)"ned smal range;)");
				_delay_ms(1000);
				LCD_ClearScreen();
				LCD_HomeScreen();
			}
			if(volt>=1014){	// it is mega ohm
				Rin=(0.01*volt)/(1024.0-volt);
				LCD_Display_String((uint8_t*)"Resistor (MOhm)");
				LCD_Display_Location(0,1);
				LCD_Display_FloatNumber(Rin,3);
				_delay_ms(1);
				LCD_Display_Location(11,1);
				LCD_Display_String((uint8_t*)"*:ext");
				//if the resistor value changed
				while(volt <1020 && volt>=1014 && exit_R != '*'){
					if(old_volt!=volt){
						old_volt=volt;
						LCD_Display_Location(0,1);
						LCD_Display_String((uint8_t*)"   ");
						Rin=(0.01*volt)/(1024.0-volt);
						LCD_Display_Location(0,1);
						LCD_Display_FloatNumber(Rin,3);
						_delay_ms(1);
					}
					volt=ADC_Read(Rpin);
					exit_R=KEYPAD_Read();
				}
			}
			else if(volt>=90){ // it is kilo ohm
				Rin=(10.0*volt)/(1024.0-volt);
				LCD_Display_String((uint8_t*)"Resistor (kOhm)");
				LCD_Display_Location(0,1);
				LCD_Display_FloatNumber(Rin,3);
				_delay_ms(1);
				LCD_Display_Location(11,1);
				LCD_Display_String((uint8_t*)"*:ext");
				//if the resistor value changed
				while(volt<1014 && volt>=90 && exit_R != '*'){
					if(old_volt!=volt){
						old_volt=volt;
						LCD_Display_Location(0,1);
						LCD_Display_String((uint8_t*)"       ");
						Rin=(10.0*volt)/(1024.0-volt);
						LCD_Display_Location(0,1);
						LCD_Display_FloatNumber(Rin,3);
						_delay_ms(1);
					}
					volt=ADC_Read(Rpin);
					exit_R=KEYPAD_Read();
				}
			}
			else{	//less than 1k
				Rin=(10000.0*volt)/(1024.0-volt);
				LCD_Display_String((uint8_t*)"Resistor (Ohm)");
				LCD_Display_Location(0,1);
				LCD_Display_FloatNumber(Rin,3);
				_delay_ms(1);
				LCD_Display_Location(11,1);
				LCD_Display_String((uint8_t*)"*:ext");
				//if the resistor value changed
				while(volt<90 && exit_R != '*'){
					if(old_volt!=volt){
						LCD_Display_Location(0,1);
						old_volt=volt;
						LCD_Display_String((uint8_t*)"       ");
						Rin=(10000.0*volt)/(1024.0-volt);
						LCD_Display_Location(0,1);
						LCD_Display_FloatNumber(Rin,3);
						_delay_ms(1);
					}
					volt=ADC_Read(Rpin);
					exit_R=KEYPAD_Read();
				}
			}
			break;
		}
	}
}

void display_Amp(uint8_t range,uint16_t volt,uint8_t mode)
{   
	// range 1:2m 2:20m 3:200m 4:1A
	if (range >'5' || range <'1'){
		LCD_ClearScreen();
		LCD_HomeScreen();
		LCD_Display_String((uint8_t*)"Wrong Range :(");
		return;
	}
	
	//check if it didn't exceed the max range
	if(volt>=1003){
		LCD_ClearScreen();
		LCD_HomeScreen();
		LCD_Display_String((uint8_t*)"error(big I) :(");
		LCD_Display_Location(0,1);
		LCD_Display_String((uint8_t*)"need big range;)");
		_delay_ms(1000);
		return;
	}
	
	uint8_t exit_I;
	exit_I=0;
	uint16_t count;
	count=0;
	
	//if you want to return
	LCD_ClearScreen();
	LCD_HomeScreen();
	LCD_Display_String((uint8_t*)"To Return press:");
	LCD_Display_Location(0,1);
	LCD_Display_String((uint8_t*)"*  ;)");
	
	//check of yo want to return
	while(exit_I!='*'){
		exit_I =KEYPAD_Read();
		_delay_ms(5);
		count++;
		if(count>=200){
			count=0;
			break;
		}
	}
	if(exit_I=='*'){
		return;
	}
	
	uint16_t old_volt;
	old_volt=volt;
	fint32_t Iin;
	count=0;
	while(exit_I != '*'){
		LCD_ClearScreen();
		LCD_HomeScreen();
		switch(mode){
			case '2':{//DC
				if(range=='4'){ //A
					Iin=Read_Amp(volt,0,range,mode);
					LCD_Display_String((uint8_t*)"Current (A)");
					LCD_Display_Location(0,1);
					LCD_Display_FloatNumber(Iin,3);
					_delay_ms(1000);
					LCD_Display_Location(11,1);
					LCD_Display_String((uint8_t*)"*:ext");
					//if the volt value changed
					while(exit_I != '*'){
						if(old_volt!=volt){
							LCD_Display_Location(0,1);
							old_volt=volt;
							LCD_Display_String((uint8_t*)"           ");
							Iin=Read_Amp(volt,0,range,mode);
							LCD_Display_Location(0,1);
							LCD_Display_FloatNumber(Iin,3);
							_delay_ms(1);
						}
						
						if(volt>=810 || volt<=200){ //make sure
							_delay_ms(100);
							volt=ADC_Read(IDCpin);
						}
						//check if it didn't exceed the max range (positive or negative)
						if(volt>=810 || volt<=200){
							LCD_ClearScreen();
							LCD_HomeScreen();
							LCD_Display_String((uint8_t*)"error(big I) :(");
							LCD_Display_Location(0,1);
							LCD_Display_String((uint8_t*)"need big range;)");
							_delay_ms(1000);
							return;
						}
						volt=ADC_Read(IDCpin);
						exit_I=KEYPAD_Read();
					}
				}
				else{//mA
					Iin=Read_Amp(volt,0,range,mode);
					LCD_Display_String((uint8_t*)"Current (mA)");
					LCD_Display_Location(0,1);
					LCD_Display_FloatNumber(Iin,3);
					_delay_ms(1000);
					LCD_Display_Location(11,1);
					LCD_Display_String((uint8_t*)"*:ext");
					//if the volt value changed
					while(exit_I != '*'){
						if(old_volt!=volt){
							LCD_Display_Location(0,1);
							old_volt=volt;
							LCD_Display_String((uint8_t*)"           ");
							Iin=Read_Amp(volt,0,range,mode);
							LCD_Display_Location(0,1);
							LCD_Display_FloatNumber(Iin,3);
							_delay_ms(1);
						}
						if(volt>=810 || volt<=200){ //make sure
							_delay_ms(100);
							volt=ADC_Read(IDCpin);
						}
						//check if it didn't exceed the max range (positive or negative)
						if(volt>=810|| volt<=200){
							LCD_ClearScreen();
							LCD_HomeScreen();
							LCD_Display_String((uint8_t*)"error(big I) :(");
							LCD_Display_Location(0,1);
							LCD_Display_String((uint8_t*)"need big range;)");
							_delay_ms(1000);
							return;
						}
						volt=ADC_Read(IDCpin);
						exit_I=KEYPAD_Read();
					}
				}
				break;
			}
			case '1':{//AC
				uint16_t Itot;
				Itot=ADC_Read(Itotpin);
				volt=Itot;
				old_volt=volt;
				Iin=Read_Amp(volt,Itot,range,mode);
				if(range=='4'){ //A
					LCD_Display_String((uint8_t*)"Current (A)");
					LCD_Display_Location(0,1);
					LCD_Display_FloatNumber(Iin,3);
					_delay_ms(1000);
					LCD_Display_Location(11,1);
					LCD_Display_String((uint8_t*)"*:ext");
					//if the volt value changed
					while(exit_I != '*'){
						if(old_volt!=volt){
							LCD_Display_Location(0,1);
							old_volt=volt;
							LCD_Display_String((uint8_t*)"           ");
							Iin=Read_Amp(volt,Itot,range,mode);
							LCD_Display_Location(0,1);
							LCD_Display_FloatNumber(Iin,3);
							_delay_ms(1);
						}
						
						if(volt>=810 || volt<=200){ //make sure
							_delay_ms(100);
							volt=ADC_Read(Itotpin);
						}
						//check if it didn't exceed the max range (positive or negative)
						if(volt>=810 || volt<=200){
							LCD_ClearScreen();
							LCD_HomeScreen();
							LCD_Display_String((uint8_t*)"error(big I) :(");
							LCD_Display_Location(0,1);
							LCD_Display_String((uint8_t*)"need big range;)");
							_delay_ms(1000);
							return;
						}
						volt=ADC_Read(Itotpin);
						exit_I=KEYPAD_Read();
					}
				}
				else{//mA
					LCD_Display_String((uint8_t*)"Current (mA)");
					LCD_Display_Location(0,1);
					LCD_Display_FloatNumber(Iin,3);
					_delay_ms(1000);
					LCD_Display_Location(11,1);
					LCD_Display_String((uint8_t*)"*:ext");
					//if the volt value changed
					while(exit_I != '*'){
						if(old_volt!=volt){
							LCD_Display_Location(0,1);
							old_volt=volt;
							LCD_Display_String((uint8_t*)"           ");
							Iin=Read_Amp(volt,Itot,range,mode);
							LCD_Display_Location(0,1);
							LCD_Display_FloatNumber(Iin,3);
							_delay_ms(1);
						}
						if(volt>=810 || volt<=200){ //make sure
							_delay_ms(100);
							volt=ADC_Read(Itotpin);
						}
						//check if it didn't exceed the max range (positive or negative)
						if(volt>=810|| volt<=200){
							LCD_ClearScreen();
							LCD_HomeScreen();
							LCD_Display_String((uint8_t*)"error(big I) :(");
							LCD_Display_Location(0,1);
							LCD_Display_String((uint8_t*)"need big range;)");
							_delay_ms(1000);
							return;
						}
						volt=ADC_Read(Itotpin);
						exit_I=KEYPAD_Read();
					}
				}
				break;
			}
		}
	}
}

void display_volt(uint8_t range,uint16_t Vtot,uint16_t volt,uint8_t mode){
	
	// range 1:300m 2:3V 3:30V 4:400V 
	if (range >'5' || range <'1'){
		LCD_ClearScreen();
		LCD_HomeScreen();
		LCD_Display_String((uint8_t*)"Wrong Range :(");
		return;
	}
	
	//check if it didn't exceed the max range
	if(volt>=1003){
		LCD_ClearScreen();
		LCD_HomeScreen();
		LCD_Display_String((uint8_t*)"error(big V) :(");
		LCD_Display_Location(0,1);
		LCD_Display_String((uint8_t*)"need big range;)");
		_delay_ms(1000);
		return;
	}
	
	uint8_t exit_V;
	exit_V=0;
	uint16_t count;
	count=0;
	
	//if you want to return
	LCD_ClearScreen();
	LCD_HomeScreen();
	LCD_Display_String((uint8_t*)"To Return press:");
	LCD_Display_Location(0,1);
	LCD_Display_String((uint8_t*)"*  ;)");
	
	//check of yo want to return
	while(exit_V!='*'){
		exit_V =KEYPAD_Read();
		_delay_ms(5);
		count++;
		if(count>=200){
			count=0;
			break;
		}
	}
	if(exit_V=='*'){
		return;
	}
	uint16_t old_volt;
	old_volt=volt;
	fint32_t vin;
	count=0;
	while(exit_V != '*'){
		LCD_ClearScreen();
		LCD_HomeScreen();
		switch(mode){
			case '2':{//DC
				if(range=='1'){ //mV
					vin=1000.0*Read_Volt(volt,Vtot,range,mode);
					LCD_Display_String((uint8_t*)"Volt (mV)");
					LCD_Display_Location(0,1);
					LCD_Display_FloatNumber(vin,3);
					_delay_ms(1000);
					LCD_Display_Location(11,1);
					LCD_Display_String((uint8_t*)"*:ext");
					//if the volt value changed
					while(exit_V != '*'){
						if(old_volt!=volt){
							LCD_Display_Location(0,1);
							old_volt=volt;
							LCD_Display_String((uint8_t*)"           ");
							vin=1000.0*Read_Volt(volt,Vtot,range,mode);
							LCD_Display_Location(0,1);
							LCD_Display_FloatNumber(vin,3);
							_delay_ms(1);
						}
						if(volt>=1003 || volt<=206){ //make sure
							_delay_ms(100);
							volt=ADC_Read(VDCpin);
						}
						//check if it didn't exceed the max range (positive or negative)
						if(volt>=1003 || volt<=206){
							LCD_ClearScreen();
							LCD_HomeScreen();
							LCD_Display_String((uint8_t*)"error(big V) :(");
							LCD_Display_Location(0,1);
							LCD_Display_String((uint8_t*)"need big range;)");
							_delay_ms(1000);
							return;
						}
						volt=ADC_Read(VDCpin);
						exit_V=KEYPAD_Read();
					}
				}
				else{//V
					vin=Read_Volt(volt,Vtot,range,mode);
					LCD_Display_String((uint8_t*)"Volt (V)");
					LCD_Display_Location(0,1);
					LCD_Display_FloatNumber(vin,3);
					_delay_ms(1000);
					LCD_Display_Location(11,1);
					LCD_Display_String((uint8_t*)"*:ext");
					//if the volt value changed
					while(exit_V != '*'){
						if(old_volt!=volt){
							LCD_Display_Location(0,1);
							old_volt=volt;
							LCD_Display_String((uint8_t*)"           ");
							vin=Read_Volt(volt,Vtot,range,mode);
							LCD_Display_Location(0,1);
							LCD_Display_FloatNumber(vin,3);
							_delay_ms(1);
							}
							if(volt>=1003 || volt<=206){ //make sure
								_delay_ms(100);
								volt=ADC_Read(VDCpin);
							}
							//check if it didn't exceed the max range (positive or negative)
							if(volt>=1003|| volt<=206){
								LCD_ClearScreen();
								LCD_HomeScreen();
								LCD_Display_String((uint8_t*)"error(big V) :(");
								LCD_Display_Location(0,1);
								LCD_Display_String((uint8_t*)"need big range;)");
								_delay_ms(1000);
								return;
							}
							volt=ADC_Read(VDCpin);
							exit_V=KEYPAD_Read();
						}
					}
			break;	
			}
			case '1':{//AC
				if(range=='1'){ //mV
					uint16_t VAC;
					VAC=ADC_Read(Vtotpin);
					vin=1000.0*Read_Volt(volt,Vtot,range,mode);
					LCD_Display_String((uint8_t*)"Volt AC (mV)");
					LCD_Display_Location(0,1);
					LCD_Display_FloatNumber(vin,3);
					_delay_ms(1000);
					LCD_Display_Location(11,1);
					LCD_Display_String((uint8_t*)"*:ext");
					old_volt=VAC;
					//if the volt value changed
					while(exit_V != '*'){
						if(old_volt!=VAC){
							//check if it didn't exceed the max range (positive or negative)
							if(volt>=1003 || volt<=206){
								LCD_ClearScreen();
								LCD_HomeScreen();
								LCD_Display_String((uint8_t*)"error(big V) :(");
								LCD_Display_Location(0,1);
								LCD_Display_String((uint8_t*)"need big range;)");
								_delay_ms(1000);
								return;
							}
							LCD_Display_Location(0,1);
							old_volt=VAC;
							LCD_Display_String((uint8_t*)"           ");
							volt=ADC_Read(VDCpin);
							vin=1000.0*Read_Volt(volt,Vtot,range,mode);
							LCD_Display_Location(0,1);
							LCD_Display_FloatNumber(vin,3);
							_delay_ms(1);
						}
						VAC=ADC_Read(Vtotpin);
						exit_V=KEYPAD_Read();
					}
				}
				else{//V
					uint16_t VAC;
					VAC=ADC_Read(Vtotpin);
					vin=Read_Volt(volt,Vtot,range,mode);
					LCD_Display_String((uint8_t*)"Volt AC (V)");
					LCD_Display_Location(0,1);
					LCD_Display_FloatNumber(vin,3);
					_delay_ms(10000);
					LCD_Display_Location(11,1);
					LCD_Display_String((uint8_t*)"*:ext");
					old_volt=VAC;
					//if the volt value changed
					while(exit_V != '*'){
						if(old_volt!=VAC){
							//check if it didn't exceed the max range (positive or negative)
							if(volt>=1003|| volt<=206){
								LCD_ClearScreen();
								LCD_HomeScreen();
								LCD_Display_String((uint8_t*)"error(big V) :(");
								LCD_Display_Location(0,1);
								LCD_Display_String((uint8_t*)"need big range;)");
								_delay_ms(1000);
								return;
							}
							LCD_Display_Location(0,1);
							old_volt=VAC;
							LCD_Display_String((uint8_t*)"           ");
							volt=ADC_Read(VDCpin);
							vin=Read_Volt(volt,Vtot,range,mode);
							LCD_Display_Location(0,1);
							LCD_Display_FloatNumber(vin,3);
							_delay_ms(1);
						}
						VAC=ADC_Read(Vtotpin);
						exit_V=KEYPAD_Read();
					}
				}
				
			break;
			}
		}
	}
}

uint8_t ask_to_return(uint8_t return_key){
	uint8_t exit_test;
	uint16_t count;
	count=0;
	exit_test=0;
	//to return
	LCD_ClearScreen();
	LCD_HomeScreen();
	LCD_Display_String((uint8_t*)"To Return press:");
	LCD_Display_Location(0,1);
	LCD_Display_Character(return_key);
	LCD_Display_String((uint8_t*)"  ;)");
	count=0;
	//check if you want to return
	while(exit_test!=return_key){
		exit_test =KEYPAD_Read();
		_delay_ms(5);
		count++;
		if(count>=300){
			count=0;
			break;
		}
	}
	if(exit_test==return_key){
		return 1;
	}
	return 0;
}

void select_mux(uint8_t device,uint8_t range)
{
	
	_delay_ms(100);
	switch(device)
	{
		case '1':
		{
			switch(range)
			{
				case '1':
				{
					// Ohm range 1
					DIO_SetPinValue(DIO_PORTB, A_MUX_2, DIO_LOW);
					DIO_SetPinValue(DIO_PORTB, B_MUX_2, DIO_LOW);
					
				}
				break;
				case '2':
				{
					// Ohm range 2
					DIO_SetPinValue(DIO_PORTB, A_MUX_2, DIO_HIGH);
					DIO_SetPinValue(DIO_PORTB, B_MUX_2, DIO_LOW);
					
				}
				break;
				case '3':
				{
					// Ohm range 3
					DIO_SetPinValue(DIO_PORTB, A_MUX_2, DIO_LOW);
					DIO_SetPinValue(DIO_PORTB, B_MUX_2, DIO_HIGH);
					
				}
				break;
			}
		}
		break;//for ohm device
		case '2'://ammeter
		{
			DIO_SetPinValue(DIO_PORTB, A_MUX_2, DIO_LOW);
			_delay_ms(100);
			switch(range)
			{
				case '1'://2mA range
				{
					// Ammeter range 1
					DIO_SetPinValue(DIO_PORTB, A_MUX_3, DIO_HIGH);
					DIO_SetPinValue(DIO_PORTB, B_MUX_3, DIO_HIGH);
				}
				break;
				case '2'://20mA range
				{
					// Ammeter range 2
					DIO_SetPinValue(DIO_PORTB, A_MUX_3, DIO_LOW);
					DIO_SetPinValue(DIO_PORTB, B_MUX_3, DIO_HIGH);
				}
				break;
				case '3'://200mA range
				{
					// ammeter range 3
					DIO_SetPinValue(DIO_PORTB, A_MUX_3, DIO_HIGH);
					DIO_SetPinValue(DIO_PORTB, B_MUX_3, DIO_LOW);
				}
				break;
				case '4'://1A range
				{
					// ammeter range 4
					DIO_SetPinValue(DIO_PORTB, A_MUX_3, DIO_LOW);
					DIO_SetPinValue(DIO_PORTB, B_MUX_3, DIO_LOW);
				}
				break;
				default:
				LCD_Display_String((uint8_t*)"Wrong, select a proper current range");
				break;
			}
		}
		break;//for Ammeter device
		case '3': //voltage
		{
			DIO_SetPinValue(DIO_PORTB, A_MUX_2, DIO_HIGH);
			_delay_ms(100);
			switch(range)
			{
				case '1':
				{
					// Volt range 1
					DIO_SetPinValue(DIO_PORTB, A_MUX_3, DIO_HIGH);
					DIO_SetPinValue(DIO_PORTB, B_MUX_3, DIO_HIGH);
				}
				break;
				case '2':
				{
					// Volt range 2
					DIO_SetPinValue(DIO_PORTB, A_MUX_3, DIO_LOW);
					DIO_SetPinValue(DIO_PORTB, B_MUX_3, DIO_HIGH);
				}
				break;
				case '3':
				{
					// Volt range 3
					DIO_SetPinValue(DIO_PORTB, A_MUX_3, DIO_HIGH);
					DIO_SetPinValue(DIO_PORTB, B_MUX_3, DIO_LOW);
				}
				break;
				case '4':
				{
					// Volt range 4
					DIO_SetPinValue(DIO_PORTB, A_MUX_3, DIO_LOW);
					DIO_SetPinValue(DIO_PORTB, B_MUX_3, DIO_LOW);
				}
				break;
			}
		}
		break;//for volt device
	}
	return;
}

uint8_t select_LCD(char row1[],char row2[],uint8_t num,uint8_t return_key){
	uint8_t keypad_read;
	uint16_t count;
	uint8_t num_test;
	num_test=0;
	count=0;
	//choosing the ranges
	LCD_ClearScreen();
	LCD_HomeScreen();
	LCD_Display_String((uint8_t*)row1);
	LCD_Display_Location(0,1);
	LCD_Display_String((uint8_t*)row2);
	keypad_read =KEYPAD_Read();
	//waiting to select
	while (keypad_read !=return_key){
		for(uint8_t i=0;i<num;i++){
			if(keypad_read==('1'+i)){
				num_test=1;
				break;
			}
		}
		if(num_test==1)
		break;
		keypad_read =KEYPAD_Read();
		_delay_ms(5);
		count++;
		//waited for too long
		if(count>=500){
			count=0;
			LCD_ClearScreen();
			LCD_HomeScreen();
			LCD_Display_String((uint8_t*)"Ok I can do this");
			LCD_Display_Location(0,1);
			LCD_Display_String((uint8_t*)"all day! :)");
			while(keypad_read !=return_key && count<500){
				keypad_read =KEYPAD_Read();
				_delay_ms(5);
				for(uint8_t i=0;i<num;i++){
					if(keypad_read==('1'+i)){
						num_test=1;
						break;
					}
				}
				if(num_test==1)
				break;
				_delay_ms(5);
				count++;
			}
			count=0;
			//ask again
			LCD_ClearScreen();
			LCD_HomeScreen();
			if(keypad_read!=return_key && num_test!=1){
				LCD_Display_String((uint8_t*)row1);
				LCD_Display_Location(0,1);
				LCD_Display_String((uint8_t*)row2);
			}
		}
	}
	return keypad_read;
}
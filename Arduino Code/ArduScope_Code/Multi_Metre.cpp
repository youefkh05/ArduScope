#include "Multi_Metre.h"

void MM_Init(void)
{
  //setting the pins
  pinMode(A_MUX_1, OUTPUT);
  pinMode(A_MUX_2, OUTPUT);
  pinMode(B_MUX_1, OUTPUT);
  pinMode(B_MUX_2, OUTPUT);
}

fint32_t Read_Volt(uint16_t Vout, uint16_t Vtot, uint8_t Vrange, uint8_t mode)
{
	//check if it didn't exceed the max range (positive or negative)
	if(1003<=Vout || Vout<=206)
  {
		return 999.99;
	}
	//check if it was too small
	if(518<=Vout && Vout <=524)
  {
		return 0.0;
	}

  // VIN_TO_V_OUT_MCU = Vdivider * VIN + Vconst
	
	fint32_t Vdivider;

	Vdivider = -1;

	fint32_t Vconst;

	Vconst  = -1;
  
	switch(Vrange)
	{
		case '1'://300mV
		Vdivider  =   5.984;
		Vconst    =   2.47859;
		break;

		case '2'://3V
		Vdivider  =   0.59884;
		Vconst    =   2.5418;
		break;

		case '3'://30V
		Vdivider  =   0.0587325;
		Vconst    =   2.5144325;
		break;

		case '4'://400V
		Vdivider  =   0.0047988;
		Vconst    =   2.545246;
		break;

    default:
		//LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
		break;
	}
	
	switch(mode){
		case '2'://DC
    { 
      fint32_t Val = Vout*5.0/1024.0;
      Val = ((Val-Vconst)/(Vdivider)); //equation
      _delay_ms(5);
      return Val;
		}

		case '1'://AC
    { 

			if(Vtot<=(Vout+2))
      { //AC is zero
				  return 0.0;
			}

			switch(Vrange)
			{
				case '1'://300mV
				Vout  =   Vtot-Vout+506;
				break;

				case '2'://3V
				Vout  =   Vtot-Vout+520;
				break;

				case '3'://30V
				Vout  =   Vtot-Vout+516;
				break;

				case '4'://400V
				Vout  =   Vtot-Vout+522;
				break;
			}					

			fint32_t Val;

			Val = Vout*5.0/1024.0;

			Val = ((Val-Vconst)/(Vdivider)); //equation

			_delay_ms(5);
			
			return Val;
		}
	}   
	
}

fint32_t Read_Amp(uint16_t Iout, uint16_t Itot, uint8_t Irange, uint8_t mode)
{	
	//check if it didn't exceed the max range (positive or negative)
	if(810<=Iout || Iout<=200)
  {
		return 999.99;
	}

	//check if it was too small
	if(406<=Iout && Iout <=414)
  {
		return 0.0;
	}
	
	// I_TO_V_OUT_MCU = I_Slope * I_input + I_intercept

	fint32_t I_input        =   -1;

	fint32_t I_TO_V_OUT_MCU =   0;

	switch(mode)
  {
		case '1': //AC
			I_TO_V_OUT_MCU = (Itot * 5.0) / 1024.0;
      break;

		case '2': //DC
			I_TO_V_OUT_MCU = (Iout * 5.0) / 1024.0;	
      break;

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
		//LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
		break;
	}

	I_input = (I_TO_V_OUT_MCU - I_intercept) / I_Slope;
	_delay_ms(5);

	return I_input;
	
}

fint32_t Read_Ohm(uint16_t Rout, uint8_t range)
{
	// range 1:10k 2:100k 3: 1M
	if (range > '5' || range < '1')
  {
		return -1;
	}

	//Rin = (Rdivider *Rout)/(Max_Volt-Rout)
  fint32_t Rdivider   =   -1;

  fint32_t Max_Volt   =   1024.0;

  switch(range)
  {
    case '1'://10k  Ohm
		Rdivider     = 0.450;
		break;

		case '2'://100k Ohm
		Rdivider     = 1.35;
		break;

		case '3'://1M   Ohm
		Rdivider     = 10.0;
		break;

    default:
		//LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
		break;
  }

	fint32_t Rin  = 0;
  
	Rin=(Rdivider *Rout)/(Max_Volt-Rout);
	_delay_ms(5);

	return Rin;

}
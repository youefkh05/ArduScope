#include "Multi_Metre.h"

void MM_Init(void)
{
  //setting the pins
  pinMode(A_MUX_1, OUTPUT);
  pinMode(A_MUX_2, OUTPUT);
  pinMode(B_MUX_1, OUTPUT);
  pinMode(B_MUX_2, OUTPUT);
}

fint32_t Read_Volt( uint8_t Vrange, uint8_t mode)
{

  // Vin = VSlope *  Vout + Vconst
	
  int Vout;

  Vout=-1;

  fint32_t Vin;

	Vin = -1;

	fint32_t V_Slope;

	V_Slope = -1;

	fint32_t Vconst;

	Vconst  = -1;
  
  switch(mode)
  { 
    case DC_MODE:

      Vout=analogRead(OUT_DC_PIN);
      
      switch(Vrange)
      {
        case  range1 ://300mV
        V_Slope   =   0.139574;
        Vconst    =   -0.28634;
        break;

        case  range2 ://3V
        V_Slope   =   1.394078;
        Vconst    =   -2.96428;
        break;

        case  range3 ://30V
        V_Slope  =   0.0587325;
        Vconst    =   2.5144325;
        break;

        case  range4 ://400V
        V_Slope  =   0.0047988;
        Vconst    =   2.545246;
        break;

        default:
        //LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
        break;
      }
    break;

    case AC_MODE:

      Vout=analogRead(OUT_AC_PIN);

      switch(Vrange)
      {
        case  range1 ://300mV
        V_Slope   =   0.1664;
        Vconst    =   -0.35624;
        break;

        case  range2 ://3V
        V_Slope   =   1.634254;
        Vconst    =   -3.683854;
        break;

        case  range3 ://30V
        V_Slope  =   0.0587325;
        Vconst    =   2.5144325;
        break;

        case  range4 ://400V
        V_Slope  =   0.0047988;
        Vconst    =   2.545246;
        break;

        default:
        //LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
        break;
      }
    break;  
  }

  //check if it didn t exceed the max range (positive or negative)
	if(880<= Vout ||  Vout<=206)
  {
		return -1.99;
	}
    
  //make it in volt and float  
  fint32_t  Vf =  Vout*5.0/1024.0;

  //Serial.print("Vf= ");
  //Serial.println(Vf);

  Vin = V_Slope*  Vf + Vconst; //equation
      
  return Vin;  
	
}

fint32_t Read_Amp(uint16_t Iout, uint16_t Itot, uint8_t Irange, uint8_t mode)
{	
	//check if it didn t exceed the max range (positive or negative)
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
		case  1 : //AC
			I_TO_V_OUT_MCU = (Itot * 5.0) / 1024.0;
      break;

		case  2 : //DC
			I_TO_V_OUT_MCU = (Iout * 5.0) / 1024.0;	
      break;

	}

	fint32_t I_Slope     = -1;

	fint32_t I_intercept = -1;

	switch(Irange)
	{
		case  1 ://2mA
		I_Slope     = 0.86857;
		I_intercept = 2.263;
		break;

		case  2 ://20mA
		I_Slope     = 0.09;
		I_intercept = 2.31;
		break;

		case  3 ://200mA
		I_Slope     = 0.0124;
		I_intercept = 2.01;
		break;

		case  4 ://1A
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
	if (range >  5  || range <  1 )
  {
		return -1;
	}

	//Rin = (Rdivider *Rout)/(Max_Volt-Rout)
  fint32_t Rdivider   =   -1;

  fint32_t Max_Volt   =   1024.0;

  switch(range)
  {
    case  1 ://10k  Ohm
		Rdivider     = 0.450;
		break;

		case  2 ://100k Ohm
		Rdivider     = 1.35;
		break;

		case  3 ://1M   Ohm
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

void Select_Mux(uint8_t device, uint8_t range)
{
	
	_delay_ms(100);
	switch(device)
	{
		case  1 :
		{ //Ohm
			switch(range)
			{
				case  1 :
				{
					// Ohm range 1
					digitalWrite( A_MUX_1, LOW);
					digitalWrite( B_MUX_1, LOW);
					
				}
				break;

				case  2 :
				{
					// Ohm range 2
					digitalWrite( A_MUX_2, HIGH);
					digitalWrite( B_MUX_2, LOW);
					
				}
				break;

				case  3 :
				{
					// Ohm range 3
					digitalWrite(  A_MUX_2,  LOW);
					digitalWrite(  B_MUX_2, HIGH);
					
				}
				break;
			}
		}
		break;//for ohm device

		case  2 ://ammeter
		{ 
      //there is only one range
      digitalWrite( A_MUX_1, LOW);
      digitalWrite( B_MUX_1, LOW);
      _delay_ms(100);
			digitalWrite( A_MUX_2, LOW);
      digitalWrite( B_MUX_2, LOW);

		}
		break;//for Ammeter device

		case  3 : //voltage
		{
			digitalWrite( A_MUX_1, LOW);
      digitalWrite( B_MUX_1, LOW);
			_delay_ms(100);
			switch(range)
			{
				case  1 :
				{
					// Volt range 1
          digitalWrite( A_MUX_2, LOW);
					digitalWrite( B_MUX_2, LOW);
					
				}
				break;

				case  2 :
				{
					// Volt range 2
          digitalWrite( A_MUX_2, HIGH);
					digitalWrite( B_MUX_2, LOW);
					
				}
				break;

				case  3 :
				{
					// Volt range 3
					digitalWrite( A_MUX_2, LOW);
					digitalWrite( B_MUX_2, HIGH);
				}
				break;

				case  4 :
				{
					// Volt range 4
					digitalWrite( A_MUX_2, HIGH);
					digitalWrite( B_MUX_2, HIGH);
				}
				break;

			}
		}
		break;//for volt device
	}
  
	return;
}
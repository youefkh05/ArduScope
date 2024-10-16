#include "Multi_Metre.h"

void MM_Init(void)
{
  //setting the pins
  pinMode(A_MUX_1, OUTPUT);
  pinMode(A_MUX_2, OUTPUT);
  pinMode(B_MUX_1, OUTPUT);
  pinMode(B_MUX_2, OUTPUT);
}

float Read_Volt(uint16_t Vout, uint16_t Vtot, uint8_t Vrange, uint8_t mode)
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
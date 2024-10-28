#include "Multi_Metre_Sig.h"

#define DC_BIAS_VAL   (450)

void MM_Init(void)
{
  //setting the pins
  pinMode(A_MUX_1_PIN, OUTPUT);
  pinMode(A_MUX_2_PIN, OUTPUT);
  pinMode(B_MUX_1_PIN, OUTPUT);
  pinMode(B_MUX_2_PIN, OUTPUT);
}

float Read_Volt( ranges Vrange, modes mode)
{
  // Vin = VSlope *  Vout + Vconst
	
  int Vout;

  Vout=-1;

  float Vin;

	Vin = -1;
  /*
	float V_Slope;

	V_Slope = -1;

	float Vconst;

	Vconst  = -1;
  */
  
  switch(mode)
  { 
    case DC_MODE:

      Vout=analogRead(OUT_DC_PIN);
      Vin =  Vout*5.0/1024.0;
      //Vin = V_Slope*  Vf + Vconst; //equation

      switch(Vrange) 
      {
        case  range1 ://300mV
        //V_Slope   =   0.139574;
        //Vconst    =   -0.28634;
        Vin= (0.139574*Vin) -0.28634;
        break;

        case  range2 ://3V
        //V_Slope   =   1.394078;
        //Vconst    =   -2.96428;
        Vin= (1.394078*Vin) -2.96428;
        break;
        /*
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
        */
      }
    break;

    case AC_MODE:

      Vout=analogRead(OUT_AC_PIN)-analogRead(OUT_DC_PIN)+DC_BIAS_VAL;
      Vin =  Vout*5.0/1024.0;

      switch(Vrange)
      {
        case  range1 ://300mV
        //V_Slope   =   0.1664;
        //Vconst    =   -0.35624;
        Vin= (0.1664*Vin) -0.35624;
        break;

        case  range2 ://3V
        //V_Slope   =   1.634254;
        //Vconst    =   -3.683854;
        Vin= (1.634254*Vin) -3.683854;
        break;
        /*
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
        */
      }
    break;  
  }

  //check if it didn t exceed the max range (positive or negative)
	if(880<= Vout ||  Vout<=206)
  {
		return -1.99;
	}
    
  //make it in volt and float  
  //float  Vf =  Vout*5.0/1024.0;

  //Serial.print("Vf= ");
  //Serial.println(Vf);

  //Vin = V_Slope*  Vf + Vconst; //equation
      
  return Vin;  
	
}

float Read_Amp( ranges Irange, modes mode)
{	

  // Iin = ISlope *  Iout + Iconst
	
  int Iout;

  Iout=-1;

  float Iin;

	Iin = -1;
  /*
	float I_Slope;

	I_Slope = -1;

	float Iconst;

	Iconst  = -1;
  */
   switch(mode)
  { 
    case DC_MODE:

      Iout=analogRead(OUT_DC_PIN);
      Iin =  Iout*5.0/1024.0;

      switch(Irange)
      {
        case  range1 ://2mAmp
        //I_Slope   =   0.139574;
        //Iconst    =   -0.28634;
        Iin= (0.139574*Iin) -0.28634;
        break;

        case  range2 ://20mAmp
        //I_Slope   =   83.8305;
        //Iconst    =   -173.84642;
        Iin= (83.8305*Iin) -173.84642;
        break;
        /*
        case  range3 ://200mAmp
        I_Slope   =   83.8305;
        Iconst    =   -173.84642;
        break;

        case  range4 ://1Amp
        I_Slope  =   0.0047988;
        Iconst    =   2.545246;
        break;

        default:
        //LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
        break;
        */
      }
    break;

    case AC_MODE:

      Iout=analogRead(OUT_AC_PIN)-analogRead(OUT_DC_PIN)+DC_BIAS_VAL;
      Iin =  Iout*5.0/1024.0;

      switch(Irange)
      {
        case  range1 ://2mAmp
        //I_Slope   =   83.8305;
        //Iconst    =   -173.84642;
        Iin= (83.8305*Iin) -173.84642;
        break;

        case  range2 ://20mAmp
        //I_Slope   =   1.634254;
        //Iconst    =   -3.683854;
        Iin= (1.634254*Iin) -3.683854;
        break;
        /*
        case  range3 ://200mAmp
        I_Slope   =   90.91;
        Iconst    =   -195.4545;
        break;

        case  range4 ://1Amp
        I_Slope  =   0.0047988;
        Iconst    =   2.545246;
        break;

        default:
        //LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
        break;
        */
      }
    break;  
  }

  //Serial.print("Iout= ");
  //Serial.println(Iout);

  //check if it didn t exceed the max range (positive or negative)
	if(1000<= Iout ||  Iout<=206)
  {
		return -1.99;
	}

  /*  
  //make it in volt and float  
  float  If =  Iout*5.0/1024.0;

  //Serial.print("If= ");
  //Serial.println(If);

  Iin = I_Slope*  If + Iconst; //equation
  */

  return Iin;  
	
}

float Read_Ohm( ranges range)
{
	// range 1:10k 2:100k 3: 1M
	if (range >  5  || range <  1 )
  {
		return -1;
	}

	//Rin = m1* Rout^2 +m2* Rout + Rconst

  int Rout=analogRead(OUT_RIN_PIN);

  float Rin  = Rout*5.0/1024.0;;
  /*
  float m1       =   -1;

  float m2       =   -1;

  float Rconst   =   -1;
  */

  switch(range)
  {
    case  range1 ://10k  Ohm

		  //m1      =   7.408666;

      //m2      =   -58.75646;

      //Rconst  =   118.38925;

      Rin=(7.408666* Rin* Rin) +(-58.75646* Rin) +118.38925;
		break;

		case  range2 ://100k Ohm
	
		//m1      =   874.13015;

    //m2      =   -8139.9605;

    //Rconst  =   18961.3339;

    Rin=(874.13015* Rin* Rin) +(-8139.9605* Rin) +18961.3339;
		break;

		case  range3 ://1M   Ohm
		
		//m1      =   17433.97271;

    //m2      =   -165272.9212;

    //Rconst  =   391784.0959;

    Rin=(17433.97271* Rin* Rin) +(-165272.9212* Rin) +391784.0959;

		break;

    default:
		//LCD_Display_String((uint8_t*)"Wrong, select a proper range ya 7aywan");
		break;
  }

  /*
  //make it in volt and float  
  float  Rf =  Rout*5.0/1024.0;

  //Serial.print("Rf= ");
  //Serial.println(Rf);
  
	Rin=m1* Rf* Rf + m2* Rf + Rconst;
  */

	return Rin;

}

void Select_Mux(devices device, ranges range)
{
	
	switch(device)
	{
		case  Ohmeter :
		{ //Ohm
			switch(range)
			{
				case  range1  :
				{
					// Ohm range 1
					digitalWrite( A_MUX_1_PIN, LOW);
					digitalWrite( B_MUX_1_PIN, LOW);
					
				}
				break;

				case  range2  :
				{
					// Ohm range 2
					digitalWrite( A_MUX_1_PIN, HIGH);
					digitalWrite( B_MUX_1_PIN, LOW);
					
				}
				break;

				case  range3  :
				{
					// Ohm range 3
					digitalWrite(  A_MUX_1_PIN,  LOW);
					digitalWrite(  B_MUX_1_PIN, HIGH);
					
				}
				break;
			}
		}
    _delay_ms(2);
		break;//for ohm device

		case  Ammeter ://ammeter
		{ 
      //there is only one range
      digitalWrite( B_MUX_2_PIN, LOW);
      

		}
    _delay_ms(2);
		break;//for Ammeter device

		case  Voltmeter : //voltage
		{
			
      digitalWrite( B_MUX_2_PIN, HIGH);
			switch(range)
			{
				case  range1 :
				{
					// Volt range 1
          digitalWrite( A_MUX_2_PIN, LOW);

				}
				break;

				case  range2 :
				{
					// Volt range 2
          digitalWrite( A_MUX_2_PIN, HIGH);

				}
				break;
        /*
				case  range3 :
				{
					// Volt range 3
					digitalWrite( A_MUX_2_PIN, LOW);

				}
				break;

				case  range4 :
				{
					// Volt range 4
					digitalWrite( A_MUX_2_PIN, HIGH);

				}
				break;
        */

			}
		}
    _delay_ms(2);
		break;//for volt device

    case  Square : //Square
		{
			
      digitalWrite( A_MUX_1_PIN, LOW);
      digitalWrite( B_MUX_1_PIN, LOW);

		}
    _delay_ms(2);
		break;//for Square device

    case  Tri  : //Tri 
		{
			
      digitalWrite( A_MUX_1_PIN, HIGH);
      digitalWrite( B_MUX_1_PIN, LOW);

		}
    _delay_ms(2);
		break;//for Tri  device

    case  Sin  : //Sin 
		{
			
      digitalWrite( A_MUX_1_PIN, LOW);
      digitalWrite( B_MUX_1_PIN, HIGH);


		}
    _delay_ms(2);
		break;//for Sin  device
	}
  
	return;
}
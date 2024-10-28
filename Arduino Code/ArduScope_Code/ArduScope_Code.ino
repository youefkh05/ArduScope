
#include "Multi_Metre_Sig.h"

#include "U8glib.h"
//#include <stdint.h>

//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_NO_ACK | U8G_I2C_OPT_FAST); // Fast I2C / TWI

ranges range=range2;
modes mode=DC_MODE;
devices device=Voltmeter;

void setup() {
  // Set the pins as output
  MM_Init();
  Select_Mux(device, range);
  Serial.begin(9600);
}

void loop()
{  
  //Serial.print("Volt = ");
  //Serial.println(sizeof(u8g));
  
    float x=Read_Volt(range, mode);
    Serial.print("Volt = ");
    Serial.println(x);
    delay(100);
    /*
    x=Read_Amp(range, mode);

    x=Read_Ohm( range);
    */
}

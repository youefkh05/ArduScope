
#include "Multi_Metre.h"

ranges range=range2;
modes mode=AC_MODE;
devices device=Voltmeter;

void setup() {
  // Set the pins as output
  MM_Init();
  Select_Mux(device, range);
  Serial.begin(9600);
}

void loop()
{  
    fint32_t x=Read_Volt(range, mode);
    Serial.print("Volt = ");
    Serial.println(x);
    delay(100);
}


#include "Multi_Metre_Sig.h"

ranges range=range2;
modes mode=DC_MODE;
devices device=Tri;

void setup() {
  // Set the pins as output
  MM_Init();
  Select_Mux(device, range);
  Serial.begin(9600);
}

void loop()
{  /*
    fint32_t x=Read_Volt(range, mode);
    Serial.print("Volt = ");
    Serial.println(x);
    delay(100);
    */
}

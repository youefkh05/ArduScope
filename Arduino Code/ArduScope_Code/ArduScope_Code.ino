
#include "Multi_Metre.h"

ranges range=range3;
modes mode=DC_MODE;
devices device=Ammeter;

void setup() {
  // Set the pins as output
  MM_Init();
  Select_Mux(device, range);
  Serial.begin(9600);
}

void loop()
{  
    fint32_t x=Read_Amp(range, mode);
    Serial.print("Amp = ");
    Serial.println(x);
    delay(100);
}

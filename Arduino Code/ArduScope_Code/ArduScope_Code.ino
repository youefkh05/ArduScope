
#include "Multi_Metre.h"

int range=range2;
int mode=DC_MODE;
int device=Ohmeter;

void setup() {
  // Set the pins as output
  MM_Init();
  Select_Mux(device, range);
  Serial.begin(9600);
}

void loop()
{  
    fint32_t x=Read_Ohm(range);
    Serial.print("Ohm = ");
    Serial.println(x);
    delay(100);
}

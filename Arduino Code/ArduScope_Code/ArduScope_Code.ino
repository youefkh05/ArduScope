
#include "Multi_Metre.h"

int range=range3;
int mode=AC_MODE;

void setup() {
  // Set the pins as output
  MM_Init();
  Serial.begin(9600);
}

void loop()
{  
    fint32_t x=Read_Amp(range, mode);
    Serial.print("Amp = ");
    Serial.println(x);
    delay(100);
}

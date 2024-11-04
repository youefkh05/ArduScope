#include "Osci.h"

extern Adafruit_SH1106 oled;        // use this when SH1106

void setup() {
  Osci_Init();
}

void loop() {
  oled.clearDisplay();
  oled.setTextSize(1);                    // at double size character
  oled.setTextColor(WHITE);
  oled.setCursor(40, 0);
  oled.println(F("ArduScdsfsdo;ope"));  
  oled.setCursor(30, 20);
  oled.println(F("Oscilloscopsdlkke")); 
  oled.setCursor(55, 42);            
  oled.println(F(";)"));                
  oled.display();                         
  delay(1500);
  oled.clearDisplay();
  oled.setTextSize(1);      
   //Osci_Run();

     oled.clearDisplay();
  oled.setTextSize(1);                    // at double size character
  oled.setTextColor(WHITE);
  oled.setCursor(40, 0);
  oled.println(F("ArduSc"));  
  oled.setCursor(30, 20);
  oled.println(F("Oscilloe")); 
  oled.setCursor(55, 42);            
  oled.println(F(";"));                
  oled.display();                         
  delay(1500);
  oled.clearDisplay();
  oled.setTextSize(1);   
  
}

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define   ANCHO 128
#define   ALTO  64

Adafruit_SSD1306  display(ANCHO,  ALTO, &Wire,  -1);

void setup(){
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)){
    Serial.println("NO DIS");
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("NO DIS");
  display.display();
  delay(100);

}

void loop(){

}
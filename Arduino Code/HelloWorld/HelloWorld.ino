#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "Osci.h"

#define   SCREEN_WIDTH 128
#define   SCREEN_HEIGHT  64

extern Adafruit_SSD1306 oled;   // device name is oled


void setup(){
  Serial.begin(9600);
  Osci_Init();
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3D)){
    Serial.println("NO DIS");
    for(;;);
  }

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.println("NO DIS");
  oled.display();
  delay(3000);

}

void loop(){
  //Osci_Run();
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.println("NO DIS2");
  oled.display();
  delay(3000);
}
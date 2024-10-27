#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "Osci.h"

#define   SCREEN_WIDTH 128
#define   SCREEN_HEIGHT  64
#define   LED1  (12)
#define   LED2  (7)
#define   LED3  (6)
#define   LED4  (5)

//extern Adafruit_SSD1306 oled;   // device name is oled

bool x=false;

void setup(){
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  digitalWrite(LED1,HIGH);
  delay(100);
  digitalWrite(LED1,LOW);
  delay(100);
  digitalWrite(LED1,HIGH);
  delay(100);
  //Serial.begin(9600);
  Osci_Init();
  digitalWrite(LED2,HIGH);
  delay(100);
  digitalWrite(LED2,LOW);
  delay(100);
  digitalWrite(LED2,HIGH);
  delay(100);
  /*
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3D)){
    Serial.println("NO DIS45");
    for(;;);
  }

  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.println("NO DIS45");
  oled.display();
  delay(3000);
  */
}

void loop(){
  digitalWrite(LED3,HIGH);
  delay(100);
  digitalWrite(LED3,LOW);
  delay(100);
  digitalWrite(LED3,HIGH);
  delay(100);
  Osci_Run();
  x=!x;
  if(x==true){
    digitalWrite(LED4,LOW);
  }
  else{
    digitalWrite(LED4,HIGH);
  }
  /*
  x++;
  Serial.print("Volt = ");
  Serial.println(x);
  delay(3000);
  /*
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(1,0);
  oled.println("NO DIS2");
  oled.display();
  delay(3000);
  */
}
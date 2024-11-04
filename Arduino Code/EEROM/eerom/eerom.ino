#include "eerom_map.h"


void setup() {
    // Initialize serial for debugging
    Serial.begin(9600);
    
    // Write each bitmap to EEPROM
    writeBitmapToEEPROM(sig_gen_bitmap,3 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(volt_bitmap,0 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(amm_bitmap,1 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(ohm_bitmap,2 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(config_bitmap ,4 , BIT_MAP_SIZE);
    
    
    delay(3000);
    // Buffer to hold the bitmap read from EEPROM
    uint8_t bitmapBuffer[BIT_MAP_SIZE];

    for(int i=0;i<5;i++){
      // Read bitmap from EEPROM
      readBitmapFromEEPROM(bitmapBuffer, i, BIT_MAP_SIZE);
      Serial.print("BIT MAP PIC  ");
      Serial.println(i);
      Serial.println();
      // For debugging, print out bitmap data
      for (int i = 0; i < 32; i++) {
          Serial.print(bitmapBuffer[i], HEX);
          Serial.print(" ");
      }
      Serial.println();
      Serial.println();
      
      delay(1000);
    }

    delay(5000);
    pinMode(LED_BUILTIN, OUTPUT);
  
    // To store other bitmaps, you can call writeBitmapToEEPROM for each, with the corresponding address
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second

    /*
    // Buffer to hold the bitmap read from EEPROM
    uint8_t bitmapBuffer[BIT_MAP_SIZE];

    for(int i=0;i<5;i++){
      // Read bitmap from EEPROM
      readBitmapFromEEPROM(bitmapBuffer, i, BIT_MAP_SIZE);
      Serial.print("BIT MAP  ");
      Serial.println(i);
      Serial.println();
      // For debugging, print out bitmap data
      for (int i = 0; i < 32; i++) {
          Serial.print(bitmapBuffer[i], HEX);
          Serial.print(" ");
      }
      Serial.println();
      Serial.println();
      
      delay(1000);
    }

    delay(5000);
    */
}

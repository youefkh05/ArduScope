#include "eerom_map.h"
#include <avr/pgmspace.h>
#include <Arduino.h>

#define MAX_ITEM_LENGTH 20 // Adjust this according to your max string length

// save some unsigned ints
const PROGMEM uint16_t charSet[] = { 65000, 32796, 16843, 10, 11234};

// save some chars
const char signMessage[] PROGMEM = {"I AM PREDATOR,  UNSEEN COMBATANT. CREATED BY THE UNITED STATES DEPART"};

unsigned int displayInt;
char myChar[MAX_ITEM_LENGTH+1];

const char menu_items[6][MAX_ITEM_LENGTH] PROGMEM = {
  {"Voltmeter"},
  {"Ammeter"},
  {"Ohmmeter"},
  {"Sig Gen"},
  {"Scope"},
  {"Config"}
};

const char sig_menu_items[4][MAX_ITEM_LENGTH] PROGMEM = {
  {"Off"},
  {"Square"},
  {"Triangular"},
  {"Sine Wave"}
};



void setup() {
    // Initialize serial for debugging
    Serial.begin(9600);
    Serial.println("Start"); 
    delay(2000);

    while (!Serial);  // wait for serial port to connect. Needed for native USB

  // put your setup code here, to run once:
  // read back a 2-byte int
  for (byte k = 0; k < 5; k++) {
    displayInt = pgm_read_word_near(charSet + k);
    Serial.println(displayInt);
  }
  Serial.println();

  // read back a char
  for (int k = 0; k < MAX_ITEM_LENGTH; k++) {
    myChar[k] = pgm_read_byte_near(signMessage + k);
    //Serial.print(myChar[]);
  }
  myChar[MAX_ITEM_LENGTH]='\0';

  Serial.println(myChar);

    /*
    // Write each bitmap to EEPROM
    writeBitmapToEEPROM(sig_gen_bitmap,3 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(volt_bitmap,0 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(amm_bitmap,1 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(ohm_bitmap,2 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(config_bitmap ,4 , BIT_MAP_SIZE);
    
    
    delay(3000);
    */
    /*
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
    */

    
    /*
    char buffer[MAX_ITEM_LENGTH]; // Buffer to hold the read string

    // Reading menu items
    for (int i = 0; i < 6; i++) {
        strcpy_P(buffer, (char*)pgm_read_word(&(menu_items[i])));
        Serial.println(buffer); // Print each menu item
    }

    // Reading signal menu items
    for (int i = 0; i < 4; i++) {
        strcpy_P(buffer, (char*)pgm_read_word(&(sig_menu_items[i])));
        Serial.println(buffer); // Print each signal menu item
    }
    */

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

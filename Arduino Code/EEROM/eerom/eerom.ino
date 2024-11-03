#include <EEPROM.h>
#include <avr/pgmspace.h>  // For PROGMEM

// EEPROM addresses for each bitmap
#define BIT_MAP_SIZE    (32)

// 'oled_display_menus-Recovered_0003_sig_gen', 16x16px
const unsigned char sig_gen_bitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x87, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 
	0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0xe0, 0xfc, 0x00, 0x00, 0x00, 0x00
};
// 'oled_display_menus-Recovered_0004_V', 16x16px
const unsigned char volt_bitmap [] PROGMEM = {
	0xfc, 0x3f, 0x60, 0x0c, 0x60, 0x08, 0x30, 0x10, 0x30, 0x10, 0x18, 0x10, 0x18, 0x20, 0x0c, 0x20, 
	0x0c, 0x40, 0x0e, 0x40, 0x06, 0x80, 0x06, 0x80, 0x03, 0x80, 0x03, 0x00, 0x01, 0x00, 0x01, 0x00
};
// 'oled_display_menus-Recovered_0006_A', 16x16px
const unsigned char amm_bitmap [] PROGMEM = {
	0x00, 0x00, 0x03, 0xc0, 0x07, 0xe0, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0x30, 
	0x0f, 0xf0, 0x0f, 0xf0, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0x30, 0x0c, 0x30, 0x00, 0x00
};
// 'oled_display_menus-Recovered_0005_Ohm', 16x16px
const unsigned char ohm_bitmap [] PROGMEM = {
	0x00, 0x00, 0x07, 0xe0, 0x1f, 0xf8, 0x3c, 0x3c, 0x78, 0x1e, 0x60, 0x06, 0xc0, 0x03, 0xc0, 0x03, 
	0xc0, 0x03, 0xc0, 0x03, 0x70, 0x0e, 0x70, 0x0e, 0x38, 0x1c, 0xf8, 0x1f, 0xf8, 0x1f, 0x00, 0x00
};

// 'oled_display_menus-Recovered_0006_config', 16x16px
const unsigned char config_bitmap [] PROGMEM = {
	0x01, 0x80, 0x01, 0x80, 0x1a, 0x58, 0x36, 0x6c, 0x20, 0x04, 0x11, 0x88, 0x33, 0xcc, 0xc6, 0x63, 
	0xc6, 0x63, 0x33, 0xcc, 0x11, 0x88, 0x20, 0x04, 0x36, 0x6c, 0x1a, 0x58, 0x01, 0x80, 0x01, 0x80
};
// Function to write bitmap to EEPROM
void writeBitmapToEEPROM(const unsigned char* bitmap, int index, int size) {
    for (int i = 0; i < size; i++) {
        // Read byte from PROGMEM and write to EEPROM
        EEPROM.write((index*BIT_MAP_SIZE)+i, pgm_read_byte(&bitmap[i]));
    }
}

// Function to read bitmap from EEPROM and store in RAM for display
void readBitmapFromEEPROM(uint8_t* buffer, int index, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = EEPROM.read((index*BIT_MAP_SIZE) + i);
    }
}

void setup() {
    // Initialize serial for debugging
    Serial.begin(9600);
    /*
    // Write each bitmap to EEPROM
    writeBitmapToEEPROM(sig_gen_bitmap,0 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(volt_bitmap,1 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(amm_bitmap,2 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(ohm_bitmap,3 , BIT_MAP_SIZE);
    writeBitmapToEEPROM(config_bitmap ,4 , BIT_MAP_SIZE);
    */
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

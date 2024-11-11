#include "application.h" 

extern Adafruit_SH1106 oled;        // oled handeler

// Function to read a string from PROGMEM
void getSignalMenuItem(uint8_t index, char *buffer, size_t bufferSize) {
    if (index < 4) { // Adjust the range according to your items count
        strncpy_P(buffer, (PGM_P)&sig_menu_items[index], bufferSize);
        buffer[bufferSize - 1] = '\0'; // Ensure null-termination
    }
}

// Function to read a string from PROGMEM
void getMenuItem(uint8_t index, char *buffer, size_t bufferSize) {
    // Make sure the index is within bounds
    if (index < 6) {
        // Read the string from PROGMEM into the buffer
        strncpy_P(buffer, (PGM_P)&menu_items[index], bufferSize);
        buffer[bufferSize - 1] = '\0'; // Ensure null-termination
    }
}

// Function to draw a menu item
void drawMenuItem(int y_position, uint8_t index, uint8_t type) {
  char itemText[MAX_ITEM_LENGTH];
  switch(type){
    case  MENU_ITEMS_TYPE :
      // Buffer to hold the bitmap read from EEPROM
      uint8_t bitmapBuffer[BIT_MAP_SIZE];
      
      getMenuItem(index, itemText, sizeof(itemText)); // Read from PROGMEM
      //delay(1);
      oled.setTextSize(TEXT_SIZE);
      oled.setTextColor(TEXT_COLOR);
      oled.setCursor(26, y_position-8);
      oled.print(itemText);
      readBitmapFromEEPROM(bitmapBuffer, index, BIT_MAP_SIZE);
      //oled.drawBitmap(3, y_position - 13, item_bitmap, 16, 16, TEXT_COLOR); // Adjusted y position for bitmap
      oled.drawBitmap(3, y_position - 13,  bitmapBuffer, 16, 16, TEXT_COLOR); // Adjusted y position for bitmap
      delay(1);
    break;

    case SIG_MENU_ITEMS_TYPE:
      getSignalMenuItem(index, itemText, sizeof(itemText)); // Read from PROGMEM

      oled.setTextSize(TEXT_SIZE);
      oled.setTextColor(TEXT_COLOR);
      oled.setCursor(26, y_position-8);
      oled.print(itemText);

    break;
  }
    
    
}

void configMenu(void){

}


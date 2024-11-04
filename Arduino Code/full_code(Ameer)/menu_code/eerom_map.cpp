#include "eerom_map.h"

void writeBitmapToEEPROM(const unsigned char* bitmap, int index, int size) {
    for (int i = 0; i < size; i++) {
        // Read byte from PROGMEM and write to EEPROM
        EEPROM.write((index*BIT_MAP_SIZE)+i, pgm_read_byte(&bitmap[i]));
    }
}


void readBitmapFromEEPROM(uint8_t* buffer, int index, int size) {
    for (int i = 0; i < size; i++) {
        buffer[i] = EEPROM.read((index*BIT_MAP_SIZE) + i);
    }
}
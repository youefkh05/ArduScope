/*
 * eerom_map.h
 *
 * Created: 10/26/2024 2:48 PM
 *  Author: Yousef
 */

#ifndef EEROM_MAP_H
#define EEROM_MAP_H

/*  Include */
#include <Arduino.h>
#include <EEPROM.h>

#define SAVE_BIT 1    //if you want to save the bit maps
#ifdef SAVE_BIT
#include <avr/pgmspace.h>  // For PROGMEM

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

// 'oled_display_menus-Recovered_0003_sig_gen', 16x16px
const unsigned char sig_gen_bitmap [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x87, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 
	0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0x20, 0x84, 0xe0, 0xfc, 0x00, 0x00, 0x00, 0x00
};

// 'oled_display_menus-Recovered_0006_config', 16x16px
const unsigned char config_bitmap [] PROGMEM = {
	0x01, 0x80, 0x01, 0x80, 0x1a, 0x58, 0x36, 0x6c, 0x20, 0x04, 0x11, 0x88, 0x33, 0xcc, 0xc6, 0x63, 
	0xc6, 0x63, 0x33, 0xcc, 0x11, 0x88, 0x20, 0x04, 0x36, 0x6c, 0x1a, 0x58, 0x01, 0x80, 0x01, 0x80
};
#endif 


//defintions
// EEPROM addresses for each bitmap
#define BIT_MAP_SIZE    (32)

//prototypes
// Function to write bitmap to EEPROM
void writeBitmapToEEPROM(const unsigned char* bitmap, int index, int size);

// Function to read bitmap from EEPROM and store in RAM for display
void readBitmapFromEEPROM(uint8_t* buffer, int index, int size);




#endif /* EEROM_MAP_H  */
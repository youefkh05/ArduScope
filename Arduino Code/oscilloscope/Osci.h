/*
 * Osci.h
 *
 * Created: 10/26/2024 2:48 PM
 *  Author: Yousef
 */

#ifndef OSCI_H
#define OSCI_H

/*  Include */
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include "Adafruit_SH1106.h"            // https://github.com/wonho-maker/Adafruit_SH1106
#include <EEPROM.h>

//OLED Definitions
#define SCREEN_WIDTH 128                // OLED display width
#define SCREEN_HEIGHT 64                // OLED display height
#define REC_LENG 200                    // size of wave data buffer
#define MIN_TRIG_SWING 5                // minimum trigger swing.(Display "Unsync" if swing smaller than this value
#define OLED_RESET     -1      // Reset pin # (or -1 if sharing Arduino reset pin)

void setConditions(void);

void writeCommonImage(void);

void readWave(void);

void dataAnalize(void);

void freqDuty(void);

int sum3(int k);

void startScreen(void);

void dispHold(void);

void dispInf(void);

void plotData(void);

void saveEEPROM(void);

void loadEEPROM(void);

void auxFunctions(void);

void uuPinOutputLow(unsigned int d, unsigned int a);

void pin2IRQ(void);















//input
#define   OUT_DC_PIN    (A0)
#define   OUT_AC_PIN    (A1)
#define   OUT_RIN_PIN   (A2)

// Define an enum for devices
enum devices {
  Ohmeter     = 1,   
  Ammeter     = 2,   
  Voltmeter   = 3,
  Square      = 4, 
  Tri         = 5, 
  Sin         = 6, 
};

// Define an enum for ranges
enum ranges{
  range1  = 1,
  range2  = 2,
  range3  = 3,
  range4  = 4,
};


// Define an enum for modes
enum modes{
  AC_MODE = 1,
  DC_MODE = 2,
};


//MUX1
#define   A_MUX_1_PIN       (5)
#define   B_MUX_1_PIN       (4)

//MUX2
#define   A_MUX_2_PIN       (3)
#define   B_MUX_2_PIN       (2)


typedef float fint32_t;



// Function Prototypes
void MM_Init(void);

//mode:AC,DC  Range:300mV, 3v, 30v, 400v
fint32_t Read_Volt( ranges Vrange, modes mode);

//mode:AC,DC  Range:2mAmp, 20mAmp, 200mAmp, 1Amp
fint32_t Read_Amp( ranges Irange, modes mode);

//Range:10k, 100k, 1M
fint32_t Read_Ohm( ranges range);

//Devices: Ohmeter, Ammeter, Voltmeter, Square, Tri, Sin    Ranges: 1, 2, 3, 4
void Select_Mux( devices device, ranges range);

uint8_t Ask_To_Return( uint8_t return_key);





#endif /* OSCI_H  */

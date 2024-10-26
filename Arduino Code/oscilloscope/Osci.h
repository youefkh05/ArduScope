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

//Pins Number
#define   Osci_Input_Bot    (2)
#define   Select_Bot        (8)
#define   Up_Bot            (9)
#define   Down_Bot          (10)
#define   Hold_Bot          (11)
#define   Osci_In           (A0)

void Osci_Init(void);

void Osci_Run(void);

static void setConditions(void);

static void writeCommonImage(void);

static void readWave(void);

static void dataAnalize(void);

static void freqDuty(void);

static int sum3(int k);

static void startScreen(void);

static void dispHold(void);

static void dispInf(void);

static void plotData(void);

static void saveEEPROM(void);

static void loadEEPROM(void);

static void auxFunctions(void);

static void uuPinOutputLow(unsigned int d, unsigned int a);

static void pin2IRQ(void);



/*


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

*/



#endif /* OSCI_H  */

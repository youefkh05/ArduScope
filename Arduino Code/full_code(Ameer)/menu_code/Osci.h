/*
 * Osci.h
 *
 * Created: 10/26/2024 2:48 PM
 *  Author: Yousef
 */

#ifndef OSCI_H
#define OSCI_H

/*  Include */
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include "Adafruit_SH1106.h"   // https://github.com/wonho-maker/Adafruit_SH1106 
#include "application.h"        
//#include <EEPROM.h>

//OLED Definitions
#define SCREEN_WIDTH      (128)   // OLED display width
#define SCREEN_HEIGHT     (64)    // OLED display height
#define OLED_RESET        (-1)    // Reset pin # (or -1 if sharing Arduino reset pin)
#define REC_LENG          (100)   // size of wave data buffer
#define MIN_TRIG_SWING    (5)     // minimum trigger swing.(Display "Unsync" if swing smaller than this value
#define OLED_I2C_ADDRESS  (0x3C)

//Pins Number
#define   Osci_Input_Bot    (2)
#define   Select_Bot        (8)
#define   Exit_Bot          (3)
#define   Up_Bot            (9)
#define   Down_Bot          (10)
#define   Hold_Bot          (11)
#define   Osci_In           (A0)
#define   Sig_In              

/*
typedef struct flag_type
{
  uint8_t button_up_f: 1;
  uint8_t button_down_f: 1;
  uint8_t button_select_f: 1;
};
*/

void Osci_Init(void);

void Osci_Run(void);

static void setConditions(char* hScale, char* vScale,int &rangeMax,int &rangeMaxDisp,int &rangeMin,int &rangeMinDisp);

static void writeCommonImage(void);

static void readWave(int *waveBuff);

static void dataAnalize(int &dataMin,int &dataMax,int &dataAve,int *waveBuff,int &trigP,boolean &trigSync,float &waveFreq,int &waveDuty);

static void freqDuty(int &dataMin,int &dataMax,int &dataAve,float &waveFreq,int &waveDuty,int *waveBuff);

static int sum3(int k,int *waveBuff);

static void startScreen(void);

static void dispHold(void);

static void dispInf(char* hScale, char* vScale,int &dataMin,int &dataMax,int &dataAve,char *chrBuff,
int &rangeMax,int &rangeMaxDisp,int &rangeMin,int &rangeMinDisp,int &trigP,boolean &trigSync,float &waveFreq,int &waveDuty);

static void plotData(int *waveBuff,int &rangeMax,int &rangeMaxDisp,int &rangeMin,int &rangeMinDisp,
int &trigP,boolean &trigSync,float &waveFreq,int &waveDuty);

static void saveEEPROM(void);

static void loadEEPROM(void);

static void auxFunctions(void);

static void uuPinOutputLow(unsigned int d, unsigned int a);

static void pin2IRQ(void);

static void pin3IRQ(void);






#endif /* OSCI_H  */

/*
 * MULTI_METRE_SIG.h
 *
 * Created: 10/15/2024 6:00 PM
 *  Author: Yousef
 */

#ifndef MULTI_METRE_SIG_H
#define MULTI_METRE_SIG_H

/*  Include */
#include <Arduino.h>
//#include <stdint.h>

//input
#define   OUT_DC_PIN    (A1)
#define   OUT_AC_PIN    (A3)
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
#define   A_MUX_1_PIN       (12)
#define   B_MUX_1_PIN       (7)

//MUX2
#define   A_MUX_2_PIN       (13)
#define   B_MUX_2_PIN       (4)

// Function Prototypes
void MM_Init(void);

//mode:AC,DC  Range:300mV, 3v, 30v, 400v
float Read_Volt( ranges Vrange, modes mode);

//mode:AC,DC  Range:2mAmp, 20mAmp, 200mAmp, 1Amp
float Read_Amp( ranges Irange, modes mode);

//Range:10k, 100k, 1M
float Read_Ohm( ranges range);

//Devices: Ohmeter, Ammeter, Voltmeter, Square, Tri, Sin    Ranges: 1, 2, 3, 4
void Select_Mux( devices device, ranges range);

//uint8_t Ask_To_Return( uint8_t return_key);





#endif /* MULTI_METRE__SIGH*/

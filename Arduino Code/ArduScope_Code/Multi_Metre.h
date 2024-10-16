/*
 * MULTI_METRE.h
 *
 * Created: 10/15/2024 6:00 PM
 *  Author: Yousef
 */

#ifndef MULTI_METRE_H
#define MULTI_METRE_H

/*  Include */
#include <Arduino.h>
#include <stdint.h>

//input
#define   OUT_DC_PIN    (A0)
#define   OUT_AC_PIN    (A1)
#define   OUT_RIN_PIN   (A2)

//devices
#define   Ohmeter       (1)
#define   Ammeter       (2)
#define   Voltmeter     (3)

//ranges
#define   range1        (1)
#define   range2        (2)
#define   range3        (3)
#define   range4        (4)

//mode
#define   AC_MODE       (1)
#define   DC_MODE       (2)

//MUX1
#define   A_MUX_1       (5)
#define   B_MUX_1       (4)

//MUX2
#define   A_MUX_2       (3)
#define   B_MUX_2       (2)


typedef float fint32_t;


// Function Prototypes
void MM_Init(void);

//mode:AC,DC  Range:300mV, 3v, 30v, 400v
fint32_t Read_Volt( uint8_t Vrange, uint8_t mode);

//mode:AC,DC  Range:2mAmp, 20mAmp, 200mAmp, 1Amp
fint32_t Read_Amp( uint8_t Vrange, uint8_t mode);

fint32_t Read_Ohm( uint8_t range);

void Select_Mux(uint8_t device, uint8_t range);

uint8_t Ask_To_Return(uint8_t return_key);





#endif /* MULTI_METRE_H*/

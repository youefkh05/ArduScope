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
#define OUT_DC_PIN A0
#define OUT_TOT_PIN A1
#define OUT_RIN_PIN A2


//MUX1
#define A_MUX_1 5
#define B_MUX_1 4

//MUX2
#define A_MUX_2 3
#define B_MUX_2 2


typedef float fint32_t;


// Function Prototypes
void MM_Init(void);
fint32_t Read_Volt(uint16_t Vout, uint16_t Vtot, uint8_t Vrange, uint8_t mode);
fint32_t Read_Amp(uint16_t x, uint16_t Itot, uint8_t Irange, uint8_t mode);
void Read_Ohm(uint8_t range, uint16_t volt);
void Select_Mux(uint8_t device, uint8_t range);
uint8_t Ask_To_Return(uint8_t return_key);





#endif /* MULTI_METRE_H*/

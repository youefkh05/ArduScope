/*
 * APP.h
 *
 * Created: 4/1/2024 10:14:38 AM
 *  Author: AZidan
 */ 


#ifndef APP_H_
#define APP_H_

#include "PERIPHERAL_LIBRARY.h"
#include "MODULE_LIBRARY.h"
#include "math.h"
#include <stdio.h>
#include <string.h>

//Ohm
#define A_MUX_2 DIO_PIN4
#define B_MUX_2 DIO_PIN5


//volt and current
#define A_MUX_3 DIO_PIN6
#define B_MUX_3 DIO_PIN7






fint32_t Read_Volt(uint16_t Vout,uint16_t Vtot, uint8_t Vrange,uint8_t mode);
fint32_t Read_Amp(uint16_t x,uint16_t Itot, uint8_t Irange,uint8_t mode);
void display_ohm(uint8_t range,uint16_t volt);
void display_volt(uint8_t range,uint16_t Vtot,uint16_t volt,uint8_t mode);
void display_Amp(uint8_t range,uint16_t volt,uint8_t mode);
void select_mux(uint8_t device,uint8_t range);
uint8_t select_LCD(char row1[],char row2[],uint8_t num,uint8_t return_key);	//select the keys from 1:4 and a return key if needed
uint8_t ask_to_return(uint8_t return_key);





#endif /* APP_H_ */
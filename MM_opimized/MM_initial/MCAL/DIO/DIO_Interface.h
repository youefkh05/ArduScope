/*
 * DIO_Interface.h
 *
 * Created: 3/4/2024 11:55:40 PM
 *  Author: oraga
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "DIO_Configuration.h"
/*------------------------PINS---------------------------*/
void DIO_SetPinDirection(port Port, pin Pin, state State);
void DIO_SetPinValue(port Port, pin Pin, status Status);
void DIO_TogglePinValue(port Port, pin Pin);
uint8_t DIO_GetPinValue(port Port, pin Pin);
void DIO_SetPinPullUp(port Port, pin Pin);
/*------------------------PORT---------------------------*/
void DIO_SetPortDirection(port Port, state State);
void DIO_SetPortValue(port Port, status Status);
void DIO_TogglePortValue(port Port);
uint8_t DIO_GetPortValue(port Port);
void DIO_SetPortPullUp(port Port);



#endif /* DIO_INTERFACE_H_ */
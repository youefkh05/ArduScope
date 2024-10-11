/*
 * CPU_CONFIGURATIONS.h
 *
 * Created: 9/15/2023 10:41:13 AM
 *  Author: oraga
 */ 


#ifndef CPU_CONFIGURATIONS_H_
#define CPU_CONFIGURATIONS_H_

/*-----------------------------CPU CONFIGURATIONS-----------------------------*/
#undef F_CPU               // Disable internal crystal
#define F_CPU 8000000     // Enable external crystal
#include <avr/io.h>        // Enable input/output registers
#include <avr/interrupt.h> // Enable interrupts of AVR
#include <util/delay.h>    // Enable delay functions
#include "BIT_MATH.h"
#include "STANDARD_TYPES.h"
#include <stdlib.h>

#endif /* CPU_CONFIGURATIONS_H_ */
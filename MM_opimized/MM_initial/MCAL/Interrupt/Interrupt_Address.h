/*
 * Interrupt_Address.h
 *
 * Created: 3/4/2024 11:50:38 PM
 *  Author: oraga
 */ 


#ifndef INTERRUPT_ADDRESS_H_
#define INTERRUPT_ADDRESS_H_

#define MCUCR  (*(volatile uint8_t*)(0x55))
#define MCUCSR (*(volatile uint8_t*)(0x54))
#define GICR   (*(volatile uint8_t*)(0x5B))
#define GIFR   (*(volatile uint8_t*)(0x5A))
#define SREG   (*(volatile uint8_t*)(0x5F))




#endif /* INTERRUPT_ADDRESS_H_ */
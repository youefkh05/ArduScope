/*
 * STANDARD_TYPES.h
 *
 * Created: 9/15/2023 10:40:43 AM
 *  Author: oraga
 */ 


#ifndef STANDARD_TYPES_H_
#define STANDARD_TYPES_H_

/*-------------------------------STANDARD TYPES-------------------------------*/
/*typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long int uint64_t;
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed long int int32_t;
typedef signed long long int int64_t*/
typedef float fint32_t;
typedef double fint64_t;

typedef enum
{
	Fasle = 0,
	True = 1
}Bool;

#define NULL 0

/* Func States  */
#define IDLE 			0
#define BUSY			1

/* My States  */
#define OK           	0
#define NOK          	1
#define NULL_POINTER 	2
#define BUSY_STATE	 	3
#define TIMEOUT_STATE 4
#define MATCH     1
#define UNMATCH   0


#endif /* STANDARD_TYPES_H_ */
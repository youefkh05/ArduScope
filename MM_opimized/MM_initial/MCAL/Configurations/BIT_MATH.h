/*
 * BIT_MATH.h
 *
 * Created: 9/15/2023 10:40:17 AM
 *  Author: oraga
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/*-----------------------------BIT MATH OPERATION-----------------------------*/
#define SET_BIT(REG,BIT) REG|=(1<<BIT)
#define CLR_BIT(REG,BIT) REG&=~(1<<BIT)
#define TGL_BIT(REG,BIT) REG^=(1<<BIT)
#define GET_BIT(REG,BIT) ((REG>>BIT)&0x01)

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#define WRITE_BIT(REG , BIT , VAL) (REG = ((REG & ~(1<<BIT)) | (VAL << BIT)))
#define READ_BIT(REG , BIT) ((REG & (1<<BIT)) >> BIT)


#endif /* BIT_MATH_H_ */
#include <stdint.h>
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR,BIT_NUM) VAR |= 1<<BIT_NUM
#define CLEAR_BIT(VAR,BIT_NUM) VAR &= ~(1<<BIT_NUM)
#define TOGGLE_BIT(VAR,BIT_NUM) VAR ^= (1<<BIT_NUM)
#define GET_BIT(VAR,BIT_NUM) ((VAR & (1 << BIT_NUM)) >> BIT_NUM)

#endif // BIT_MATH_H

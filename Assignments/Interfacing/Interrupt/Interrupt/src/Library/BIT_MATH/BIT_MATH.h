#ifndef BIT_MATH_H
#define BIT_MATH_H

#include <stdint.h>

#define SET_BIT(VAR, BIT_NUM) VAR |= 1 << BIT_NUM
#define SET_BIT_VALUE(VAR, BIT_NUM, VALUE) VAR |= VALUE << BIT_NUM
#define CLEAR_BIT(VAR, BIT_NUM) VAR &= ~(1 << BIT_NUM)
#define TOGGLE_BIT(VAR, BIT_NUM) VAR ^= (1 << BIT_NUM)
#define GET_BIT(VAR, BIT_NUM) ((VAR & (1 << BIT_NUM)) >> BIT_NUM)
#define LEFT_ROTATE_SHIFT_8_BIT(VAR) VAR = ((VAR << 1) | (VAR >> (8 - 1)))
#define RIGHT_ROTATE_SHIFT_8_BIT(VAR) VAR = ((VAR >> 1) | (VAR << (8 - 1)))

#endif // BIT_MATH_H

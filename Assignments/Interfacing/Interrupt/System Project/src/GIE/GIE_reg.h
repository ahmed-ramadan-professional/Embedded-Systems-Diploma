#ifndef GIE_REG_H
#define GIE_REG_H

#include <stdint.h>

#define SREG        *((volatile uint8_t *)0x5F)
#define SREG_I      7u

#endif // !GIE_REG_H
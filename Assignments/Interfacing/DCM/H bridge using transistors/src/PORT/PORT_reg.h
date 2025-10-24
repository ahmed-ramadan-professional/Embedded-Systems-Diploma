#ifndef PORT_REG_H
#define PORT_REG_H

#include <stdint.h>

#define  PORTA		*((volatile uint8_t*)0x3B)
#define  DDRA		*((volatile uint8_t*)0x3A)

#define  PORTB		*((volatile uint8_t*)0x38)
#define  DDRB		*((volatile uint8_t*)0x37)

#define  PORTC		*((volatile uint8_t*)0x35)
#define  DDRC		*((volatile uint8_t*)0x34)

#define  PORTD		*((volatile uint8_t*)0x32)
#define  DDRD		*((volatile uint8_t*)0x31)

#endif
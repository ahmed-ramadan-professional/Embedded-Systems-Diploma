#ifndef DIO_PRV_H
#define DIO_PRV_H

#include "DIO_reg.h"
#include <stdint.h>

#define DIO_u8PORT_WIDTH 8
#define DIO_u8PORT_COUNT 4
#define DIO_u8SIGNAL_STATES 2
#define DIO_u8DIRECTIONS_COUNT 2

typedef enum {
    DIO_VALID_PORT,
    DIO_VALID_PIN,
    DIO_VALID_SIGNAL,
    DIO_VALID_DIR,
} ValidationRule;

uint8_t *const DIO_pu8ArrPortDirections[] = {
    &DDRA,
    &DDRB,
    &DDRC,
    &DDRD,
};

uint8_t *const DIO_pu8ArrPortRegisters[] = {
    &PORTA,
    &PORTB,
    &PORTC,
    &PORTD,
};

uint8_t *const DIO_pu8ArrInputRegisters[] = {
    &PINA,
    &PINB,
    &PINC,
    &PIND,
};

#endif
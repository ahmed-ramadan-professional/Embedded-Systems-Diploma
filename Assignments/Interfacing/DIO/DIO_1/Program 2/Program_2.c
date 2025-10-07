#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define BLINK_CYCLE 250

void port_shift_right(volatile uint8_t *port) {
    uint8_t i;
    for (i = 0; i < (uint8_t)8; i++) {
        SET_BIT(*port, (uint8_t)7 - i);
        _delay_ms(BLINK_CYCLE / 2);
        *port = 0x00;
        _delay_ms(BLINK_CYCLE / 2);
    }
}

void main(void) {
    DDRC = 0xff;
    while (1) {
        port_shift_right(&PORTC);
    }
}

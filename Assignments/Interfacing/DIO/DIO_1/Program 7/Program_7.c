#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define BLINK_CYCLE 300

void port_snake_shift_left(volatile uint8_t *port) {
    uint8_t i;
    *port = 0x00;
    _delay_ms(BLINK_CYCLE);
    for (i = 0; i < (uint8_t)8; i++) {
        SET_BIT(*port, i);
        _delay_ms(BLINK_CYCLE);
    }
}

void main(void) {
    DDRC = 0xff;
    while (1) {
        port_snake_shift_left(&PORTC);
    }
}

#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define BLINK_CYCLE 500

void port_blink(volatile uint8_t *port) {
    *port = 0xFF;
    _delay_ms(BLINK_CYCLE / 2);
    *port = 0x00;
    _delay_ms(BLINK_CYCLE / 2);
}

void main(void) {
    DDRC = 0xff;

    while (1) {
        port_blink(&PORTC);
    }
}

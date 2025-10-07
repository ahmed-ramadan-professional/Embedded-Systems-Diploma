#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define BLINK_CYCLE 250

void port_ping_pong(volatile uint8_t *port) {
    SET_BIT(*port, 0);
    _delay_ms(BLINK_CYCLE);
    *port = 0x00;
    _delay_ms(BLINK_CYCLE);
    
    while (1) {
        uint8_t i;
        for (i = 1; i < (uint8_t)8; i++) {
            SET_BIT(*port, i);
            _delay_ms(BLINK_CYCLE);
            *port = 0x00;
            _delay_ms(BLINK_CYCLE);
        }
        for (i = 1; i < (uint8_t)8; i++) {
            SET_BIT(*port, (uint8_t)7 - i);
            _delay_ms(BLINK_CYCLE);
            *port = 0x00;
            _delay_ms(BLINK_CYCLE);
        }
    }
}

void main(void) {
    DDRC = 0xff;
    while (1) {
        port_ping_pong(&PORTC);
    }
}

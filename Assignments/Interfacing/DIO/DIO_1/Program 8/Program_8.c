#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define BLINK_CYCLE 300

void port_2leds_diverging_and_converging(volatile uint8_t *port) {
    uint8_t i;
    for (i = 0; i < (uint8_t)5; i++) {
        SET_BIT(*port, (uint8_t)3 + i);
        SET_BIT(*port, (uint8_t)7 - (uint8_t)3 - i);
        _delay_ms(BLINK_CYCLE);
    }
    for (i = 0; i < (uint8_t)4; i++) {
        CLEAR_BIT(*port, i);
        CLEAR_BIT(*port, (uint8_t)7 - i);
        _delay_ms(BLINK_CYCLE);
    }
}

void main(void) {
    DDRC = 0xff;
    while (1) {
        port_2leds_diverging_and_converging(&PORTC);
    }
}

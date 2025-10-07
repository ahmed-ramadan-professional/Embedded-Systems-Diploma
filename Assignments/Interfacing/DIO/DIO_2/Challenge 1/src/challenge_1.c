#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define BLINK_CYCLE 600

void challenge_1(volatile uint8_t *port, volatile uint8_t *dir) {
    uint8_t i;
    for (i = 0; i < (uint8_t)5; i++) {
        *dir = 0b11 << i;
        *port = 0b10 << i;
        _delay_ms(BLINK_CYCLE / 2);
        *port = 0b01 << i;
        _delay_ms(BLINK_CYCLE / 2);
    }
}

void main(void) {
    while (1) {
        challenge_1(&PORTC, &DDRC);
    }
}

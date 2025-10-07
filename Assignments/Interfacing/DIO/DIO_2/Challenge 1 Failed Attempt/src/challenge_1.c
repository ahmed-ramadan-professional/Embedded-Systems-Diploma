#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define BLINK_CYCLE 600

void challenge_1(volatile uint8_t *port, volatile uint8_t *dir) {
    uint8_t i;
    for (i = 0; i < (uint8_t)8; i++) {
        SET_BIT(*dir, i);
        CLEAR_BIT(*port, i);
        _delay_ms(BLINK_CYCLE / 2);
        SET_BIT(*port, i);
        _delay_ms(BLINK_CYCLE / 2);
        CLEAR_BIT(*dir, i);
    }
}

void main(void) {
    while (1) {
        challenge_1(&PORTC,&DDRC);
    }
}

#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

// This logic was taken out, packaged and encapsulated into its own include file and c file
// check out COTS/BUTTON_PRESS/BUTTON_PRESS.h and COTS/BUTTON_PRESS/BUTTON_PRESS.c

#define CONFIRMATION_TIME_DELAY 200

uint8_t is_button_pressed(uint8_t *port, uint8_t pin) {
    if (!GET_BIT(*port, pin)) {
        _delay_ms(CONFIRMATION_TIME_DELAY);
        return !GET_BIT(*port, pin);
    }
    return 0;
}

void main(void) {
    DDRC = 0xFF;
    DDRD = 0x00;
    while (1) {
        if (is_button_pressed(&PIND, 2)) {
            PORTC = 0xFF;
        } else {
            PORTC = 0x00;
        }
    }
}

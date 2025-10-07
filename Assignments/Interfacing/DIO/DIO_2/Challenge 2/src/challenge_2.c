#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define TRANSITION_DELAY 10
#define DISPLAY_DELAY 50

#define OUTPUT_PORT PORTA
#define OUTPUT_PORT_DIR DDRA
#define CONTROL_PORT PORTC
#define CONTROL_PORT_DIR DDRC

// This logic was taken out, packaged and encapsulated into its own include file and c file
// check out COTS/DOUBLE_7_SEGMENTS/DOUBLE_7_SEGMENTS.h and COTS/DOUBLE_7_SEGMENTS/DOUBLE_7_SEGMENTS.c

const digits[10] = {0b01111110, 0b00001100, 0b10110110, 0b10011110, 0b11001100,
                    0b11011010, 0b11111000, 0b00001110, 0b11111110, 0b11011110};

void challenge_2(void) {
    uint8_t i, j;

    OUTPUT_PORT_DIR = 0xFF;
    CONTROL_PORT_DIR = 0xFF;

    for (i = 0; i < (uint8_t)10; i++) {
        for (j = 0; j < (uint8_t)10; j++) {
            volatile uint32_t counter = 0;
            while (counter < DISPLAY_DELAY) {
                CONTROL_PORT = 0b10000000;
                OUTPUT_PORT = digits[i];
                _delay_ms(TRANSITION_DELAY);
                CONTROL_PORT = 0b01000000;
                OUTPUT_PORT = digits[j];
                _delay_ms(TRANSITION_DELAY);
                counter++;
            }
        }
    }
}

void main(void) {
    while (1) {
        challenge_2();
    }
}

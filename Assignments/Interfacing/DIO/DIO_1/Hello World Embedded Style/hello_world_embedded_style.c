#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>

#define MORSE_SPACE_DELAY 1200
#define MORSE_LONG_DELAY 800
#define MORSE_SHORT_DELAY 200

void morse_delay(char c) {
    if (c == '-' || c == ' ')
        _delay_ms(MORSE_LONG_DELAY);
    if (c == '.')
        _delay_ms(MORSE_SHORT_DELAY);
    if (c == '/')
        _delay_ms(MORSE_SPACE_DELAY);
}

void morse_blink(uint8_t *port, uint8_t pin, char *str) {

    while (str && *str != '\0') {
        CLEAR_BIT(*port, pin);
        if (*str == '.' || *str == '-') SET_BIT(*port, pin);
        morse_delay(*str);
        CLEAR_BIT(*port, pin);
        morse_delay('.');
        str++;
    }
}

void main(void) {
    while (1) {
        char hello_world[] = ".... . .-.. .-.. --- / .-- --- .-. .-.. -..";
        SET_BIT(DDRC, 2);
        morse_blink(&PORTC, 2, hello_world);
    }
}

#include <avr/io.h>
#include <util/delay.h>

#include <Library/BIT_MATH/BIT_MATH.h>
#include <Library/BUTTON_PRESS/BUTTON_PRESS.h>

#define BLINK_CYCLE 300
#define BLINKING_PORT PORTB

uint8_t operation = 0;
uint8_t operation_change = 1;

uint8_t seven_segments_digits_representation[10] = {0b01111110, 0b00001100, 0b10110110, 0b10011110, 0b11001100,
                                                    0b11011010, 0b11111000, 0b00001110, 0b11111110, 0b11011110};

void exit(){
    TOGGLE_BIT(operation_change, 0);
    PORTB = 0xFF;
    _delay_ms(BLINK_CYCLE);
    PORTB = 0x00;
    _delay_ms(BLINK_CYCLE);
    PORTB = 0xFF;
    _delay_ms(BLINK_CYCLE);
    PORTB = 0x00;
    _delay_ms(BLINK_CYCLE);
}

void port_blink(volatile uint8_t *port) {
    *port = 0xFF;
    _delay_ms(BLINK_CYCLE / 2);
    *port = 0x00;
    _delay_ms(BLINK_CYCLE / 2);
}

void port_shift_right(volatile uint8_t *port) {
    uint8_t i;
    for (i = 0; i < (uint8_t)8; i++) {
        // without the use of interrupts i had to exit in this ugly way, sorry :(
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        SET_BIT(*port, (uint8_t)7 - i);
        _delay_ms(BLINK_CYCLE / 2);
        *port = 0x00;
        _delay_ms(BLINK_CYCLE / 2);
    }
}

void port_shift_left(volatile uint8_t *port) {
    uint8_t i;
    for (i = 0; i < (uint8_t)8; i++) {
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        SET_BIT(*port, i);
        _delay_ms(BLINK_CYCLE / 2);
        *port = 0x00;
        _delay_ms(BLINK_CYCLE / 2);
    }
}

void port_converging(volatile uint8_t *port) {
    uint8_t i;
    *port = 0x00;
    _delay_ms(BLINK_CYCLE);
    for (i = 0; i < (uint8_t)4; i++) {
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        SET_BIT(*port, i);
        SET_BIT(*port, (uint8_t)7 - i);
        _delay_ms(BLINK_CYCLE);
    }
}

void port_diverging(volatile uint8_t *port) {
    uint8_t i;
    *port = 0x00;
    _delay_ms(BLINK_CYCLE);
    for (i = 0; i < (uint8_t)5; i++) {
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        SET_BIT(*port, (uint8_t)3 + i);
        SET_BIT(*port, (uint8_t)7 - (uint8_t)3 - i);
        _delay_ms(BLINK_CYCLE);
    }
}

void port_ping_pong(volatile uint8_t *port) {
    SET_BIT(*port, 0);
    _delay_ms(BLINK_CYCLE);
    *port = 0x00;

    uint8_t i;
    for (i = 1; i < (uint8_t)8; i++) {
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        SET_BIT(*port, i);
        _delay_ms(BLINK_CYCLE);
        *port = 0x00;
    }
    for (i = 1; i < (uint8_t)7; i++) {
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        SET_BIT(*port, (uint8_t)7 - i);
        _delay_ms(BLINK_CYCLE);
        *port = 0x00;
    }
}

void port_snake_shift_left(volatile uint8_t *port) {
    uint8_t i;
    *port = 0x00;
    _delay_ms(BLINK_CYCLE);
    for (i = 0; i < (uint8_t)8; i++) {
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        SET_BIT(*port, i);
        _delay_ms(BLINK_CYCLE);
    }
}

void port_2leds_diverging_and_converging(volatile uint8_t *port) {
    uint8_t i;
    for (i = 0; i < (uint8_t)5; i++) {
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        SET_BIT(*port, (uint8_t)3 + i);
        SET_BIT(*port, (uint8_t)7 - (uint8_t)3 - i);
        _delay_ms(BLINK_CYCLE);
    }
    for (i = 0; i < (uint8_t)4; i++) {
        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
            return;
        }
        CLEAR_BIT(*port, i);
        CLEAR_BIT(*port, (uint8_t)7 - i);
        _delay_ms(BLINK_CYCLE);
    }
}

void operator(uint8_t operation) {
    switch (operation) {
        case 0:
            port_blink(&BLINKING_PORT);
            break;

        case 1:
            port_shift_right(&BLINKING_PORT);
            break;

        case 2:
            port_shift_left(&BLINKING_PORT);
            break;

        case 3:
            port_converging(&BLINKING_PORT);
            break;

        case 4:
            port_diverging(&BLINKING_PORT);
            break;

        case 5:
            port_ping_pong(&BLINKING_PORT);
            break;

        case 6:
            port_snake_shift_left(&BLINKING_PORT);
            break;

        case 7:
            port_2leds_diverging_and_converging(&BLINKING_PORT);
            break;

        default:
            break;
    }
}

void main(void) {
    DDRB = 0xFF;
    DDRA = 0xFF;
    SET_BIT(DDRC, 6);
    SET_BIT(PORTC, 6);
    PORTB = 0x00;

    while (1) {

        if (is_button_pressed(&PIND, &DDRD, 2)) { TOGGLE_BIT(operation, 2); }
        if (is_button_pressed(&PIND, &DDRD, 3)) { TOGGLE_BIT(operation, 1); }
        if (is_button_pressed(&PIND, &DDRD, 4)) { TOGGLE_BIT(operation, 0); }

        PORTA = seven_segments_digits_representation[operation];

        if (!operation_change) {
            operator(operation);
        }

        if (is_button_pressed(&PIND, &DDRD, 5)) {
            exit();
        }
    }
}

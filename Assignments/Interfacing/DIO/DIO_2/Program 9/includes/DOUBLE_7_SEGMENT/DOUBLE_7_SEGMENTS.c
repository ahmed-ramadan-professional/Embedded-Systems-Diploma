#include <Library/BIT_MATH/BIT_MATH.h>
#include <util/delay.h>

#include "DOUBLE_7_SEGMENTS.h"

uint8_t seven_segments_digits_representation[10] = {0b01111110, 0b00001100, 0b10110110, 0b10011110, 0b11001100,
                                                    0b11011010, 0b11111000, 0b00001110, 0b11111110, 0b11011110};

uint8_t *_OUTPUT_REGISTER = 0x0;
uint8_t *_CONTROL_REGISTER = 0x0;

uint8_t _control_pin_1 = 0;
uint8_t _control_pin_2 = 0;

void double_7_segments_init(uint8_t *OUTPUT_REGISTER, uint8_t *OUTPUT_DIR_REGISTER,
                            uint8_t *CONTROL_REGISTER, uint8_t *CONTROL_DIR_REGISTER,
                            uint8_t control_pin_1, uint8_t control_pin_2) {

    _OUTPUT_REGISTER = OUTPUT_REGISTER;
    _CONTROL_REGISTER = CONTROL_REGISTER;

    _control_pin_1 = control_pin_1;
    _control_pin_2 = control_pin_2;

    *OUTPUT_DIR_REGISTER = 0xFF;

    SET_BIT(*CONTROL_DIR_REGISTER, _control_pin_1);
    SET_BIT(*CONTROL_DIR_REGISTER, _control_pin_2);
}

// excessive use of tens and ones digits to avoid using division which
// may be a little annoying for programmer user but way easier on the poor embedded device (｡◕‿‿◕｡)
void double_7_segments_display(uint8_t tens_digit, uint8_t ones_digit) {
    volatile uint32_t counter = 0;
    while (counter < DISPLAY_DELAY) {
        CLEAR_BIT(*_CONTROL_REGISTER, _control_pin_2);
        SET_BIT(*_CONTROL_REGISTER, _control_pin_1);
        *_OUTPUT_REGISTER = seven_segments_digits_representation[tens_digit];

        _delay_ms(TRANSITION_DELAY);

        CLEAR_BIT(*_CONTROL_REGISTER, _control_pin_1);
        SET_BIT(*_CONTROL_REGISTER, _control_pin_2);
        *_OUTPUT_REGISTER = seven_segments_digits_representation[ones_digit];
        _delay_ms(TRANSITION_DELAY);
        counter++;
    }
}

void double_7_segments_count_up(uint8_t from_tens, uint8_t from_ones, uint8_t to_tens, uint8_t to_ones) {
    uint8_t i, j;

    for (i = from_tens; i <= to_tens; i++) {
        for ((j = i == from_tens ? from_ones : 0); j <= (i == to_tens ? to_ones : (uint8_t)9); j++) {
            volatile uint32_t counter = 0;
            while (counter < DISPLAY_DELAY) {
                double_7_segments_display(i, j);
                counter++;
            }
        }
    }
}
void double_7_segments_count_down(uint8_t from_tens, uint8_t from_ones, uint8_t to_tens, uint8_t to_ones) {
    int8_t i, j;

    for (i = from_tens; i >= to_tens; i--) {
        for (j = (i == from_tens ? from_ones : (int8_t)9); j >= (i == to_tens ? to_ones : 0); j--) {
            volatile uint32_t counter = 0;
            while (counter < DISPLAY_DELAY) {
                double_7_segments_display(i, j);
                counter++;
            }
        }
    }
}

#include <stdint.h>
#ifndef DOUBLE_7_SEGMENTS
#define DOUBLE_7_SEGMENTS

#define TRANSITION_DELAY 10
#define DISPLAY_DELAY 6



void double_7_segments_init(uint8_t *OUTPUT_REGISTER, uint8_t *OUTPUT_DIR_REGISTER,
                            uint8_t *CONTROL_REGISTER, uint8_t *CONTROL_DIR_REGISTER,
                            uint8_t control_pin_1, uint8_t control_pin_2);

void double_7_segments_display(uint8_t tens_digit, uint8_t ones_digit);
void double_7_segments_count_up(uint8_t from_tens, uint8_t from_ones, uint8_t to_tens, uint8_t to_ones);
void double_7_segments_count_down(uint8_t from_tens, uint8_t from_ones, uint8_t to_tens, uint8_t to_ones);

#endif // DOUBLE_7_SEGMENTS

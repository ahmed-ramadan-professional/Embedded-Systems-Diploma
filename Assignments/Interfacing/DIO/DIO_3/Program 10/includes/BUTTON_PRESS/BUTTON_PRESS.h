#include <stdint.h>
#ifndef BUTTON_PRESS_H
#define BUTTON_PRESS_H

#define CONFIRMATION_TIME_DELAY 200

uint8_t is_button_pressed(uint8_t *PIN_REGISTER, uint8_t *DDR_REGISTER, uint8_t input_pin);

#endif // BUTTON_PRESS_H


#include <util/delay.h>

#include "BUTTON_PRESS.h"


uint8_t is_button_pressed(uint8_t *PIN_REGISTER, uint8_t *DDR_REGISTER, uint8_t input_pin) {
    uint8_t temp = *DDR_REGISTER;
    *DDR_REGISTER &= ~(1 << input_pin);
    if (!((*PIN_REGISTER & (1 << input_pin)) >> input_pin)) {
        _delay_ms(CONFIRMATION_TIME_DELAY);
        return !((*PIN_REGISTER & (1 << input_pin)) >> input_pin);
    }
    *DDR_REGISTER = temp;
    return 0;
}

#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"

#include "DIO/DIO_interface.h"

#include "Button/Button_helper.h"
#include "Button/Button_interface.h"

void main(void) {

    BUTTON_sCONFIGS Button_1;

    DIO_u8SetPortDirection(DIO_u8PORTD, DIO_u8DIR_INPUT);
    DIO_u8SetPortDirection(DIO_u8PORTC, DIO_u8DIR_OUTPUT);

    BUTTON_MACRO_SET_CONFIGS_VALUES(Button_1, DIO_u8PORTD, DIO_u8PIN2);

    uint8_t Local_u8ButtonValue_1 = 0;

    while (1) {
        Button_u8IsPressed(&Button_1, &Local_u8ButtonValue_1);

        if (!Local_u8ButtonValue_1) {
            DIO_u8SetPortValue(DIO_u8PORTC, DIO_u8SIGNAL_HIGH);
        } else {
            DIO_u8SetPortValue(DIO_u8PORTC, DIO_u8SIGNAL_LOW);
        }
    }
}

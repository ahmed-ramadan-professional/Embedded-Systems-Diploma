#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"

#include "DIO/DIO_interface.h"

#include "LED/LED_helper.h"
#include "LED/LED_interface.h"

void main(void) {

    LED_sCONFIGS LED_1;
    LED_sCONFIGS LED_2;

    DIO_u8SetPortDirection(DIO_u8PORTC, DIO_u8DIR_OUTPUT);

    LED_MACRO_SET_CONFIGS_VALUES(LED_1, DIO_u8PORTC, DIO_u8PIN2, TRUE);
    LED_MACRO_SET_CONFIGS_VALUES(LED_2, DIO_u8PORTC, DIO_u8PIN1, TRUE);

    while (1) {
        LED_u8TurnOFF(&LED_2);
        LED_u8TurnON(&LED_1);
        _delay_ms(500);

        LED_u8TurnOFF(&LED_1);
        LED_u8TurnON(&LED_2);
        _delay_ms(500);
    }
}

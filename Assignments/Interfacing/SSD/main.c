#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"

#include "DIO/DIO_interface.h"

#include "SSD/SSD_helper.h"
#include "SSD/SSD_interface.h"

void main(void) {

    SSD_sDISPLAY_CONFIGS SSD_1;
    SSD_sDISPLAY_CONFIGS SSD_2;

    DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8DIR_OUTPUT);
    DIO_u8SetPortDirection(DIO_u8PORTC, DIO_u8DIR_OUTPUT);

    SSD_MACRO_SET_CONFIGS_VALUES(SSD_1, DIO_u8PORTA, TRUE, DIO_u8PORTC, DIO_u8PIN6, FALSE);
    SSD_MACRO_SET_CONFIGS_VALUES(SSD_2, DIO_u8PORTA, TRUE, DIO_u8PORTC, DIO_u8PIN7, FALSE);

    while (1) {
        SSD_u8DisplayOFF(&SSD_2);
        SSD_u8DisplayValue(&SSD_1, SSD_u8VALUE_0);
        _delay_ms(10);

        SSD_u8DisplayOFF(&SSD_1);
        SSD_u8DisplayValue(&SSD_2, SSD_u8VALUE_E);
        _delay_ms(10);
        
    }
}

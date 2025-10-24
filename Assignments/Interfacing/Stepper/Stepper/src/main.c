#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"
#include "PORT/PORT_interface.h"
#include "Stepper/Stepper_helper.h"
#include "Stepper/Stepper_interface.h"

void main(void) {

    PORT_voidInit();

    CLCD_voidInit();

    STEPPER_sCONFIGS STEPPER;
    STEPPER_MACRO_SET_CONFIGS_VALUES(STEPPER, DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3);

    CLCD_u8SetCursorToXY(0, 0);
    uint8_t test = 0b00010001;
    RIGHT_ROTATE_SHIFT_8_BIT(test);
    CLCD_voidSendDataInt32(test);

    while (1) {
        CLCD_voidSendCmdByte(1);
        CLCD_voidSendDataString("Clockwise..");
        Stepper_u8Turn(&STEPPER, STEPPER_u8CLOCKWISE_DIRECTION, 64);

        CLCD_voidSendCmdByte(1);
        CLCD_voidSendDataString("Stop..");
        _delay_ms(1500);

        CLCD_voidSendCmdByte(1);
        CLCD_voidSendDataString("Anti-Clockwise..");
        Stepper_u8Turn(&STEPPER, STEPPER_u8ANTI_CLOCKWISE_DIRECTION, 64);

        CLCD_voidSendCmdByte(1);
        CLCD_voidSendDataString("Stop..");
        _delay_ms(1500);
    }
}

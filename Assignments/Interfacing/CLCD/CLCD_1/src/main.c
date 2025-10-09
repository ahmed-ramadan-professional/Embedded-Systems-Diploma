
#include <Library/BIT_MATH/BIT_MATH.h>

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"

void main(void) {
    DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8DIR_OUTPUT);
    DIO_u8SetPortDirection(DIO_u8PORTB, DIO_u8DIR_OUTPUT);
    CLCD_voidInit();
    CLCD_voidSendDataString("Ahmed Ramadan");
    CLCD_voidSendCmdByte(0xC0);
    CLCD_voidSendDataInt32(-1234000);

    while (1) {
    }
}

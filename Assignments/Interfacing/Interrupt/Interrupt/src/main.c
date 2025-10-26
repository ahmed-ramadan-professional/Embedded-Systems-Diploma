#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "EXTI/EXTI_interface.h"
#include "GIE/GIE_interface.h"
#include "PORT/PORT_interface.h"

void INT0_Callback(void) {
    DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8SIGNAL_HIGH);
}

void INT1_Callback(void) {
    DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8SIGNAL_LOW);
}

void main(void) {

    PORT_voidInit();

    GIE_voidEnableGlobal();

    EXTI_voidInit();

    EXTI_voidSetCallback(EXTI_u8INT0,&INT0_Callback);
    EXTI_voidSetCallback(EXTI_u8INT1,&INT1_Callback);

    while (1) {
    }
}

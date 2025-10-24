#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"
#include "DCM/DCM_helper.h"
#include "DCM/DCM_interface.h"
#include "PORT/PORT_interface.h"



void main(void) {

    PORT_voidInit();

    CLCD_voidInit();

    DCM_sCONFIGS DCM;
    DCM_MACRO_SET_CONFIGS_VALUES(DCM,DIO_u8PORTB,DIO_u8PIN0,DIO_u8PIN1);

    
    CLCD_u8SetCursorToXY(0, 0);
    while (1) {
        CLCD_voidSendCmdByte(1);
        CLCD_voidSendDataString("Clockwise..");
        DCM_u8Turn(&DCM,DCM_u8CLOCKWISE_DIRECTION);
        _delay_ms(3000);

        CLCD_voidSendCmdByte(1);
        CLCD_voidSendDataString("Stop..");
        DCM_u8Stop(&DCM);
        _delay_ms(1500);

        CLCD_voidSendCmdByte(1);
        CLCD_voidSendDataString("Anti-Clockwise..");
        DCM_u8Turn(&DCM,DCM_u8ANTI_CLOCKWISE_DIRECTION);
        _delay_ms(3000);

        CLCD_voidSendCmdByte(1);
        CLCD_voidSendDataString("Stop..");
        DCM_u8Stop(&DCM);
        _delay_ms(1500);
        
    }
}

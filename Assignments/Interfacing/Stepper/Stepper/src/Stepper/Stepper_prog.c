#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"
#include <util/delay.h>

#include "DIO/DIO_interface.h"

#include "Stepper_interface.h"
#include "Stepper_prv.h"

uint8_t Stepper_u8Turn(STEPPER_sCONFIGS *Copy_psConfigs, uint8_t Copy_u8Direction, uint16_t Copy_u16Steps) {
    if (!Copy_psConfigs) return ERROR_NULL_POINTER;
    if (Copy_u8Direction != STEPPER_u8CLOCKWISE_DIRECTION && Copy_u8Direction != STEPPER_u8ANTI_CLOCKWISE_DIRECTION)
        return ERROR_INVALID_VALUE;

    uint8_t Local_u8ErrorCode = NO_ERROR;

    // here we initiate state variable with 0b0001 and for clockwise movement then we left rotate shift state variable
    // for anti-clockwise movement initiate the state with 0b1000 we right rotate shift state variable
    // the minimum variable size is 8 bits so we repeat the state twice 0b00010001 or 0b10001000
    uint8_t Local_u8State = Copy_u8Direction == STEPPER_u8CLOCKWISE_DIRECTION ? 0x11 : 0x88;
    uint16_t Local_u16LoopIdx;

    for (Local_u16LoopIdx = 0; Local_u16LoopIdx <= Copy_u16Steps; Local_u16LoopIdx++) {
        Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->PORT, Copy_psConfigs->PIN_0, GET_BIT(Local_u8State, 0));
        if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

        Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->PORT, Copy_psConfigs->PIN_1, GET_BIT(Local_u8State, 1));
        if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

        Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->PORT, Copy_psConfigs->PIN_2, GET_BIT(Local_u8State, 2));
        if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

        Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->PORT, Copy_psConfigs->PIN_3, GET_BIT(Local_u8State, 3));
        if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

        if (Copy_u8Direction == STEPPER_u8CLOCKWISE_DIRECTION)
            LEFT_ROTATE_SHIFT_8_BIT(Local_u8State);
        else
            RIGHT_ROTATE_SHIFT_8_BIT(Local_u8State);

        _delay_ms(STEPPER_SINGLE_STEP_DELAY_MS);
    }

    return Local_u8ErrorCode;
}


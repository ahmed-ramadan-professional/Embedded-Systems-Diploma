#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "SSD_interface.h"

// some configs are missing as it's the responsibility of DIO module to validate them
uint8_t SSD_u8ValidateConfigs(SSD_sDISPLAY_CONFIGS *Copy_psConfigs) {
    if (!Copy_psConfigs) return ERROR_NULL_POINTER;

    if (Copy_psConfigs->IS_DATA_PINS_SHIFTED_BY_ONE != FALSE &&
        Copy_psConfigs->IS_DATA_PINS_SHIFTED_BY_ONE != TRUE)
        return ERROR_INVALID_VALUE;

    if (Copy_psConfigs->IS_COM_CATHODE != FALSE &&
        Copy_psConfigs->IS_COM_CATHODE != TRUE)
        return ERROR_INVALID_VALUE;

    return NO_ERROR;
}

uint8_t SSD_u8DisplayOFF(SSD_sDISPLAY_CONFIGS *Copy_psConfigs) {
    return DIO_u8SetPinValue(Copy_psConfigs->CONTROL_PORT,
                             Copy_psConfigs->CONTROL_PIN,
                             Copy_psConfigs->IS_COM_CATHODE
                                 ? DIO_u8SIGNAL_HIGH
                                 : DIO_u8SIGNAL_LOW);
}

uint8_t SSD_u8DisplayValue(SSD_sDISPLAY_CONFIGS *Copy_psConfigs, uint8_t Copy_u8Value) {
    uint8_t Local_u8ErrorCode = SSD_u8ValidateConfigs(Copy_psConfigs);
    if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

    uint8_t Local_u8ShiftValue = Copy_psConfigs->IS_DATA_PINS_SHIFTED_BY_ONE ? 1u : 0u;

    DIO_u8SetPortDirection(DIO_u8PORTD, DIO_u8DIR_OUTPUT);
    DIO_u8SetPortCustomValue(DIO_u8PORTD, 0);
    DIO_u8SetPortCustomValue(DIO_u8PORTD, Copy_psConfigs->CONTROL_PIN);

    if (!(Copy_psConfigs->IS_COM_CATHODE)) {
        uint8_t Local_u8LoopIteration;
        for (Local_u8LoopIteration = 0; Local_u8LoopIteration < 7u; Local_u8LoopIteration++)
            TOGGLE_BIT(Copy_u8Value, Local_u8LoopIteration);
    }

    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->DATA_PORT, DIO_u8PIN0 + Local_u8ShiftValue, GET_BIT(Copy_u8Value, 0));
    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->DATA_PORT, DIO_u8PIN1 + Local_u8ShiftValue, GET_BIT(Copy_u8Value, 1));
    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->DATA_PORT, DIO_u8PIN2 + Local_u8ShiftValue, GET_BIT(Copy_u8Value, 2));
    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->DATA_PORT, DIO_u8PIN3 + Local_u8ShiftValue, GET_BIT(Copy_u8Value, 3));
    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->DATA_PORT, DIO_u8PIN4 + Local_u8ShiftValue, GET_BIT(Copy_u8Value, 4));
    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->DATA_PORT, DIO_u8PIN5 + Local_u8ShiftValue, GET_BIT(Copy_u8Value, 5));
    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->DATA_PORT, DIO_u8PIN6 + Local_u8ShiftValue, GET_BIT(Copy_u8Value, 6));

    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->CONTROL_PORT,
                                          Copy_psConfigs->CONTROL_PIN,
                                          Copy_psConfigs->IS_COM_CATHODE
                                              ? DIO_u8SIGNAL_LOW
                                              : DIO_u8SIGNAL_HIGH);

    return Local_u8ErrorCode;
}

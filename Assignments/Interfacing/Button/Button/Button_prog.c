#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "Button_interface.h"

// some configs are missing as it's the responsibility of DIO module to validate them
uint8_t Button_u8ValidateConfigs(BUTTON_sCONFIGS *Copy_psConfigs) {
    if (!Copy_psConfigs) return ERROR_NULL_POINTER;
    return NO_ERROR;
}

uint8_t Button_u8IsPressed(BUTTON_sCONFIGS *Copy_psConfigs, uint8_t *Copy_pu8ReturnValue) {
    uint8_t Local_u8ErrorCode = Button_u8ValidateConfigs(Copy_psConfigs);
    if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;
    if (!Copy_pu8ReturnValue) return ERROR_NULL_POINTER;

    return DIO_u8GetPinValue(Copy_psConfigs->PORT, Copy_psConfigs->PIN, Copy_pu8ReturnValue);
}

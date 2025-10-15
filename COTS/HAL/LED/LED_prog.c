#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "LED_interface.h"

// some configs are missing as it's the responsibility of DIO module to validate them
uint8_t LED_u8ValidateConfigs(LED_sCONFIGS *Copy_psConfigs) {
    if (!Copy_psConfigs) return ERROR_NULL_POINTER;

    if (Copy_psConfigs->IS_ANODE_CONNECTED != FALSE &&
        Copy_psConfigs->IS_ANODE_CONNECTED != TRUE)
        return ERROR_INVALID_VALUE;

    return NO_ERROR;
}

uint8_t LED_u8TurnOFF(LED_sCONFIGS *Copy_psConfigs) {
    uint8_t Local_u8ErrorCode = LED_u8ValidateConfigs(Copy_psConfigs);
    if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

    return DIO_u8SetPinValue(Copy_psConfigs->PORT,
                             Copy_psConfigs->PIN,
                             Copy_psConfigs->IS_ANODE_CONNECTED
                                 ? DIO_u8SIGNAL_LOW
                                 : DIO_u8SIGNAL_HIGH);
}

uint8_t LED_u8TurnON(LED_sCONFIGS *Copy_psConfigs) {
    uint8_t Local_u8ErrorCode = LED_u8ValidateConfigs(Copy_psConfigs);
    if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

    return DIO_u8SetPinValue(Copy_psConfigs->PORT,
                             Copy_psConfigs->PIN,
                             Copy_psConfigs->IS_ANODE_CONNECTED
                                 ? DIO_u8SIGNAL_HIGH
                                 : DIO_u8SIGNAL_LOW);
}



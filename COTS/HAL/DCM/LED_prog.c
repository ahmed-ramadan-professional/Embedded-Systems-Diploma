#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "DCM_interface.h"

uint8_t DCM_u8Turn(DCM_sCONFIGS *Copy_psConfigs, uint8_t Copy_u8Direction) {
    if (!Copy_psConfigs) return ERROR_NULL_POINTER;
    if (Copy_u8Direction != DCM_u8CLOCKWISE_DIRECTION && Copy_u8Direction != DCM_u8ANTI_CLOCKWISE_DIRECTION)
        return ERROR_INVALID_VALUE;

    uint8_t Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->PORT,
                                                  Copy_psConfigs->PIN_1,
                                                  Copy_u8Direction == DCM_u8CLOCKWISE_DIRECTION
                                                      ? DIO_u8SIGNAL_LOW
                                                      : DIO_u8SIGNAL_HIGH);
    if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->PORT,
                                          Copy_psConfigs->PIN_2,
                                          Copy_u8Direction == DCM_u8CLOCKWISE_DIRECTION
                                              ? DIO_u8SIGNAL_HIGH
                                              : DIO_u8SIGNAL_LOW);

    return Local_u8ErrorCode;
}

uint8_t DCM_u8Stop(DCM_sCONFIGS *Copy_psConfigs) {
    if (!Copy_psConfigs) return ERROR_NULL_POINTER;

    uint8_t Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->PORT,
                                                  Copy_psConfigs->PIN_1,
                                                  DIO_u8SIGNAL_LOW);

    if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

    Local_u8ErrorCode = DIO_u8SetPinValue(Copy_psConfigs->PORT,
                                          Copy_psConfigs->PIN_2,
                                          DIO_u8SIGNAL_LOW);

    return Local_u8ErrorCode;
}

#include <stdint.h>

#include "../Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "../DIO/DIO_interface.h"

#include "KPD_cfg.h"
#include "KPD_interface.h"
#include "KPD_prv.h"

uint8_t KPD_u8GetKeyPressed(uint8_t *Copy_u8KeyValue) {
    uint8_t Local_u8ColIndex, Local_u8RowIndex, Local_u8ErrorCode, Local_u8PinValue = KPD_u8NON_PRESSED_VALUE;

    uint8_t Local_au8ColPins[] = {KPD_u8COL_PIN0, KPD_u8COL_PIN1, KPD_u8COL_PIN2, KPD_u8COL_PIN3};
    uint8_t Local_au8RowPins[] = {KPD_u8ROW_PIN0, KPD_u8ROW_PIN1, KPD_u8ROW_PIN2, KPD_u8ROW_PIN3};

    for (Local_u8ColIndex = 0; Local_u8ColIndex < KPD_u8COL_SIZE; Local_u8ColIndex++) {
        Local_u8ErrorCode = DIO_u8SetPinValue(KPD_u8COL_PORT, Local_au8ColPins[Local_u8ColIndex], DIO_u8SIGNAL_LOW);
        if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

        for (Local_u8RowIndex = 0; Local_u8RowIndex < KPD_u8ROW_SIZE; Local_u8RowIndex++) {
            Local_u8ErrorCode = DIO_u8GetPinValue(KPD_u8ROW_PORT, Local_au8RowPins[Local_u8RowIndex], &Local_u8PinValue);
            if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

            if (Local_u8PinValue == DIO_u8SIGNAL_LOW) {
                *Copy_u8KeyValue = KPD_au8KEYS[Local_u8RowIndex][Local_u8ColIndex];
                while (Local_u8PinValue == DIO_u8SIGNAL_LOW) {
                    Local_u8ErrorCode = DIO_u8GetPinValue(KPD_u8ROW_PORT, Local_au8RowPins[Local_u8RowIndex], &Local_u8PinValue);
                    if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;
                };
                break;
            }
        }

        Local_u8ErrorCode = DIO_u8SetPinValue(KPD_u8COL_PORT, Local_au8ColPins[Local_u8ColIndex], DIO_u8SIGNAL_HIGH);
        if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;
    }

    return NO_ERROR;
}

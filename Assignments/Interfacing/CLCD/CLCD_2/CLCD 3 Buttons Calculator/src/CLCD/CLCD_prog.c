#include <stdint.h>
#include <util/delay.h>

#include "../Library/BIT_MATH/BIT_MATH.h"
#include "../Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "../Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "../DIO/DIO_interface.h"

#include "CLCD_prv.h"

#include "CLCD_cfg.h"
#include "CLCD_interface.h"

static uint8_t CLCD_u8InitBegan = FALSE;

void CLCD_voidOutputToDataBus(uint8_t Copy_u8Data) {
    if (CLCD_u8OperationMode == CLCD_u8MODE_8_BIT_DATA) {
        DIO_u8SetPortCustomValue(CLCD_u8DATA_PORT, Copy_u8Data);
    } else {
        DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D7, GET_BIT(Copy_u8Data, 7u));
        DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D6, GET_BIT(Copy_u8Data, 6u));
        DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D5, GET_BIT(Copy_u8Data, 5u));
        DIO_u8SetPinValue(CLCD_u8DATA_PORT, CLCD_u8D4, GET_BIT(Copy_u8Data, 4u));
    }

    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8EN_PIN, DIO_u8SIGNAL_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8EN_PIN, DIO_u8SIGNAL_LOW);
}

void CLCD_voidWriteOperator(uint8_t Copy_u8Data) {
    if (CLCD_u8RW_PIN != CLCD_u8PIN_CONNECTED_TO_GROUND)
        DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RW_PIN, DIO_u8SIGNAL_LOW);

    if (CLCD_u8OperationMode == CLCD_u8MODE_8_BIT_DATA)
        return CLCD_voidOutputToDataBus(Copy_u8Data);

    if (!CLCD_u8InitBegan) {
        CLCD_u8InitBegan = TRUE;
        CLCD_voidOutputToDataBus(Copy_u8Data);
    }

    CLCD_voidOutputToDataBus(Copy_u8Data);
    CLCD_voidOutputToDataBus(Copy_u8Data << 4);
}

void CLCD_voidSendDataByte(uint8_t Copy_u8Data) {
    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RS_PIN, DIO_u8SIGNAL_HIGH);

    CLCD_voidWriteOperator(Copy_u8Data);
}

void CLCD_voidSendCmdByte(uint8_t Copy_u8Cmd) {
    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RS_PIN, DIO_u8SIGNAL_LOW);

    CLCD_voidWriteOperator(Copy_u8Cmd);
}

void CLCD_voidSendDataString(char *Copy_pcString) {
    while (*Copy_pcString != '\0') {
        CLCD_voidSendDataByte(*Copy_pcString++);
    }
}



void CLCD_voidSendDataBytes(char *Copy_pcBytes, uint8_t Copy_u8Size) {
    uint8_t Local_u8Counter = 0;
    while (Local_u8Counter != Copy_u8Size) {
        CLCD_voidSendDataByte(Copy_pcBytes[Local_u8Counter++]);
    }
}

void CLCD_voidSendDataBytesReversed(char *Copy_pcBytes, uint8_t Copy_u8Size) {
    while (Copy_u8Size != 0) {
        CLCD_voidSendDataByte(Copy_pcBytes[Copy_u8Size-- - 1]);
    }
}

// the beauty of recursion
void CLCD_voidSendDataInt32(int32_t Copy_s32Number) {
    if (Copy_s32Number < 0) {
        CLCD_voidSendDataByte('-');
        Copy_s32Number *= -1;
    }
    if (Copy_s32Number == 0) {
        CLCD_voidSendDataByte('0');
        return;
    }

    if (Copy_s32Number / 10 != 0) CLCD_voidSendDataInt32(Copy_s32Number / 10);
    CLCD_voidSendDataByte((int32_t)'0' + Copy_s32Number % 10);
}

uint8_t CLCD_u8SetCursorToXY(uint8_t Copy_u8XPos, uint8_t Copy_u8YPos) {
    if (Copy_u8XPos >= CLCD_u8X_POSITIONS_COUNT) return ERROR_VALUE_OUT_OF_BOUND;
    if (Copy_u8YPos >= CLCD_u8Y_POSITIONS_COUNT) return ERROR_VALUE_OUT_OF_BOUND;

    uint8_t Local_u8Address;

    Local_u8Address = Copy_u8YPos == 0u ? Copy_u8XPos : 0x40 + Copy_u8XPos;

    // Set bit 7 for SetDDRAM Address command
    SET_BIT(Local_u8Address, 7u);

    // Execute Set DDRAM Address command
    CLCD_voidSendCmdByte(Local_u8Address);

    return NO_ERROR;
}

// you must set the cursor to a valid DDRAM location after using this function
uint8_t CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(uint8_t *Copy_pu8Character, uint8_t Copy_u8CGRAMLocation) {
    if (!Copy_pu8Character) return ERROR_NULL_POINTER;
    if (Copy_u8CGRAMLocation >= CLCD_u8CG_RAM_LOCATIONS_COUNT) return ERROR_VALUE_OUT_OF_BOUND;

    uint8_t Local_u8Counter;

    uint8_t Local_u8CGRAMAddress = Copy_u8CGRAMLocation * 8;

    SET_BIT(Local_u8CGRAMAddress, 6u);

    CLCD_voidSendCmdByte(Local_u8CGRAMAddress);

    // Write the input pattern inside CGRAM
    for (Local_u8Counter = 0u; Local_u8Counter < CLCD_u8SINGLE_PATTERN_ROWS_COUNT; Local_u8Counter++) {
        CLCD_voidSendDataByte(Copy_pu8Character[Local_u8Counter]);
    }

    return NO_ERROR;
}

uint8_t CLCD_u8DisplayCharacterFromCGRAMAddress(uint8_t Copy_u8XPos, uint8_t Copy_u8YPos, uint8_t Copy_u8CGRAMLocation) {
    if (Copy_u8CGRAMLocation >= CLCD_u8CG_RAM_LOCATIONS_COUNT) return ERROR_VALUE_OUT_OF_BOUND;

    uint8_t Local_u8ErrorCode = CLCD_u8SetCursorToXY(Copy_u8XPos, Copy_u8YPos);
    if (Local_u8ErrorCode != NO_ERROR) return Local_u8ErrorCode;

    CLCD_voidSendDataByte(Copy_u8CGRAMLocation);

    return NO_ERROR;
}

void CLCD_voidInit(void) {
    _delay_ms(40);

    char CLCD_u8CMD = 0b00111000;
    if (CLCD_u8OperationMode == CLCD_u8MODE_4_BIT_DATA) CLEAR_BIT(CLCD_u8CMD, 4);
    if (CLCD_u8LCD_LINES == CLCD_u8LCD_ONE_LINE) CLEAR_BIT(CLCD_u8CMD, 3);
    if (CLCD_u8LCD_FONT_SIZE == CLCD_u8FONT_SIZE_LARGE) SET_BIT(CLCD_u8CMD, 2);
    CLCD_voidSendCmdByte(CLCD_u8CMD);

    CLCD_u8CMD = 0b00001100;
    if (CLCD_u8LCD_CURSOR_DISPLAY == CLCD_u8DISPLAY_CURSOR) SET_BIT(CLCD_u8CMD, 1);
    if (CLCD_u8LCD_CURSOR_BEHAVIOUR == CLCD_u8CURSOR_BLINK) SET_BIT(CLCD_u8CMD, 0);
    CLCD_voidSendCmdByte(CLCD_u8CMD);

    CLCD_voidSendCmdByte(1);
}

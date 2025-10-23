#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"
#include "KPD/KPD_interface.h"
#include "PORT/PORT_interface.h"

uint8_t Global_u8Time[][2] = {{0, 0}, {0, 0}, {0, 0}};
uint8_t Global_u8TimeSelect = 0, Global_u8DigitSelect = 0;
uint8_t Global_pu8CharacterFigure[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00010001};

void voidDisplayCharacterFigureStandingLeftTalking(char *Copy_pcString) {
    CLCD_voidSendCmdByte(1);

    CLCD_u8SetCursorToXY(0, 0);

    CLCD_voidSendDataString(Copy_pcString);

    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
}

void voidDisplayTime(uint8_t Copy_u8DisplaySelect) {
    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);
    uint8_t i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            CLCD_voidSendDataInt32(Global_u8Time[i][j]);
        }
        if (i != 2) CLCD_voidSendDataByte(':');
    }
    if (Copy_u8DisplaySelect) {
        CLCD_u8SetCursorToXY(Global_u8TimeSelect * 3 + Global_u8DigitSelect, 1);
        CLCD_voidSendDataByte('^');
    }
}

void voidDisplayTimeFromSeconds(uint16_t Copy_u16Seconds) {
    uint8_t Local_u8Hours = Copy_u16Seconds / 3600;
    uint8_t Local_u8Minutes = Copy_u16Seconds % 3600 / 60;
    uint8_t Local_uSeconds = Copy_u16Seconds % 60;

    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);
    if (Local_u8Hours < 10) CLCD_voidSendDataByte('0');
    CLCD_voidSendDataInt32(Local_u8Hours);
    CLCD_voidSendDataByte(':');
    if (Local_u8Minutes < 10) CLCD_voidSendDataByte('0');
    CLCD_voidSendDataInt32(Local_u8Minutes);
    CLCD_voidSendDataByte(':');
    if (Local_uSeconds < 10) CLCD_voidSendDataByte('0');
    CLCD_voidSendDataInt32(Local_uSeconds);
}

void voidDisplayCountdown() {
    uint16_t Local_u16Seconds = (Global_u8Time[0][0] * 10 + Global_u8Time[0][1]) * 3600;
    Local_u16Seconds += (Global_u8Time[1][0] * 10 + Global_u8Time[1][1]) * 60;
    Local_u16Seconds += (Global_u8Time[2][0] * 10 + Global_u8Time[2][1]);

    while (Local_u16Seconds != 0) {
        voidDisplayTimeFromSeconds(Local_u16Seconds);
        _delay_ms(1000);
        Local_u16Seconds--;
    }
    voidDisplayTimeFromSeconds(0);
    _delay_ms(1000);
}

void main(void) {

    PORT_voidInit();

    uint8_t Local_u8Temp = KPD_u8NON_PRESSED_VALUE;

    CLCD_voidInit();

    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8CharacterFigure, 0);

    CLCD_u8SetCursorToXY(0, 0);

    voidDisplayTime(TRUE);

    while (1) {
        KPD_u8GetKeyPressed(&Local_u8Temp);

        if (Local_u8Temp != KPD_u8NON_PRESSED_VALUE) {
            if (Local_u8Temp >= '0' && Local_u8Temp <= '9') {
                Global_u8Time[Global_u8TimeSelect][Global_u8DigitSelect] = Local_u8Temp - '0';
                voidDisplayTime(TRUE);
            }
            if (Local_u8Temp == '<') {
                if (!Global_u8TimeSelect && !Global_u8DigitSelect)
                    continue;
                else if (Global_u8DigitSelect)
                    Global_u8DigitSelect--;
                else if (!Global_u8DigitSelect) {
                    Global_u8TimeSelect--;
                    Global_u8DigitSelect++;
                }
                voidDisplayTime(TRUE);
            }
            if (Local_u8Temp == '>') {
                if (Global_u8TimeSelect == 2 && Global_u8DigitSelect)
                    continue;
                else if (!Global_u8DigitSelect)
                    Global_u8DigitSelect++;
                else if (Global_u8DigitSelect) {
                    Global_u8TimeSelect++;
                    Global_u8DigitSelect--;
                }
                voidDisplayTime(TRUE);
            }
            if (Local_u8Temp == 'S') {
                voidDisplayCountdown();
                voidDisplayCharacterFigureStandingLeftTalking(" Time Is Up..");
                while (1) {
                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8SIGNAL_HIGH);
                    _delay_ms(500);
                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8SIGNAL_LOW);
                    _delay_ms(500);
                }
            }
        }

        Local_u8Temp = KPD_u8NON_PRESSED_VALUE;
    }
}

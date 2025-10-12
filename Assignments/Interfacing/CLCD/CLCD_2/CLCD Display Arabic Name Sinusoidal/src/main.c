
#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"

uint8_t Global_u8ArabicCharacterDash[8] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b00000000, 0b00000000, 0b00000000};
uint8_t Global_u8ArabicCharacterAlf[8] = {0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000100, 0b00000000, 0b00000000, 0b00000000};
uint8_t Global_u8ArabicCharacter7a2[8] = {0b00000000, 0b00001100, 0b00010010, 0b00000001, 0b00011111, 0b00000000, 0b00000000, 0b00000000};
uint8_t Global_u8ArabicCharacterMem[8] = {0b00000000, 0b00000000, 0b00000100, 0b00001010, 0b00010001, 0b00001110, 0b00000000, 0b00000000};
uint8_t Global_u8ArabicCharacterDal[8] = {0b00000000, 0b00000000, 0b00000100, 0b00000100, 0b00011111, 0b00000000, 0b00000000, 0b00000000};
uint8_t Global_u8ArabicCharacterRa2[8] = {0b00000000, 0b00000000, 0b00000010, 0b00000010, 0b00000100, 0b00001000, 0b00000000, 0b00000000};
uint8_t Global_u8ArabicCharacterDad[8] = {0b00000010, 0b00000000, 0b00000110, 0b00011001, 0b00011111, 0b00010000, 0b00000000, 0b00000000};
uint8_t Global_u8ArabicCharacterNon[8] = {0b00000000, 0b00000000, 0b00010101, 0b00010001, 0b00011111, 0b00000000, 0b00000000, 0b00000000};

char Global_Display_Bytes[] = {1, 2, 3, 4};
uint8_t Global_u8PositionX = 12, Global_u8PositionY = 0;

void voidChangePosition() {
    if (Global_u8PositionX)
        Global_u8PositionX -= 2;
    else
        Global_u8PositionX = 12;

    TOGGLE_BIT(Global_u8PositionY, 0);
}

void main(void) {
    DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8DIR_OUTPUT);

    CLCD_voidInit();

    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_u8ArabicCharacterDash, 0);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_u8ArabicCharacterAlf, 1);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_u8ArabicCharacter7a2, 2);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_u8ArabicCharacterMem, 3);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_u8ArabicCharacterDal, 4);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_u8ArabicCharacterRa2, 5);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_u8ArabicCharacterDad, 6);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_u8ArabicCharacterNon, 7);

    while (1) {
        CLCD_voidSendCmdByte(1);
        CLCD_u8SetCursorToXY(Global_u8PositionX, Global_u8PositionY);
        CLCD_voidSendDataBytesReversed(Global_Display_Bytes, 4);
        voidChangePosition();
        _delay_ms(500);
    }
}

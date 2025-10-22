#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"
#include "KPD/KPD_interface.h"
#include "PORT/PORT_interface.h"

#define LINE_WIDTH 16u
#define SIGN_TRANSFORM_OFFSET 1000

char Global_acEquation[LINE_WIDTH], Global_acEquationCleaned[LINE_WIDTH];
uint8_t Global_u8CharIdx = 0;

int32_t Global_ai32TransformedEquation[LINE_WIDTH];
int32_t Global_i32Result = 0;

uint8_t u8IsSign(char Copy_cSign) {
    return Copy_cSign == '+' || Copy_cSign == '-' || Copy_cSign == '*' || Copy_cSign == '/';
}

void voidRemoveRepeats() {
    uint8_t Local_u8LoopIdx, Local_u8EquationIdx = 0, Local_u8IsFirstFound = FALSE;
    for (Local_u8LoopIdx = 0; Local_u8LoopIdx < LINE_WIDTH; Local_u8LoopIdx++) {
        if (!Local_u8IsFirstFound) {
            if (u8IsSign(Global_acEquation[Local_u8LoopIdx])) continue;

            Local_u8IsFirstFound = TRUE;
        }

        Global_acEquationCleaned[Local_u8EquationIdx] = (char)Global_acEquation[Local_u8LoopIdx];

        while (u8IsSign(Global_acEquationCleaned[Local_u8EquationIdx]) && u8IsSign(Global_acEquation[Local_u8LoopIdx + 1]) && Local_u8LoopIdx < LINE_WIDTH) {
            Local_u8LoopIdx++;
        }

        Local_u8EquationIdx++;
    }
}

void voidCleanEnd() {
    uint8_t Local_u8LoopIdx = 0;
    for (Local_u8LoopIdx = 0; Local_u8LoopIdx < LINE_WIDTH; Local_u8LoopIdx++) {
        if (u8IsSign(Global_acEquationCleaned[Local_u8LoopIdx]) && Global_acEquationCleaned[Local_u8LoopIdx + 1] == ' ')
            Global_acEquationCleaned[Local_u8LoopIdx] = ' ';
    }
}

uint16_t u16NumWeightLookUp(char *Copy_cDigit) {
    if (*(Copy_cDigit + 1) == '\0' || *(Copy_cDigit + 1) == ' ' || u8IsSign(*(Copy_cDigit + 1)))
        return 1u;
    return 10u * u16NumWeightLookUp(Copy_cDigit + 1);
}

uint8_t u8IsNumber(char Copy_cDigit) {
    return Copy_cDigit >= '0' && Copy_cDigit <= '9';
}

void voidTransform() {
    uint8_t Local_u8LoopIdx, Local_u8TransformedEquIdx = 0;
    for (Local_u8LoopIdx = 0; Local_u8LoopIdx < LINE_WIDTH; Local_u8LoopIdx++) {
        if (u8IsNumber(Global_acEquationCleaned[Local_u8LoopIdx])) {
            int16_t Local_s16Sum = 0;
            do {
                Local_s16Sum += (Global_acEquationCleaned[Local_u8LoopIdx] - '0') * u16NumWeightLookUp(&Global_acEquationCleaned[Local_u8LoopIdx]);
                Local_u8LoopIdx++;
            } while ((Local_u8LoopIdx < LINE_WIDTH) && u8IsNumber(Global_acEquationCleaned[Local_u8LoopIdx]));
            Global_ai32TransformedEquation[Local_u8TransformedEquIdx] = Local_s16Sum;
            Local_u8LoopIdx--;
        } else if (u8IsSign(Global_acEquationCleaned[Local_u8LoopIdx])) {
            Global_ai32TransformedEquation[Local_u8TransformedEquIdx] = SIGN_TRANSFORM_OFFSET + Global_acEquationCleaned[Local_u8LoopIdx];
        }
        Local_u8TransformedEquIdx++;
    }
}

uint16_t u16GetNext(uint8_t Copy_u8Idx, uint8_t Copy_u8Default) {
    if (Copy_u8Idx >= LINE_WIDTH) return Copy_u8Default;

    if (Global_ai32TransformedEquation[Copy_u8Idx] == SIGN_TRANSFORM_OFFSET)
        return u16GetNext(Copy_u8Idx + 1,Copy_u8Default);

    uint16_t Local_u16Temp = Global_ai32TransformedEquation[Copy_u8Idx];
    Global_ai32TransformedEquation[Copy_u8Idx] = SIGN_TRANSFORM_OFFSET;
    return Local_u16Temp;
}

uint16_t u16GetPrev(uint8_t Copy_u8Idx, uint8_t Copy_u8Default) {
    if (Copy_u8Idx < 0) return Copy_u8Default;

    if (Global_ai32TransformedEquation[Copy_u8Idx] == SIGN_TRANSFORM_OFFSET)
        return u16GetPrev(Copy_u8Idx - 1,Copy_u8Default);

    uint16_t Local_u16Temp = Global_ai32TransformedEquation[Copy_u8Idx];
    Global_ai32TransformedEquation[Copy_u8Idx] = SIGN_TRANSFORM_OFFSET;
    return Local_u16Temp;
}

uint8_t u8Eval(char Copy_cSign) {
    uint8_t Local_u8IsSignFound = FALSE;
    int16_t Local_s16Temp;

    while (TRUE) {
        uint8_t Local_u8LoopIdx;
        Local_u8IsSignFound = FALSE;
        for (Local_u8LoopIdx = 0; Local_u8LoopIdx < LINE_WIDTH; Local_u8LoopIdx++) {
            if (Global_ai32TransformedEquation[Local_u8LoopIdx] == (Copy_cSign + SIGN_TRANSFORM_OFFSET)) {

                switch (Copy_cSign) {
                    case '+':
                        Global_ai32TransformedEquation[Local_u8LoopIdx] = u16GetPrev(Local_u8LoopIdx - 1, 0) + u16GetNext(Local_u8LoopIdx + 1, 0);
                        break;
                    case '-':
                        Global_ai32TransformedEquation[Local_u8LoopIdx] = (int32_t)u16GetPrev(Local_u8LoopIdx - 1, 0) - (int32_t)u16GetNext(Local_u8LoopIdx + 1, 0);
                        break;
                    case '*':
                        Global_ai32TransformedEquation[Local_u8LoopIdx] = u16GetPrev(Local_u8LoopIdx - 1, 1) * u16GetNext(Local_u8LoopIdx + 1, 1);
                        break;
                    case '/':
                        Local_s16Temp = u16GetNext(Local_u8LoopIdx + 1, 1);
                        if (Local_s16Temp == 0) {
                            CLCD_u8SetCursorToXY(0, 1);
                            CLCD_voidSendDataString("ERR DIV BY 0");
                            return ERROR_INVALID_VALUE;
                        }
                        Global_ai32TransformedEquation[Local_u8LoopIdx] = u16GetPrev(Local_u8LoopIdx - 1, 1) / Local_s16Temp;
                        break;

                    default:
                        break;
                }

                Local_u8IsSignFound = TRUE;
                break;
            }
        }
        if (!Local_u8IsSignFound) break;
    }
    return NO_ERROR;
}

int32_t s32GetResult() {
    uint8_t Local_u8LoopIdx;
    for (Local_u8LoopIdx = 0; Local_u8LoopIdx < LINE_WIDTH; Local_u8LoopIdx++) {
        if (Global_ai32TransformedEquation[Local_u8LoopIdx] == SIGN_TRANSFORM_OFFSET)
            continue;
        return Global_ai32TransformedEquation[Local_u8LoopIdx];
    }
}

void main(void) {

    PORT_voidInit();

    uint8_t Local_u8Temp = KPD_u8NON_PRESSED_VALUE;

    CLCD_voidInit();
    CLCD_u8SetCursorToXY(0, 0);

    while (1) {
        KPD_u8GetKeyPressed(&Local_u8Temp);

        if (Local_u8Temp != KPD_u8NON_PRESSED_VALUE) {
            if (Global_u8CharIdx < LINE_WIDTH && Local_u8Temp != '=' && Local_u8Temp != '<') {
                CLCD_voidSendDataByte(Local_u8Temp);
                Global_acEquation[Global_u8CharIdx++] = Local_u8Temp;
                Global_acEquation[Global_u8CharIdx] = ' ';
            }
            if (Global_u8CharIdx && Local_u8Temp == '<') {
                Global_acEquation[Global_u8CharIdx] = ' ';
                CLCD_u8SetCursorToXY(--Global_u8CharIdx, 0);
                CLCD_voidSendDataByte(' ');
                CLCD_u8SetCursorToXY(Global_u8CharIdx, 0);
            }
            if (Global_u8CharIdx && Local_u8Temp == '=') {
                voidRemoveRepeats();
                voidCleanEnd();
                voidTransform();
                u8Eval('*');
                if (u8Eval('/') != NO_ERROR) goto RESET;
                u8Eval('+');
                u8Eval('-');
                CLCD_u8SetCursorToXY(0, 1);

                CLCD_voidSendDataString("=");
                CLCD_voidSendDataInt32(s32GetResult());
                CLCD_voidSendDataByte(' ');

            RESET:

                Local_u8Temp = KPD_u8NON_PRESSED_VALUE;
                while (1) {
                    KPD_u8GetKeyPressed(&Local_u8Temp);
                    if (Local_u8Temp == '=') {
                        CLCD_voidSendCmdByte(1);
                        uint8_t i;
                        for (i = 0; i < LINE_WIDTH; i++) {
                            Global_ai32TransformedEquation[i] = Global_acEquation[i] = Global_acEquationCleaned[i] = 0;
                            Global_u8CharIdx = Global_i32Result = 0;
                        }
                        break;
                    }
                }
            }
            Local_u8Temp = KPD_u8NON_PRESSED_VALUE;
        }
    }
}


#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"

#include "BUTTON_PRESS/BP_interface.h"

typedef enum {
    u8FIRST_NUMBER_SELECTED,
    u8SECOND_NUMBER_SELECTED,
    u8SIGN_SELECTED,
    u8EQUAL_SELECTED
} Selection;

uint8_t Global_pu8ArrowCharacter[8] = {0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00000100, 0b00000100, 0b00000000, 0b00000000};

int32_t Global_int32FirstNumber = 1, Global_int32SecondNumber = 1;
uint8_t Global_u8Selection = u8FIRST_NUMBER_SELECTED;
char Global_u8Sign = '+';

uint8_t u8DigitsCount(int32_t Copy_i32Number) {
    if (Copy_i32Number / 10 == 0) return 1;
    return 1 + u8DigitsCount(Copy_i32Number / 10);
}

void voidPrintArrow() {
    CLCD_voidSendCmdByte(0xC0);

    uint8_t Local_u8Offset = 0;

    if (Global_u8Selection != u8FIRST_NUMBER_SELECTED && Global_int32FirstNumber < 0)
        Local_u8Offset++;

    switch (Global_u8Selection) {
        case u8FIRST_NUMBER_SELECTED:
            break;

        case u8SIGN_SELECTED:
            Local_u8Offset += 1 + u8DigitsCount(Global_int32FirstNumber);
            break;

        case u8SECOND_NUMBER_SELECTED:
            Local_u8Offset += 3 + u8DigitsCount(Global_int32FirstNumber);
            break;

        case u8EQUAL_SELECTED:
            return;
            break;

        default:
            break;
    }

    uint8_t Local_u8Loop;
    for (Local_u8Loop = Local_u8Offset; Local_u8Loop > 0; Local_u8Loop--) {
        CLCD_voidSendDataByte(' ');
    }

    CLCD_voidSendDataByte(1);
}

void voidPrintEquation() {
    CLCD_voidSendCmdByte(1);

    CLCD_voidSendDataInt32(Global_int32FirstNumber);
    CLCD_voidSendDataByte(' ');
    CLCD_voidSendDataByte(Global_u8Sign);
    CLCD_voidSendDataByte(' ');
    CLCD_voidSendDataInt32(Global_int32SecondNumber);

    if (Global_u8Selection == u8EQUAL_SELECTED) {
        CLCD_voidSendDataString(" = ");

        switch (Global_u8Sign) {
            case '+':
                CLCD_voidSendDataInt32(Global_int32FirstNumber + Global_int32SecondNumber);
                break;
            case '-':
                CLCD_voidSendDataInt32(Global_int32FirstNumber - Global_int32SecondNumber);
                break;
            case '*':
                CLCD_voidSendDataInt32(Global_int32FirstNumber * Global_int32SecondNumber);
                break;
            case '/':
                CLCD_voidSendDataInt32(Global_int32FirstNumber / Global_int32SecondNumber);
                if (Global_int32FirstNumber % Global_int32SecondNumber) {
                    CLCD_voidSendDataString(".");
                    int32_t Local_i32Temp = Global_int32FirstNumber % Global_int32SecondNumber * 100;
                    if (Local_i32Temp < 0) Local_i32Temp *= -1;
                    CLCD_voidSendDataInt32(Local_i32Temp / Global_int32SecondNumber);
                }

                break;

            default:
                break;
        }
    }

    voidPrintArrow();
}

void voidNextSelection() {
    switch (Global_u8Selection) {
        case u8FIRST_NUMBER_SELECTED:
            Global_u8Selection = u8SIGN_SELECTED;
            break;
        case u8SIGN_SELECTED:
            Global_u8Selection = u8SECOND_NUMBER_SELECTED;
            break;
        case u8SECOND_NUMBER_SELECTED:
            Global_u8Selection = u8EQUAL_SELECTED;
            break;

        case u8EQUAL_SELECTED:
            Global_u8Selection = u8FIRST_NUMBER_SELECTED;
            Global_int32FirstNumber = 1;
            Global_int32SecondNumber = 1;
            Global_u8Sign = '+';
            break;

        default:
            break;
    }
}

void voidAddToSelection() {
    switch (Global_u8Selection) {
        case u8FIRST_NUMBER_SELECTED:
            Global_int32FirstNumber++;
            break;

        case u8SIGN_SELECTED:
            switch (Global_u8Sign) {
                case '+':
                    Global_u8Sign = '-';
                    break;
                case '-':
                    Global_u8Sign = '*';
                    break;
                case '*':
                    Global_u8Sign = '/';
                    break;

                default:
                    break;
            }
            break;

        case u8SECOND_NUMBER_SELECTED:
            Global_int32SecondNumber++;
            if (!Global_int32SecondNumber && Global_u8Sign == '/')
                Global_int32SecondNumber++;
            break;

        default:
            break;
    }
}

void voidSubtractFromSelection() {
    switch (Global_u8Selection) {
        case u8FIRST_NUMBER_SELECTED:
            Global_int32FirstNumber--;
            break;

        case u8SIGN_SELECTED:
            switch (Global_u8Sign) {
                case '/':
                    Global_u8Sign = '*';
                    break;
                case '*':
                    Global_u8Sign = '-';
                    break;
                case '-':
                    Global_u8Sign = '+';
                    break;

                default:
                    break;
            }
            break;

        case u8SECOND_NUMBER_SELECTED:
            Global_int32SecondNumber--;
            if (!Global_int32SecondNumber && Global_u8Sign == '/')
                Global_int32SecondNumber--;
            break;

        default:
            break;
    }
}

void main(void) {
    DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8DIR_OUTPUT);

    CLCD_voidInit();

    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8ArrowCharacter, 1);

    CLCD_u8SetCursorToXY(0, 0);

    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN2, DIO_u8DIR_INPUT);
    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN3, DIO_u8DIR_INPUT);
    DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN4, DIO_u8DIR_INPUT);

    DIO_u8SetPortDirection(DIO_u8PORTC, DIO_u8DIR_OUTPUT);

    voidPrintEquation();

    while (1) {
        if (!ButtonPress_u8IsPressed(DIO_u8PORTD, DIO_u8PIN4)) {
            voidNextSelection();
            voidPrintEquation();
        }

        if (!ButtonPress_u8IsPressed(DIO_u8PORTD, DIO_u8PIN3)) {
            voidAddToSelection();
            voidPrintEquation();
        }

        if (!ButtonPress_u8IsPressed(DIO_u8PORTD, DIO_u8PIN2)) {
            voidSubtractFromSelection();
            voidPrintEquation();
        }
    }
}

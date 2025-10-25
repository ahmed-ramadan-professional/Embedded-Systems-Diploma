#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"
#include "DCM/DCM_helper.h"
#include "DCM/DCM_interface.h"
#include "KPD/KPD_interface.h"
#include "PORT/PORT_interface.h"
#include "Stepper/Stepper_helper.h"
#include "Stepper/Stepper_interface.h"

#define SPEECH_DELAY 1000
#define RUNNING_DELAY 50

uint8_t Global_pu8Hamoksha[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00010001};
uint8_t Global_pu8HamokshaRunningRight[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00010100};
uint8_t Global_pu8HamokshaRunningLeft[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00000101};

void voidDisplayHamokshaStandingRightTalking(char *Copy_pcString) {
    CLCD_voidSendCmdByte(1);

    CLCD_u8SetCursorToXY(0, 0);

    CLCD_voidSendDataString(Copy_pcString);

    CLCD_u8SetCursorToXY(15, 1);
    CLCD_voidSendDataByte(0);
}

void voidInit(void) {
    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
    _delay_ms(SPEECH_DELAY);

    voidRunHamokshaToLeft();

    voidDisplayHamokshaStandingRightTalking("Welcome to..");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingRightTalking("Motor Dashboard");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingRightTalking("Press..");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingRightTalking("1 for DC Motor");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingRightTalking("2 for Stepper");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingRightTalking("Waiting..");
}

void voidRunHamokshaToLeft() {
    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);

    uint8_t Local_u8Loop;
    for (Local_u8Loop = 0; Local_u8Loop < 15u; Local_u8Loop++) {
        CLCD_voidSendCmdByte(1);
        CLCD_u8SetCursorToXY(Local_u8Loop, 1);
        if (Local_u8Loop % 2 == 0)
            CLCD_voidSendDataByte(1);
        else
            CLCD_voidSendDataByte(0);

        _delay_ms(RUNNING_DELAY);
    }

    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(Local_u8Loop, 1);
    CLCD_voidSendDataByte(0);
    _delay_ms(RUNNING_DELAY);
}

void main(void) {

    PORT_voidInit();

    CLCD_voidInit();

    uint8_t Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;

    DCM_sCONFIGS DCM;
    DCM_MACRO_SET_CONFIGS_VALUES(DCM, DIO_u8PORTB, DIO_u8PIN4, DIO_u8PIN5);

    STEPPER_sCONFIGS STEPPER;
    STEPPER_MACRO_SET_CONFIGS_VALUES(STEPPER, DIO_u8PORTB, DIO_u8PIN0, DIO_u8PIN1, DIO_u8PIN2, DIO_u8PIN3);

    CLCD_voidInit();

    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8Hamoksha, 0);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8HamokshaRunningRight, 1);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8HamokshaRunningLeft, 2);

    CLCD_u8SetCursorToXY(0, 0);

    voidInit();

    while (1) {
        KPD_u8GetKeyPressed(&Local_u8PressedButton);

        if (Local_u8PressedButton == '1') {
            Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
            voidDisplayHamokshaStandingRightTalking("Press..");
            _delay_ms(SPEECH_DELAY);
            voidDisplayHamokshaStandingRightTalking("1 for Clockwise");
            _delay_ms(SPEECH_DELAY);
            voidDisplayHamokshaStandingRightTalking("2 for Anti-clockwise");
            _delay_ms(SPEECH_DELAY);
            voidDisplayHamokshaStandingRightTalking("Waiting..");

            while (1) {
                KPD_u8GetKeyPressed(&Local_u8PressedButton);

                if (Local_u8PressedButton == '1') {
                    Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
                    CLCD_voidSendCmdByte(1);
                    voidDisplayHamokshaStandingRightTalking("Clockwise..");
                    DCM_u8Turn(&DCM, DCM_u8CLOCKWISE_DIRECTION);
                    _delay_ms(5000);
                    DCM_u8Stop(&DCM);
                    goto END;
                }

                if (Local_u8PressedButton == '2') {
                    Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
                    CLCD_voidSendCmdByte(1);
                    voidDisplayHamokshaStandingRightTalking("Anti-Clockwise..");
                    DCM_u8Turn(&DCM, DCM_u8ANTI_CLOCKWISE_DIRECTION);
                    _delay_ms(5000);
                    DCM_u8Stop(&DCM);
                    goto END;
                }
            }
        }

        if (Local_u8PressedButton == '2') {
            Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
            voidDisplayHamokshaStandingRightTalking("Press..");
            _delay_ms(SPEECH_DELAY);
            voidDisplayHamokshaStandingRightTalking("1 for Clockwise");
            _delay_ms(SPEECH_DELAY);
            voidDisplayHamokshaStandingRightTalking("2 for Anti-clockwise");
            _delay_ms(SPEECH_DELAY);
            voidDisplayHamokshaStandingRightTalking("Waiting..");

            uint8_t Local_u8Direction;

            while (1) {
                KPD_u8GetKeyPressed(&Local_u8PressedButton);

                if (Local_u8PressedButton == '1') {
                    Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
                    CLCD_voidSendCmdByte(1);
                    voidDisplayHamokshaStandingRightTalking("Clockwise..");
                    _delay_ms(SPEECH_DELAY);
                    Local_u8Direction = STEPPER_u8CLOCKWISE_DIRECTION;
                    break;
                }

                if (Local_u8PressedButton == '2') {
                    Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
                    CLCD_voidSendCmdByte(1);
                    voidDisplayHamokshaStandingRightTalking("Anti-Clockwise..");
                    _delay_ms(SPEECH_DELAY);
                    Local_u8Direction = STEPPER_u8ANTI_CLOCKWISE_DIRECTION;
                    break;
                }
            }
            uint8_t Local_au8Digits[] = {0, 0, 0, 0};
            uint8_t Local_u8DigitsIdx = 0;

            voidDisplayHamokshaStandingRightTalking("How many steps..");
            _delay_ms(SPEECH_DELAY);
            voidDisplayHamokshaStandingRightTalking("Enter 3 digits");
            _delay_ms(SPEECH_DELAY);
            voidDisplayHamokshaStandingRightTalking(">");

            while (1) {
                KPD_u8GetKeyPressed(&Local_u8PressedButton);
                if (Local_u8DigitsIdx >= 3) break;
                if (Local_u8PressedButton >= '0' && Local_u8PressedButton <= '9') {
                    CLCD_u8SetCursorToXY(1 + Local_u8DigitsIdx, 0);
                    CLCD_voidSendDataByte(Local_u8PressedButton);
                    Local_au8Digits[Local_u8DigitsIdx] = Local_u8PressedButton;
                    Local_u8DigitsIdx++;
                    Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
                }
            }

            if (Local_u8Direction == STEPPER_u8CLOCKWISE_DIRECTION) {
                CLCD_voidSendCmdByte(1);
                CLCD_voidSendDataString("CW - ");
                CLCD_voidSendDataString(Local_au8Digits);
                CLCD_u8SetCursorToXY(15, 1);
                CLCD_voidSendDataByte(0);
                uint16_t Local_u16Steps = (Local_au8Digits[0] - '0') * 100 + (Local_au8Digits[1] - '0') * 10 + (Local_au8Digits[2] - '0');
                Stepper_u8Turn(&STEPPER, STEPPER_u8CLOCKWISE_DIRECTION, Local_u16Steps);
                goto END;
            } else {
                CLCD_voidSendCmdByte(1);
                CLCD_voidSendDataString("ACW - ");
                CLCD_voidSendDataString(Local_au8Digits);
                CLCD_u8SetCursorToXY(15, 1);
                CLCD_voidSendDataByte(0);
                uint16_t Local_u16Steps = (Local_au8Digits[0] - '0') * 100 + (Local_au8Digits[1] - '0') * 10 + (Local_au8Digits[2] - '0');
                Stepper_u8Turn(&STEPPER, STEPPER_u8ANTI_CLOCKWISE_DIRECTION, Local_u16Steps);
                goto END;
            }
        }
    }
    uint8_t Local_u8Loop;
END:
    for (Local_u8Loop = 0; Local_u8Loop < 15u; Local_u8Loop++) {
        CLCD_voidSendCmdByte(1);
        CLCD_u8SetCursorToXY(15u - Local_u8Loop, 1);
        if (Local_u8Loop % 2 == 0)
            CLCD_voidSendDataByte(2);
        else
            CLCD_voidSendDataByte(0);
        _delay_ms(RUNNING_DELAY);
    }

    CLCD_voidSendCmdByte(1);
    CLCD_voidSendDataString("Thanks..");
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
    _delay_ms(SPEECH_DELAY);
}

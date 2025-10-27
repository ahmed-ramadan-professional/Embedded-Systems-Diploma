#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"
#include "Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"
#include "DCM/DCM_helper.h"
#include "DCM/DCM_interface.h"
#include "EXTI/EXTI_interface.h"
#include "GIE/GIE_interface.h"
#include "KPD/KPD_interface.h"
#include "PORT/PORT_interface.h"

#define SPEECH_DELAY 1000
#define RUNNING_DELAY 50

uint8_t Global_pu8Hamoksha[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00010001};
uint8_t Global_pu8HamokshaRunningRight[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00010100};
uint8_t Global_pu8HamokshaRunningLeft[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00000101};

uint8_t volatile Global_u8IsSystemEnabled = FALSE;

DCM_sCONFIGS DCM;

void voidSystemStop(void);

void voidDisplayHamokshaStandingRightTalking(char *Copy_pcString) {
    CLCD_voidSendCmdByte(1);

    CLCD_u8SetCursorToXY(0, 0);

    CLCD_voidSendDataString(Copy_pcString);

    CLCD_u8SetCursorToXY(15, 1);
    CLCD_voidSendDataByte(0);
}

void voidInit(void) {
    DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8SIGNAL_LOW);
    DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN1, DIO_u8SIGNAL_LOW);

    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
    _delay_ms(SPEECH_DELAY);

    voidRunHamokshaToLeft();
    voidDisplayHamokshaStandingRightTalking("Welcome to..");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingRightTalking("System Project");
    _delay_ms(SPEECH_DELAY);

    uint8_t Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;

    uint8_t Local_u8LoopIdx;
    for (Local_u8LoopIdx = 0; Local_u8LoopIdx < 3; Local_u8LoopIdx++) {
        voidDisplayHamokshaStandingRightTalking("Enter ID");
        _delay_ms(SPEECH_DELAY);
        voidDisplayHamokshaStandingRightTalking(">");

        uint8_t Local_au8ID[] = {'1', '2', '3', '4', 0};
        uint8_t Local_au8Pass[] = {'1', '2', '3', '4', 0};

        uint8_t Local_au8Digits[] = {0, 0, 0, 0, 0};
        uint8_t Local_u8DigitsIdx = 0;

        while (1) {
            KPD_u8GetKeyPressed(&Local_u8PressedButton);
            if (Local_u8DigitsIdx > 3) break;
            if (Local_u8PressedButton >= '0' && Local_u8PressedButton <= '9') {
                CLCD_u8SetCursorToXY(1 + Local_u8DigitsIdx, 0);
                CLCD_voidSendDataByte(Local_u8PressedButton);
                Local_au8Digits[Local_u8DigitsIdx] = Local_u8PressedButton;
                Local_u8DigitsIdx++;
                Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
            }
        }

        uint8_t Local_u8InnerLoopIdx, Local_u8IsValid = TRUE;
        for (Local_u8InnerLoopIdx = 0; Local_u8InnerLoopIdx < 5; Local_u8InnerLoopIdx++) {
            if (Local_au8Digits[Local_u8InnerLoopIdx] != Local_au8ID[Local_u8InnerLoopIdx]) {
                voidDisplayHamokshaStandingRightTalking("Wrong ID");
                _delay_ms(SPEECH_DELAY);
                Local_u8IsValid = FALSE;
                break;
            }
        }
        if (!Local_u8IsValid) continue;

        voidDisplayHamokshaStandingRightTalking("Enter Pass");
        _delay_ms(SPEECH_DELAY);
        CLCD_voidSendCmdByte(1);
        
        CLCD_voidSendDataString(">"); // Hamoksha won't see your password
        Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
        Local_u8DigitsIdx = 0;

        while (1) {
            KPD_u8GetKeyPressed(&Local_u8PressedButton);
            if (Local_u8DigitsIdx > 3) break;
            if (Local_u8PressedButton >= '0' && Local_u8PressedButton <= '9') {
                CLCD_u8SetCursorToXY(1 + Local_u8DigitsIdx, 0);
                CLCD_voidSendDataByte(Local_u8PressedButton);
                Local_au8Digits[Local_u8DigitsIdx] = Local_u8PressedButton;
                Local_u8DigitsIdx++;
                Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;
            }
        }

        Local_u8IsValid = TRUE;
        for (Local_u8InnerLoopIdx = 0; Local_u8InnerLoopIdx < 5; Local_u8InnerLoopIdx++) {
            if (Local_au8Digits[Local_u8InnerLoopIdx] != Local_au8Pass[Local_u8InnerLoopIdx]) {
                voidDisplayHamokshaStandingRightTalking("Wrong Pass");
                _delay_ms(SPEECH_DELAY);
                Local_u8IsValid = FALSE;
                break;
            }
        }

        if (!Local_u8IsValid) continue;

        Global_u8IsSystemEnabled = TRUE;

        DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8SIGNAL_HIGH);

        voidDisplayHamokshaStandingRightTalking("Running..");

        EXTI_voidSetCallback(EXTI_u8INT2, &voidSystemStop);

        return;

        //change callback
    }
    //lock system
    for (Local_u8LoopIdx = 0; Local_u8LoopIdx < 15u; Local_u8LoopIdx++) {
        CLCD_voidSendCmdByte(1);
        CLCD_u8SetCursorToXY(15u - Local_u8LoopIdx, 1);
        if (Local_u8LoopIdx % 2 == 0)
            CLCD_voidSendDataByte(2);
        else
            CLCD_voidSendDataByte(0);
        _delay_ms(RUNNING_DELAY);
    }

    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);
    CLCD_voidSendDataString("System Lock");
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
    DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN1, DIO_u8SIGNAL_HIGH);
}

void voidSystemStop(void) {
    Global_u8IsSystemEnabled = FALSE;
    DCM_u8Stop(&DCM);
    DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8SIGNAL_LOW);
    DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN1, DIO_u8SIGNAL_LOW);
    EXTI_voidSetCallback(EXTI_u8INT2, &voidInit);

    uint8_t Local_u8LoopIdx;
    for (Local_u8LoopIdx = 0; Local_u8LoopIdx < 15u; Local_u8LoopIdx++) {
        CLCD_voidSendCmdByte(1);
        CLCD_u8SetCursorToXY(15u - Local_u8LoopIdx, 1);
        if (Local_u8LoopIdx % 2 == 0)
            CLCD_voidSendDataByte(2);
        else
            CLCD_voidSendDataByte(0);
        _delay_ms(RUNNING_DELAY);
    }

    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);
    CLCD_voidSendDataString("Thanks");
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
    _delay_ms(SPEECH_DELAY);

    CLCD_voidSendCmdByte(1);
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
void INT0_Callback(void) {
    DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN2, DIO_u8SIGNAL_HIGH);
}

void main(void) {

    PORT_voidInit();

    CLCD_voidInit();

    uint8_t Local_u8PressedButton = KPD_u8NON_PRESSED_VALUE;

    DCM_MACRO_SET_CONFIGS_VALUES(DCM, DIO_u8PORTB, DIO_u8PIN4, DIO_u8PIN5);

    CLCD_voidInit();

    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8Hamoksha, 0);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8HamokshaRunningRight, 1);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8HamokshaRunningLeft, 2);

    CLCD_u8SetCursorToXY(0, 0);

    GIE_voidEnableGlobal();

    EXTI_voidInit();

    EXTI_voidSetCallback(EXTI_u8INT2, &voidInit);

    while (1) {
        while (Global_u8IsSystemEnabled) {
            DIO_u8SetPinValue(DIO_u8PORTC, DIO_u8PIN0, DIO_u8SIGNAL_HIGH);
            DCM_u8Turn(&DCM, DCM_u8CLOCKWISE_DIRECTION);
            _delay_ms(1000);
            DCM_u8Stop(&DCM);

            DCM_u8Turn(&DCM, DCM_u8ANTI_CLOCKWISE_DIRECTION);
            _delay_ms(1000);
            DCM_u8Stop(&DCM);
        }
    }
}

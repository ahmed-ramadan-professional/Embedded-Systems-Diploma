#include <util/delay.h>

#include "Library/BIT_MATH/BIT_MATH.h"

#include "DIO/DIO_interface.h"

#include "CLCD/CLCD_interface.h"

#define SPEECH_DELAY 1500
#define RUNNING_DELAY 100
#define BALL_PLAYING_COUNTER 20
#define BALL_DELAY 350
#define DANCING_COUNTER 20
#define DANCE_DELAY 300
#define BULLET_DELAY 100

uint8_t Global_pu8Hamoksha[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00010001};

uint8_t Global_pu8HamokshaRunningRight[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00010100};
uint8_t Global_pu8HamokshaRunningLeft[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010101, 0b00000100, 0b00001010, 0b00000101};

uint8_t Global_pu8HamokshaDancingRight[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00010110, 0b00000100, 0b00001010, 0b00010000};
uint8_t Global_pu8HamokshaDancingLeft[8] = {0b00000100, 0b00001010, 0b00000100, 0b00001110, 0b00001101, 0b00000100, 0b00001010, 0b00000001};

uint8_t Global_pu8Gun[8] = {0b00000000, 0b00000000, 0b00011111, 0b00011111, 0b00000101, 0b00000011, 0b00000011, 0b00000000};

void voidDisplayHamokshaStandingLeftTalking(char *Copy_pcString) {
    CLCD_voidSendCmdByte(1);

    CLCD_u8SetCursorToXY(0, 0);

    CLCD_voidSendDataString(Copy_pcString);

    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
}

void voidInit(void) {
    voidDisplayHamokshaStandingLeftTalking("Hello..");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingLeftTalking("I'm Hamoksha");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingLeftTalking("I'm Quite Tiny");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingLeftTalking("But..");
    _delay_ms(SPEECH_DELAY);
    voidDisplayHamokshaStandingLeftTalking("I Can Do a Lot");
    _delay_ms(SPEECH_DELAY);
}

void voidRunHamoksha() {
    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);

    voidDisplayHamokshaStandingLeftTalking("I Can Run..");
    _delay_ms(SPEECH_DELAY);

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
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
}

void voidPlayBallHamoksha() {
    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);

    voidDisplayHamokshaStandingLeftTalking("I Play The Ball..");
    _delay_ms(SPEECH_DELAY);

    uint8_t Local_u8Loop;
    for (Local_u8Loop = 0; Local_u8Loop < BALL_PLAYING_COUNTER; Local_u8Loop++) {
        CLCD_voidSendCmdByte(1);
        CLCD_u8SetCursorToXY(0, 1);
        if (Local_u8Loop % 2 == 0) {
            CLCD_voidSendDataByte(1);
            CLCD_voidSendDataByte('.');
        } else {
            CLCD_voidSendDataByte(0);
            CLCD_voidSendDataByte(0b10100101);
        }
        _delay_ms(BALL_DELAY);
    }

    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
}

void voidDanceHamoksha() {
    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 0);

    voidDisplayHamokshaStandingLeftTalking("I Can Dance..");
    _delay_ms(SPEECH_DELAY);

    uint8_t Local_u8Loop;
    for (Local_u8Loop = 0; Local_u8Loop < DANCING_COUNTER; Local_u8Loop++) {
        CLCD_voidSendCmdByte(1);
        CLCD_u8SetCursorToXY(0, 1);
        if (Local_u8Loop % 2 == 0) {
            CLCD_voidSendDataByte(3);
        } else {
            CLCD_voidSendDataByte(4);
        }
        _delay_ms(DANCE_DELAY);
    }

    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0);
}

void voidShootHamoksha() {
    CLCD_voidSendCmdByte(1);

    voidDisplayHamokshaStandingLeftTalking("What is this..");
    CLCD_u8SetCursorToXY(15, 1);
    CLCD_voidSendDataByte(5);
    _delay_ms(SPEECH_DELAY);

    voidDisplayHamokshaStandingLeftTalking("Why..");
    CLCD_u8SetCursorToXY(15, 1);
    CLCD_voidSendDataByte(5);
    _delay_ms(SPEECH_DELAY);

    voidDisplayHamokshaStandingLeftTalking("Don't Kill Me..");
    CLCD_u8SetCursorToXY(15, 1);
    CLCD_voidSendDataByte(5);
    _delay_ms(SPEECH_DELAY);

    voidDisplayHamokshaStandingLeftTalking("Please..");
    CLCD_u8SetCursorToXY(15, 1);
    CLCD_voidSendDataByte(5);
    _delay_ms(SPEECH_DELAY);

    voidDisplayHamokshaStandingLeftTalking("Nooooooo!!..");
    CLCD_u8SetCursorToXY(15, 1);
    CLCD_voidSendDataByte(5);

    uint8_t Local_u8Loop;
    for (Local_u8Loop = 0; Local_u8Loop < 15u; Local_u8Loop++) {
        if (Local_u8Loop) {
            CLCD_u8SetCursorToXY(14u - Local_u8Loop + 1, 1);
            CLCD_voidSendDataByte(' ');
        }
        CLCD_u8SetCursorToXY(14u - Local_u8Loop, 1);
        CLCD_voidSendDataByte(0b10100101);

        _delay_ms(BULLET_DELAY);
    }

    CLCD_voidSendCmdByte(1);
    CLCD_u8SetCursorToXY(0, 1);
    CLCD_voidSendDataByte(0b11110011);
}

void main(void) {
    DIO_u8SetPortDirection(DIO_u8PORTA, DIO_u8DIR_OUTPUT);

    CLCD_voidInit();

    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8Hamoksha, 0);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8HamokshaRunningRight, 1);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8HamokshaRunningLeft, 2);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8HamokshaDancingRight, 3);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8HamokshaDancingLeft, 4);
    CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(Global_pu8Gun, 5);

    voidInit();
    voidRunHamoksha();
    voidPlayBallHamoksha();
    voidDanceHamoksha();
    voidShootHamoksha();

    while (1) {
    }
}

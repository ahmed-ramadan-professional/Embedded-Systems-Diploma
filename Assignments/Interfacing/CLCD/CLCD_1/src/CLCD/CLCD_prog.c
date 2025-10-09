#include <stdint.h>
#include <util/delay.h>

#include "../Library/BIT_MATH/BIT_MATH.h"
#include "../Library/STD_DEFINSINS/STD_DEFINSINS.h"

#include "../DIO/DIO_interface.h"

#include "CLCD_cfg.h"
#include "CLCD_interface.h"
#include "CLCD_prv.h"

// will be built upon later to cover 4-bit mode operations 
void CLCD_voidOutputToDataBus(uint8_t Copy_u8Data) {
    uint8_t valid = DIO_u8SetPortCustomValue(CLCD_u8DATA_PORT, Copy_u8Data);
}

void CLCD_voidSendDataByte(uint8_t Copy_u8Data) {
    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RS_PIN, DIO_u8SIGNAL_HIGH);

    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RW_PIN, DIO_u8SIGNAL_LOW);

    CLCD_voidOutputToDataBus(Copy_u8Data);

    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8EN_PIN, DIO_u8SIGNAL_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8EN_PIN, DIO_u8SIGNAL_LOW);
}

void CLCD_voidSendCmdByte(uint8_t Copy_u8Cmd) {
    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RS_PIN, DIO_u8SIGNAL_LOW);

    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RW_PIN, DIO_u8SIGNAL_LOW);

    CLCD_voidOutputToDataBus(Copy_u8Cmd);

    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8EN_PIN, DIO_u8SIGNAL_HIGH);
    _delay_ms(2);
    DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8EN_PIN, DIO_u8SIGNAL_LOW);
}

void CLCD_voidSendDataString(char *Copy_pcString) {
    while (*Copy_pcString != '\0') {
        CLCD_voidSendDataByte(*Copy_pcString++);
    }
}

// the beauty of recursion
void CLCD_voidSendDataInt32(int32_t number) {
    if (number < 0) {
        CLCD_voidSendDataByte('-');
        number *= -1;
    }
    if (number == 0) {
        CLCD_voidSendDataByte('0');
        return;
    }

    if (number / 10 != 0) CLCD_voidSendDataInt32(number / 10);
    CLCD_voidSendDataByte((int32_t)'0' + number % 10);
}

void CLCD_voidInit(void) {
    _delay_ms(40);

    // Function set command: 2 lines, Font size: 5x7
    // CLCD_voidSendCmdByte(0b00111000);
    char cmd = 0b00111000;
    if (CLCD_u8LCD_LINES == CLCD_u8LCD_ONE_LINE) CLEAR_BIT(cmd, 3);
    if (CLCD_u8LCD_FONT_SIZE == CLCD_u8FONT_SIZE_LARGE) SET_BIT(cmd, 2);
    CLCD_voidSendCmdByte(cmd);

    // Display on off control : Display on, cursor off, blink cursor off
    // CLCD_voidSendCmdByte(0b00001100);
    cmd = 0b00001100;
    if (CLCD_u8LCD_CURSOR_DISPLAY == CLCD_u8DISPLAY_CURSOR) SET_BIT(cmd, 1);
    if (CLCD_u8LCD_CURSOR_BEHAVIOUR == CLCD_uCURSOR_BLINK) SET_BIT(cmd, 0);
    CLCD_voidSendCmdByte(cmd);

    CLCD_voidSendCmdByte(1);
}

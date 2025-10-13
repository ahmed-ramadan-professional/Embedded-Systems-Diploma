#ifndef CLCD_CFG_H
#define CLCD_CFG_H


// CLCD_u8MODE_4_BIT_DATA for 4-bit DATA bus
// CLCD_u8MODE_8_BIT_DATA for 8-bit DATA bus
#define CLCD_u8OPERATION_MODE           CLCD_u8MODE_4_BIT_DATA

#define CLCD_u8CONTROL_PORT             DIO_u8PORTA
#define CLCD_u8DATA_PORT                DIO_u8PORTA
#define CLCD_u8RS_PIN                   1
#define CLCD_u8EN_PIN                   2

// if RW pin is connected to ground its value to "CLCD_u8PIN_CONNECTED_TO_GROUND"
#define CLCD_u8RW_PIN                   CLCD_u8PIN_CONNECTED_TO_GROUND

#if CLCD_u8OPERATION_MODE == CLCD_u8MODE_4_BIT_DATA
    #define CLCD_u8D4                   DIO_u8PIN3                   
    #define CLCD_u8D5                   DIO_u8PIN4
    #define CLCD_u8D6                   DIO_u8PIN5
    #define CLCD_u8D7                   DIO_u8PIN6
#endif

#define CLCD_u8LCD_WIDTH                16

// CLCD_u8LCD_TWO_LINES Or CLCD_u8LCD_ONE_LINE
#define CLCD_u8LCD_LINES                CLCD_u8LCD_TWO_LINES

// CLCD_u8FONT_SIZE_SMALL Or CLCD_u8FONT_SIZE_LARGE
#define CLCD_u8LCD_FONT_SIZE            CLCD_u8FONT_SIZE_SMALL

// CLCD_u8NO_CURSOR Or CLCD_u8DISPLAY_CURSOR
#define CLCD_u8LCD_CURSOR_DISPLAY       CLCD_u8NO_CURSOR

// CLCD_uNO_BLINK Or CLCD_uCURSOR_BLINK
#define CLCD_u8LCD_CURSOR_BEHAVIOUR     CLCD_u8NO_BLINK

#endif
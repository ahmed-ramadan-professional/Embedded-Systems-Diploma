#ifndef CLCD_CFG_H
#define CLCD_CFG_H

typedef enum {
    CLCD_u8UNSET_CONFIG,
    CLCD_u8M_4_BIT_DATA,
    CLCD_u8M_8_BIT_DATA,
    CLCD_u8LCD_ONE_LINE,
    CLCD_u8LCD_TWO_LINES,
    CLCD_u8FONT_SIZE_SMALL,
    CLCD_u8FONT_SIZE_LARGE,
    CLCD_u8NO_CURSOR,
    CLCD_u8DISPLAY_CURSOR,
    CLCD_uCURSOR_BLINK,
    CLCD_uNO_BLINK,

} CONFIG_PARAMETARS;

// M_4_BIT_DATA for 4-bit DATA bus
// M_8_BIT_DATA for 8-bit DATA bus
#define CLCD_u8OPERATION_MODE           CLCD_u8M_8_BIT_DATA

// required for any mode
#define CLCD_u8CONTROL_PORT             DIO_u8PORTA
#define CLCD_u8DATA_PORT                DIO_u8PORTB
#define CLCD_u8RS_PIN                   0
#define CLCD_u8RW_PIN                   1
#define CLCD_u8EN_PIN                   2


#define CLCD_u8LCD_WIDTH                16
#define CLCD_u8LCD_LINES                CLCD_u8LCD_TWO_LINES
#define CLCD_u8LCD_FONT_SIZE            CLCD_u8FONT_SIZE_SMALL
#define CLCD_u8LCD_CURSOR_DISPLAY       CLCD_u8NO_CURSOR
#define CLCD_u8LCD_CURSOR_BEHAVIOUR     CLCD_uNO_BLINK

#endif
#ifndef CLCD_PRV_H
#define CLCD_PRV_H

#include "CLCD_cfg.h"

#define CLCD_u8X_POSITIONS_COUNT                                    40u
#define CLCD_u8Y_POSITIONS_COUNT                                    2u
#define CLCD_u8SINGLE_PATTERN_ROWS_COUNT                            8u
#define CLCD_u8CG_RAM_LOCATIONS_COUNT                               8u

typedef enum {
    CLCD_u8PRESERVED_CONFIG_VALUE, // to avoid 0 values
    CLCD_u8MODE_4_BIT_DATA,
    CLCD_u8MODE_8_BIT_DATA,
    CLCD_u8LCD_ONE_LINE,
    CLCD_u8LCD_TWO_LINES,
    CLCD_u8FONT_SIZE_SMALL,
    CLCD_u8FONT_SIZE_LARGE,
    CLCD_u8NO_CURSOR,
    CLCD_u8DISPLAY_CURSOR,
    CLCD_u8NO_BLINK,
    CLCD_u8CURSOR_BLINK,

} CONFIG_PARAMETERS;

// it can't be a valid pin or port number 
const uint8_t CLCD_u8PIN_CONNECTED_TO_GROUND = 255;

const uint8_t CLCD_u8OperationMode = CLCD_u8OPERATION_MODE;

#endif
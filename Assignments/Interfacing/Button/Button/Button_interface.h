#ifndef Button_INTERFACE_H
#define Button_INTERFACE_H

#include <stdint.h>

typedef struct {
    uint8_t PORT;
    uint8_t PIN;
} BUTTON_sCONFIGS;

uint8_t Button_u8IsPressed(BUTTON_sCONFIGS *Copy_psConfigs, uint8_t *Copy_pu8ReturnValue);

#endif // !BUTTON_INTERFACE_H

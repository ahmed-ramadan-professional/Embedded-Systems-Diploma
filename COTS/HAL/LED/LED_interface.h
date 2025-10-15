#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include <stdint.h>

typedef struct {
    uint8_t PORT;
    uint8_t PIN;
    uint8_t IS_ANODE_CONNECTED;

} LED_sCONFIGS;


uint8_t LED_u8TurnOFF(LED_sCONFIGS *Copy_psConfigs);
uint8_t LED_u8TurnON(LED_sCONFIGS *Copy_psConfigs);

#endif // !LED_INTERFACE_H

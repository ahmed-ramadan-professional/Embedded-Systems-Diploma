#ifndef DCM_INTERFACE_H
#define DCM_INTERFACE_H

#include <stdint.h>

typedef enum {
    DCM_u8CLOCKWISE_DIRECTION,
    DCM_u8ANTI_CLOCKWISE_DIRECTION,
} DCM_u8DIRECTION;

typedef struct {
    uint8_t PORT;
    uint8_t PIN_1;
    uint8_t PIN_2;

} DCM_sCONFIGS;

uint8_t DCM_u8Turn(DCM_sCONFIGS *Copy_psConfigs, uint8_t Copy_u8Direction);
uint8_t DCM_u8Stop(DCM_sCONFIGS *Copy_psConfigs);

#endif // !DCM_INTERFACE_H

#ifndef STEPPER_INTERFACE_H
#define STEPPER_INTERFACE_H

#include <stdint.h>

typedef enum {
    STEPPER_u8CLOCKWISE_DIRECTION,
    STEPPER_u8ANTI_CLOCKWISE_DIRECTION,
} STEPPER_u8DIRECTION;

typedef struct {
    uint8_t PORT;
    uint8_t PIN_0;
    uint8_t PIN_1;
    uint8_t PIN_2;
    uint8_t PIN_3;

} STEPPER_sCONFIGS;

uint8_t Stepper_u8Turn(STEPPER_sCONFIGS *Copy_psConfigs, uint8_t Copy_u8Direction, uint16_t Copy_u16Steps);

#endif // !STEPPER_INTERFACE_H

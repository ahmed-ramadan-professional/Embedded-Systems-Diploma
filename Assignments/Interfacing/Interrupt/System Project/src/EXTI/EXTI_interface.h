#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include <stdint.h>

typedef enum {
    EXTI_u8DISABLED,
    EXTI_u8ENABLED
} EXTI_State_t;

typedef enum {
    EXTI_u8INT0,
    EXTI_u8INT1,
    EXTI_u8INT2,
} EXTI_Channel_t;

typedef enum {
    EXTI_u8LOW_LEVEL,
    EXTI_u8ON_CHANGE,
    EXTI_u8FALLING_EDGE,
    EXTI_u8RISING_EDGE
} EXTI_SenseCtrl_t;

void EXTI_voidInit(void);
uint8_t EXTI_u8SetSenseCtrl(EXTI_Channel_t Copy_Channel, EXTI_SenseCtrl_t SenseCtrl);
uint8_t EXTI_u8SetState(EXTI_Channel_t Copy_Channel, EXTI_State_t Copy_State);
uint8_t EXTI_voidSetCallback(EXTI_Channel_t Copy_Channel, void *Copy_pvCallback(void));

#endif // !EXTI_INTERFACE_Hs
#include <stdint.h>

#include "../Library/BIT_MATH/BIT_MATH.h"
#include "../Library/STD_DEFINSINS/STD_DEFINSINS.h"
#include "../Library/STD_ERROR_CODES/STD_ERROR_CODES.h"

#include "EXTI_cfg.h"
#include "EXTI_interface.h"
#include "EXTI_reg.h"

static void (*EXTI_Global_apvCallbacks[3])(void) = {NULL};

uint8_t EXTI_u8SetSenseCtrl(EXTI_Channel_t Copy_Channel, EXTI_SenseCtrl_t SenseCtrl) {
    if (SenseCtrl != EXTI_u8LOW_LEVEL && SenseCtrl != EXTI_u8ON_CHANGE && SenseCtrl != EXTI_u8RISING_EDGE && SenseCtrl != EXTI_u8FALLING_EDGE)
        return ERROR_INVALID_VALUE;

    switch (Copy_Channel) {
        case EXTI_u8INT0:
            SET_BIT_VALUE(MCUCR, MCUCR_ISC00, GET_BIT(SenseCtrl, 0));
            SET_BIT_VALUE(MCUCR, MCUCR_ISC01, GET_BIT(SenseCtrl, 1));
            break;

        case EXTI_u8INT1:
            SET_BIT_VALUE(MCUCR, MCUCR_ISC10, GET_BIT(SenseCtrl, 0));
            SET_BIT_VALUE(MCUCR, MCUCR_ISC11, GET_BIT(SenseCtrl, 1));
            break;

        case EXTI_u8INT2:
            SET_BIT_VALUE(MCUCSR, MCUCSR_ISC2, GET_BIT(SenseCtrl, 1));
            break;

        default:
            return ERROR_INVALID_VALUE;
    }

    return NO_ERROR;
}
uint8_t EXTI_u8SetState(EXTI_Channel_t Copy_Channel, EXTI_State_t Copy_State) {
    if (Copy_State != EXTI_u8ENABLED && Copy_State != EXTI_u8DISABLED)
        return ERROR_INVALID_VALUE;

    switch (Copy_Channel) {
        case EXTI_u8INT0:
            SET_BIT_VALUE(GICR, GICR_INT0, GET_BIT(Copy_State, 0));
            break;

        case EXTI_u8INT1:
            SET_BIT_VALUE(GICR, GICR_INT1, GET_BIT(Copy_State, 0));
            break;

        case EXTI_u8INT2:
            SET_BIT_VALUE(GICR, GICR_INT2, GET_BIT(Copy_State, 0));
            break;

        default:
            return ERROR_INVALID_VALUE;
    }

    return NO_ERROR;
}

uint8_t EXTI_voidSetCallback(EXTI_Channel_t Copy_Channel, void *Copy_pvCallback(void)) {
    if (Copy_Channel != EXTI_u8INT0 && Copy_Channel != EXTI_u8INT1 && Copy_Channel != EXTI_u8INT2) return ERROR_INVALID_VALUE;
    if (!Copy_pvCallback) return ERROR_NULL_POINTER;

    EXTI_Global_apvCallbacks[Copy_Channel] = Copy_pvCallback;

    return NO_ERROR;
}

void EXTI_voidInit(void) {
    EXTI_u8SetSenseCtrl(EXTI_u8INT0, EXTI_u8INT0_SENSE_CTRL);
    EXTI_u8SetSenseCtrl(EXTI_u8INT1, EXTI_u8INT1_SENSE_CTRL);
    EXTI_u8SetSenseCtrl(EXTI_u8INT2, EXTI_u8INT2_SENSE_CTRL);

    EXTI_u8SetState(EXTI_u8INT0, EXTI_u8INT0_INIT_STATE);
    EXTI_u8SetState(EXTI_u8INT1, EXTI_u8INT1_INIT_STATE);
    EXTI_u8SetState(EXTI_u8INT2, EXTI_u8INT2_INIT_STATE);
}

__attribute__((signal)) void __vector_1(void);
void __vector_1(void) {
    if (EXTI_Global_apvCallbacks[0])
        EXTI_Global_apvCallbacks[0]();
}

__attribute__((signal)) void __vector_2(void);
void __vector_2(void) {
    if (EXTI_Global_apvCallbacks[1])
        EXTI_Global_apvCallbacks[1]();
}

__attribute__((signal)) void __vector_3(void);
void __vector_3(void) {
    if (EXTI_Global_apvCallbacks[2])
        EXTI_Global_apvCallbacks[2]();
}

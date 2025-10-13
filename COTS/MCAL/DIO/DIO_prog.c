#include <stdint.h>

#include "../Library/BIT_MATH/BIT_MATH.h"
#include "../Library/STD_DEFINSINS/STD_DEFINSINS.h"

#include "DIO_cfg.h"
#include "DIO_interface.h"
#include "DIO_prv.h"
#include "DIO_reg.h"

// ================================ Validation ======================================

uint8_t DIO_u8ValidateFuncArgs(ValidationRule Copy_u8Rule, uint8_t Copy_u8Value) {
    switch (Copy_u8Rule) {
        case DIO_VALID_PIN:
            return (Copy_u8Value >= 0 && Copy_u8Value < DIO_u8PORT_WIDTH);

        case DIO_VALID_PORT:
            return (Copy_u8Value >= 0 && Copy_u8Value < DIO_u8PORT_COUNT) &&
                   (DIO_pu8ArrPortRegisters[Copy_u8Value] != NULL);

        case DIO_VALID_DIR:
            return (Copy_u8Value >= 0 && Copy_u8Value < DIO_u8DIRECTIONS_COUNT);

        case DIO_VALID_SIGNAL:
            return (Copy_u8Value >= 0 && Copy_u8Value < DIO_u8SIGNAL_STATES);

        default:
            return 0u;
    }
}
// ================================ Direction ======================================

uint8_t DIO_u8SetPortDirection(uint8_t Copy_u8Port, uint8_t Copy_u8Direction) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_DIR, Copy_u8Direction)) return 0;

    if (Copy_u8Direction == DIO_u8DIR_OUTPUT)
        *(DIO_pu8ArrPortDirections[Copy_u8Port]) = 0xFF;
    else
        *(DIO_pu8ArrPortDirections[Copy_u8Port]) = 0x00;

    return 1u;
}

uint8_t DIO_u8SetPinDirection(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t Copy_u8Direction) {

    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PIN, Copy_u8Pin)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_DIR, Copy_u8Direction)) return 0;

    if (Copy_u8Direction == DIO_u8DIR_OUTPUT)
        SET_BIT(*(DIO_pu8ArrPortDirections[Copy_u8Port]), Copy_u8Pin);
    else
        CLEAR_BIT(*(DIO_pu8ArrPortDirections[Copy_u8Port]), Copy_u8Pin);

    return 1u;
}

uint8_t DIO_u8GetPortDirection(uint8_t Copy_u8Port, uint8_t *Copy_pu8Direction) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!Copy_pu8Direction) return 0;

    *Copy_pu8Direction = *(DIO_pu8ArrPortDirections[Copy_u8Port]);

    return 1u;
}

uint8_t DIO_u8GetPinDirection(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t *Copy_pu8Direction) {

    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PIN, Copy_u8Pin)) return 0;
    if (!Copy_pu8Direction) return 0;

    *Copy_pu8Direction = GET_BIT(*(DIO_pu8ArrPortDirections[Copy_u8Port]), Copy_u8Pin);

    return 1u;
}

// ================================ Pin Functions ======================================

uint8_t DIO_u8SetPinValue(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t Copy_u8Value) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PIN, Copy_u8Pin)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_SIGNAL, Copy_u8Value)) return 0;

    if (Copy_u8Value == DIO_u8SIGNAL_HIGH)
        SET_BIT(*(DIO_pu8ArrPortRegisters[Copy_u8Port]), Copy_u8Pin);
    else
        CLEAR_BIT(*(DIO_pu8ArrPortRegisters[Copy_u8Port]), Copy_u8Pin);
    return 1u;
}

uint8_t DIO_u8TogglePinValue(uint8_t Copy_u8Port, uint8_t Copy_u8Pin) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PIN, Copy_u8Pin)) return 0;

    TOGGLE_BIT(*(DIO_pu8ArrPortRegisters[Copy_u8Port]), Copy_u8Pin);
    return 1u;
}
uint8_t DIO_u8GetPinValue(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t *Copy_pu8Value) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PIN, Copy_u8Pin)) return 0;
    if (!Copy_pu8Value) return 0;

    *Copy_pu8Value = GET_BIT(*(DIO_pu8ArrInputRegisters[Copy_u8Port]), Copy_u8Pin);
    return 1u;
}

// ================================ Port Functions ====================================

uint8_t DIO_u8SetPortCustomValue(uint8_t Copy_u8Port, uint8_t Copy_u8Value) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;

    *(DIO_pu8ArrPortRegisters[Copy_u8Port]) = Copy_u8Value;

    return 1u;
}

uint8_t DIO_u8SetPortValue(uint8_t Copy_u8Port, uint8_t Copy_u8Value) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_SIGNAL, Copy_u8Value)) return 0;

    *(DIO_pu8ArrPortRegisters[Copy_u8Port]) = Copy_u8Value == DIO_u8SIGNAL_HIGH ? 0xFF : 0x00;

    return 1u;
}

uint8_t DIO_u8TogglePortValue(uint8_t Copy_u8Port) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;

    *(DIO_pu8ArrPortRegisters[Copy_u8Port]) = ~(*DIO_pu8ArrPortRegisters[Copy_u8Port]);

    return 1u;
}

uint8_t DIO_u8GetPortValue(uint8_t Copy_u8Port, uint8_t *Copy_pu8Value) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!Copy_pu8Value) return 0;

    *Copy_pu8Value = *(DIO_pu8ArrInputRegisters[Copy_u8Port]);

    return 1u;
}

// ================================ Pull-Up ======================================

uint8_t DIO_u8PullPinUp(uint8_t Copy_u8Port, uint8_t Copy_u8Pin) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PIN, Copy_u8Pin)) return 0;

    uint8_t DIO_u8Temp;
    DIO_u8GetPinDirection(Copy_u8Port, Copy_u8Pin, &DIO_u8Temp);
    if (DIO_u8Temp == DIO_u8DIR_OUTPUT) return 0;

    DIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, DIO_u8SIGNAL_HIGH);

    return 1u;
}

uint8_t DIO_u8PullPortUp(uint8_t Copy_u8Port) {
    if (!DIO_u8ValidateFuncArgs(DIO_VALID_PORT, Copy_u8Port)) return 0;

    uint8_t DIO_u8Temp;
    DIO_u8GetPortDirection(Copy_u8Port, &DIO_u8Temp);
    if (DIO_u8Temp == DIO_u8DIR_OUTPUT) return 0;

    DIO_u8SetPortValue(Copy_u8Port, DIO_u8SIGNAL_HIGH);

    return 1u;
}

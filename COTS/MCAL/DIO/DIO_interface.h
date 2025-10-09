#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

#include <stdint.h>

// ================================ Definitions ======================================

#define DIO_u8PORTA 0u
#define DIO_u8PORTB 1u
#define DIO_u8PORTC 2u
#define DIO_u8PORTD 3u

#define DIO_u8PIN0 0u
#define DIO_u8PIN1 1u
#define DIO_u8PIN2 2u
#define DIO_u8PIN3 3u
#define DIO_u8PIN4 4u
#define DIO_u8PIN5 5u
#define DIO_u8PIN6 6u
#define DIO_u8PIN7 7u

#define DIO_u8DIR_INPUT 0u
#define DIO_u8DIR_OUTPUT 1u

#define DIO_u8SIGNAL_LOW 0u
#define DIO_u8SIGNAL_HIGH 1u

// ================================ Direction ==========================================

uint8_t DIO_u8SetPinDirection(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t Copy_u8Direction);
uint8_t DIO_u8SetPortDirection(uint8_t Copy_u8Port, uint8_t Copy_u8Direction);
uint8_t DIO_u8GetPortDirection(uint8_t Copy_u8Port, uint8_t *Copy_pu8Direction);
uint8_t DIO_u8GetPinDirection(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t *Copy_pu8Direction);

// ================================ Pin Functions ======================================

uint8_t DIO_u8SetPinValue(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t Copy_u8Value);
uint8_t DIO_u8TogglePinValue(uint8_t Copy_u8Port, uint8_t Copy_u8Pin);
uint8_t DIO_u8GetPinValue(uint8_t Copy_u8Port, uint8_t Copy_u8Pin, uint8_t *Copy_pu8Value);

// ================================ Port Functions =====================================

uint8_t DIO_u8SetPortValue(uint8_t Copy_u8Port, uint8_t Copy_u8Value);
uint8_t DIO_u8SetPortValueHighOrLow(uint8_t Copy_u8Port, uint8_t Copy_u8Value);
uint8_t DIO_u8TogglePortValue(uint8_t Copy_u8Port);
uint8_t DIO_u8GetPortValue(uint8_t Copy_u8Port, uint8_t *Copy_pu8Value);

// =================================== Pull-Up =========================================

uint8_t DIO_u8PullPinUp(uint8_t Copy_u8Port, uint8_t Copy_u8Pin);
uint8_t DIO_u8PullPortUp(uint8_t Copy_u8Port);

#endif

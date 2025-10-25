#ifndef KPD_CFG_H
#define KPD_CFG_H

#include "DIO/DIO_interface.h"

#define KPD_u8ROW_PORT DIO_u8PORTD
#define KPD_u8COL_PORT DIO_u8PORTD

#define KPD_u8ROW_PIN0 DIO_u8PIN0
#define KPD_u8ROW_PIN1 DIO_u8PIN1
#define KPD_u8ROW_PIN2 DIO_u8PIN2
#define KPD_u8ROW_PIN3 DIO_u8PIN3

#define KPD_u8COL_PIN0 DIO_u8PIN4
#define KPD_u8COL_PIN1 DIO_u8PIN5
#define KPD_u8COL_PIN2 DIO_u8PIN6
#define KPD_u8COL_PIN3 DIO_u8PIN7

#define KPD_u8COL_SIZE 4u
#define KPD_u8ROW_SIZE 4u

const uint8_t KPD_au8KEYS[][KPD_u8COL_SIZE] = {{'7', '8', '9', 'X'}, {'4', '5', '6', 'X'}, {'1', '2', '3', 'X'}, {'X', '0', 'E', 'X'}};

#endif // !KPD_CFG_H
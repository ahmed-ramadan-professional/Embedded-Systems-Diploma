#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

#include <stdint.h>

void CLCD_voidSendCmdByte(uint8_t Copy_u8Cmd);

void CLCD_voidSendDataByte(uint8_t Copy_u8Data);

void CLCD_voidSendDataString(char *Copy_pcString);

void CLCD_voidSendDataInt32(int32_t number);

void CLCD_voidInit(void);


#endif

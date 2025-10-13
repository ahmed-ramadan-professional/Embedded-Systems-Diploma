#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

#include <stdint.h>

void CLCD_voidSendCmdByte(uint8_t Copy_u8Cmd);

void CLCD_voidSendDataByte(uint8_t Copy_u8Data);

void CLCD_voidSendDataBytes(char *Copy_pcBytes, uint8_t Copy_u8Size);

void CLCD_voidSendDataBytesReversed(char *Copy_pcBytes, uint8_t Copy_u8Size);

void CLCD_voidSendDataString(char *Copy_pcString);

void CLCD_voidSendDataInt32(int32_t Copy_s32Number);

uint8_t CLCD_u8SetCursorToXY(uint8_t Copy_u8XPos, uint8_t Copy_u8YPos);

uint8_t CLCD_u8SetEightRowsPatternArrayToCGRAMLocation(uint8_t *Copy_pu8Character, uint8_t Copy_u8CGRAMLocation);

uint8_t CLCD_u8DisplayCharacterFromCGRAMAddress(uint8_t Copy_u8XPos, uint8_t Copy_u8YPos, uint8_t Copy_u8CGRAMLocation);


void CLCD_voidInit(void);



#endif

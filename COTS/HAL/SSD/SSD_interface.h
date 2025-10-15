#ifndef SSD_INTERFACE_H
#define SSD_INTERFACE_H

#include <stdint.h>

typedef struct {
    uint8_t DATA_PORT;
    uint8_t CONTROL_PORT;
    uint8_t IS_DATA_PINS_SHIFTED_BY_ONE;
    uint8_t CONTROL_PIN;
    uint8_t IS_COM_CATHODE;

} SSD_sDISPLAY_CONFIGS;


uint8_t SSD_u8DisplayOFF(SSD_sDISPLAY_CONFIGS *Copy_psConfigs);
uint8_t SSD_u8DisplayValue(SSD_sDISPLAY_CONFIGS *Copy_psConfigs, uint8_t Copy_u8Value);

#endif // !SSD_INTERFACE_H

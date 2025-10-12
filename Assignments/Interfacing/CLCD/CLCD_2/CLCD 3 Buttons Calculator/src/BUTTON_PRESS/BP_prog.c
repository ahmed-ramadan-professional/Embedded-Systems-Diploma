#include <util/delay.h>

#include "../Library/BIT_MATH/BIT_MATH.h"

#include "../DIO/DIO_interface.h"

#include "BP_cfg.h"
#include "BP_interface.h"


uint8_t ButtonPress_u8IsPressed(uint8_t Copy_u8Port, uint8_t Copy_u8Pin) {
    uint8_t Local_u8Temp;
    DIO_u8GetPinValue(Copy_u8Port,Copy_u8Pin,&Local_u8Temp);

    if (Local_u8Temp) {
        _delay_ms(BUTTON_PRESS_CONFIRMATION_TIME_DELAY);
        DIO_u8GetPinValue(Copy_u8Port,Copy_u8Pin,&Local_u8Temp);
        return Local_u8Temp;
    }
    return 0;
}

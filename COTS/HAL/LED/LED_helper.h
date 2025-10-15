#ifndef LED_HELPER_H
#define LED_HELPER_H

#define LED_MACRO_SET_CONFIGS_VALUES(LED, L_PORT, L_PIN, IS_A_C) \
    LED.PORT = L_PORT;                                         \
    LED.PIN = L_PIN;                                           \
    LED.IS_ANODE_CONNECTED = IS_A_C;

#endif // !LED_HELPER_H
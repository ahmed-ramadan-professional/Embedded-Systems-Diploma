#ifndef BUTTON_HELPER_H
#define BUTTON_HELPER_H

#define BUTTON_MACRO_SET_CONFIGS_VALUES(BUTTON, B_PORT, B_PIN) \
    BUTTON.PORT = B_PORT;                                      \
    BUTTON.PIN = B_PIN;

#endif // !BUTTON_HELPER_H
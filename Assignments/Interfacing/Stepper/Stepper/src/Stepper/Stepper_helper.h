#ifndef STEPPER_HELPER_H
#define STEPPER_HELPER_H

#define STEPPER_MACRO_SET_CONFIGS_VALUES(STEPPER, S_PORT, S_PIN_0, S_PIN_1, S_PIN_2, S_PIN_3) \
    STEPPER.PORT = S_PORT;                                                                    \
    STEPPER.PIN_0 = S_PIN_0;                                                                  \
    STEPPER.PIN_1 = S_PIN_1;                                                                  \
    STEPPER.PIN_2 = S_PIN_2;                                                                  \
    STEPPER.PIN_3 = S_PIN_3;

#endif // !STEPPER_HELPER_H
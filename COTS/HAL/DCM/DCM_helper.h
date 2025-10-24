#ifndef DCM_HELPER_H
#define DCM_HELPER_H

#define DCM_MACRO_SET_CONFIGS_VALUES(DCM, M_PORT, M_PIN_1, M_PIN_2) \
    DCM.PORT = M_PORT;                                              \
    DCM.PIN_1 = M_PIN_1;                                                \
    DCM.PIN_2 = M_PIN_2;

#endif // !DCM_HELPER_H
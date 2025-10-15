#ifndef SSD_HELPER_H
#define SSD_HELPER_H

#define SSD_MACRO_SET_CONFIGS_VALUES(SSD, DPORT, IS_SHIFTED, CPORT, CPIN, IS_C_C) \
    SSD.DATA_PORT = DPORT;                                                                      \
    SSD.IS_DATA_PINS_SHIFTED_BY_ONE = IS_SHIFTED;                                               \
    SSD.CONTROL_PORT = CPORT;                                                                   \
    SSD.CONTROL_PIN = CPIN;                                                                     \
    SSD.IS_COM_CATHODE = IS_C_C;                                                                \


#define SSD_u8VALUE_0  0b11000000  // 0
#define SSD_u8VALUE_1  0b11111001  // 1
#define SSD_u8VALUE_2  0b10100100  // 2
#define SSD_u8VALUE_3  0b10110000  // 3
#define SSD_u8VALUE_4  0b10011001  // 4
#define SSD_u8VALUE_5  0b10010010  // 5
#define SSD_u8VALUE_6  0b10000010  // 6
#define SSD_u8VALUE_7  0b11111000  // 7
#define SSD_u8VALUE_8  0b10000000  // 8
#define SSD_u8VALUE_9  0b10010000  // 9

#define SSD_u8VALUE_A  0b10001000  // A
#define SSD_u8VALUE_B  0b10000011  // b
#define SSD_u8VALUE_C  0b11000110  // C
#define SSD_u8VALUE_D  0b10100001  // d
#define SSD_u8VALUE_E  0b10000110  // E
#define SSD_u8VALUE_F  0b10001110  // F

#endif // !SSD_HELPER_H
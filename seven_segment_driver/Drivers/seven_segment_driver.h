#include "main.h"

enum ENUM_SEVSEG_CHAR { //enum vs #define, more overhead but prefer the type safety
    ENUM_SEVSEG_0 = 0x3F, // 0
    ENUM_SEVSEG_1 = 0x06, // 1
    ENUM_SEVSEG_2 = 0x5B, // 2
    ENUM_SEVSEG_3 = 0x4F, // 3
    ENUM_SEVSEG_4 = 0x66, // 4
    ENUM_SEVSEG_5 = 0x6D, // 5
    ENUM_SEVSEG_6 = 0x7D, // 6
    ENUM_SEVSEG_7 = 0x07, // 7
    ENUM_SEVSEG_8 = 0x7F, // 8
    ENUM_SEVSEG_9 = 0x6F, // 9
    ENUM_SEVSEG_A = 0x77, // A
    ENUM_SEVSEG_b = 0x7C, // b
    ENUM_SEVSEG_c = 0x58, // c
    ENUM_SEVSEG_d = 0x5E, // d
    ENUM_SEVSEG_E = 0x79, // E
    ENUM_SEVSEG_F = 0x71, // F
    ENUM_SEVSEG_g = 0x6F, // g
    ENUM_SEVSEG_H = 0x76, // H
    ENUM_SEVSEG_L = 0x38, // L
    ENUM_SEVSEG_n = 0x54, // n
    ENUM_SEVSEG_o = 0x5C, // o
    ENUM_SEVSEG_p = 0x73, // p
    ENUM_SEVSEG_r = 0x50, // r
    ENUM_SEVSEG_t = 0x78, // t
    ENUM_SEVSEG_u = 0x1C, // u
    ENUM_SEVSEG_y = 0x6E  // y
};

static inline void SEVSEG_READ();
#ifndef __SEVEN_SEGMENT_DRIVER_H
	#define __SEVEN_SEGMENT_DRIVER_H
	#include "seven_segment_driver.h"
#endif

inline static uint8_t SEVSEG_GET_DATA(enum ENUM_SEVSEG_CHAR val) {
    switch (val) {
    case ENUM_SEVSEG_0:
        return 0x3F; // Example: 0 (binary 0111111 for 7-segment)
    case ENUM_SEVSEG_1:
        return 0x06; // Example: 1
    case ENUM_SEVSEG_2:
        return 0x5B; // Example: 2
    case ENUM_SEVSEG_3:
        return 0x4F; // Example: 3
    case ENUM_SEVSEG_4:
        return 0x66; // Example: 4
    case ENUM_SEVSEG_5:
        return 0x6D; // Example: 5
    case ENUM_SEVSEG_6:
        return 0x7D; // Example: 6
    case ENUM_SEVSEG_7:
        return 0x07; // Example: 7
    case ENUM_SEVSEG_8:
        return 0x7F; // Example: 8
    case ENUM_SEVSEG_9:
        return 0x6F; // Example: 9
    case ENUM_SEVSEG_A:
        return 0x77; // Example: A
    case ENUM_SEVSEG_b:
        return 0x7C; // Example: b
    case ENUM_SEVSEG_c:
        return 0x58; // Example: c
    case ENUM_SEVSEG_d:
        return 0x5E; // Example: d
    case ENUM_SEVSEG_E:
        return 0x79; // Example: E
    case ENUM_SEVSEG_F:
        return 0x71; // Example: F
    case ENUM_SEVSEG_g:
        return 0x6F; // Example: g
    case ENUM_SEVSEG_H:
        return 0x76; // Example: H
    case ENUM_SEVSEG_L:
        return 0x38; // Example: L
    case ENUM_SEVSEG_n:
        return 0x54; // Example: n
    case ENUM_SEVSEG_o:
        return 0x5C; // Example: o
    case ENUM_SEVSEG_p:
        return 0x73; // Example: p
    case ENUM_SEVSEG_r:
        return 0x50; // Example: r
    case ENUM_SEVSEG_t:
        return 0x78; // Example: t
    case ENUM_SEVSEG_u:
        return 0x1C; // Example: u
    case ENUM_SEVSEG_y:
        return 0x6E; // Example: y
    default:
        return 0x00; // Invalid character
    } 
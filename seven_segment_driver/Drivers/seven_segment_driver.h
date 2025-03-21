#ifndef __SEVEN_SEGMENT_DRIVER_H
#define __SEVEN_SEGMENT_DRIVER_H

#include "main.h"

enum ENUM_SEVSEG_CHAR { // COMMON ANODE
	ENUM_SEVSEG_0 = 0xC0, 
	ENUM_SEVSEG_1 = 0xF9, 
	ENUM_SEVSEG_2 = 0xA4,
	ENUM_SEVSEG_3 = 0xB0,
	ENUM_SEVSEG_4 = 0x99,
	ENUM_SEVSEG_5 = 0x92,
	ENUM_SEVSEG_6 = 0x82,
	ENUM_SEVSEG_7 = 0xF8,
	ENUM_SEVSEG_8 = 0x80,
	ENUM_SEVSEG_9 = 
};


extern const enum ENUM_SEVSEG_CHAR ENUM_SEVSEG_CHAR_Index[24];

typedef struct {
	const SPI_HandleTypeDef* spi_handler;
	const GPIO_TypeDef* CS_port;
	const uint8_t CS_pin;
    const GPIO_TypeDef* RES_port;
    const uint8_t RES_pin;
	uint8_t char_index; // index of character to be displayed
} SEVSEG_TypeDef;


HAL_StatusTypeDef SEVSEG_Write(enum ENUM_SEVSEG_CHAR data, SPI_HandleTypeDef* spi_handler);

#endif

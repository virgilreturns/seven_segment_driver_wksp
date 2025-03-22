#ifndef __SEVEN_SEGMENT_DRIVER_H
#define __SEVEN_SEGMENT_DRIVER_H

#include "main.h"

#ifdef SEVSEG_QTY_DIGITS
#if SEVSEG_QTY_DIGITS > 8
	#undef SEVSEG_QTY_DIGITS
	#define SEVSEG_QTY_DIGITS 8
#elif SEVSEG_QTY_DIGITS < 1
	#undef SEVSEG_QTY_DIGITS
	#define SEVSEG_QTY_DIGITS 1
#endif
#endif

enum ENUM_SEVSEG_CHAR
enum ENUM_SEVSEG_DIGIT { //digit index
	ENUM_SEVSEG_DIGIT_0 = 0,
	ENUM_SEVSEG_DIGIT_1 = 1,
	ENUM_SEVSEG_DIGIT_2 = 2,
	ENUM_SEVSEG_DIGIT_3 = 3,
	ENUM_SEVSEG_DIGIT_4 = 4,
	ENUM_SEVSEG_DIGIT_5 = 5,
	ENUM_SEVSEG_DIGIT_6 = 6,
	ENUM_SEVSEG_DIGIT_7 = 7
};

extern const enum ENUM_SEVSEG_CHAR ENUM_SEVSEG_CHAR_Index[];

typedef struct {
	const GPIO_TypeDef* DS_port;
	const uint16_t DS_pin;
	enum ENUM_SEVSEG_CHAR char_data; //when programming UI, make sure to use the array to incrementally select
} SEVSEG_DS_PIN;

typedef struct {
	const SPI_HandleTypeDef* spi_handler;
	const SEVSEG_DS_PIN digit_select[SEVSEG_QTY_DIGITS];
} SEVSEG_DISPLAY_TypeDef;

void SEVSEG_StoreDataBuf(SEVSEG_DISPLAY_TypeDef* seveg, enum ENUM_SEVSEG_CHAR data[]);
HAL_StatusTypeDef SEVSEG_DigitTx(SEVSEG_DISPLAY_TypeDef* sevseg, enum ENUM_SEVSEG_DIGIT digit);
HAL_StatusTypeDef SEVSEG_Write(SEVSEG_DISPLAY_TypeDef* sevseg);

#endif

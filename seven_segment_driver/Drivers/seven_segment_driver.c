#include "seven_segment_driver.h"

HAL_StatusTypeDef SEVSEG_Write(SEVSEG_TypeDef* sevseg) {

	HAL_StatusTypeDef success = HAL_SPI_Transmit(sevseg->spi_handler, ENUM_SEVSEG_CHAR_Index[sevseg->char_index], 1, 1000); //send data through MOSI pin
	HAL_GPIO_WritePin(sevseg->CS_port, sevseg->CS_pin, GPIO_PIN_SET); //activate latch on wanted chip
	HAL_GPIO_WritePin(sevseg->CS_port, sevseg->CS_pin, GPIO_PIN_RESET);
	return success;
};

void SEVSEG_Reset(SEVSEG_TypeDef* sevseg, GPIO_TypeDef* RES_port, uint8_t RES_pin)
{
	HAL_GPIO_WritePin(sevseg->RES_port, sev->RES_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(sevseg->RES_port, sevseg->RES_pin, GPIO_PIN_SET);
}

const enum ENUM_SEVSEG_CHAR ENUM_SEVSEG_CHAR_Index[24] = {
	ENUM_SEVSEG_NULL,
	ENUM_SEVSEG_0,
	ENUM_SEVSEG_1,
	ENUM_SEVSEG_2,
	ENUM_SEVSEG_3,
	ENUM_SEVSEG_4,
	ENUM_SEVSEG_5,
	ENUM_SEVSEG_6,
	ENUM_SEVSEG_7,
	ENUM_SEVSEG_8,
	ENUM_SEVSEG_9,
	ENUM_SEVSEG_A,
	ENUM_SEVSEG_b,
	ENUM_SEVSEG_c,
	ENUM_SEVSEG_d,
	ENUM_SEVSEG_E,
	ENUM_SEVSEG_F,
	ENUM_SEVSEG_g,
	ENUM_SEVSEG_H,
	ENUM_SEVSEG_L,
	ENUM_SEVSEG_n,
	ENUM_SEVSEG_o,
	ENUM_SEVSEG_p,
	ENUM_SEVSEG_r,
	ENUM_SEVSEG_t,
	ENUM_SEVSEG_u,
	ENUM_SEVSEG_y
}


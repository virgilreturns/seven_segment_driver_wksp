#include "seven_segment_driver.h"

HAL_StatusTypeDef SEVSEG_WRITE(enum ENUM_SEVSEG_CHAR data, SPI_HandleTypeDef *spi_handler, 
								GPIO_TypeDef* CS_port, uint8_t CS_pin) {
	
	HAL_StatusTypeDef success = HAL_SPI_Transmit(spi_handler, &data, 1, 1000); //send data through MOSI pin
	HAL_GPIO_WritePin(CS_port, CS_pin, GPIO_PIN_SET); //activate latch on wanted chip


	return HAL_OK;
	return HAL_ERROR;
	return HAL_BUSY;
	return HAL_TIMEOUT;


};


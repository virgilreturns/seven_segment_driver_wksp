#include "seven_segment_driver.h"

volatile enum ENUM_SEVSEG_CHAR data[SEVSEG_QTY_DIGITS] = { ENUM_SEVSEG_H, ENUM_SEVSEG_E, ENUM_SEVSEG_L, ENUM_SEVSEG_L, ENUM_SEVSEG_o };

void SEVSEG_StoreDataBuf(SEVSEG_DISPLAY_TypeDef* seveg, enum ENUM_SEVSEG_CHAR data[]) {
	for (i = 0; i < SEVSEG_QTY_DIGITS; i++) {
		seveg->digit_select[i].char_data = data[i];
	}
};

HAL_StatusTypeDef SEVSEG_DigitTx(SEVSEG_DISPLAY_TypeDef* sevseg, enum ENUM_SEVSEG_DIGIT digit) {

    HAL_StatusTypeDef success = HAL_SPI_Transmit(sevseg->spi_handler, sevseg->digit_select->char_data, 1, 1000); //send data through MOSI pin
	if (success != HAL_OK) return success; //if error, return error code
    
    HAL_GPIO_WritePin(SPI_CS1_Port, SPI_CS1_Pin, GPIO_PIN_SET); //pulse latch on wanted chip
	HAL_GPIO_WritePin(SPI_CS1_Port, SPI_CS1_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(sevseg->digit_select[digit].DS_port, sevseg->digit_select[digit].DS_pin, GPIO_PIN_SET);
	HAL_Delay(5); // 5ms delay to see the digit
    HAL_GPIO_WritePin(sevseg->digit_select[digit].DS_port, sevseg->digit_select[digit].DS_pin, GPIO_PIN_RESET);
	return success;
};

//FIRST DEMO IMPLREMENTATION: NO 'PLAY' MODE, JUST WRITE 5 CHAR TO 5 DIGIT DISPLAY
HAL_StatusTypeDef SEVSEG_Write(SEVSEG_DISPLAY_TypeDef* sevseg) {
	for (i=0; i < SEVSEG_QTY_DIGITS; i++) {
		SEVSEG_DigitTx(sevseg, i); }
};

void SEVSEG_Reset(SEVSEG_TypeDef* sevseg, GPIO_TypeDef* RES_port, uint8_t RES_pin)
{
	HAL_GPIO_WritePin(sevseg->RES_port, sev->RES_pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(sevseg->RES_port, sevseg->RES_pin, GPIO_PIN_SET);
}

const enum ENUM_SEVSEG_CHAR sevseg_chars[] = {
        ENUM_SEVSEG_0, ENUM_SEVSEG_1, ENUM_SEVSEG_2, ENUM_SEVSEG_3, ENUM_SEVSEG_4,
        ENUM_SEVSEG_5, ENUM_SEVSEG_6, ENUM_SEVSEG_7, ENUM_SEVSEG_8, ENUM_SEVSEG_9,
        ENUM_SEVSEG_A, ENUM_SEVSEG_b, ENUM_SEVSEG_C, ENUM_SEVSEG_d, ENUM_SEVSEG_E,
        ENUM_SEVSEG_f, ENUM_SEVSEG_H, ENUM_SEVSEG_J, ENUM_SEVSEG_n, ENUM_SEVSEG_o,
        ENUM_SEVSEG_p, ENUM_SEVSEG_r, ENUM_SEVSEG_t, ENUM_SEVSEG_U, ENUM_SEVSEG_v,
        ENUM_SEVSEG_null
    };

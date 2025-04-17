/*
 * app_main.c
 *
 *  Created on: Apr 16, 2025
 *      Author: virgilreturns
 */

#include "main.h"

extern SPI_HandleTypeDef hspi2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern SEVSEG_DISPLAY_TypeDef sevseg;

GPIO_PIN_TypeDef DIGIT_SEL_PINS_ARRAY[SEVSEG_QTY_DIGITS];
volatile enum ENUM_SEVSEG_DIGIT cursor_selection = ENUM_SEVSEG_DIGIT_0; //maybe add a UI handler


static void SEVSEG_Init();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef*);


int app_main(){

SEVSEG_Init();

uint8_t myDataa[5] = {ENUM_SEVSEG_CHAR_H,
					  ENUM_SEVSEG_CHAR_E,
					  ENUM_SEVSEG_CHAR_L,
					  ENUM_SEVSEG_CHAR_L,
					  ENUM_SEVSEG_CHAR_o};

SEVSEG_StoreDataBuf(&sevseg, myDataa); //stores enum indexes (user-defined-pointers) into each DIGIT in sevseg.digits_select[DIGIT]
	while(1){

	}
}


static void SEVSEG_Init(){

	GPIO_PIN_TypeDef DIGIT_SEL_PINS_ARRAY[SEVSEG_QTY_DIGITS] = {
			[ENUM_SEVSEG_DIGIT_0].port = DIGIT_SEL_0_GPIO_Port,
			[ENUM_SEVSEG_DIGIT_0].pin = DIGIT_SEL_0_Pin,
			[ENUM_SEVSEG_DIGIT_1].port = DIGIT_SEL_1_GPIO_Port,
			[ENUM_SEVSEG_DIGIT_1].pin = DIGIT_SEL_1_Pin,
			[ENUM_SEVSEG_DIGIT_2].port = DIGIT_SEL_2_GPIO_Port,
			[ENUM_SEVSEG_DIGIT_2].pin = DIGIT_SEL_2_Pin,
			[ENUM_SEVSEG_DIGIT_3].port = DIGIT_SEL_3_GPIO_Port,
			[ENUM_SEVSEG_DIGIT_3].pin = DIGIT_SEL_3_Pin,
			[ENUM_SEVSEG_DIGIT_4].port = DIGIT_SEL_4_GPIO_Port,
			[ENUM_SEVSEG_DIGIT_4].pin = DIGIT_SEL_4_Pin,
	};

	sevseg.digit_select[0].DS_pin = DIGIT_SEL_0_Pin;
	sevseg.digit_select[0].DS_port = DIGIT_SEL_0_GPIO_Port;
	sevseg.digit_select[0].current_char_index = 0;

	sevseg.digit_select[1].DS_pin = DIGIT_SEL_1_Pin;
	sevseg.digit_select[1].DS_port = DIGIT_SEL_1_GPIO_Port;
	sevseg.digit_select[1].current_char_index = 0;

	sevseg.digit_select[2].DS_pin = DIGIT_SEL_2_Pin;
	sevseg.digit_select[2].DS_port = DIGIT_SEL_2_GPIO_Port;
	sevseg.digit_select[2].current_char_index = 0;

	sevseg.digit_select[3].DS_pin = DIGIT_SEL_3_Pin;
	sevseg.digit_select[3].DS_port = DIGIT_SEL_3_GPIO_Port;
	sevseg.digit_select[3].current_char_index = 0;

	sevseg.digit_select[4].DS_pin = DIGIT_SEL_4_Pin;
	sevseg.digit_select[4].DS_port = DIGIT_SEL_4_GPIO_Port;
	sevseg.digit_select[4].current_char_index = 0;

	sevseg.refresh_target = ENUM_SEVSEG_DIGIT_0;

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
}

void HAL_GPIO_EXTI_Callback(uint16_t pin){
	return;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi){
}

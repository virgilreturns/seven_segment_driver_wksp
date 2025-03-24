/**
 ******************************************************************************
  * @file    seven_segment_driver.c
  * @author  Anderson Nguyen
  * @brief   Seven Segment Display Driver.
  * 
  *          This file provides firmware functions to use SPI with a single
			 SIPO shift register 74HC595 to interface with a Seven Segment 
			 Display of up to 8 digits.
  *          
  *
  ******************************************************************************
  @virgilreturns
  ==============================================================================
                 ##### Seven Segment Display Driver Features #####
  ==============================================================================

  [..]
  This driver comes with customized mode functionality for user interface with 
  a seven segment display. The purpose of this driver is to provide a simple way
  for a user to change values on a seven segment display using only a few discrete
  buttons. This would function as a basic text editor.

  Such UI implementations include:
  (+) One button config, where a single button is used to cycle through
	  the characters on the display; only compatible with a single digit.
  (+) Two button config, where one button is used to increment the character and
	  another to decrement the character.
  (+) Two button config plus, where a single button is used to cycle through
	  the characters and another to cycle through the digits.
  (+) Three button config, where one button is used to increment the character,
	  another to decrement the character, and a third to cycle digits.
  (+) Rotary Encoder config, where a rotary encoder can cycle digits or character, 
	  and a switch multiplexes which to cycle through
  
					   ##### How to use this driver #####
  ==============================================================================

	(#) define SEVSEG_QTY_DIGITS to the number of digits on the display

	(#) Create a SEVSEG_DISPLAY_TypeDef object and initialize it with the SPI handler
		and the GPIO digit select pins for each digit.

	(#) Initialize buttons/switches and other UI elements for external interrupts

	(#) create a data buffer of ENUM_SEVSEG_CHAR and initialize it with ENUM_SEVSEG_CHAR
		characters that you wish to display.

	(#) Call SEVSEG_StoreDataBuf() to store the data buffer in the display struct





  @endvirgilreturns
  ******************************************************************************
  */

#include "seven_segment_driver.h"

void SEVSEG_StoreDataBuf(SEVSEG_DISPLAY_TypeDef* seveg, enum ENUM_SEVSEG_CHAR data[]) {
	for (int i = 0; i < SEVSEG_QTY_DIGITS; i++) {
		seveg->digit_select[i].char_data = data[i];
	}
};

HAL_StatusTypeDef SEVSEG_DigitTx(SEVSEG_DISPLAY_TypeDef* sevseg, enum ENUM_SEVSEG_DIGIT digit) {

    HAL_StatusTypeDef success = HAL_SPI_Transmit(sevseg->spi_handler, &(sevseg->digit_select->char_data), 1, 1000); //send data through MOSI pin
	if (success != HAL_OK) return success; //if error, return error code
    
    HAL_GPIO_WritePin(SPI_LATCH_GPIO_Port, SPI_LATCH_Pin, GPIO_PIN_SET); //pulse latch on wanted chip
	HAL_GPIO_WritePin(SPI_LATCH_GPIO_Port, SPI_LATCH_Pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(sevseg->digit_select[digit].DS_port, sevseg->digit_select[digit].DS_pin, GPIO_PIN_SET);
	HAL_Delay(5); // 5ms delay to see the digit
    HAL_GPIO_WritePin(sevseg->digit_select[digit].DS_port, sevseg->digit_select[digit].DS_pin, GPIO_PIN_RESET);
	return success;
};

//FIRST DEMO IMPLREMENTATION: NO 'PLAY' MODE, JUST WRITE 5 CHAR TO 5 DIGIT DISPLAY
HAL_StatusTypeDef SEVSEG_Write(SEVSEG_DISPLAY_TypeDef* sevseg) {
	HAL_StatusTypeDef success;
	for (int i=0; i < SEVSEG_QTY_DIGITS; i++) {
		success = SEVSEG_DigitTx(sevseg, i);
		if (success != HAL_OK) return success;
	}
	return success;
};

// Array of all ENUM_SEVSEG_CHAR values
const enum ENUM_SEVSEG_CHAR SEVSEG_CHAR_ARRAY[] = {
    ENUM_SEVSEG_CHAR_0,
    ENUM_SEVSEG_CHAR_1,
    ENUM_SEVSEG_CHAR_2,
    ENUM_SEVSEG_CHAR_3,
    ENUM_SEVSEG_CHAR_4,
    ENUM_SEVSEG_CHAR_5,
    ENUM_SEVSEG_CHAR_6,
    ENUM_SEVSEG_CHAR_7,
    ENUM_SEVSEG_CHAR_8,
    ENUM_SEVSEG_CHAR_9,
    ENUM_SEVSEG_CHAR_A,
    ENUM_SEVSEG_CHAR_B,
    ENUM_SEVSEG_CHAR_C,
    ENUM_SEVSEG_CHAR_D,
    ENUM_SEVSEG_CHAR_E,
    ENUM_SEVSEG_CHAR_F,
    ENUM_SEVSEG_CHAR_h,
    ENUM_SEVSEG_CHAR_H,
    ENUM_SEVSEG_CHAR_L,
    ENUM_SEVSEG_CHAR_n,
    ENUM_SEVSEG_CHAR_o,
    ENUM_SEVSEG_CHAR_P,
    ENUM_SEVSEG_CHAR_r,
    ENUM_SEVSEG_CHAR_t,
    ENUM_SEVSEG_CHAR_U,
    ENUM_SEVSEG_CHAR_Y,
    ENUM_SEVSEG_CHAR_Dash,
    ENUM_SEVSEG_CHAR_Blank
    };

enum ENUM_SEVSEG_CHAR ASCIItoSEVSEG_CHAR_ENUM[255] = {0};
ASCIItoSEVSEG_CHAR_ENUM['0'] = ENUM_SEVSEG_CHAR_0;
ASCIItoSEVSEG_CHAR_ENUM['1'] = ENUM_SEVSEG_CHAR_1;
ASCIItoSEVSEG_CHAR_ENUM['2'] = ENUM_SEVSEG_CHAR_2;
ASCIItoSEVSEG_CHAR_ENUM['3'] = ENUM_SEVSEG_CHAR_3;
ASCIItoSEVSEG_CHAR_ENUM['4'] = ENUM_SEVSEG_CHAR_4;
ASCIItoSEVSEG_CHAR_ENUM['5'] = ENUM_SEVSEG_CHAR_5;
ASCIItoSEVSEG_CHAR_ENUM['6'] = ENUM_SEVSEG_CHAR_6;
ASCIItoSEVSEG_CHAR_ENUM['7'] = ENUM_SEVSEG_CHAR_7;
ASCIItoSEVSEG_CHAR_ENUM['8'] = ENUM_SEVSEG_CHAR_8;
ASCIItoSEVSEG_CHAR_ENUM['9'] = ENUM_SEVSEG_CHAR_9;
ASCIItoSEVSEG_CHAR_ENUM['A'] = ENUM_SEVSEG_CHAR_A;
ASCIItoSEVSEG_CHAR_ENUM['B'] = ENUM_SEVSEG_CHAR_B;
ASCIItoSEVSEG_CHAR_ENUM['C'] = ENUM_SEVSEG_CHAR_C;
ASCIItoSEVSEG_CHAR_ENUM['D'] = ENUM_SEVSEG_CHAR_D;
ASCIItoSEVSEG_CHAR_ENUM['E'] = ENUM_SEVSEG_CHAR_E;
ASCIItoSEVSEG_CHAR_ENUM['F'] = ENUM_SEVSEG_CHAR_F;
ASCIItoSEVSEG_CHAR_ENUM['h'] = ENUM_SEVSEG_CHAR_h;
ASCIItoSEVSEG_CHAR_ENUM['H'] = ENUM_SEVSEG_CHAR_H;
ASCIItoSEVSEG_CHAR_ENUM['L'] = ENUM_SEVSEG_CHAR_L;
ASCIItoSEVSEG_CHAR_ENUM['n'] = ENUM_SEVSEG_CHAR_n;
ASCIItoSEVSEG_CHAR_ENUM['o'] = ENUM_SEVSEG_CHAR_o;
ASCIItoSEVSEG_CHAR_ENUM['P'] = ENUM_SEVSEG_CHAR_P;
ASCIItoSEVSEG_CHAR_ENUM['r'] = ENUM_SEVSEG_CHAR_r;
ASCIItoSEVSEG_CHAR_ENUM['t'] = ENUM_SEVSEG_CHAR_t;
ASCIItoSEVSEG_CHAR_ENUM['U'] = ENUM_SEVSEG_CHAR_U;
ASCIItoSEVSEG_CHAR_ENUM['Y'] = ENUM_SEVSEG_CHAR_Y;
ASCIItoSEVSEG_CHAR_ENUM['-'] = ENUM_SEVSEG_CHAR_Dash;
ASCIItoSEVSEG_CHAR_ENUM[' '] = ENUM_SEVSEG_CHAR_Blank;

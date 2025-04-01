/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

SEVSEG_DISPLAY_TypeDef sevseg;
//volatile DEBOUNCE_Typedef button_debounce;
//enum ENUM_SEVSEG_DIGIT refresh_target; //used to cycle through array of digits
GPIO_PIN_TypeDef DIGIT_SEL_PINS_ARRAY[SEVSEG_QTY_DIGITS]; //containing gpio pins of all digits
//volatile CYCLE_STATE cycle_state;
//volatile uint8_t tim1up, tim2up;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
static void SEVSEG_Init();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef*);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

volatile enum ENUM_SEVSEG_CHAR data[SEVSEG_QTY_DIGITS] =
{ ENUM_SEVSEG_CHAR_H, ENUM_SEVSEG_CHAR_E, ENUM_SEVSEG_CHAR_L, ENUM_SEVSEG_CHAR_L, ENUM_SEVSEG_CHAR_o };


/*void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){ // SPI Transmission completed interrupt
	  if (hspi->Instance == SPI2){
		  HAL_TIM_Base_Start_IT(&htim1); // start latch pulse width timer ~500 ns 10 counts, 16 Mhz = 625 ns
		  HAL_GPIO_WritePin(SPI_LATCH_GPIO_Port, SPI_LATCH_Pin, GPIO_PIN_SET); // set latch
		  HAL_TIM_Base_Start_IT(&htim2); // start delay for refresh rate ~2ms per digit :) timer 2 is 50 kHz
	  }
  }
*/

volatile enum ENUM_SEVSEG_DIGIT cursor_selection = ENUM_SEVSEG_DIGIT_0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){

	if (htim->Instance == SPI_LATCH_Timer){ // ************** TIMER 1 ******************
		(sevseg.cycle_state) = CYCLE_STATE_3;
	if (htim->Instance == DIGIT_SEL_Timer){ // ************** TIMER 2 ******************
		tim2up = 1;
	}

	else {
	 sevseg.cycle_state = CYCLE_STATE_1;
	    if(sevseg.refresh_target == SEVSEG_QTY_DIGITS - 1){
	    			sevseg.refresh_target = ENUM_SEVSEG_DIGIT_0;
	    		} else sevseg.refresh_target++;

	    HAL_GPIO_WritePin(DIGIT_SEL_PINS_ARRAY[(sevseg.refresh_target)].port, DIGIT_SEL_PINS_ARRAY[(sevseg.refresh_target)].pin, GPIO_PIN_RESET);
	// ****************************************************************************  END
	else if (htim->Instance == SPI_LATCH_Timer){ // ************** TIMER 1 ******************
		tim1up = 1;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t pin){
    if (button_debounce == DEBOUNCE_FALSE){
    	return;
    }

	switch (pin) {
		case UI_COUNTUP_Pin:
			if(sevseg.digit_select[cursor_selection].current_char_index == INDEX_FROM_ENUM[ENUM_SEVSEG_CHAR_Blank]){
				sevseg.digit_select[cursor_selection].current_char_index = INDEX_FROM_ENUM[ENUM_SEVSEG_CHAR_0]; //return to beginning of array if at end
			}
			else
			sevseg.digit_select[cursor_selection].current_char_index++;
			break;
		case UI_COUNTDOWN_Pin:
			if(sevseg.digit_select[cursor_selection].current_char_index == INDEX_FROM_ENUM[ENUM_SEVSEG_CHAR_0]){
				sevseg.digit_select[cursor_selection].current_char_index = INDEX_FROM_ENUM[ENUM_SEVSEG_CHAR_Blank]; //return to beginning of array if at end
			}
			else
			sevseg.digit_select[cursor_selection].current_char_index--;
			break;
		case UI_CURSOR_Pin:
			if(cursor_selection == SEVSEG_QTY_DIGITS-1){
				cursor_selection = ENUM_SEVSEG_DIGIT_0;
			}
			else
			cursor_selection++;

			break;
	}

	//button_debounce = debounce_false
	//start debounce delay timer
	//config timer to set debounce = true again
	return;
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef* hspi){
	// PASSES LED TEST
	sevseg.cycle_state = CYCLE_STATE_2;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
switch (sevseg->cycle_state)

case CYCLE_STATE_0:
    break;
case CYCLE_STATE_1:
    SEVSEG_DigitTx(sevseg, sevseg->refresh_target);
    sevseg->cycle_state = CYCLE_STATE_0;
    break;
case CYCLE_STATE_2:
    HAL_TIM_Base_Start_IT(htim1);
    sevseg->cycle_state = CYCLE_STATE_0;
    break;
case CYCLE_STATE_3:
    break;
}

tim2up = 0; time1up = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  SEVSEG_Init();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
 
  uint8_t myDataa[5] = {ENUM_SEVSEG_CHAR_H, ENUM_SEVSEG_CHAR_E, ENUM_SEVSEG_CHAR_L, ENUM_SEVSEG_CHAR_L, ENUM_SEVSEG_CHAR_o};
  SEVSEG_StoreDataBuf(&sevseg, myDataa); //stores enum indexes (user-defined-pointers) into each DIGIT in sevseg.digits_select[DIGIT]

  // replace 2nd arg with refresh_target to start the refresh loop

  //SEVSEG_DigitTx(&sevseg, ENUM_SEVSEG_DIGIT_0); // for testing transmission of a single byte to a single digit, not be used in main or a design

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  SEVSEG_Cycle(&sevseg, &htim1, &htim2);
	SEVSEG_DigitTx(&sevseg);
	if (not(success)) continue;

	HAL_GPIO_WritePin(SPI_LATCH_GPIO_Port, SPI_LATCH_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(SPI_LATCH_GPIO_Port, SPI_LATCH_Pin, GPIO_PIN_RESET);

	SEVSEG_DIGIT_TypeDef* temp = (sevseg.digit_select[sevseg.refresh_target]);
	HAL_GPIO_WritePin(temp->port, temp->pin, GPIO_PIN_SET);
	HAL_Delay(1000);	
	HAL_GPIO_WritePin(temp->port, temp->pin, GPIO_PIN_RESET);
	
	sevseg.refresh_target += 1;
	
	  /* TIM2 UP
   		HAL_GPIO_WritePin(DIGIT_SEL_PINS_ARRAY[refresh_target].port, DIGIT_SEL_PINS_ARRAY[refresh_target].pin, GPIO_PIN_RESET );

		//return to first digit if refresh_target is at last digit
		if(refresh_target == SEVSEG_QTY_DIGITS - 1){
			refresh_target = ENUM_SEVSEG_DIGIT_0;
		} else refresh_target++;

		SEVSEG_DigitTx(&sevseg, refresh_target);

		TIM1 up
   		HAL_GPIO_WritePin(SPI_LATCH_GPIO_Port, SPI_LATCH_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(DIGIT_SEL_PINS_ARRAY[refresh_target].port, DIGIT_SEL_PINS_ARRAY[refresh_target].pin, GPIO_PIN_SET); //activate digit select pin: HIGH
		HAL_TIM_Base_Start_IT(&htim2);
   	  */
	  //HAL_SPI_Transmit(sevseg.spi_handler, myDataa, 1, 1000);
	  
	  

     //******INTEGRATED TEST*******
	 //HAL_GPIO_WritePin(SPI_RESET_GPIO_Port, SPI_RESET_Pin, GPIO_PIN_RESET);
	 //HAL_GPIO_WritePin(SPI_RESET_GPIO_Port, SPI_RESET_Pin, GPIO_PIN_SET);





    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV16;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 16-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OnePulse_Init(&htim1, TIM_OPMODE_SINGLE) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 16-1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 2-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 2000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SPI_RESET_Pin|DIGIT_SEL_2_Pin|DIGIT_SEL_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DIGIT_SEL_3_Pin|DIGIT_SEL_1_Pin|DIGIT_SEL_0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : UI_COUNTDOWN_Pin UI_COUNTUP_Pin UI_CURSOR_Pin */
  GPIO_InitStruct.Pin = UI_COUNTDOWN_Pin|UI_COUNTUP_Pin|UI_CURSOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI_RESET_Pin */
  GPIO_InitStruct.Pin = SPI_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI_RESET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DIGIT_SEL_3_Pin DIGIT_SEL_1_Pin DIGIT_SEL_0_Pin */
  GPIO_InitStruct.Pin = DIGIT_SEL_3_Pin|DIGIT_SEL_1_Pin|DIGIT_SEL_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DIGIT_SEL_2_Pin DIGIT_SEL_4_Pin */
  GPIO_InitStruct.Pin = DIGIT_SEL_2_Pin|DIGIT_SEL_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
static void SEVSEG_Init(){

	refresh_target = ENUM_SEVSEG_DIGIT_0;
	button_debounce = DEBOUNCE_TRUE;
	cycle_state = CYCLE_STATE_1;

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

	SEVSEG_DIGIT_TypeDef DIGIT_0 = {
			  .DS_pin = DIGIT_SEL_0_Pin,
			  .DS_port = DIGIT_SEL_0_GPIO_Port,
			  .current_char_index = 0
	};

	SEVSEG_DIGIT_TypeDef DIGIT_1 = {
			  .DS_pin = DIGIT_SEL_1_Pin,
			  .DS_port = DIGIT_SEL_1_GPIO_Port,
			  .current_char_index = 0
	};

	SEVSEG_DIGIT_TypeDef DIGIT_2 = {
			  .DS_pin = DIGIT_SEL_2_Pin,
			  .DS_port = DIGIT_SEL_2_GPIO_Port,
			  .current_char_index = 0
	};

	SEVSEG_DIGIT_TypeDef DIGIT_3 = {
			  .DS_pin = DIGIT_SEL_3_Pin,
			  .DS_port = DIGIT_SEL_3_GPIO_Port,
			  .current_char_index = 0
	};

	SEVSEG_DIGIT_TypeDef DIGIT_4 = {
			  .DS_pin = DIGIT_SEL_4_Pin,
			  .DS_port = DIGIT_SEL_4_GPIO_Port,
			  .current_char_index = 0
	};

	sevseg.spi_handler = &hspi2;
	sevseg.digit_select[0] = DIGIT_0;
	sevseg.digit_select[1] = DIGIT_1;
	sevseg.digit_select[2] = DIGIT_2;
	sevseg.digit_select[3] = DIGIT_3;
	sevseg.digit_select[4] = DIGIT_4;
	sevseg.cycle_state = cycle_state;
	sevseg.refresh_target = refresh_target;

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

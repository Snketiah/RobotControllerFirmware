/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    xspi.c
  * @brief   This file provides code for the configuration
  *          of the XSPI instances.
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
#include "xspi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

XSPI_HandleTypeDef hxspi1;
XSPI_HandleTypeDef hxspi2;

/* XSPI1 init function */
void MX_XSPI1_Init(void)
{

  /* USER CODE BEGIN XSPI1_Init 0 */

  /* USER CODE END XSPI1_Init 0 */

  XSPIM_CfgTypeDef sXspiManagerCfg = {0};

  /* USER CODE BEGIN XSPI1_Init 1 */

  /* USER CODE END XSPI1_Init 1 */
  hxspi1.Instance = XSPI1;
  hxspi1.Init.FifoThresholdByte = 4;
  hxspi1.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
  hxspi1.Init.MemoryType = HAL_XSPI_MEMTYPE_MICRON;
  hxspi1.Init.MemorySize = HAL_XSPI_SIZE_64MB;
  hxspi1.Init.ChipSelectHighTimeCycle = 3;
  hxspi1.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
  hxspi1.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
  hxspi1.Init.WrapSize = HAL_XSPI_WRAP_NOT_SUPPORTED;
  hxspi1.Init.ClockPrescaler = 3-1;
  hxspi1.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_HALFCYCLE;
  hxspi1.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_DISABLE;
  hxspi1.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;
  hxspi1.Init.MaxTran = 0;
  hxspi1.Init.Refresh = 0;
  hxspi1.Init.MemorySelect = HAL_XSPI_CSSEL_NCS1;
  if (HAL_XSPI_Init(&hxspi1) != HAL_OK)
  {
    Error_Handler();
  }
  sXspiManagerCfg.nCSOverride = HAL_XSPI_CSSEL_OVR_NCS1;
  sXspiManagerCfg.IOPort = HAL_XSPIM_IOPORT_1;
  if (HAL_XSPIM_Config(&hxspi1, &sXspiManagerCfg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN XSPI1_Init 2 */


  /* USER CODE END XSPI1_Init 2 */

}
/* XSPI2 init function */
void MX_XSPI2_Init(void)
{

  /* USER CODE BEGIN XSPI2_Init 0 */

  /* USER CODE END XSPI2_Init 0 */

  XSPIM_CfgTypeDef sXspiManagerCfg = {0};
  XSPI_HyperbusCfgTypeDef sHyperBusCfg = {0};

  /* USER CODE BEGIN XSPI2_Init 1 */

  /* USER CODE END XSPI2_Init 1 */
  hxspi2.Instance = XSPI2;
  hxspi2.Init.FifoThresholdByte = 4;
  hxspi2.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
  hxspi2.Init.MemoryType = HAL_XSPI_MEMTYPE_HYPERBUS;
  hxspi2.Init.MemorySize = HAL_XSPI_SIZE_64MB;
  hxspi2.Init.ChipSelectHighTimeCycle = 2;
  hxspi2.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
  hxspi2.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
  hxspi2.Init.WrapSize = HAL_XSPI_WRAP_128_BYTES;
  hxspi2.Init.ClockPrescaler = 8-1;
  hxspi2.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
  hxspi2.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_ENABLE;
  hxspi2.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;
  hxspi2.Init.MaxTran = 0;
  hxspi2.Init.Refresh = 200;
  hxspi2.Init.MemorySelect = HAL_XSPI_CSSEL_NCS2;
  if (HAL_XSPI_Init(&hxspi2) != HAL_OK)
  {
    Error_Handler();
  }
  sXspiManagerCfg.nCSOverride = HAL_XSPI_CSSEL_OVR_NCS1;
  sXspiManagerCfg.IOPort = HAL_XSPIM_IOPORT_2;
  if (HAL_XSPIM_Config(&hxspi2, &sXspiManagerCfg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  sHyperBusCfg.RWRecoveryTimeCycle = 2;
  sHyperBusCfg.AccessTimeCycle = 7;
  sHyperBusCfg.WriteZeroLatency = HAL_XSPI_NO_LATENCY_ON_WRITE;
  sHyperBusCfg.LatencyMode = HAL_XSPI_FIXED_LATENCY;
  if (HAL_XSPI_HyperbusCfg(&hxspi2, &sHyperBusCfg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN XSPI2_Init 2 */
	uint16_t rx;
	uint16_t tx;

	tx = (S27KS0642_NORMAL_OPERATION << 15) |
	   (S27KS0642_46_OHMS << 12) |
	   (S27KS0642_CR0_RESERVED << 8) |
	   (S27KS0642_7_CLOCK_LATENCY << 4) |
	   (S27KS0642_FIXED_LATENCY << 3) |
	   (S27KS0642_LEGACY_WRAPPED_BURST << 2) |
	   (S27KS0642_128_BYTES);

	XSPI_HyperbusCmdTypeDef cmd;

	uint8_t reg_data[2] = {0};
	reg_data[1] = tx >> 8;
	reg_data[0] = (uint8_t) tx;

	cmd.Address = S27KS0642_CR0*2;
	cmd.AddressSpace = HAL_XSPI_REGISTER_ADDRESS_SPACE;
	cmd.AddressWidth = HAL_XSPI_ADDRESS_32_BITS;
	cmd.DQSMode = HAL_XSPI_DQS_DISABLE;
	cmd.DataLength = 2;
	cmd.DataMode = HAL_XSPI_DATA_8_LINES;

	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	if (HAL_XSPI_Transmit(&hxspi2, reg_data, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	tx = (S27KS0642_CR1_RESERVED_HIGH << 8) |
	 (S27KS0642_CR1_RESERVED_BIT7 << 7) |
	 (S27KS0642_DIFFERENTIAL_CK << 6) |
	 (S27KS0642_NORMAL_OPERATION_CR1 << 5) |
	 (S27KS0642_FULL_ARRAY << 2) |
	 (S27KS0642_REFRESH_4US);

	reg_data[1] = tx >> 8;
	reg_data[0] = (uint8_t) tx;

	cmd.Address = S27KS0642_CR1*2;

	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	if (HAL_XSPI_Transmit(&hxspi2, reg_data, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}


	if (HAL_XSPI_DeInit(&hxspi2) != HAL_OK)
	{
		Error_Handler();
	}


	hxspi2.Instance = XSPI2;
	hxspi2.Init.FifoThresholdByte = 4;
	hxspi2.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
	hxspi2.Init.MemoryType = HAL_XSPI_MEMTYPE_HYPERBUS;
        /* The S27KS0642 device is a 64-Mbit HyperRAM (8 MB). Using the raw
         * enumeration value (29) was confusing and selected the 8-Gbit size.
         * Explicitly use the HAL constant for an 8-MByte memory. */
        hxspi2.Init.MemorySize = HAL_XSPI_SIZE_8MB;
	hxspi2.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
	hxspi2.Init.WrapSize = HAL_XSPI_WRAP_NOT_SUPPORTED;
	hxspi2.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
	hxspi2.Init.MemorySelect = HAL_XSPI_CSSEL_NCS2;
	hxspi2.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_ENABLE;
	hxspi2.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
	hxspi2.Init.MaxTran = 0;
	hxspi2.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;

	hxspi2.Init.ChipSelectHighTimeCycle = 2;	//CS High Time = 6ns
	hxspi2.Init.ClockPrescaler = 2-1;		//(180 MHz) Input Clock set to 180MHz
	hxspi2.Init.Refresh = 700;		//Chip Select maximum low time = 4us

	if (HAL_XSPI_Init(&hxspi2) != HAL_OK)
	{
		Error_Handler();
	}

	sHyperBusCfg.RWRecoveryTimeCycle = 7;	//(6.3 cycles at 180MHz) Read-write recovery time = 35ns
	sHyperBusCfg.AccessTimeCycle = 7;		//(6.3 cycles at 180MHz) Access time = 35ns
	sHyperBusCfg.WriteZeroLatency = HAL_XSPI_LATENCY_ON_WRITE;	//No Latency on write for register config
	sHyperBusCfg.LatencyMode = HAL_XSPI_FIXED_LATENCY;		//Latency Fixed for initial access
	if (HAL_XSPI_HyperbusCfg(&hxspi2, &sHyperBusCfg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
	Error_Handler();
	}


	cmd.AddressSpace = HAL_XSPI_REGISTER_ADDRESS_SPACE;
	cmd.AddressWidth = HAL_XSPI_ADDRESS_32_BITS;
	cmd.DQSMode = HAL_XSPI_DQS_ENABLE;
	cmd.DataLength = 2;
	cmd.DataMode = HAL_XSPI_DATA_8_LINES;

	uint8_t rx_data[2];

	cmd.Address = S27KS0642_CR0*2;

	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	if (HAL_XSPI_Receive(&hxspi2, rx_data, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}
	rx = rx_data[0] | rx_data[1] << 8;


	cmd.Address = S27KS0642_CR1*2;

	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	if (HAL_XSPI_Receive(&hxspi2, rx_data, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}
	rx = rx_data[0] | rx_data[1] << 8;



	cmd.Address = 0;
	cmd.AddressSpace = HAL_XSPI_MEMORY_ADDRESS_SPACE;
	cmd.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
	cmd.DQSMode = HAL_XSPI_DQS_ENABLE;
	cmd.DataLength = 10;
	cmd.DataMode = HAL_XSPI_DATA_8_LINES;

	uint8_t tx_array[10];
	for (uint8_t i = 0; i < 10; i++){
		tx_array[i] = i+100;
	}

	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	if (HAL_XSPI_Transmit(&hxspi2, tx_array, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	cmd.Address = 0;
	cmd.AddressSpace = HAL_XSPI_MEMORY_ADDRESS_SPACE;
	cmd.AddressWidth = HAL_XSPI_ADDRESS_32_BITS;
	cmd.DQSMode = HAL_XSPI_DQS_ENABLE;
	cmd.DataLength = 10;
	cmd.DataMode = HAL_XSPI_DATA_8_LINES;

	uint8_t rx_array[10];

	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	if (HAL_XSPI_Receive(&hxspi2, rx_array, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	//Enabling Memory mapped Mode

	XSPI_MemoryMappedTypeDef sMemMappedCfg;

	cmd.Address = 0;
	cmd.AddressSpace = HAL_XSPI_MEMORY_ADDRESS_SPACE;
	cmd.AddressWidth = HAL_XSPI_ADDRESS_32_BITS;
	cmd.DQSMode = HAL_XSPI_DQS_ENABLE;
	cmd.DataLength = 1;
	cmd.DataMode = HAL_XSPI_DATA_8_LINES;

	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		Error_Handler();
	}

	sMemMappedCfg.TimeOutActivation = HAL_XSPI_TIMEOUT_COUNTER_DISABLE;

	if (HAL_XSPI_MemoryMapped(&hxspi2, &sMemMappedCfg) != HAL_OK){
		Error_Handler();
	}




  /* USER CODE END XSPI2_Init 2 */

}

static uint32_t HAL_RCC_XSPIM_CLK_ENABLED=0;

void HAL_XSPI_MspInit(XSPI_HandleTypeDef* xspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(xspiHandle->Instance==XSPI1)
  {
  /* USER CODE BEGIN XSPI1_MspInit 0 */

  /* USER CODE END XSPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_XSPI1;
    PeriphClkInit.Xspi1ClockSelection = RCC_XSPI1CLKSOURCE_HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* XSPI1 clock enable */
    HAL_RCC_XSPIM_CLK_ENABLED++;
    if(HAL_RCC_XSPIM_CLK_ENABLED==1){
      __HAL_RCC_XSPIM_CLK_ENABLE();
    }
    __HAL_RCC_XSPI1_CLK_ENABLE();

    __HAL_RCC_GPIOP_CLK_ENABLE();
    __HAL_RCC_GPIOO_CLK_ENABLE();
    /**XSPI1 GPIO Configuration
    PP2     ------> XSPIM_P1_IO2
    PP3     ------> XSPIM_P1_IO3
    PO4     ------> XSPIM_P1_CLK
    PP0     ------> XSPIM_P1_IO0
    PP1     ------> XSPIM_P1_IO1
    PO0     ------> XSPIM_P1_NCS1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P1;
    HAL_GPIO_Init(GPIOP, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P1;
    HAL_GPIO_Init(GPIOO, &GPIO_InitStruct);

  /* USER CODE BEGIN XSPI1_MspInit 1 */

  /* USER CODE END XSPI1_MspInit 1 */
  }
  else if(xspiHandle->Instance==XSPI2)
  {
  /* USER CODE BEGIN XSPI2_MspInit 0 */

  /* USER CODE END XSPI2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_XSPI2;
    PeriphClkInit.Xspi2ClockSelection = RCC_XSPI2CLKSOURCE_PLL2T;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* XSPI2 clock enable */
    HAL_RCC_XSPIM_CLK_ENABLED++;
    if(HAL_RCC_XSPIM_CLK_ENABLED==1){
      __HAL_RCC_XSPIM_CLK_ENABLE();
    }
    __HAL_RCC_XSPI2_CLK_ENABLE();

    __HAL_RCC_GPION_CLK_ENABLE();
    /**XSPI2 GPIO Configuration
    PN8     ------> XSPIM_P2_IO4
    PN4     ------> XSPIM_P2_IO2
    PN5     ------> XSPIM_P2_IO3
    PN7     ------> XSPIM_P2_NCLK
    PN6     ------> XSPIM_P2_CLK
    PN9     ------> XSPIM_P2_IO5
    PN2     ------> XSPIM_P2_IO0
    PN10     ------> XSPIM_P2_IO6
    PN0     ------> XSPIM_P2_DQS0
    PN11     ------> XSPIM_P2_IO7
    PN3     ------> XSPIM_P2_IO1
    PN1     ------> XSPIM_P2_NCS1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7
                          |GPIO_PIN_6|GPIO_PIN_9|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_0|GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_XSPIM_P2;
    HAL_GPIO_Init(GPION, &GPIO_InitStruct);

  /* USER CODE BEGIN XSPI2_MspInit 1 */

  /* USER CODE END XSPI2_MspInit 1 */
  }
}

void HAL_XSPI_MspDeInit(XSPI_HandleTypeDef* xspiHandle)
{

  if(xspiHandle->Instance==XSPI1)
  {
  /* USER CODE BEGIN XSPI1_MspDeInit 0 */

  /* USER CODE END XSPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_XSPIM_CLK_ENABLED--;
    if(HAL_RCC_XSPIM_CLK_ENABLED==0){
      __HAL_RCC_XSPIM_CLK_DISABLE();
    }
    __HAL_RCC_XSPI1_CLK_DISABLE();

    /**XSPI1 GPIO Configuration
    PP2     ------> XSPIM_P1_IO2
    PP3     ------> XSPIM_P1_IO3
    PO4     ------> XSPIM_P1_CLK
    PP0     ------> XSPIM_P1_IO0
    PP1     ------> XSPIM_P1_IO1
    PO0     ------> XSPIM_P1_NCS1
    */
    HAL_GPIO_DeInit(GPIOP, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_0|GPIO_PIN_1);

    HAL_GPIO_DeInit(GPIOO, GPIO_PIN_4|GPIO_PIN_0);

  /* USER CODE BEGIN XSPI1_MspDeInit 1 */

  /* USER CODE END XSPI1_MspDeInit 1 */
  }
  else if(xspiHandle->Instance==XSPI2)
  {
  /* USER CODE BEGIN XSPI2_MspDeInit 0 */

  /* USER CODE END XSPI2_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_XSPIM_CLK_ENABLED--;
    if(HAL_RCC_XSPIM_CLK_ENABLED==0){
      __HAL_RCC_XSPIM_CLK_DISABLE();
    }
    __HAL_RCC_XSPI2_CLK_DISABLE();

    /**XSPI2 GPIO Configuration
    PN8     ------> XSPIM_P2_IO4
    PN4     ------> XSPIM_P2_IO2
    PN5     ------> XSPIM_P2_IO3
    PN7     ------> XSPIM_P2_NCLK
    PN6     ------> XSPIM_P2_CLK
    PN9     ------> XSPIM_P2_IO5
    PN2     ------> XSPIM_P2_IO0
    PN10     ------> XSPIM_P2_IO6
    PN0     ------> XSPIM_P2_DQS0
    PN11     ------> XSPIM_P2_IO7
    PN3     ------> XSPIM_P2_IO1
    PN1     ------> XSPIM_P2_NCS1
    */
    HAL_GPIO_DeInit(GPION, GPIO_PIN_8|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7
                          |GPIO_PIN_6|GPIO_PIN_9|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_0|GPIO_PIN_11|GPIO_PIN_3|GPIO_PIN_1);

  /* USER CODE BEGIN XSPI2_MspDeInit 1 */
  __HAL_RCC_XSPI2_FORCE_RESET();
  __HAL_RCC_XSPI2_RELEASE_RESET();

  /* USER CODE END XSPI2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void S27KS0642_XSPI_init(void){




}

/* USER CODE END 1 */

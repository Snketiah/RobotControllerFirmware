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
#include "extmem_manager.h"
#include "memorymap.h"
#include "sbs.h"
#include "xspi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "S27KS0642.h"
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

/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SBS_Init();
  MX_XSPI1_Init();
  MX_XSPI2_Init();
  MX_EXTMEM_MANAGER_Init();
  /* USER CODE BEGIN 2 */
//  S27KS0642 hyperram_controller;
//  hyperram_controller.xspi_hnd = &hxspi2;

	//Read ID register
//	XSPI_HyperbusCmdTypeDef cmd;
//	uint8_t rx_data[2] = {0XFF, 0XFF};
//	uint8_t tx_data[2] = {0b10111111, 0b11110100};
//	uint16_t* rx;
//	uint16_t tx;
//
//	cmd.Address = S27KS0642_CR0*2;
//	cmd.AddressSpace = HAL_XSPI_REGISTER_ADDRESS_SPACE;
//	cmd.AddressWidth = HAL_XSPI_ADDRESS_32_BITS;
//	cmd.DQSMode = HAL_XSPI_DQS_DISABLE;
//	cmd.DataLength = 2;
//	cmd.DataMode = HAL_XSPI_DATA_8_LINES;
//
//	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
//	Error_Handler();
//	}
//
//	if (HAL_XSPI_Transmit(&hxspi2, tx_data, HAL_MAX_DELAY) != HAL_OK){
//	Error_Handler();
//	}
//
//
//	cmd.Address = S27KS0642_ID0*2;
//	cmd.AddressSpace = HAL_XSPI_REGISTER_ADDRESS_SPACE;
//	cmd.AddressWidth = HAL_XSPI_ADDRESS_32_BITS;
//	cmd.DQSMode = HAL_XSPI_DQS_ENABLE;
//	cmd.DataLength = 2;
//	cmd.DataMode = HAL_XSPI_DATA_8_LINES;
//
//	if (HAL_XSPI_HyperbusCmd(&hxspi2, &cmd, HAL_MAX_DELAY) != HAL_OK){
//	Error_Handler();
//	}
//
//	if (HAL_XSPI_Receive(&hxspi2, rx_data, HAL_MAX_DELAY) != HAL_OK){
//	Error_Handler();
//	}
//	S27KS0642_register_read(&hyperram_controller, S27KS0642_ID0*2, rx);
//
//	tx = (S27KS0642_NORMAL_OPERATION << 15) |
//	     (S27KS0642_46_OHMS << 12) |
//	     (S27KS0642_CR0_RESERVED << 8) |
//	     (S27KS0642_7_CLOCK_LATENCY << 4) |
//	     (S27KS0642_FIXED_LATENCY << 3) |
//	     (S27KS0642_LEGACY_WRAPPED_BURST << 2) |
//	     (S27KS0642_128_BYTES);
//
//	S27KS0642_register_write(&hyperram_controller, S27KS0642_CR0*2, tx);
//
//	S27KS0642_register_read(&hyperram_controller, S27KS0642_CR0*2, rx);
//
//	tx = (S27KS0642_CR1_RESERVED_HIGH << 8) |
//	     (S27KS0642_CR1_RESERVED_BIT7 << 7) |
//	     (S27KS0642_DIFFERENTIAL_CK << 6) |
//	     (S27KS0642_NORMAL_OPERATION_CR1 << 5) |
//	     (S27KS0642_FULL_ARRAY << 2) |
//	     (S27KS0642_REFRESH_4US);
//
//	S27KS0642_register_write(&hyperram_controller, S27KS0642_CR1*2, tx);
//
//	S27KS0642_register_read(&hyperram_controller, S27KS0642_CR1*2, rx);
//
//	  if (HAL_XSPI_DeInit(&hxspi2) != HAL_OK)
//	  	{
//	  	Error_Handler();
//	  	}
//
//
//		XSPI_HyperbusCfgTypeDef sHyperBusCfg = {0};
//
//		hxspi2.Instance = XSPI2;
//		hxspi2.Init.FifoThresholdByte = 4;
//		hxspi2.Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
//		hxspi2.Init.MemoryType = HAL_XSPI_MEMTYPE_HYPERBUS;
//		hxspi2.Init.MemorySize = HAL_XSPI_SIZE_8MB;
//		hxspi2.Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
//		hxspi2.Init.WrapSize = HAL_XSPI_WRAP_128_BYTES;
//		hxspi2.Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
//		hxspi2.Init.MemorySelect = HAL_XSPI_CSSEL_NCS2;
//		hxspi2.Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_ENABLE;
//		hxspi2.Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
//		hxspi2.Init.MaxTran = 0;
//		hxspi2.Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;
//
//		hxspi2.Init.ChipSelectHighTimeCycle = 2;	//CS High Time = 6ns
//		hxspi2.Init.ClockPrescaler = 1-1;		//(100MHz) Input Clock set to 400MHz
//		hxspi2.Init.Refresh = 700;		//Chip Select maximum low time = 4us
//
//		if (HAL_XSPI_Init(&hxspi2) != HAL_OK)
//		{
//		Error_Handler();
//		}
//
//		sHyperBusCfg.RWRecoveryTimeCycle = 7;	//(3.5 cycles at 100MHz) Read-write recovery time = 35ns
//		sHyperBusCfg.AccessTimeCycle = 7;		//(3.5 cycles at 100MHz) Access time = 35ns
//		sHyperBusCfg.WriteZeroLatency = HAL_XSPI_NO_LATENCY_ON_WRITE;	//No Latency on write for register config
//		sHyperBusCfg.LatencyMode = HAL_XSPI_FIXED_LATENCY;		//Latency Fixed for initial access
//		if (HAL_XSPI_HyperbusCfg(&hxspi2, &sHyperBusCfg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//		{
//		Error_Handler();
//		}
//
//		S27KS0642_register_read(&hyperram_controller, S27KS0642_CR0*2, rx);
//
//
//		S27KS0642_register_read(&hyperram_controller, S27KS0642_CR1*2, rx);
//
//
//		S27KS0642_register_read(&hyperram_controller, S27KS0642_ID1*2, rx);

//	SSROBOT_Status stat;
//	S27KS0642_init(&hyperram_controller);

//	S27KS0642_XSPI_init();








  /* USER CODE END 2 */

  /* Launch the application */
  if (BOOT_OK != BOOT_Application())
  {
    Error_Handler();
  }
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL1.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL1.PLLM = 1;
  RCC_OscInitStruct.PLL1.PLLN = 60;
  RCC_OscInitStruct.PLL1.PLLP = 1;
  RCC_OscInitStruct.PLL1.PLLQ = 2;
  RCC_OscInitStruct.PLL1.PLLR = 2;
  RCC_OscInitStruct.PLL1.PLLS = 2;
  RCC_OscInitStruct.PLL1.PLLT = 2;
  RCC_OscInitStruct.PLL1.PLLFractional = 0;
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL2.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL2.PLLM = 1;
  RCC_OscInitStruct.PLL2.PLLN = 60;
  RCC_OscInitStruct.PLL2.PLLP = 2;
  RCC_OscInitStruct.PLL2.PLLQ = 2;
  RCC_OscInitStruct.PLL2.PLLR = 2;
  RCC_OscInitStruct.PLL2.PLLS = 2;
  RCC_OscInitStruct.PLL2.PLLT = 2;
  RCC_OscInitStruct.PLL2.PLLFractional = 0;
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL3.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL3.PLLM = 1;
  RCC_OscInitStruct.PLL3.PLLN = 40;
  RCC_OscInitStruct.PLL3.PLLP = 2;
  RCC_OscInitStruct.PLL3.PLLQ = 2;
  RCC_OscInitStruct.PLL3.PLLR = 16;
  RCC_OscInitStruct.PLL3.PLLS = 2;
  RCC_OscInitStruct.PLL3.PLLT = 2;
  RCC_OscInitStruct.PLL3.PLLFractional = 0;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK4|RCC_CLOCKTYPE_PCLK5;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
  RCC_ClkInitStruct.APB5CLKDivider = RCC_APB5_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /* Disables all MPU regions */
  for(uint8_t i=0; i<__MPU_REGIONCOUNT; i++)
  {
    HAL_MPU_DisableRegion(i);
  }

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.BaseAddress = 0x08000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.BaseAddress = 0x70000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER3;
  MPU_InitStruct.Size = MPU_REGION_SIZE_8MB;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER4;
  MPU_InitStruct.BaseAddress = 0x90000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_256MB;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Number = MPU_REGION_NUMBER5;
  MPU_InitStruct.Size = MPU_REGION_SIZE_8MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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

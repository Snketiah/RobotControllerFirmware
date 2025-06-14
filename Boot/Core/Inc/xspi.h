/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    xspi.h
  * @brief   This file contains all the function prototypes for
  *          the xspi.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __XSPI_H__
#define __XSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "S27KS0642.h"
/* USER CODE END Includes */

extern XSPI_HandleTypeDef hxspi1;

extern XSPI_HandleTypeDef hxspi2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_XSPI1_Init(void);
void MX_XSPI2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __XSPI_H__ */


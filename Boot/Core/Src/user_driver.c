/**
  ******************************************************************************
  * @file    stm32_user_driver.c
  * @author  MCD Application Team
  * @brief   This file includes a driver for user support
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32_extmem.h"
#include "stm32_extmem_conf.h"
#if EXTMEM_DRIVER_USER == 1
#include "user_driver_api.h"
#include "stm32_user_driver_type.h"
#include "xspi.h"
/** @defgroup USER USER driver
  * @ingroup EXTMEM_DRIVER
  * @{
  */

/* Private Macro ------------------------------------------------------------*/
/** @defgroup USER_Private_Macro Private Macro
  * @{
  */
#define SST26VF064B_PAGE_SIZE		0x100


#define SST26VF064B_TIMEOUT 1000
#define SST26VF064B_WIP 0x81
#define SST26VF064B_WEL 0x02


/* ---------Device Commands-------------*/

/* ---------Configuration-------------*/
#define SST26VF064B_NOP 			0x00
#define SST26VF064B_RSTEN 			0x66
#define SST26VF064B_RST 			0x99
#define SST26VF064B_EQIO 			0x38
#define SST26VF064B_RSTQIO 			0xFF
#define SST26VF064B_RDSR 			0x05
#define SST26VF064B_WRSR 			0x01
#define SST26VF064B_RDCR 			0x35

/* --------- Read -------------*/
#define SST26VF064B_READ 			0x03
#define SST26VF064B_HIGH_SPEED_READ 0x0B
#define SST26VF064B_SQOR			0x6B
#define SST26VF064B_SQIOR			0xEB
#define SST26VF064B_SDOR			0x3B
#define SST26VF064B_SDIOR			0XBB
#define SST26VF064B_SB				0xC0
#define SST26VF064B_RBSQI			0x0C
#define SST26VF064B_RBSPI			0xEC

/* --------- Write -------------*/
#define SST26VF064B_WREN			0x06
#define SST26VF064B_WRDI			0x04
#define SST26VF064B_SE				0x20
#define SST26VF064B_BE				0xD8
#define SST26VF064B_CE				0xC7
#define SST26VF064B_PP				0x02
#define SST26VF064B_SPI_QUAD_PP		0x32
#define SST26VF064B_WRSU			0xB0
#define SST26VF064B_WRRE			0x30

/* --------- Memory Protection -------------*/
#define SST26VF064B_ULBPR			0x98
#define SST26VF064B_RBPR			0x72

/* --------- J-ID -------------*/
#define SST26VF064B_JID_READ		0xAF
/**
  * @}
  */
/* Private typedefs ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup USER_Exported_Functions Exported Functions
  * @{
  */

EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Init(uint32_t MemoryId,
                                                         EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
	HAL_GPIO_WritePin(GPIOP, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOP, GPIO_PIN_3, GPIO_PIN_SET);

	HAL_Delay(1);

	if ( SST26VF064B_Reset() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	HAL_Delay(1);
	if ( SST26VF064B_Reset_QIO() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	HAL_GPIO_WritePin(GPIOP, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOP, GPIO_PIN_3, GPIO_PIN_SET);

	HAL_Delay(1);

	if ( SST26VF064B_Enable_QIO() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	if ( SST26VF064B_Global_Block_Protecion_Unlock() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
  return EXTMEM_DRIVER_USER_OK;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_DeInit(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)UserObject;
  return retr;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Read(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject,
                                                         uint32_t Address, uint8_t* Data, uint32_t Size)
{
	 XSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_HIGH_SPEED_READ;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Address = Address;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_4_LINES;
	sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
	sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DummyCycles = 6;
	sCommand.DataMode = HAL_XSPI_DATA_4_LINES;
	sCommand.DataLength = Size;
	sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	if (HAL_XSPI_Receive(&hxspi1,Data, SST26VF064B_TIMEOUT) != HAL_OK ){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Write(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject, uint32_t Address, uint8_t* Data, uint32_t Size)
{
	 if (SST26VF064B_Write(Data, Address, Size) != EXTMEM_DRIVER_USER_OK){
		 return EXTMEM_DRIVER_USER_ERROR_1;
	 }

	return EXTMEM_DRIVER_USER_OK;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_EraseSector(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject,
                                                                uint32_t Address, uint32_t Size)
{

	if (SST26VF064B_Write_EN() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	XSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_SE;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Address = Address;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_4_LINES;
	sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
	sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	if (SST26VF064B_AutoPollingMemReady() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_MassErase(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{

	if (SST26VF064B_Write_EN() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	XSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_CE;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	if (SST26VF064B_AutoPollingMemReady() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Enable_MemoryMappedMode(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
	XSPI_RegularCmdTypeDef sCommand;
	XSPI_MemoryMappedTypeDef sMemMappedCfg;

	sCommand.OperationType = HAL_XSPI_OPTYPE_READ_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_SQIOR;
	sCommand.Instruction = SST26VF064B_HIGH_SPEED_READ;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Address = 0;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_4_LINES;
	sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
	sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DummyCycles = 6;
	sCommand.DataMode = HAL_XSPI_DATA_4_LINES;
	sCommand.DataLength = 0;
	sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;


	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	sCommand.OperationType = HAL_XSPI_OPTYPE_WRITE_CFG;
	sCommand.Instruction = SST26VF064B_PP;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	sMemMappedCfg.TimeOutActivation = HAL_XSPI_TIMEOUT_COUNTER_DISABLE;

	if(HAL_XSPI_MemoryMapped(&hxspi1, &sMemMappedCfg) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_Disable_MemoryMappedMode(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject)
{
	if (HAL_XSPI_Abort(&hxspi1) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	return EXTMEM_DRIVER_USER_OK;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_GetMapAddress(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject, uint32_t* BaseAddress)
{
  *BaseAddress = 0x90000000;
  return EXTMEM_DRIVER_USER_OK;
}

 EXTMEM_DRIVER_USER_StatusTypeDef EXTMEM_DRIVER_USER_GetInfo(EXTMEM_DRIVER_USER_ObjectTypeDef* UserObject, EXTMEM_USER_MemInfoTypeDef* MemInfo)
{
  EXTMEM_DRIVER_USER_StatusTypeDef retr = EXTMEM_DRIVER_USER_NOTSUPPORTED;
  (void)*UserObject;
  (void)MemInfo;
  return retr;
}

/**
  * @}
  */

/** @addtogroup USER_Private_Functions
  * @{
  */

 EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_Reset()
{
	XSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_RSTEN;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_NONE;
	sCommand.DataLength = 0;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	sCommand.Instruction = SST26VF064B_RST;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;
}




EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_Enable_QIO()
{

	XSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_EQIO;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_NONE;
	sCommand.DataLength = 0;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	return EXTMEM_DRIVER_USER_OK;

}


EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_Reset_QIO()
{
	XSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_RSTQIO;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_1_LINE;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_NONE;
	sCommand.DataLength = 0;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	return EXTMEM_DRIVER_USER_OK;

}


EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_Write_EN(){

	XSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_WREN;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_NONE;
	sCommand.DataLength = 0;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	if (SST26VF064B_AutoPollingWriteEnableLatch() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	return EXTMEM_DRIVER_USER_OK;
}



EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_Global_Block_Protecion_Unlock(){
	if (SST26VF064B_Write_EN() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	XSPI_RegularCmdTypeDef sCommand;

	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_ULBPR;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_NONE;
	sCommand.DataLength = 0;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	if (SST26VF064B_AutoPollingMemReady() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;
}



EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_Page_Write(uint8_t* tx,  uint32_t address, uint32_t Datalength){
	if (SST26VF064B_Write_EN() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	XSPI_RegularCmdTypeDef sCommand;
	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_PP;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.Address = address;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_4_LINES;
	sCommand.AddressWidth = HAL_XSPI_ADDRESS_24_BITS;
	sCommand.AddressDTRMode = HAL_XSPI_ADDRESS_DTR_DISABLE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_4_LINES;
	sCommand.DataLength = Datalength;
	sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
	sCommand.DummyCycles = 0;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	if (HAL_XSPI_Transmit(&hxspi1, tx, HAL_MAX_DELAY) != HAL_OK ){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}
	if (SST26VF064B_AutoPollingMemReady() != EXTMEM_DRIVER_USER_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;


}



EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_AutoPollingMemReady()
{
	XSPI_RegularCmdTypeDef sCommand;
	XSPI_AutoPollingTypeDef autoPolling;

	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_RDSR;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_4_LINES;
	sCommand.DataLength = 1;
	sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
	sCommand.DummyCycles = 2;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;

	autoPolling.MatchValue = 0x00;
	autoPolling.MatchMask = SST26VF064B_WIP;
	autoPolling.MatchMode = HAL_XSPI_MATCH_MODE_AND;
	autoPolling.AutomaticStop = HAL_XSPI_AUTOMATIC_STOP_ENABLE;
	autoPolling.IntervalTime = 0x10;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	if (HAL_XSPI_AutoPolling(&hxspi1, &autoPolling, SST26VF064B_TIMEOUT)){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;
}

EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_AutoPollingWriteEnableLatch()
{
	XSPI_RegularCmdTypeDef sCommand;
	XSPI_AutoPollingTypeDef autoPolling;

	sCommand.OperationType = HAL_XSPI_OPTYPE_COMMON_CFG;
	sCommand.IOSelect = HAL_XSPI_SELECT_IO_3_0;
	sCommand.Instruction = SST26VF064B_RDSR;
	sCommand.InstructionMode = HAL_XSPI_INSTRUCTION_4_LINES;
	sCommand.InstructionWidth = HAL_XSPI_INSTRUCTION_8_BITS;
	sCommand.InstructionDTRMode = HAL_XSPI_INSTRUCTION_DTR_DISABLE;
	sCommand.AddressMode = HAL_XSPI_ADDRESS_NONE;
	sCommand.AlternateBytesMode = HAL_XSPI_ALT_BYTES_NONE;
	sCommand.DataMode = HAL_XSPI_DATA_4_LINES;
	sCommand.DataLength = 1;
	sCommand.DataDTRMode = HAL_XSPI_DATA_DTR_DISABLE;
	sCommand.DummyCycles = 2;
	sCommand.DQSMode = HAL_XSPI_DQS_DISABLE;


	autoPolling.MatchValue = SST26VF064B_WEL;
	autoPolling.MatchMask = SST26VF064B_WEL;
	autoPolling.MatchMode = HAL_XSPI_MATCH_MODE_OR;
	autoPolling.AutomaticStop = HAL_XSPI_AUTOMATIC_STOP_ENABLE;
	autoPolling.IntervalTime = 0x10;

	if (HAL_XSPI_Command(&hxspi1, &sCommand, SST26VF064B_TIMEOUT) != HAL_OK){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	if (HAL_XSPI_AutoPolling(&hxspi1, &autoPolling, SST26VF064B_TIMEOUT)){
		return EXTMEM_DRIVER_USER_ERROR_1;
	}

	return EXTMEM_DRIVER_USER_OK;
}


EXTMEM_DRIVER_USER_StatusTypeDef SST26VF064B_Write(uint8_t* tx,  uint32_t address, uint32_t Datalength)
{
	uint32_t end_address = address + Datalength;
	uint32_t current_buff_size = SST26VF064B_PAGE_SIZE - (address % SST26VF064B_PAGE_SIZE);

	if (current_buff_size > Datalength){
	        current_buff_size = Datalength;
	    }


	do {
		if (SST26VF064B_Page_Write(tx, address, current_buff_size) != EXTMEM_DRIVER_USER_OK){
			return EXTMEM_DRIVER_USER_ERROR_1;
		}


		tx += current_buff_size;
		address += current_buff_size;

		current_buff_size = (end_address - address < SST26VF064B_PAGE_SIZE)? (end_address - address) : SST26VF064B_PAGE_SIZE;
	}
	while (address < end_address);

	return EXTMEM_DRIVER_USER_OK;


}

/**
  * @}
  */

/**
  * @}
  */
#endif /* EXTMEM_DRIVER_USER == 1 */

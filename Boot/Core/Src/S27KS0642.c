/*
 * S27KS0642.c
 *
 *  Created on: Apr 21, 2025
 *      Author: stevenketiah
 */


#include "S27KS0642.h"

extern XSPI_HandleTypeDef hxspi2;

SSROBOT_Status S27KS0642_init(S27KS0642 *hnd){

	// Configuring CRO and CR1 registers.

	uint16_t cr0_tx;
	uint16_t cr1_tx;
	uint16_t* cr0_rx;
	uint16_t* cr1_rx;

	cr0_tx = (S27KS0642_NORMAL_OPERATION << 15) |
			 (S27KS0642_46_OHMS << 12) |
			 (S27KS0642_CR0_RESERVED << 8) |
			 (S27KS0642_7_CLOCK_LATENCY << 4) |
			 (S27KS0642_FIXED_LATENCY << 3) |
			 (S27KS0642_LEGACY_WRAPPED_BURST << 2) |
		 (S27KS0642_128_BYTES);

	if (S27KS0642_register_write(hnd, S27KS0642_CR0*2, cr0_tx) != SSROBOT_OK){
		return SSROBOT_ERROR;
	}


	cr1_tx = (S27KS0642_CR1_RESERVED_HIGH << 8) |
		     (S27KS0642_CR1_RESERVED_BIT7 << 7) |
		     (S27KS0642_DIFFERENTIAL_CK << 6) |
		     (S27KS0642_NORMAL_OPERATION_CR1 << 5) |
		     (S27KS0642_FULL_ARRAY << 2) |
		     (S27KS0642_REFRESH_4US);

	if (S27KS0642_register_write(hnd, S27KS0642_CR1*2, cr1_tx) != SSROBOT_OK){
		return SSROBOT_ERROR;
	}

//	S27KS0642_XSPI_init();

//	if (HAL_XSPI_DeInit(&hxspi2) != HAL_OK)
//	{
//		return SSROBOT_ERROR;
//	}
//
//
//	XSPI_HyperbusCfgTypeDef sHyperBusCfg = {0};
//
//	hnd->xspi_hnd->Instance = XSPI2;
//	hnd->xspi_hnd->Init.FifoThresholdByte = 4;
//	hnd->xspi_hnd->Init.MemoryMode = HAL_XSPI_SINGLE_MEM;
//	hnd->xspi_hnd->Init.MemoryType = HAL_XSPI_MEMTYPE_HYPERBUS;
//	hnd->xspi_hnd->Init.MemorySize = HAL_XSPI_SIZE_8MB;
//	hnd->xspi_hnd->Init.FreeRunningClock = HAL_XSPI_FREERUNCLK_DISABLE;
//	hnd->xspi_hnd->Init.WrapSize = HAL_XSPI_WRAP_128_BYTES;
//	hnd->xspi_hnd->Init.SampleShifting = HAL_XSPI_SAMPLE_SHIFT_NONE;
//	hnd->xspi_hnd->Init.MemorySelect = HAL_XSPI_CSSEL_NCS2;
//	hnd->xspi_hnd->Init.DelayHoldQuarterCycle = HAL_XSPI_DHQC_ENABLE;
//	hnd->xspi_hnd->Init.ClockMode = HAL_XSPI_CLOCK_MODE_0;
//	hnd->xspi_hnd->Init.MaxTran = 0;
//	hnd->xspi_hnd->Init.ChipSelectBoundary = HAL_XSPI_BONDARYOF_NONE;
//
//	hnd->xspi_hnd->Init.ChipSelectHighTimeCycle = 2;	//CS High Time = 6ns
//	hnd->xspi_hnd->Init.ClockPrescaler = 1-1;		//(180 MHz) Input Clock set to 180MHz
//	hnd->xspi_hnd->Init.Refresh = 720;		//Chip Select maximum low time = 4us
//
//	if (HAL_XSPI_Init(hnd->xspi_hnd) != HAL_OK)
//	{
//		return SSROBOT_ERROR;
//	}
//
//	sHyperBusCfg.RWRecoveryTimeCycle = 7;	//(6.3 cycles at 180MHz) Read-write recovery time = 35ns
//	sHyperBusCfg.AccessTimeCycle = 7;		//(6.3 cycles at 180MHz) Access time = 35ns
//	sHyperBusCfg.WriteZeroLatency = HAL_XSPI_NO_LATENCY_ON_WRITE;	//No Latency on write for register config
//	sHyperBusCfg.LatencyMode = HAL_XSPI_FIXED_LATENCY;		//Latency Fixed for initial access
//	if (HAL_XSPI_HyperbusCfg(&hxspi2, &sHyperBusCfg, HAL_XSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//	{
//		return SSROBOT_ERROR;
//	}

//
//	if (S27KS0642_register_read(hnd, S27KS0642_CR1*2, cr1_rx) != SSROBOT_OK){
//		return SSROBOT_ERROR;
//	}
//
////	if (cr0_tx != *rx){
////		return SSROBOT_ERROR;
////	}
//
//	if (S27KS0642_register_read(hnd, S27KS0642_CR0*2, cr0_rx) != SSROBOT_OK){
//		return SSROBOT_ERROR;
//	}
//
//	if (cr1_tx != *cr1_rx){
//		return SSROBOT_ERROR;
//	}


	return SSROBOT_OK;

}


SSROBOT_Status S27KS0642_register_read(XSPI_HandleTypeDef *xspi_hnd, uint32_t address, uint16_t* data){
	XSPI_HyperbusCmdTypeDef cmd;
	 uint8_t rx_data[2];

	cmd.Address = address;
	cmd.AddressSpace = HAL_XSPI_REGISTER_ADDRESS_SPACE;
	cmd.AddressWidth = HAL_XSPI_ADDRESS_32_BITS;
	cmd.DQSMode = HAL_XSPI_DQS_ENABLE;
	cmd.DataLength = 2;
	cmd.DataMode = HAL_XSPI_DATA_8_LINES;

	if (HAL_XSPI_HyperbusCmd(xspi_hnd, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		return SSROBOT_ERROR;
	}

	if (HAL_XSPI_Receive(xspi_hnd, rx_data, S27KS0642_TIMEOUT) != HAL_OK){
		return SSROBOT_ERROR;
	}
	*data = rx_data[0] | rx_data[1] << 8;

	return SSROBOT_OK;
}

SSROBOT_Status S27KS0642_register_write(XSPI_HandleTypeDef *xspi_hnd, uint32_t address, uint16_t data){
	XSPI_HyperbusCmdTypeDef cmd;

	uint8_t reg_data[2] = {0};
	reg_data[1] = data >> 8;
	reg_data[0] = (uint8_t) data;

	cmd.Address = address;
	cmd.AddressSpace = HAL_XSPI_REGISTER_ADDRESS_SPACE;
	cmd.AddressWidth = HAL_XSPI_ADDRESS_32_BITS;
	cmd.DQSMode = HAL_XSPI_DQS_DISABLE;
	cmd.DataLength = 2;
	cmd.DataMode = HAL_XSPI_DATA_8_LINES;

	if (HAL_XSPI_HyperbusCmd(xspi_hnd, &cmd, S27KS0642_TIMEOUT) != HAL_OK){
		return SSROBOT_ERROR;
	}

	if (HAL_XSPI_Transmit(xspi_hnd, reg_data, S27KS0642_TIMEOUT) != HAL_OK){
		return SSROBOT_ERROR;
	}

	return SSROBOT_OK;


}







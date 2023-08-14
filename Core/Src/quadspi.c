/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    quadspi.c
 * @brief   This file provides code for the configuration
 *          of the QUADSPI instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2021 STMicroelectronics.
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
#include "quadspi.h"

/* USER CODE BEGIN 0 */
#include "W25Q256.h"

static uint8_t QSPI_ResetChip(void);
static uint8_t QSPI_AutoPollingMemReady(void);
static uint8_t QSPI_WriteEnable(void);
static uint8_t QSPI_Configuration(void);
static uint32_t QSPI_ReadID(void);


/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

	/* USER CODE BEGIN QUADSPI_Init 0 */

	/* USER CODE END QUADSPI_Init 0 */

	/* USER CODE BEGIN QUADSPI_Init 1 */

	/* USER CODE END QUADSPI_Init 1 */
	hqspi.Instance = QUADSPI;
	hqspi.Init.ClockPrescaler = 3;
	hqspi.Init.FifoThreshold = 4;
	hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_HALFCYCLE;
	hqspi.Init.FlashSize = 24;
	hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_6_CYCLE;
	hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
	hqspi.Init.FlashID = QSPI_FLASH_ID_1;
	hqspi.Init.DualFlash = QSPI_DUALFLASH_DISABLE;
	if (HAL_QSPI_Init(&hqspi) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN QUADSPI_Init 2 */

	/* USER CODE END QUADSPI_Init 2 */

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = { 0 };
	if (qspiHandle->Instance == QUADSPI)
	{
		/* USER CODE BEGIN QUADSPI_MspInit 0 */

		/* USER CODE END QUADSPI_MspInit 0 */
		/** Initializes the peripherals clock
		 */
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_QSPI;
		PeriphClkInitStruct.QspiClockSelection = RCC_QSPICLKSOURCE_PLL;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
			Error_Handler();
		}

		/* QUADSPI clock enable */
		__HAL_RCC_QSPI_CLK_ENABLE();

		__HAL_RCC_GPIOE_CLK_ENABLE();
		__HAL_RCC_GPIOF_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**QUADSPI GPIO Configuration
		 PE2     ------> QUADSPI_BK1_IO2
		 PF9     ------> QUADSPI_BK1_IO1
		 PB2     ------> QUADSPI_CLK
		 PD11     ------> QUADSPI_BK1_IO0
		 PD13     ------> QUADSPI_BK1_IO3
		 PB6     ------> QUADSPI_BK1_NCS
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_9;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_2;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_13;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_6;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN QUADSPI_MspInit 1 */

		/* USER CODE END QUADSPI_MspInit 1 */
	}
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

	if (qspiHandle->Instance == QUADSPI)
	{
		/* USER CODE BEGIN QUADSPI_MspDeInit 0 */

		/* USER CODE END QUADSPI_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_QSPI_CLK_DISABLE();

		/**QUADSPI GPIO Configuration
		 PE2     ------> QUADSPI_BK1_IO2
		 PF9     ------> QUADSPI_BK1_IO1
		 PB2     ------> QUADSPI_CLK
		 PD11     ------> QUADSPI_BK1_IO0
		 PD13     ------> QUADSPI_BK1_IO3
		 PB6     ------> QUADSPI_BK1_NCS
		 */
		HAL_GPIO_DeInit(GPIOE, GPIO_PIN_2);

		HAL_GPIO_DeInit(GPIOF, GPIO_PIN_9);

		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2 | GPIO_PIN_6);

		HAL_GPIO_DeInit(GPIOD, GPIO_PIN_11 | GPIO_PIN_13);

		/* USER CODE BEGIN QUADSPI_MspDeInit 1 */

		/* USER CODE END QUADSPI_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */

/* QUADSPI Init function */
uint8_t CSP_QUADSPI_Init(void)
{
	hqspi.Instance = QUADSPI;

	/* prepare QSPI peripheral for ST-Link Utility operations */
	if (HAL_QSPI_DeInit(&hqspi) != HAL_OK)
	{
		return HAL_ERROR;
	}

	MX_QUADSPI_Init();

	/*--------------------------------------------------------------------------------------------*/

	if (QSPI_ResetChip() != HAL_OK)
	{
		return HAL_ERROR;
	}

	HAL_Delay(1);

	/* ??? */
	if (QSPI_AutoPollingMemReady() != HAL_OK)
	{
		return HAL_ERROR;
	}

	uint32_t W25Qxx_ID = QSPI_ReadID();

	/* Send a 'Write Enable' command */
	if (QSPI_WriteEnable() != HAL_OK)
	{
		return HAL_ERROR;
	}

	/* 'Quad Enable' and set 100% of Output Driver Strength */
	if (QSPI_Configuration() != HAL_OK)
	{
		return HAL_ERROR;
	}

	W25Qxx_ID = 0x00;
	W25Qxx_ID = QSPI_ReadID();

	return HAL_OK;
}

/*------------------------------------------------------------------------------------------------*/

/** Block Erase (64KB). Completion can be checked in 'BUSY' bit with QSPI_AutoPollingMemReady() */
uint8_t CSP_QSPI_EraseBlock(uint32_t flash_address)
{
	QSPI_CommandTypeDef sCommand = { 0 };
	HAL_StatusTypeDef ret;

	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Enable write operations ------------------------------------------- */
	if ((ret = QSPI_WriteEnable()) != HAL_OK)
	{
		return ret;
	}

	/* Erasing Sequence -------------------------------------------------- */
	sCommand.Instruction = BLOCK_ERASE_CMD;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.Address = flash_address;
	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.DummyCycles = 0;

	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	return HAL_OK;
}

/** Sector Erase (4KB). This function is waiting for the erasing process to complete. */
uint8_t CSP_QSPI_EraseSectorWithPending(uint32_t EraseStartAddress, uint32_t EraseEndAddress)
{
	QSPI_CommandTypeDef sCommand = { 0 };
	HAL_StatusTypeDef ret;

	EraseStartAddress = EraseStartAddress - EraseStartAddress % MEMORY_SECTOR_SIZE;

	/* Erasing Sequence -------------------------------------------------- */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = SECTOR_ERASE_CMD;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.DummyCycles = 0;

	while (EraseEndAddress >= EraseStartAddress)
	{
		sCommand.Address = (EraseStartAddress & 0x0FFFFFFF);

		if (QSPI_WriteEnable() != HAL_OK)
		{
			return HAL_ERROR;
		}

		if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		{
			return HAL_ERROR;
		}

		EraseStartAddress += MEMORY_SECTOR_SIZE;

		if (QSPI_AutoPollingMemReady() != HAL_OK)
		{
			return HAL_ERROR;
		}
	}

	return HAL_OK;
}

/** 'buffer' - data to be written to FLASH; 'address' - address in FLASH; */
uint8_t CSP_QSPI_WriteMemory(uint8_t* buffer, uint32_t address, uint32_t buffer_size)
{
	QSPI_CommandTypeDef sCommand = { 0 };
	HAL_StatusTypeDef ret;
	uint32_t end_addr, current_size, current_addr;

	/* Calculation of the size between the write address and the end of the page */
	current_addr = 0;

	/* calculate the space remaining in current page :
	 * current_size = MEMORY_PAGE_SIZE - (address % MEMORY_PAGE_SIZE);*/
	while (current_addr <= address)
	{
		current_addr += MEMORY_PAGE_SIZE;
	}
	current_size = current_addr - address;

	/* Check if the size of the data is less than the remaining place in the page */
	if (current_size > buffer_size)
	{
		current_size = buffer_size;
	}

	/* Initialize the adress variables */
	current_addr = address;
	end_addr = address + buffer_size;

	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = QUAD_PAGE_PROGRAM;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = buffer_size;
	sCommand.Address = address;
	sCommand.DummyCycles = 0;

	/* Perform the write page by page */
	do
	{
		sCommand.Address = current_addr;
		sCommand.NbData = current_size;

		if (current_size == 0)
		{
			return HAL_OK;
		}

		/* Enable write operations */
		if ((ret = QSPI_WriteEnable()) != HAL_OK)
		{
			return ret;
		}

		/* Configure the command */
		if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
		{
			return ret;
		}

		/* Transmission of the data */
		if ((ret = HAL_QSPI_Transmit(&hqspi, buffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
		{
			return ret;
		}

		/* Configure automatic polling mode to wait for end of program */
		if ((ret = QSPI_AutoPollingMemReady()) != HAL_OK)
		{
			return ret;
		}

		/* Update the address and size variables for next page programming */
		current_addr += current_size;
		buffer += current_size;
		current_size = ((current_addr + MEMORY_PAGE_SIZE) > end_addr) ?
				(end_addr - current_addr) : MEMORY_PAGE_SIZE;

	} while (current_addr <= end_addr);

	return HAL_OK;
}

uint8_t CSP_QSPI_EnableMemoryMappedMode(void)
{
	QSPI_CommandTypeDef sCommand;
	QSPI_MemoryMappedTypeDef sMemMappedCfg;
	HAL_StatusTypeDef ret;

	/* Enable Memory-Mapped mode-------------------------------------------------- */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = QUAD_OUT_FAST_READ_CMD;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
	sCommand.AddressMode = QSPI_ADDRESS_1_LINE;
	sCommand.Address = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = 0;
	sCommand.DummyCycles = 8;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.AlternateBytes = 0;
	sCommand.AlternateBytesSize = 0;

	sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
	sMemMappedCfg.TimeOutPeriod = 0;

	if ((ret = HAL_QSPI_MemoryMapped(&hqspi, &sCommand, &sMemMappedCfg)) != HAL_OK)
	{
		return ret;
	}

	return HAL_OK;
}

uint8_t CSP_QSPI_EnableMemoryMappedMode_QuadIO(void)
{
	QSPI_CommandTypeDef sCommand;
	QSPI_MemoryMappedTypeDef sMemMappedCfg;
	HAL_StatusTypeDef ret;

	/* Enable Memory-Mapped mode-------------------------------------------------- */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = QUAD_IN_OUT_FAST_READ_CMD;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;
	sCommand.AddressMode = QSPI_ADDRESS_4_LINES;
	sCommand.Address = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.DataMode = QSPI_DATA_4_LINES;
	sCommand.NbData = 0;
	sCommand.DummyCycles = 4;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_4_LINES;
	sCommand.AlternateBytes = 0xFF;
	sCommand.AlternateBytesSize = 1;

	sMemMappedCfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE;
	sMemMappedCfg.TimeOutPeriod = 0;

	if ((ret = HAL_QSPI_MemoryMapped(&hqspi, &sCommand, &sMemMappedCfg)) != HAL_OK)
	{
		return ret;
	}

	return HAL_OK;
}

/*------------------------------------------------------------------------------------------------*/

/* Reset the chip */
static uint8_t QSPI_ResetChip()
{
	QSPI_CommandTypeDef sCommand = { 0 };
	HAL_StatusTypeDef ret;

	/* Enable Reset --------------------------- */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = RESET_ENABLE_CMD;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Send Reset Enable command */
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	/* Use the automatic polling flag bit to wait for the end of communication */
	if ((ret = QSPI_AutoPollingMemReady()) != HAL_OK)
	{
		return ret;
	}

	/* Reset Device --------------------------- */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = RESET_EXECUTE_CMD;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;

	/* Send Reset Device command */
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	/* Use the automatic polling flag bit to wait for the end of communication */
	if ((ret = QSPI_AutoPollingMemReady()) != HAL_OK)
	{
		return ret;
	}

//	for (temp = 0; temp < 500000; temp++)
//	{
//		__NOP();
//	}

	return HAL_OK;
}

/* Query 'BUSY' bit (Erase/Write In Progress) in 'Status Register 1' */
static uint8_t QSPI_AutoPollingMemReady(void)
{
	QSPI_CommandTypeDef sCommand = { 0 };
	QSPI_AutoPollingTypeDef sConfig;
	HAL_StatusTypeDef ret;

	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;					// Disable DDR mode
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;		// Data delay in DDR mode is not used here
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;//	Every time the data is transmitted, an instruction is sent	
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.Instruction = READ_STATUS_REG_CMD;

	/* Status Register 1:
	 * S7   S6 S5  S4  S3  S2  S1  S0
	 * SRP0 TB BP3 BP2 BP1 BP0 WEL BUSY
	 * 
	 * BUSY			- Erase/Write In Progress – Status Only;									*
	 * WEL			- Write Enable Latch ('1' after a 'Write Enable Instruction') – Status Only;*
	 * BP3...BP0	- Block Protect Bits – Volatile/Non-Volatile Writable;
	 * TB			- Top/Bottom Block Protect – Volatile/Non-Volatile Writable;
	 * SRP0, SRP1	- Status Register Protect - Volatile/Non-Volatile Writable;
	 */

	/* Match value with 'AND Mode' for 'BUSY' bit (Erase/Write In Progress) is '0' */
	sConfig.Match = 0;
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
	sConfig.StatusBytesSize = 1;
	sConfig.Mask = STATUS_REG1_BUSY_BIT;

	/* Send Polling Wait command */
	if ((ret = HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig, HAL_QSPI_TIMEOUT_DEFAULT_VALUE))
			!= HAL_OK)
	{
		return ret;
	}

	return HAL_OK;
}

/* Send a 'Write Enable' command */
static uint8_t QSPI_WriteEnable(void)
{
	QSPI_CommandTypeDef sCommand = { 0 };
	QSPI_AutoPollingTypeDef sConfig;
	HAL_StatusTypeDef ret;

	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;		// Data delay in DDR mode is not used here
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;				// Every time the data is transmitted, an instruction is sent	
	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.DummyCycles = 0;
	sCommand.Instruction = WRITE_ENABLE_CMD;

	/* Send a write enable command */
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	/* Status Register 1:
	 * S7   S6 S5  S4  S3  S2  S1  S0
	 * SRP0 TB BP3 BP2 BP1 BP0 WEL BUSY
	 * 
	 * BUSY			- Erase/Write In Progress – Status Only;									*
	 * WEL			- Write Enable Latch ('1' after a 'Write Enable Instruction') – Status Only;*
	 * BP3...BP0	- Block Protect Bits – Volatile/Non-Volatile Writable;
	 * TB			- Top/Bottom Block Protect – Volatile/Non-Volatile Writable;
	 * SRP0, SRP1	- Status Register Protect - Volatile/Non-Volatile Writable;
	 */

	/* Match value with 'AND Mode' for 'WEL' bit (Erase/Write In Progress) is '0b00000010' */
	sConfig.Match = 0x02; 											// Match value
	sConfig.MatchMode = QSPI_MATCH_MODE_AND;
	sConfig.Interval = 0x10;
	sConfig.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;
	sConfig.StatusBytesSize = 1;
	sConfig.Mask = STATUS_REG1_WEL_BIT;

	/* Query 'WEL' bit (Write Enable Latch) in 'Status Register 1' */
	sCommand.Instruction = READ_STATUS_REG_CMD;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.NbData = 1;

	/* Send Polling Wait command */
	if ((ret = HAL_QSPI_AutoPolling(&hqspi, &sCommand, &sConfig, HAL_QSPI_TIMEOUT_DEFAULT_VALUE))
			!= HAL_OK)
	{
		return ret;
	}

	return HAL_OK;
}

static uint8_t QSPI_Configuration(void)
{
	QSPI_CommandTypeDef sCommand = { 0 };
	uint8_t reg;
	HAL_StatusTypeDef ret;

	/* STATUS AND CONFIGURATION REGISTERS:
	 * 
	 * Status Register-1:
	 * S7   S6 S5  S4  S3  S2  S1  S0
	 * SRP0 TB BP3 BP2 BP1 BP0 WEL BUSY
	 * 
	 * BUSY			- Erase/Write In Progress – Status Only;									*
	 * WEL			- Write Enable Latch ('1' after a 'Write Enable Instruction') – Status Only;*
	 * BP3...BP0	- Block Protect Bits – Volatile/Non-Volatile Writable;
	 * TB			- Top/Bottom Block Protect – Volatile/Non-Volatile Writable;
	 * SRP0, SRP1	- Status Register Protect - Volatile/Non-Volatile Writable;
	 * 
	 * 
	 * Status Register-2:
	 * S15 S14 S13 S12 S11 S10 S9 S8
	 * SUS CMP LB3 LB2 LB1 (R) QE SRP1
	 * 
	 * SUS			- Erase/Program Suspend – Status Only;										*
	 * CMP			- Complement Protect – Volatile/Non-Volatile Writable;
	 * LB1...LB3	- Security Register Lock Bits – Volatile/Non-Volatile OTP Writable;
	 * (R)			- Reserved;
	 * QE			- Quad Enable – Volatile/Non-Volatile Writable;								!!!
	 * SRP1			- Status Register Protect 1 - Volatile/Non-Volatile Writable;
	 * 
	 * 
	 * Status Register-3:
	 * S23      S22  S21  S20 S19 S18 S17 S16
	 * HOLD/RST DRV1 DRV0 (R) (R) WPS ADP ADS
	 * 
	 * ADS			- Current Address Mode – Status Only;
	 * ADP			- Power-Up Address Mode – Non-Volatile Writable;
	 * WPS			- Write Protect Selection – Volatile/Non-Volatile Writable;
	 * (R)			- Reserved;
	 * DRV0...DRV1	- Output Driver Strength – Volatile/Non-Volatile Writable;
	 * HOLD/RST		- /HOLD or /RESET Pin Function – Volatile/Non-Volatile Writable;
	 * 
	 */

	/* Read 'Status Register 2' */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = READ_STATUS_REG2_CMD;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData = 1;

	/* Read 'Status Register 2'. 'reg' will contain value of 'Status Register 2' */
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK
			|| (ret = HAL_QSPI_Receive(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	/* Enable Volatile Write operations ---------------------------------------- */
	sCommand.DataMode = QSPI_DATA_NONE;
	sCommand.Instruction = WRITE_ENABLE_STATUS_REG_CMD;
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	/* In readed value of 'Status Register 2' set 'QE' bit - 'Quad Enable' */
	reg |= 2;

	/* Write new value to the 'Status Register 2' (QE = 1) */
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.Instruction = WRITE_STATUS_REG2_CMD;

	/* Write new value to the 'Status Register 2' (QE = 1) */
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK
			|| (ret = HAL_QSPI_Transmit(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	/* Read 'Status Register 3' */
	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction = READ_STATUS_REG3_CMD;
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData = 1;

	/* 'reg' will contain value of 'Status Register 3' */
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK
			|| (ret = HAL_QSPI_Receive(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	/* In readed value of 'Status Register 3' clear DRV1..DRV0 bits (100% of strength) */
	reg &= 0x9f;

	/* Write 'Status Register 3' (DRV1:2 = 00) */
	sCommand.Instruction = WRITE_STATUS_REG3_CMD;
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK
			|| (ret = HAL_QSPI_Transmit(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	return HAL_OK;
}

/* W25Q256FVEM - 0xEF4019 */
static uint32_t QSPI_ReadID(void)
{
	QSPI_CommandTypeDef sCommand = { 0 };
	QSPI_AutoPollingTypeDef sConfig;
	HAL_StatusTypeDef ret;
	uint8_t recBuf[3];

	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
	sCommand.AddressSize = QSPI_ADDRESS_24_BITS;			/* NOTE! */
	sCommand.AddressMode = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
	sCommand.DataMode = QSPI_DATA_1_LINE;
	sCommand.DummyCycles = 0;
	sCommand.Instruction = JEDEC_ID_CMD;
	sCommand.NbData = 3;

	/* 'recBuf' will contain data from "Read JEDEC ID' command */
	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK
			|| (ret = HAL_QSPI_Receive(&hqspi, recBuf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
	{
		return ret;
	}

	/* Combined with the obtained data into ID */
	uint32_t W25Qxx_ID = (recBuf[0] << 16) | (recBuf[1] << 8) | recBuf[2];

	return W25Qxx_ID;
}

/*------------------------------------------------------------------------------------------------*/

#ifndef w25q64_H
#define w25q64_H
#include "stm32h7xx_hal.h"
#include "main.h"

/* ---------------------------------------------------------------- name Parameter macro ------------------------------------------- */

#define QSPI_W25Qxx_OK           		0			// W25QXX communication is normal
#define W25Qxx_ERROR_INIT         		-1			// Initialization error
#define W25Qxx_ERROR_WriteEnable       -2			// write enable error
#define W25Qxx_ERROR_AUTOPOLLING       -3			// Polling waiting error, no response
#define W25Qxx_ERROR_Erase         		-4			// Erase error
#define W25Qxx_ERROR_TRANSMIT         	-5			// Transfer error
#define W25Qxx_ERROR_MemoryMapped		-6    		// Memory mapping mode error

#define W25Qxx_CMD_EnableReset  		0x66		// Enable reset
#define W25Qxx_CMD_ResetDevice   		0x99		// Reset device
#define W25Qxx_CMD_JedecID 				0x9F		// JEDEC ID  
#define W25Qxx_CMD_WriteEnable			0X06		// write enable

#define W25Qxx_CMD_SectorErase 			0x20		// sector erase, 4K byte, reference erase time 45ms
#define W25Qxx_CMD_BlockErase_32K 		0x52		// Block erase, 32K bytes, reference erase time 120ms
#define W25Qxx_CMD_BlockErase_64K 		0xD8		// Block erase, 64K bytes, reference erase time 150ms
#define W25Qxx_CMD_ChipErase 			0xC7		// Whole erase, reference erase time 20s

#define W25Qxx_CMD_QuadInputPageProgram  	0x32  	// 1-1-4 mode (1 line directive 1 line address 4 line data), page programming instruction, reference write time 0.4ms 
#define W25Qxx_CMD_FastReadQuad_IO       	0xEB  	// 1-4-4 mode (1 line directive 4 line address 4 line data), quickly read the instruction

#define W25Qxx_CMD_ReadStatus_REG1			0X05	// Read Status Register 1
#define W25Qxx_Status_REG1_BUSY  			0x01	// Read the 0th (read only) of the status register 1, the BUSY flag, when erase / writes the data / write command, 1
#define W25Qxx_Status_REG1_WEL  			0x02	// Read the first bit (read only) of the status register 1, the WEL write enable flag, the logo bit is 1, the representative can write

#define W25Qxx_PageSize       				256			// Page size, 256 bytes
#define W25Qxx_FlashSize       				0x800000	// W25Q64 size, 8M byte
#define W25Qxx_FLASH_ID           			0Xef4017    // W25Q64 JEDEC ID
#define W25Qxx_ChipErase_TIMEOUT_MAX		100000U		// Timeout waiting time, the maximum time required for W25Q64 whole erase is 100s
#define W25Qxx_Mem_Addr						0x90000000 	// Memory map mode

/*----------------------------------------------- Function declaration--------------------------------------------*/

int8_t QSPI_W25Qxx_Init(void);						// W25Qxx initialization
int8_t QSPI_W25Qxx_Reset(void);					// Reset device
uint32_t QSPI_W25Qxx_ReadID(void);					// Read device ID
int8_t QSPI_W25Qxx_MemoryMappedMode(void);			// Enter memory mapping mode

int8_t QSPI_W25Qxx_SectorErase(uint32_t SectorAddress);	// Sector erase, 4K bytes, reference erase time 45ms
int8_t QSPI_W25Qxx_BlockErase_32K(uint32_t SectorAddress);// Block erase, 32K bytes, reference erase time 120ms
int8_t QSPI_W25Qxx_BlockErase_64K(uint32_t SectorAddress);// Block erase, 64K bytes, reference erase time 150ms, the actual use of the proposed 64K erase, erase the fastest time
int8_t QSPI_W25Qxx_ChipErase(void);                         	// The reference erasing time is 20S

// Write by page, up to 256 bytes
int8_t QSPI_W25Qxx_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
// Write data, the maximum can not exceed the size of the flash chip
int8_t QSPI_W25Qxx_WriteBuffer(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
// Read data, the maximum can not exceed the size of the flash chip
int8_t QSPI_W25Qxx_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
#endif

/* Check W25Q64 */
int8_t QSPI_W25Qxx_Init(void)
{
	uint32_t Device_ID;

	MX_QUADSPI_Init();												// Initialize QSPI
	QSPI_W25Qxx_Reset();												// Reset
	Device_ID = QSPI_W25Qxx_ReadID();												// Read ID

	if (Device_ID == W25Qxx_FLASH_ID)									// Check peripheral devices
	{
		STM_printf("W25Q64 OK,flash ID:%X\r\n", Device_ID);	// Initialization success, print Debug information
		return QSPI_W25Qxx_OK;											// Return success mark		
	}
	else
	{
		STM_printf("W25Q64 ERROR!!!!!  ID:%X\r\n", Device_ID);			//initialization failed		
		return W25Qxx_ERROR_INIT;											// Return the error flag
	}
}

// Polling to confirm if the flash is idle (used to wait for the end of the communication, etc.)
int8_t QSPI_W25Qxx_AutoPollingMemReady(void)
{
	QSPI_CommandTypeDef s_command;	   						// qspi transmission configuration
	QSPI_AutoPollingTypeDef s_config;			// Polling compare related configuration parameters

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;		// 1 line instruction mode
	s_command.AddressMode = QSPI_ADDRESS_NONE;			// No address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;	// No delivery bytes 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;	    // Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	// DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;	   	// Send instructions each time transfer	
	s_command.DataMode = QSPI_DATA_1_LINE;				// 1 line data mode
	s_command.DummyCycles = 0;							// empty cycle
	s_command.Instruction = W25Qxx_CMD_ReadStatus_REG1;	// Read Status Information Register

// Contact W25QXX_CMD_READSTATUS_REG1 register, compare the W25QXX_STATUS_REG1_BUSY and 0 in the read status byte
// Read the 0th (read only) of the status register 1, the BUSY flag, when the / write data / write command is being erased / written, idle or communication is 0
	s_config.Match = 0;   							// Matching value
	s_config.MatchMode = QSPI_MATCH_MODE_AND;	      		//
	s_config.Interval = 0x10;	                     	// Polling interval
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;		// Automatic stop mode
	s_config.StatusBytesSize = 1;	                        	// Status byte
	s_config.Mask = W25Qxx_Status_REG1_BUSY;// Shielding the status byte received in polling mode, only the need to use

	// Send a polling waiting command
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
			!= HAL_OK)
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting unactfumble

	return QSPI_W25Qxx_OK; // Communication is normal
}

// Flash software reset
int8_t QSPI_W25Qxx_Reset(void)
{
	QSPI_CommandTypeDef s_command; // qspi transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;   	// 1 line instruction mode
	s_command.AddressMode = QSPI_ADDRESS_NONE;   			// No address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; 	// No delivery byte 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;     	// Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY; // DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;	 	// Send instructions each time transfer
	s_command.DataMode = QSPI_DATA_NONE;       		// No data mode	
	s_command.DummyCycles = 0;                     		// empty cycle
	s_command.Instruction = W25Qxx_CMD_EnableReset;       // Execute a reset enable command

	// Send a reset enable command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Qxx_ERROR_INIT;       // If the send failed, return an error message
	// Use the automatic polling flag, wait for the end of the communication
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
		return W25Qxx_ERROR_AUTOPOLLING;	// Polling waiting unactfumble

	s_command.Instruction = W25Qxx_CMD_ResetDevice;	// Reset device command    

	// Send a reset device command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Qxx_ERROR_INIT;	// If the send failed, return an error message

	// Use the automatic polling flag, wait for the end of the communication
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
		return W25Qxx_ERROR_AUTOPOLLING;	// Polling waiting unactfumble

	return QSPI_W25Qxx_OK;	// Reset success
}

uint32_t QSPI_W25Qxx_ReadID(void)
{
	QSPI_CommandTypeDef s_command;	// qspi transmission configuration
	uint8_t QSPI_ReceiveBuff[3];	// Store the data read by QSPI
	uint32_t W25Qxx_ID;	// Device ID

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;    	// 1 line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;     	// 24 bit address
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  	// No delivery byte 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;      	// Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;  // DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;	 	// Send instructions each time transfer
	s_command.AddressMode = QSPI_ADDRESS_NONE;   			// No address mode
	s_command.DataMode = QSPI_DATA_1_LINE;       	 	// 1 line data mode
	s_command.DummyCycles = 0;                   			// empty cycle
	s_command.NbData = 3;                       		// Transport data length
	s_command.Instruction = W25Qxx_CMD_JedecID;         	// Perform a read device ID command

	// Send instructions
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Qxx_ERROR_INIT;         	// If the send failed, return an error message
	// Receive data
	if (HAL_QSPI_Receive(&hqspi, QSPI_ReceiveBuff, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Qxx_ERROR_TRANSMIT;	// If the received failed, return an error message

	// Combined with the obtained data into ID
	W25Qxx_ID = (QSPI_ReceiveBuff[0] << 16) | (QSPI_ReceiveBuff[1] << 8) | QSPI_ReceiveBuff[2];
	return W25Qxx_ID;	// Return ID
}

// Set QSPI for memory mapping mode
// This mode is read-only and cannot be written.
int8_t QSPI_W25Qxx_MemoryMappedMode(void)
{
	QSPI_CommandTypeDef s_command;	// qspi transmission configuration
	QSPI_MemoryMappedTypeDef s_mem_mapped_cfg;	// Memory map access parameters

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;    	// 1 line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;            	// 24 bit address
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  	// No delivery byte 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;     				// Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;		// DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;				// Send instructions each time transfer	
	s_command.AddressMode = QSPI_ADDRESS_4_LINES; 				// 4 line address mode
	s_command.DataMode = QSPI_DATA_4_LINES;    					// 4 line data mode
	s_command.DummyCycles = 6;                    				// empty cycle
	s_command.Instruction = W25Qxx_CMD_FastReadQuad_IO;			// 1-4-4 mode (1 line directive 4 line address 4 line data), quickly read the instruction

	s_mem_mapped_cfg.TimeOutActivation = QSPI_TIMEOUT_COUNTER_DISABLE; // Disable timeout counter, NCS remains activated
	s_mem_mapped_cfg.TimeOutPeriod = 0;							   // timeout judgment cycle

	QSPI_W25Qxx_Reset();							   	// Reset W25QXX

	if (HAL_QSPI_MemoryMapped(&hqspi, &s_command, &s_mem_mapped_cfg) != HAL_OK)			// Configure
		return W25Qxx_ERROR_MemoryMapped;						// Set the memory mapping mode error

	return QSPI_W25Qxx_OK; // Configure success
}

// write enable
int8_t QSPI_W25Qxx_WriteEnable(void)
{
	QSPI_CommandTypeDef s_command;	   	// qspi transmission configuration
	QSPI_AutoPollingTypeDef s_config;		// Polling compare related configuration parameters

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;    	// 1 line instruction mode
	s_command.AddressMode = QSPI_ADDRESS_NONE;   		    // No address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  	// No delivery byte 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;      	// Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;  // DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;		// Send instructions each time transfer	
	s_command.DataMode = QSPI_DATA_NONE;       	    // No data mode
	s_command.DummyCycles = 0;                   	        // empty cycle
	s_command.Instruction = W25Qxx_CMD_WriteEnable;      	// Send a write enable command

	// Send a write enable command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
		return W25Qxx_ERROR_WriteEnable;
// Contact W25QXX_CMD_READSTATUS_REG1 register, compare the W25QXX_STATUS_REG1_WEL and 0x02 in the read status byte
// Read the first bit (read only) of the status register 1, the WEL write enable flag, the logo bit is 1, the representative can write

	s_config.Match = 0x02;  								// Matching value
	s_config.Mask = W25Qxx_Status_REG1_WEL;	// Read the first bit (read only) of the status register 1, the WEL write enable flag, the logo bit is 1, the representative can write
	s_config.MatchMode = QSPI_MATCH_MODE_AND;			 		//
	s_config.StatusBytesSize = 1;									// Status byte
	s_config.Interval = 0x10;							 	// Polling interval
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;			// Automatic stop mode

	s_command.Instruction = W25Qxx_CMD_ReadStatus_REG1;			// Read Status Information Register
	s_command.DataMode = QSPI_DATA_1_LINE;					// 1 line data mode
	s_command.NbData = 1;									// Data length

	// Send a polling waiting command	
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)
			!= HAL_OK)
		return W25Qxx_ERROR_AUTOPOLLING;		// Polling waiting unactfustuance, return an error

	return QSPI_W25Qxx_OK;									// Communication is normal
}

/* Erase */
// Here, the original document is repeated, and the instructions are repeated.
int8_t QSPI_W25Qxx_SectorErase(uint32_t SectorAddress)
{
	QSPI_CommandTypeDef s_command;	// qspi transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;// 1 line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;// 24 bit address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;// No delivery bytes 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;// Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;// DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;// Send instructions each time transfer
	s_command.AddressMode = QSPI_ADDRESS_1_LINE;// 1 line address mode
	s_command.DataMode = QSPI_DATA_NONE;// no data
	s_command.DummyCycles = 0;// empty cycle
	s_command.Address = SectorAddress;// To erase the address
	s_command.Instruction = W25Qxx_CMD_SectorErase;// sector erase command

	// Send write enable
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable;		// write enable failure
	}
	// Emieve command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase;				// Erase failed
	}
	// Use the automatic polling flag, waiting for the end of the erase 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING;		// Polling waiting unactfumble
	}
	return QSPI_W25Qxx_OK; // Erase success
}

int8_t QSPI_W25Qxx_BlockErase_32K(uint32_t SectorAddress)
{
	QSPI_CommandTypeDef s_command;	// qspi transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;    // 1 line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;       // 24 bit address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  // No delivery bytes 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;      // Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;  // DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;	// Send instructions each time transfer
	s_command.AddressMode = QSPI_ADDRESS_1_LINE;        // 1 line address mode
	s_command.DataMode = QSPI_DATA_NONE;             // no data
	s_command.DummyCycles = 0;                          // empty cycle
	s_command.Address = SectorAddress;              // To erase the address
	s_command.Instruction = W25Qxx_CMD_BlockErase_32K;  // Block Erase command, each erase 32k bytes

	// Send write enable	
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable;		// write enable failure
	}
	// Emieve command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase;				// Erase failed
	}
	// Use the automatic polling flag, waiting for the end of the erase 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING;		// Polling waiting unactfumble
	}
	return QSPI_W25Qxx_OK;	// Erase success
}

int8_t QSPI_W25Qxx_BlockErase_64K(uint32_t SectorAddress)
{
	QSPI_CommandTypeDef s_command;	// qspi transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;    // 1 line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;       // 24 bit address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  // No delivery bytes 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;      // Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;  // DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;	// Send instructions each time transfer
	s_command.AddressMode = QSPI_ADDRESS_1_LINE;        // 1 line address mode
	s_command.DataMode = QSPI_DATA_NONE;             // no data
	s_command.DummyCycles = 0;                          // empty cycle
	s_command.Address = SectorAddress;              // To erase the address
	s_command.Instruction = W25Qxx_CMD_BlockErase_64K; // Block erase command, each erase 64K bytes	

	// Send write enable
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable;	// write enable failure
	}
	// Emieve command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase;			// Erase failed
	}
	// Use the automatic polling flag, waiting for the end of the erase 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING;	// Polling waiting unactfumble
	}
	return QSPI_W25Qxx_OK;		// Erase success
}

int8_t QSPI_W25Qxx_ChipErase(void)
{
	QSPI_CommandTypeDef s_command;		// qspi transmission configuration
	QSPI_AutoPollingTypeDef s_config;	// Polling waiting for configuration parameters

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;    // 1 line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;       // 24 bit address mode
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;  // No delivery bytes 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;      // Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;  // DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;	// Send instructions each time transfer
	s_command.AddressMode = QSPI_ADDRESS_NONE;       	// No address
	s_command.DataMode = QSPI_DATA_NONE;             // no data
	s_command.DummyCycles = 0;                          // empty cycle
	s_command.Instruction = W25Qxx_CMD_ChipErase;       // Erase the command to make a whole erase

	// Send write enable	
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable;	// write enable failure
	}
	// Emieve command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_Erase;		 // Erase failed
	}

// Contact W25QXX_CMD_READSTATUS_REG1 register, compare the W25QXX_STATUS_REG1_BUSY in the read status byte to 0
// Read the 0th (read only) of the status register 1, the BUSY flag, when the / write data / write command is being erased / written, idle or communication is 0

	s_config.Match = 0;   									// Matching value
	s_config.MatchMode = QSPI_MATCH_MODE_AND;	      	//
	s_config.Interval = 0x10;	                     	// Polling interval
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;	// Automatic stop mode
	s_config.StatusBytesSize = 1;	                        	// Status byte
	s_config.Mask = W25Qxx_Status_REG1_BUSY;// Shielding the status byte received in polling mode, only the need to use

	s_command.Instruction = W25Qxx_CMD_ReadStatus_REG1;	// Read Status Information Register
	s_command.DataMode = QSPI_DATA_1_LINE;					// 1 line data mode
	s_command.NbData = 1;										// Data length

	// W25Q64 Typical reference time is 20s, the maximum time is 100s, the timeout wait value W25QXX_CHIPERASE_TIMEOUT_MAX is 100s
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, W25Qxx_ChipErase_TIMEOUT_MAX) != HAL_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING;	 // Polling waiting unactfumble
	}
	return QSPI_W25Qxx_OK;
}

/* Write */
int8_t QSPI_W25Qxx_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	QSPI_CommandTypeDef s_command;	// qspi transmission configuration	

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;// 1 line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;// 24 bit address
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;// No delivery byte 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;// Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;// DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;// Send instructions each time transfer	
	s_command.AddressMode = QSPI_ADDRESS_1_LINE;// 1 line address mode
	s_command.DataMode = QSPI_DATA_4_LINES;// 4 line data mode
	s_command.DummyCycles = 0;// empty cycle
	s_command.NbData = NumByteToWrite;// Data length, maximum 256 bytes
	s_command.Address = WriteAddr;// To write to W25QXX's address
	s_command.Instruction = W25Qxx_CMD_QuadInputPageProgram;// 1-1-4 mode (1 line instruction 1 line address 4 line data), page programming instruction

	// write enable
	if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_WriteEnable;	// write enable failure
	}
	// write command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT;		// Transfer data error
	}
	// Start transfer data
	if (HAL_QSPI_Transmit(&hqspi, pBuffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT;		// Transfer data error
	}
	// Use the automatic polling flag, wait for the end of the write 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting unactfumble
	}
	return QSPI_W25Qxx_OK;	// write data success
}


int8_t QSPI_W25Qxx_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size)
{
	uint32_t end_addr, current_size, current_addr;
	uint8_t* write_data;  // To write data

	current_size = W25Qxx_PageSize - (WriteAddr % W25Qxx_PageSize); // Calculate the remaining space remaining in the current page

	if (current_size > Size)	// Determine if the remaining space remains enough to write all data
	{
		current_size = Size;		// If enough, you can get the current length directly.
	}

	current_addr = WriteAddr;		// Get the address to be written
	end_addr = WriteAddr + Size;	// Computing end address
	write_data = pBuffer;			// Get the data to be written

	do
	{
		// Send write enable
		if (QSPI_W25Qxx_WriteEnable() != QSPI_W25Qxx_OK)
		{
			return W25Qxx_ERROR_WriteEnable;
		}

		// Write data by page
		else if (QSPI_W25Qxx_WritePage(write_data, current_addr, current_size) != QSPI_W25Qxx_OK)
		{
			return W25Qxx_ERROR_TRANSMIT;
		}

		// Use the automatic polling flag, wait for the end of the write 
		else if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
		{
			return W25Qxx_ERROR_AUTOPOLLING;
		}

		else // Write the data successfully on page, perform the next write data preparation
		{
			current_addr += current_size;	// Calculate the address to be written next
			write_data += current_size;	// Get the next time the data store address to be written
			// Calculate the length of the next write data
			current_size = ((current_addr + W25Qxx_PageSize) > end_addr) ?
					(end_addr - current_addr) : W25Qxx_PageSize;
		}
	}
	while (current_addr < end_addr); // Judgment if the data is all written

	return QSPI_W25Qxx_OK;	// Write data success
}

/* Read */
int8_t QSPI_W25Qxx_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{
	QSPI_CommandTypeDef s_command;	// qspi transmission configuration

	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;// 1 line instruction mode
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;// 24 bit address
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;// No delivery byte 
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;// Prohibit DDR mode
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;// DDR mode data delay, not used here
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;// Send instructions each time transfer	
	s_command.AddressMode = QSPI_ADDRESS_4_LINES;// 4 line address mode
	s_command.DataMode = QSPI_DATA_4_LINES;// 4 line data mode
	s_command.DummyCycles = 6;// empty cycle
	s_command.NbData = NumByteToRead;// Data length, the maximum size of the Flash chip
	s_command.Address = ReadAddr;// To read the address of W25QXX
	s_command.Instruction = W25Qxx_CMD_FastReadQuad_IO;// 1-4-4 mode (1 line directive 4 line address 4 line data), quickly read the instruction

	// Send a read command
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT;		// Transfer data error
	}

	//	Receive data

	if (HAL_QSPI_Receive(&hqspi, pBuffer, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		return W25Qxx_ERROR_TRANSMIT;		// Transfer data error
	}

	// Use the automatic polling flag to wait for the end of the reception 
	if (QSPI_W25Qxx_AutoPollingMemReady() != QSPI_W25Qxx_OK)
	{
		return W25Qxx_ERROR_AUTOPOLLING; // Polling waiting unactfumble
	}
	return QSPI_W25Qxx_OK;	// Read data success
}


//uint8_t QSPI_Configuration(void)
//{
//	QSPI_CommandTypeDef sCommand = { 0 };
//	uint8_t reg;
//	HAL_StatusTypeDef ret;
//
//	/* Read Volatile Configuration register 2 --------------------------- */
//	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
//	sCommand.Instruction = READ_STATUS_REG2_CMD;
//	sCommand.AddressMode = QSPI_ADDRESS_NONE;
//	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DataMode = QSPI_DATA_1_LINE;
//	sCommand.DummyCycles = 0;
//	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
//	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
//	sCommand.NbData = 1;
//
//	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
//	{
//		return ret;
//	}
//
//	if ((ret = HAL_QSPI_Receive(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
//	{
//		return ret;
//	}
//
//	/* Enable Volatile Write operations ---------------------------------------- */
//	sCommand.DataMode = QSPI_DATA_NONE;
//	sCommand.Instruction = VOLATILE_SR_WRITE_ENABLE;
//
//	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//	{
//		return ret;
//	}
//
//	/* Write Volatile Configuration register 2 (QE = 1) -- */
//	sCommand.DataMode = QSPI_DATA_1_LINE;
//	sCommand.Instruction = WRITE_STATUS_REG2_CMD;
//	reg |= 2; // QE bit
//
//	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//	{
//		return ret;
//	}
//
//	if (HAL_QSPI_Transmit(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//	{
//		return ret;
//	}
//
//	/* Read Volatile Configuration register 3 --------------------------- */
//	sCommand.InstructionMode = QSPI_INSTRUCTION_1_LINE;
//	sCommand.Instruction = READ_STATUS_REG3_CMD;
//	sCommand.AddressMode = QSPI_ADDRESS_NONE;
//	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
//	sCommand.DataMode = QSPI_DATA_1_LINE;
//	sCommand.DummyCycles = 0;
//	sCommand.DdrMode = QSPI_DDR_MODE_DISABLE;
//	sCommand.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;
//	sCommand.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;
//	sCommand.NbData = 1;
//
//	if ((ret = HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
//	{
//		return ret;
//	}
//
//	if ((ret = HAL_QSPI_Receive(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE)) != HAL_OK)
//	{
//		return ret;
//	}
//
//	/* Write Volatile Configuration register 2 (DRV1:2 = 00) -- */
//	sCommand.Instruction = WRITE_STATUS_REG3_CMD;
//	reg &= 0x9f; // DRV1:2 bit
//
//	if (HAL_QSPI_Command(&hqspi, &sCommand, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//	{
//		return ret;
//	}
//
//	if (HAL_QSPI_Transmit(&hqspi, &reg, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
//	{
//		return ret;
//	}
//
//	return HAL_OK;
//}

/* USER CODE END 1 */

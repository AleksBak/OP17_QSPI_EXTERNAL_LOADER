/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

extern QSPI_HandleTypeDef hqspi;

uint8_t CSP_QUADSPI_Init(void);
uint8_t CSP_QSPI_EraseSectorWithPending(uint32_t EraseStartAddress, uint32_t EraseEndAddress);
uint8_t CSP_QSPI_WriteMemory(uint8_t* buffer, uint32_t address, uint32_t buffer_size);
uint8_t CSP_QSPI_EnableMemoryMappedMode(void);
uint8_t CSP_QSPI_Erase_Chip (void);

/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */

/** W25Q256АFVEM memory parameters */
#define MEMORY_FLASH_SIZE				0x2000000		/* 256Mbit -> 32Mbyte */
#define MEMORY_BLOCK_SIZE				0x10000			/* 64KBytes, Total 512 blocks, Pages can be erased in that groups */
#define MEMORY_SECTOR_SIZE				0x1000			/* 4kBytes, Pages can be erased in that groups */
#define MEMORY_PAGE_SIZE				0x100			/* Up to 256 bytes can be programmed at a time */

/** W25Q256FVEM commands (See Tabl. 8.1.2 from DS) */
#define WRITE_DISABLE_CMD				0x04
#define WRITE_ENABLE_CMD				0x06
#define WRITE_ENABLE_STATUS_REG_CMD		0x50
#define WRITE_STATUS_REG1_CMD			0x01			/* REG1 */
#define READ_STATUS_REG_CMD				0x05			/* REG1 */
#define WRITE_STATUS_REG2_CMD			0x31
#define READ_STATUS_REG2_CMD			0x35
#define WRITE_STATUS_REG3_CMD			0x11
#define READ_STATUS_REG3_CMD			0x15

#define JEDEC_ID_CMD				0x9F			/* JEDEC ID */
#define CHIP_ERASE_CMD					0xC7

#define RESET_ENABLE_CMD				0x66
#define RESET_EXECUTE_CMD				0x99

#define SECTOR_ERASE_CMD				0x20	/* 4KB */
#define BLOCK_ERASE_CMD					0xD8	/* 64KB */

#define FAST_PROG_CMD					0x02	/* Page Program */

#define QUAD_PAGE_PROGRAM				0x32	/* Quad Instructions */
#define QUAD_OUT_FAST_READ_CMD			0x6B	/* Quad Instructions */
#define QUAD_IN_OUT_FAST_READ_CMD		0xEB	/* Quad Instructions */

/* Read Status Register 1 bit #0 (read-only), busy flag bit.
 * When erasing/writing data/writing
 * command is in progress, it will be set to 1 */
#define STATUS_REG1_BUSY_BIT			0x01

/*   */
#define STATUS_REG1_WEL_BIT			0x01

#define DUMMY_CLOCK_CYCLES_READ_QUAD	8



///** W25N01GVZEIG memory parameters */
//#define MEMORY_FLASH_SIZE				0x8000000		/* 1Gbit => 128Mbyte */
//#define MEMORY_SECTOR_SIZE				0x20000			/* 128kBytes (1 block, total 1024 blocks) */
//#define MEMORY_PAGE_SIZE				0x800			/* 2048 bytes */
//
///** W25N01GVZEIG commands */
//#define READ_STATUS_REG_CMD				0x05
//#define WRITE_ENABLE_CMD				0x06
//#define ENTER_4_BYTE_ADD_CMD			0xB7
//#define WRITE_VOL_CFG_REG_CMD			0x81
//#define SECTOR_ERASE_CMD				0xD8
//#define CHIP_ERASE_CMD					0xC7
//#define QUAD_IN_FAST_PROG_CMD			0x32
//#define READ_CONFIGURATION_REG_CMD		0x85
//#define QUAD_OUT_FAST_READ_CMD			0x6B
//#define DUMMY_CLOCK_CYCLES_READ_QUAD	10
//#define RESET_ENABLE_CMD				0x66
//#define RESET_EXECUTE_CMD				0x99
//
///** W25N01GVZEIG timeouts */
//#define QUADSPI_MAX_ERASE_TIMEOUT		460000			/* 460s max */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */


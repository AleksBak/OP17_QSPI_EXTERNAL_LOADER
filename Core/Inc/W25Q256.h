/*
 * W25Q256.h
 *
 *  Created on: Dec 3, 2021
 *      Author: User
 */

#ifndef INC_W25Q256_H_
#define INC_W25Q256_H_

#include "main.h"

#define W25Q256			0x01
#define W25Q64			0x02

//Write protect
#define W25X_WriteEnable		0x06
#define W25X_WriteDisable		0x04
//Read and write W25Qxx status register
#define W25X_ReadStatusReg1		0x05
#define W25X_ReadStatusReg2		0x35
#define W25X_ReadStatusReg3		0x15
#define W25X_WriteStatusReg1    0x01
#define W25X_WriteStatusReg2    0x31
#define W25X_WriteStatusReg3    0x11
//Read data
#define W25X_ReadData			0x03
#define W25X_FastReadData		0x0B
#define W25X_FastReadDual		0x3B
//Write by page
#define W25X_PageProgram		0x02
//Erase
#define W25X_BlockErase			0xD8
#define W25X_SectorErase		0x20
#define W25X_ChipErase			0xC7
//Off / low power consumption
#define W25X_PowerDown			0xB9
#define W25X_ReleasePowerDown	0xAB
//ID related
#define W25X_DeviceID			0xAB
#define W25X_ManufactDeviceID	0x90
#define W25X_JedecDeviceID		0x9F
//4-byte address mode
#define W25X_Enable4ByteAddr    0xB7
#define W25X_Exit4ByteAddr      0xE9
//Set read parameters
#define W25X_SetReadParam		0xC0
//Use QSPI mode
#define W25X_EnterQPIMode       0x38
#define W25X_ExitQPIMode        0xFF


void NORFLASH_Init(void);													//Initialize W25QXX
void NORFLASH_Qspi_Enable(void);											//Enable QSPI mode
void NORFLASH_Qspi_Disable(void);											//Turn off QSPI mode
uint16_t NORFLASH_ReadID(void);													//Read FLASH ID
uint8_t NORFLASH_ReadSR(uint8_t regno);										//Read status register 
void NORFLASH_4ByteAddr_Enable(void);									//Enable 4-byte address mode
void NORFLASH_Write_SR(uint8_t regno, uint8_t sr);							//Write status register
void NORFLASH_Write_Enable(void);  											//Write enable 
void NORFLASH_Write_Disable(void);											//Write protect
void NORFLASH_Write_NoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);	//Write flash without checking
void NORFLASH_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);   		//Read flash
void NORFLASH_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);	//Write flash
void NORFLASH_Erase_Chip(void);    	  										//Chip Erase 
void NORFLASH_Erase_Sector(uint32_t Dst_Addr);									//Sector Erase 
void NORFLASH_Wait_Busy(void);

#endif /* INC_W25Q256_H_ */

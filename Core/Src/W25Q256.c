/*
 * W25Q256.c
 *
 *  Created on: Dec 3, 2021
 *      Author: User
 */

#include "W25Q256.h"


uint16_t NORFLASH_TYPE = W25Q256;	//Use W25Q256
uint8_t NORFLASH_QPI_MODE = 0;		//QSPI mode flag: 0,SPI mode; 1,QSPI mode

/**
 * 4Kbytes For a Sector
 * 16 One sector is one Block
 * W25Q64 It has a capacity of 8M bytes, 128 blocks and 2048 sectors. W25Q256 is just four times as large as it
 */

//Initialize the IO port of SPI FLASH
void NORFLASH_Init(void)
{
	uint8_t temp;
	QSPI_Init();						//Initialize QSPI
	NORFLASH_Qspi_Enable();				//Enable QSPI mode
	NORFLASH_TYPE = NORFLASH_ReadID();	//Read FLASH ID
	if (NORFLASH_TYPE == W25Q64)
	{
		NORFLASH_Write_Enable();		//Write enable
		QSPI_Send_CMD(W25X_SetReadParam, 0, (3 << 6) | (0 << 4) | (0 << 2) | (3 << 0), 0);
		//QSPI set read parameter instruction, address is 0, 4 line transfer data_ 8-bit address_ No address_ 4-wire transmission instruction, no empty cycle, 1 byte data
		temp = 3 << 4;						//Set P4 & P5 = 11, 8 dummy clocks,104M
		QSPI_Transmit(&temp, 1);			//Send 1 byte
	}
	printf("ID:%x\r\n", NORFLASH_TYPE);	//Print FLASH parameters
}

//W25QXX enters QSPI mode 
void NORFLASH_Qspi_Enable(void)
{
	uint8_t stareg2 = 0;
	stareg2 = NORFLASH_ReadSR(2);		//Read out the original value of status register 2 first 
	//Printf ("stareg2: X, R, n", stareg2); / / print parameters
	if ((stareg2 & 0X02) == 0)				//QE bit not enabled
	{
		NORFLASH_Write_Enable();		//Write enable 
		stareg2 |= 1 << 1;					//Enable QE bit		
		NORFLASH_Write_SR(2, stareg2);	//Write status register 2
	}
	QSPI_Send_CMD(W25X_EnterQPIMode, 0, (0 << 6) | (0 << 4) | (0 << 2) | (1 << 0), 0);
	//Write command instruction, address 0, no data_ 8-bit address_ No address_ Single line transmission instruction, no empty period, 0 byte data
	NORFLASH_QPI_MODE = 1;				//Marking QSPI mode
}

//W25QXX quits QSPI mode
void NORFLASH_Qspi_Disable(void)
{
	QSPI_Send_CMD(W25X_ExitQPIMode, 0, (0 << 6) | (0 << 4) | (0 << 2) | (3 << 0), 0);
	//Write command instruction, address 0, no data_ 8-bit address_ No address_ 4-wire transmission instruction, no empty cycle, 0 byte data
	NORFLASH_QPI_MODE = 0;				//Label SPI mode
}

/* Read the status register of W25QXX */
//W25QXX has three status registers
//Status register 1:
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR: default 0, status register protection bit, used with WP
//TB,BP2,BP1,BP0:FLASH area write protection settings
//WEL: write enable lock
//BUSY: BUSY flag bit (1, BUSY; 0, idle)
//Default: 0x00
//Status register 2:
//BIT7  6   5   4   3   2   1   0
//SUS   CMP LB3 LB2 LB1 (R) QE  SRP1
//Status register 3:
//BIT7      6    5    4   3   2   1   0
//HOLD/RST  DRV1 DRV0 (R) (R) WPS ADP ADS
//regno: status register number, range: 1 ~ 3
//Return value: status register value
uint8_t NORFLASH_ReadSR(uint8_t regno)
{
	uint8_t byte = 0, command = 0;
	switch (regno)
	{
		case 1:
			command = W25X_ReadStatusReg1;    //Read status register 1 instruction
			break;
		case 2:
			command = W25X_ReadStatusReg2;    //Read status register 2 instruction
			break;
		case 3:
			command = W25X_ReadStatusReg3;    //Read status register 3 instruction
			break;
		default:
			command = W25X_ReadStatusReg1;
			break;
	}
	if (NORFLASH_QPI_MODE)
		QSPI_Send_CMD(command, 0, (3 << 6) | (0 << 4) | (0 << 2) | (3 << 0), 0);
	//QSPI mode, write command instruction, address 0, 4 wire data_ 8-bit address_ No address_ 4-wire transmission instruction, no empty cycle, 1 byte data
	else
		QSPI_Send_CMD(command, 0, (1 << 6) | (0 << 4) | (0 << 2) | (1 << 0), 0);
	//SPI mode, write command instruction, address 0, single line data transmission_ 8-bit address_ No address_ Single line transmission instruction, no empty period, 1 byte data
	QSPI_Receive(&byte, 1);

	return byte;
}

//Write W25QXX status register
void NORFLASH_Write_SR(uint8_t regno, uint8_t sr)
{
	uint8_t command = 0;
	switch (regno)
	{
		case 1:
			command = W25X_WriteStatusReg1;    //Write status register 1 instruction
			break;
		case 2:
			command = W25X_WriteStatusReg2;    //Write status register 2 instruction
			break;
		case 3:
			command = W25X_WriteStatusReg3;    //Write status register 3 instruction
			break;
		default:
			command = W25X_WriteStatusReg1;
			break;
	}
	if (NORFLASH_QPI_MODE)
		QSPI_Send_CMD(command, 0, (3 << 6) | (0 << 4) | (0 << 2) | (3 << 0), 0);
	//QPI, write command instruction, address 0, 4 line data_ 8-bit address_ No address_ 4-wire transmission instruction, no empty cycle, 1 byte data
	else
		QSPI_Send_CMD(command, 0, (1 << 6) | (0 << 4) | (0 << 2) | (1 << 0), 0);
	//SPI, write command instruction, address 0, single line data transmission_ 8-bit address_ No address_ Single line transmission instruction, no empty period, 1 byte data
	QSPI_Transmit(&sr, 1);
}

//W25QXX write enable
//Set the WEL of S1 register
void NORFLASH_Write_Enable(void)
{
	if (NORFLASH_QPI_MODE)
		QSPI_Send_CMD(W25X_WriteEnable, 0, (0 << 6) | (0 << 4) | (0 << 2) | (3 << 0), 0);
	//QPI, write enable instruction, address 0, no data_ 8-bit address_ No address_ 4-wire transmission instruction, no empty cycle, 0 byte data
	else
		QSPI_Send_CMD(W25X_WriteEnable, 0, (0 << 6) | (0 << 4) | (0 << 2) | (1 << 0), 0);
	//SPI, write enable instruction, address 0, no data_ 8-bit address_ No address_ Single line transmission instruction, no empty period, 0 byte data
}

//W25QXX write forbidden	
//Clear WEL  
void NORFLASH_Write_Disable(void)
{
	if (NORFLASH_QPI_MODE)
		QSPI_Send_CMD(W25X_WriteDisable, 0, (0 << 6) | (0 << 4) | (0 << 2) | (3 << 0), 0);
	//QPI, write inhibit instruction, address 0, no data_ 8-bit address_ No address_ 4-wire transmission instruction, no empty cycle, 0 byte data
	else
		QSPI_Send_CMD(W25X_WriteDisable, 0, (0 << 6) | (0 << 4) | (0 << 2) | (1 << 0), 0);
	//SPI, write inhibit instruction, address 0, no data_ 8-bit address_ No address_ Single line transmission instruction, no empty period, 0 byte data 
}

//The return values are as follows:				   
//0XEF13, indicating that the chip model is W25Q80  
//0XEF14, indicating that the chip model is W25Q16    
//0XEF15, indicating that the chip model is W25Q32  
//0XEF16, indicating that the chip model is W25Q64 
//0XEF17, indicating that the chip model is W25Q128 	  
//0XEF18, indicating that the chip model is W25Q256
uint16_t NORFLASH_ReadID(void)
{
	uint8_t temp[2];
	uint16_t deviceid;
	if (NORFLASH_QPI_MODE)
		QSPI_Send_CMD(W25X_ManufactDeviceID, 0, (3 << 6) | (2 << 4) | (3 << 2) | (3 << 0), 0);
	//QPI, read id, address 0, 4-wire data transmission_ 24 bit address_ 4-wire transmission address_ 4-wire transmission instruction, no empty cycle, 2 bytes of data
	else
		QSPI_Send_CMD(W25X_ManufactDeviceID, 0, (1 << 6) | (2 << 4) | (1 << 2) | (1 << 0), 0);
	//SPI, read id, address 0, single line data transmission_ 24 bit address_ Single line transmission address_ Single line transmission instruction, no empty cycle, 2 bytes of data
	QSPI_Receive(temp, 2);
	deviceid = (temp[0] << 8) | temp[1];

	return deviceid;
}

//Read SPI FLASH, only support QSPI mode
//Start reading data of the specified length at the specified address
//pBuffer: data store
//ReadAddr: address to start reading (maximum 32bit)
//NumByteToRead: number of bytes to read (maximum 65535)
void NORFLASH_Read(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	QSPI_Send_CMD(W25X_FastReadData, ReadAddr, (3 << 6) | (2 << 4) | (3 << 2) | (3 << 0), 8);
	//QPI, fast read data, address ReadAddr,4-wire data transmission_ 24 bit address_ 4-wire transmission address_ 4-wire transmission instruction, 8 null cycles, NumByteToRead data
	QSPI_Receive(pBuffer, NumByteToRead);
}

//SPI writes less than 256 bytes of data in one page (0-65535)
//Write a maximum of 256 bytes of data at the specified address
//pBuffer: data store
//WriteAddr: address to start writing (maximum 32bit)
//NumByteToWrite: the number of bytes to write (maximum 256), which should not exceed the remaining bytes of the page!!!	 
void NORFLASH_Write_Page(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	NORFLASH_Write_Enable();    //Write enable
	QSPI_Send_CMD(W25X_PageProgram, WriteAddr, (3 << 6) | (2 << 4) | (3 << 2) | (3 << 0), 0);
	//QPI, page write instruction, address is WriteAddr,4-wire data transmission_ 24 bit address_ 4-wire transmission address_ 4-wire transmission instruction, no empty cycle, NumByteToWrite data
	QSPI_Transmit(pBuffer, NumByteToWrite);
	NORFLASH_Wait_Busy();    //Wait for the end of the write
}

//Write SPI FLASH without verification
//You must make sure that all the data in the address range written are 0 XFF, otherwise the data written in non 0 XFF will fail!
//With automatic page change function
//Write the data of the specified length at the specified address, but make sure that the address does not cross the boundary!
//pBuffer: data store
//WriteAddr: address to start writing (maximum 32bit)
//NumByteToWrite: number of bytes to write (maximum 65535)
//CHECK OK
void NORFLASH_Write_NoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint16_t pageremain;
	pageremain = 256 - WriteAddr % 256;    //The number of bytes left in a single page		 	    
	if (NumByteToWrite <= pageremain)
		pageremain = NumByteToWrite;    //No more than 256 bytes
	while (1)
	{
		NORFLASH_Write_Page(pBuffer, WriteAddr, pageremain);
		if (NumByteToWrite == pageremain)
			break;    //End of write
		else    //NumByteToWrite>pageremain
		{
			pBuffer += pageremain;
			WriteAddr += pageremain;

			NumByteToWrite -= pageremain;    //Subtract the number of bytes that have been written
			if (NumByteToWrite > 256)
				pageremain = 256;    //256 bytes can be written at a time
			else
				pageremain = NumByteToWrite;    //Not 256 bytes
		}
	}
}

//Write SPI FLASH
//Write data of the specified length at the specified address
//The function with erase operation!
//pBuffer: data store
//WriteAddr: address to start writing (maximum 32bit)
//NumByteToWrite: number of bytes to write (maximum 65535)
uint8_t NORFLASH_BUFFER[4096];

void NORFLASH_Write(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;
	uint16_t i;
	uint8_t* NORFLASH_BUF;

	NORFLASH_BUF = NORFLASH_BUFFER;
	secpos = WriteAddr / 4096;    //Sector base address
	secoff = WriteAddr % 4096;    //Offset address
	secremain = 4096 - secoff;    //Sector remaining space size

	//Printf ("ad: X, Nb: X, R, n", writeaddr, numbytetowrite); / / for testing
	if (NumByteToWrite <= secremain)
		secremain = NumByteToWrite; //If the number of bytes to be written is not more than 4096 bytes, the size to be written is limited to one block size
	while (1)
	{
		NORFLASH_Read(NORFLASH_BUF, secpos * 4096, 4096);    //Read out the whole sector
		for (i = 0; i < secremain; i++)    //Calibration data
		{
			if (NORFLASH_BUF[secoff + i] != 0XFF)    //If there is a non empty area
				break;    //Need to erase
		}
		if (i < secremain) //If the byte to be written is less than the remaining space, it needs to be erased
		{
			NORFLASH_Erase_Sector(secpos);    //Erase this sector
			for (i = 0; i < secremain; i++)
			{
				NORFLASH_BUF[i + secoff] = pBuffer[i];    //Copy the written content to FLASH	  
			}
			NORFLASH_Write_NoCheck(NORFLASH_BUF, secpos * 4096, 4096);  //Write the entire sector   
		}
		else
			//If you don't need to erase
			NORFLASH_Write_NoCheck(pBuffer, WriteAddr, secremain); //Write directly to the remaining empty sector

		if (NumByteToWrite == secremain)
			break;    //End of write
		else    //Write is not finished, and then write the next sector
		{
			secpos++;    //Sector address increased by 1
			secoff = 0;    //The offset position is 0 	 

			pBuffer += secremain;    //Pointer offset
			WriteAddr += secremain;    //Write address offset
			NumByteToWrite -= secremain;    //Byte decrement
			if (NumByteToWrite > 4096)
				secremain = 4096;    //The next sector can't be finished
			else
				secremain = NumByteToWrite;    //The next sector can be written
		}
	}
}

//Full erase
//The waiting time will be long
void NORFLASH_Erase_Chip(void)
{
	NORFLASH_Write_Enable();    //WEL set
	NORFLASH_Wait_Busy();
	QSPI_Send_CMD(W25X_ChipErase, 0, (0 << 6) | (0 << 4) | (0 << 2) | (3 << 0), 0);
	//QPI, write full chip erase instruction, address 0, no data_ 8-bit address_ No address_ 4-wire transmission instruction, no empty cycle, 0 byte data
	NORFLASH_Wait_Busy();    //Wait for the end of chip erase
}

//Erase a sector
//Dst_Addr: the sector address is set according to the actual capacity
//Minimum time to erase a sector: 150ms
void NORFLASH_Erase_Sector(uint32_t Dst_Addr)
{
	//printf("fe:%x\r\n",Dst_Addr); / / monitor the falsh erasure, test with  	  
	Dst_Addr *= 4096;
	NORFLASH_Write_Enable();    //WEL set
	NORFLASH_Wait_Busy();
	QSPI_Send_CMD(W25X_SectorErase, Dst_Addr, (0 << 6) | (2 << 4) | (3 << 2) | (3 << 0), 0);
	//QPI, write sector erase instruction, address 0, no data_ 24 bit address_ 4-wire transmission address_ 4-wire transmission instruction, no empty cycle, 0 byte data
	NORFLASH_Wait_Busy();    //Wait for the erase to complete
}

//Waiting for free
void NORFLASH_Wait_Busy(void)
{
	while ((NORFLASH_ReadSR(1) & 0x01) == 0x01);	// Wait for the BUSY bit to clear
}


UART1 - SIM7100E-PCIE;
UART4 - RS-485 with DE (2 ГНЕЗДА);
UART6 - ST-LINK VCP or HC-12;
UART7 - RS-485 with DE (1 ГНЕЗДО);

PB4_MODULE_RESET

------------------------

PD12 (I2C4_SCL)	- GY6180_VL53L0/1XV2
PB7 (I2C4_SDA)	- GY6180_VL53L0/1XV2

PB8 (I2C1_SCL)	- LCD_CTP (FT5316 or GT9271)
PB9 (I2C1_SDA)	- LCD_CTP (FT5316 or GT9271)

------------------------

OP17_QSPI_EXTERNAL_LOADER

QUADSPI сейчас (29.11.2021) : Winbond W25N01GVZEIG WSON8 6x8
Тогда для нее 'FLASH SIZE' будет такое:
1Gb = 128MB = 2^27					(16MB = 2^24, 32MB = 2^25, 64MB = 2^26, 128MB = 2^27)
FLASH SIZE = 27 - 1 = 26

QUADSPI сейчас (02.12.2021) : Winbond W25Q256FVEM WSON8 6x8
Тогда для нее 'FLASH SIZE' будет такое:
256Mb = 32MB = 2^25					(16MB = 2^24, 32MB = 2^25, 64MB = 2^26, 128MB = 2^27)
FLASH SIZE = 25 - 1 = 24

PE2(1)		QUADSPI_BK1_IO2
PF9(27)		QUADSPI_BK1_IO1
PB2(58)		QUADSPI_CLK
PD11(99)	QUADSPI_BK1_IO0
PD12(101)	QUADSPI_BK1_IO3
PB5(164)	QUADSPI_BK1_NCS

------------------------

/* FMC отображает адреса SDRAM по определённым адресам. В 'Reference Manual' на контроллер:
 * 
 * 0xC000 0000
 * 
 * ...
 * 
 * SDRAM Bank 1 -> 4 x 64 MB
 * 
 * ...
 * 
 * 0xCFFF FFFF
 * 
 * 0xD000 0000
 * 
 * ...
 * 
 * SDRAM Bank 2 -> 4 x 64 MB
 * 
 * ...
 * 
 * 0xDFFF FFFF
 * 
 * 
 * Т.к. в OpenH743 м/с SDRAM использует 'Clock and Chip Enable' => 'SDCKE1 + SDNE1',
 * то тут именно 'SDRAM Bank 2' будет у нас.
 */

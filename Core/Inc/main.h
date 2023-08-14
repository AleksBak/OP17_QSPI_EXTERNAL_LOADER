/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MODULE_ENABLE_Pin GPIO_PIN_3
#define MODULE_ENABLE_GPIO_Port GPIOE
#define DISP_Pin GPIO_PIN_8
#define DISP_GPIO_Port GPIOI
#define USER_BTN_1_Pin GPIO_PIN_13
#define USER_BTN_1_GPIO_Port GPIOC
#define USER_BTN_2_Pin GPIO_PIN_4
#define USER_BTN_2_GPIO_Port GPIOH
#define USER_BTN_3_Pin GPIO_PIN_4
#define USER_BTN_3_GPIO_Port GPIOA
#define DISP_EN_PWM_Pin GPIO_PIN_6
#define DISP_EN_PWM_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOB
#define RELAY_ON_Pin GPIO_PIN_3
#define RELAY_ON_GPIO_Port GPIOG
#define SDMMC1_CD_Pin GPIO_PIN_3
#define SDMMC1_CD_GPIO_Port GPIOD
#define MODULE_RESET_Pin GPIO_PIN_4
#define MODULE_RESET_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

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
#define DB2_Pin GPIO_PIN_2
#define DB2_GPIO_Port GPIOE
#define DB3_Pin GPIO_PIN_3
#define DB3_GPIO_Port GPIOE
#define DB4_Pin GPIO_PIN_4
#define DB4_GPIO_Port GPIOE
#define DB5_Pin GPIO_PIN_5
#define DB5_GPIO_Port GPIOE
#define DB6_Pin GPIO_PIN_6
#define DB6_GPIO_Port GPIOE
#define DB7_Pin GPIO_PIN_7
#define DB7_GPIO_Port GPIOE
#define DB8_Pin GPIO_PIN_8
#define DB8_GPIO_Port GPIOE
#define DB9_Pin GPIO_PIN_9
#define DB9_GPIO_Port GPIOE
#define DB10_Pin GPIO_PIN_10
#define DB10_GPIO_Port GPIOE
#define DB11_Pin GPIO_PIN_11
#define DB11_GPIO_Port GPIOE
#define DB12_Pin GPIO_PIN_12
#define DB12_GPIO_Port GPIOE
#define DB13_Pin GPIO_PIN_13
#define DB13_GPIO_Port GPIOE
#define DB14_Pin GPIO_PIN_14
#define DB14_GPIO_Port GPIOE
#define DB15_Pin GPIO_PIN_15
#define DB15_GPIO_Port GPIOE
#define WRn_Pin GPIO_PIN_14
#define WRn_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_13
#define RS_GPIO_Port GPIOD
#define BACKLIGHT_Pin GPIO_PIN_14
#define BACKLIGHT_GPIO_Port GPIOD
#define RDn_Pin GPIO_PIN_15
#define RDn_GPIO_Port GPIOD
#define CSn_Pin GPIO_PIN_8
#define CSn_GPIO_Port GPIOC
#define DB0_Pin GPIO_PIN_0
#define DB0_GPIO_Port GPIOE
#define DB1_Pin GPIO_PIN_1
#define DB1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

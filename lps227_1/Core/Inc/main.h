/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
//extern ADC_HandleTypeDef hadc4;
//
//extern I2C_HandleTypeDef hi2c1;
//extern I2C_HandleTypeDef hi2c2;
//extern I2C_HandleTypeDef hi2c3;
//extern I2C_HandleTypeDef hi2c4;
//
//extern RTC_HandleTypeDef hrtc;
//
//extern SPI_HandleTypeDef hspi1;
//extern SPI_HandleTypeDef hspi2;
//extern SPI_HandleTypeDef hspi3;
//
//extern UART_HandleTypeDef huart1;
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
#define VBUS_SENSE_Pin GPIO_PIN_2
#define VBUS_SENSE_GPIO_Port GPIOC
#define DRDY_LSM6DSOX_INT2_Pin GPIO_PIN_7
#define DRDY_LSM6DSOX_INT2_GPIO_Port GPIOE
#define DRDY_LSM6DSOX_INT2_EXTI_IRQn EXTI7_IRQn
#define DRDY_LSM6DSOX_INT1_Pin GPIO_PIN_8
#define DRDY_LSM6DSOX_INT1_GPIO_Port GPIOE
#define DRDY_LSM6DSOX_INT1_EXTI_IRQn EXTI8_IRQn
#define DRDY_LIS3MDL_Pin GPIO_PIN_9
#define DRDY_LIS3MDL_GPIO_Port GPIOE
#define DRDY_LIS3MDL_EXTI_IRQn EXTI9_IRQn
#define DRDY_LSM6DSO32_INT1_Pin GPIO_PIN_10
#define DRDY_LSM6DSO32_INT1_GPIO_Port GPIOE
#define DRDY_LSM6DSO32_INT1_EXTI_IRQn EXTI10_IRQn
#define DRDY_ADXL375_Pin GPIO_PIN_11
#define DRDY_ADXL375_GPIO_Port GPIOE
#define DRDY_ADXL375_EXTI_IRQn EXTI11_IRQn
#define DRDY_LSM6DSO32_INT2_Pin GPIO_PIN_12
#define DRDY_LSM6DSO32_INT2_GPIO_Port GPIOE
#define DRDY_LSM6DSO32_INT2_EXTI_IRQn EXTI12_IRQn
#define DRDY_LPS27HHW_Pin GPIO_PIN_6
#define DRDY_LPS27HHW_GPIO_Port GPIOC
#define DRDY_LPS27HHW_EXTI_IRQn EXTI6_IRQn
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/**
 ******************************************************************************
 * @file           : test_file.h
 * @brief          : Header for test functions
 ******************************************************************************
 **/

#ifndef __TEST_FILE_H
#define __TEST_FILE_H

#include "main.h"

/**
 * @brief Test function for testing individual sensors
 * @param void * output: Output for sensor
 * @retval ret_status: Error status
 */
uint8_t test_fnc(void *output);

/**
 * @brief  Initializes all sensors to test
 * @param  I2C_HandleTypeDef I2C_Periph1: The I2C1 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph2: The I2C2 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph3: The I2C3 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph4: The I2C4 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph1: The SPI1 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph2: The SPI2 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph3: The SPI3 peripheral on the micro-controller
 * 		   ADC_HandleTypeDef ADC_Perpiph1: The ADC4 peripheral on the micro-controller
 * @retval Error status
 */
uint8_t sensorsInit(I2C_HandleTypeDef I2C_Periph1 , I2C_HandleTypeDef I2C_Periph2 ,
		I2C_HandleTypeDef I2C_Periph3 , I2C_HandleTypeDef I2C_Periph4 ,
		SPI_HandleTypeDef SPI_Periph1 , SPI_HandleTypeDef SPI_Periph2 ,
		SPI_HandleTypeDef SPI_Periph3 , ADC_HandleTypeDef ADC_Perpiph1);

#endif

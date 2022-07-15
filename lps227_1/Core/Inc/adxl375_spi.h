/**
 ******************************************************************************
 * @file           : adxl375_spi.h
 * @brief          : Header for API for pressure calculations [SPI communication protocol]
 ******************************************************************************
 **/


#ifndef __ADXL375_SPI_H
#define __ADXL375_SPI_H

#include "adxl375_defs.h"
#include "main.h"

#define SPI_WRITE_BIT_1 (0x00)
#define SPI_READ_BIT_1 (0x80)

/**
 * @brief ADXL375 Device Identification
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375SPIWhoami(SPI_HandleTypeDef SPI_Handle);

/**
 * @brief ADXL375 Sensor Initialization
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375SPISetup(SPI_HandleTypeDef SPI_Handle);

/**
 * @brief ADXL375 Acceleration raw data acquisition
 * @param : int16_t acc_data[]: Pointer to acquired acceleration data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375SPIAccData(SPI_HandleTypeDef SPI_Handle , int16_t acc_data[]);


#endif

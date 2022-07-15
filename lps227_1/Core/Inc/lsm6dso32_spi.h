/**
 ******************************************************************************
 * @file           : lsm6dso32_spi.h
 * @brief          : Header for API for IMU calculations [SPI communication protocol]
 ******************************************************************************
 **/


#ifndef __LSM6DSO32_SPI_H
#define __LSM6DSO32_SPI_H

#include "lsm6dso32_defs.h"
#include "main.h"

#define SPI_WRITE_BIT_2 (0x00)
#define SPI_READ_BIT_2 (0x80)

/**
 * @brief LSM6DSO32 Device Identification
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32SPIWhoami(SPI_HandleTypeDef SPI_Handle);

/**
 * @brief LSM6DSO32 Sensor Initialization
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32SPISetup(SPI_HandleTypeDef SPI_Handle);

/**
 * @brief LSM6DSO32 Acceleration data acquisition
 * @param : int16_t acc_data[]: Pointer to acquired acceleration data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32SPIAccData(SPI_HandleTypeDef SPI_Handle , int16_t acc_data[]);

/**
 * @brief LSM6DSO32 Gyroscope data acquisition
 * @param : int16_t gyro_data[]: Pointer to acquired gyroscope data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32SPIGyroData(SPI_HandleTypeDef SPI_Handle , int16_t gyro_data[]);


#endif

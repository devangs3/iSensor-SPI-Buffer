/**
 ******************************************************************************
 * @file           : lps277_spi.h
 * @brief          : Header for API for pressure calculations [SPI communication protocol]
 ******************************************************************************
 **/


#ifndef __LPS277_SPI_H
#define __LPS277_SPI_H

#include <lps277_defs.h>
#include "main.h"



/**
 * @brief LPS27 Device Identification
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps227SPIWhoami(SPI_HandleTypeDef SPI_Handle);

/**
 * @brief LPS27 Sesnsor Initialization
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277SPISetup( SPI_HandleTypeDef SPI_Handle);

/**
 * @brief LPS27 Pressure raw data acquisition
 * @param : uint8_t pres_data[]: Pointer to acquired pressure data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * 			uint8_t *conv_flag: User-defined flag to check if data ready pin was triggered
 * @retval ret_status: Error status
 */
uint8_t lps277SPIPressureRawData(uint8_t pres_data[], SPI_HandleTypeDef SPI_Handle);

/**
 * @brief LPS27 Pressure final data conversion
 * 		  Concatenate the 24 bit data acquired from the data registers and divide by the sensitivity to get the pressure in hPa
 * 		  Reference: Application Note AN5837
 * @param : uint8_t *pres_raw_data: Pointer to acquired pressure data [input]
 * 			uint8_t pres_size: Size of array of the pressure data
 * @retval ret_status: Error status
 */
uint32_t lps277SPIPressureFinalData(uint8_t *pres_raw_data , uint8_t pres_size);

/**
 * @brief LPS27 Pressure data acquisition
 * @param : uint32_t pres_data: Pointer to acquired pressure data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * 			uint8_t *conv_flag: User-defined flag to check if data ready pin was triggered
 * @retval ret_status: Error status
 */
uint8_t lps277SPIPressureData(uint32_t *pres_data, SPI_HandleTypeDef SPI_Handle);

/**
 * @brief LPS27 Sensor De-initialization [SPI]
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277SPIDeinit(SPI_HandleTypeDef SPI_Handle);



#endif

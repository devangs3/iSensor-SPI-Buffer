/**
 ******************************************************************************
 * @file           : lps277_i2c.h
 * @brief          : Header for API for pressure calculations
 ******************************************************************************
 **/


#ifndef __LPS277_I2C_H
#define __LPS277_I2C_H

#include <lps277_defs.h>
#include "main.h"

#define LPS277_I2C_ADDR  (0xB8u)


/**
 * @brief LPS27 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps227I2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LPS27 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277I2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
  * @brief LPS27 Pressure raw data acquisition
  * @param : uint8_t pres_data[]: Pointer to acquired pressure data [output]
  * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
  * @retval ret_status: Error status
  */
uint8_t lps277I2CPressureRawData( uint8_t *pres_data , I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LPS27 Pressure final data conversion
 * 		  Concatenate the 24 bit data acquired from the data registers and divide by the sensitivity to get the pressure in hPa
 * 		  Reference: Application Note AN5837
 * @param : uint8_t *pres_raw_data: Pointer to acquired pressure data [input]
 * 			uint8_t pres_size: Size of array of the pressure data
 * @retval ret_status: Error status
 */
uint32_t lps277I2CPressureFinalData(uint8_t *pres_raw_data, uint8_t pres_size);

/**
 * @brief LPS27 Sensor De-initialization [I2C]
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277I2CDeinit(I2C_HandleTypeDef I2C_Handle);


#endif


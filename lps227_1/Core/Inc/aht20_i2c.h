/**
 ******************************************************************************
 * @file           : adxl375_i2c.h
 * @brief          : Header for API for accelerometer calculations [I2C]
 ******************************************************************************
 **/

#ifndef __AHT20_I2C_H
#define __AHT20_I2C_H

#include "aht20_defs.h"
#include "main.h"

#define AHT20_I2C_ADDR   (0x70)

/**
 * @brief   Temperature and Humidity data acquisition
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval  ret_status: Error status
 */
uint8_t aht20TempHumiditySetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief   Temperature and Humidity data acquisition
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 			float: Pointer to acquired temperature data (in degC) [output]
 * 			float: Pointer to acquired humidity data (in RH) [output]
 * @retval  ret_status: Error status
 */
uint8_t aht20TempHumidityData(I2C_HandleTypeDef I2C_Handle , float *temp_C , float *humidity);

/**
 * @brief   Temperature data acquisition
 * @param : uint8_t raw_data[] : raw temperature data
 * @retval  float temp: Temperature data
 */
uint8_t aht20TempData(float *temp , I2C_HandleTypeDef I2C_Handle);

/**
 * @brief   Humiidty data acquisition
 * @param : uint8_t raw_data[] : raw temperature data
 * @retval  float temp: Temperature data
 */
uint8_t aht20HumidityData(float *humidity, I2C_HandleTypeDef I2C_Handle);

/**
 * @brief   Soft reset
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval  ret_status: Error status
 */
uint8_t aht20SoftReset(I2C_HandleTypeDef I2C_Handle);


#endif

/**
 ******************************************************************************
 * @file           : tsl2591_i2c.h
 * @brief          : Header for API for accelerometer calculations [I2C]
 ******************************************************************************
 **/

#ifndef __TSL2591_I2C_H
#define __TSL2591_I2C_H

#include "tsl2591_defs.h"
#include "main.h"

#define TSL2591_I2C_ADDR    (0x52)

/**
 * @brief TSL2591 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t tsl2591I2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief TSL2591 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t tsl2591I2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief TSL2591 Sensor Data acquisition
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  float* : Light (in lux) data [output]
 * @retval ret_status: Error status
 */
uint8_t tsl2591LightData(I2C_HandleTypeDef I2C_Handle , float *light_lux);



#endif

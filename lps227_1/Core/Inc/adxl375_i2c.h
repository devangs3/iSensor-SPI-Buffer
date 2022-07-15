/**
 ******************************************************************************
 * @file           : adxl375_i2c.h
 * @brief          : Header for API for accelerometer calculations [I2C]
 ******************************************************************************
 **/

#ifndef __ADXL375_I2C_H
#define __ADXL375_I2C_H

#include"adxl375_defs.h"
#include "main.h"

#define ADXL375_I2C_ADDR    (0xA6)
/**
 * @brief ADXl375 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375I2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief ADXL375 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375I2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief ADXL375 Acceleration data acquisition
 * @param : int16_t acc_data[]: Pointer to acquired magnetic data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375I2CAccData(int16_t acc_data[], I2C_HandleTypeDef I2C_Handle);


#endif

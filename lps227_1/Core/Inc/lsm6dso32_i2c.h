/**
 ******************************************************************************
 * @file           : lsm6dso32_i2c.h
 * @brief          : Header for API for IMU [I2C]
 ******************************************************************************
 **/


#ifndef __LSM6DSOX32_I2C_H
#define __LSM6DSO32_I2C_H

#include "main.h"
#include "lsm6dso32_defs.h"

//Use alternate address by pulling SDO to VCC
//NOTE: Pull SDO to VCC to use alternate address
#define LSM6DSO32_I2C_ADDR  (0xD6u)

/**
 * @brief LSM6DSO32 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32I2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LSM6DSO32 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32I2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LSM6DSOX Sensor Accelerometer Data acquisition
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  Pointer to acceleration data (3 axes) (output)
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32I2CAccRawData(I2C_HandleTypeDef I2C_Handle , int16_t acc_data[]);

/**
 * @brief LSM6DSO32 Sensor Gyroscope Data acquisition
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  Pointer to gyroscope data (3 axes) (output)
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32I2CGyroRawData(I2C_HandleTypeDef I2C_Handle , int16_t gyro_data[]);


#endif

/**
 ******************************************************************************
 * @file           : lsm6dsox_i2c.h
 * @brief          : Header for API for IMU [I2C]
 ******************************************************************************
 **/


#ifndef __LSM6DSOX_I2C_H
#define __LSM6DSOX_I2C_H

#include "main.h"
#include "lsm6dsox_defs.h"

#define LSM6DSOX_I2C_ADDR  (0xD4u)

/**
 * @brief LSM6DSOX Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LSM6DSOX Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LSM6DSOX Sensor Gyroscope Data acquisition
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  Pointer to gyroscope data (3 axes) (output)
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CGyroData(I2C_HandleTypeDef I2C_Handle , int16_t gyro_data[]);


/**
 * @brief LSM6DSOX Sensor Accelerometer Data acquisition
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  Pointer to acceleration data (3 axes) (output)
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CAccData(I2C_HandleTypeDef I2C_Handle , int16_t acc_data[]);



#endif

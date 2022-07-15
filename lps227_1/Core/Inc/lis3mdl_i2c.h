/**
 ******************************************************************************
 * @file           : li3mdl_i2c.h
 * @brief          : Header for API for magnetometer calculations [I2C]
 ******************************************************************************
 **/


#ifndef __LIS3MDL_I2C_H
#define __LIS3MDL_I2C_H

#include <lis3mdl_defs.h>
#include "main.h"

#define LIS3MDL_I2C_ADDR  (0x38u)


/**
 * @brief LIS3MDL Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis3mdlI2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LIS3MDL Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis3mdlI2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LIS3MDL Magnetic raw data acquisition
 * @param : uint8_t magn_data[]: Pointer to acquired magnetic data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis3mdlMagneticData(int16_t magn_data[], I2C_HandleTypeDef I2C_Handle);



#endif

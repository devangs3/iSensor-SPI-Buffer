/**
 ******************************************************************************
 * @file           : lis2mdl_i2c.h
 * @brief          : Header for API for magnetometer calculations [I2C]
 ******************************************************************************
 **/


#ifndef __LIS2MDL_I2C_H
#define __LIS2MDL_I2C_H

#include <lis2mdl_defs.h>
#include "main.h"

#define LIS2MDL_I2C_ADDR  (0x3Cu)


/**
 * @brief LIS2MDL Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlI2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LIS2MDL Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlI2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LIS2MDL Magnetic raw data acquisition
 * @param : uint8_t magn_data[]: Pointer to acquired magnetic data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlMagneticRawData(uint8_t magn_data[], I2C_HandleTypeDef I2C_Handle);

/**
 * @brief LIS2MDL Magnetic final data conversion
 * 		  Reference: Application Note AN5069
 * @param : uint8_t *magn_raw_data: Pointer to acquired magnetic data [input]
 * 			uint8_t magn_size: Size of array of the magnetic data
 * 			float magn_final_data[]: Pointer to final magnetic data (in mG)
 * @retval ret_status: Error status
 */
uint8_t lis2mdlI2CMagneticFinalData(uint8_t *magn_raw_data , uint8_t magn_size , float magn_final_data[]);

/**
 * @brief LIS2MDL Magnetic raw data acquisition
 * @param : uint8_t magn_data[]: Pointer to acquired magnetic data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlMagneticData(float mag_data[], I2C_HandleTypeDef I2C_Handle);


#endif

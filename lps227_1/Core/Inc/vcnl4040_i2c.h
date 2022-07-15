/**
 ******************************************************************************
 * @file           : vcnl4040_i2c.h
 * @brief          : Header for API for proximity sensor calculations [I2C]
 ******************************************************************************
 **/


#ifndef __VCNL4044_I2C_H
#define __VCNL4044_I2C_H

#include "main.h"
#include "vcnl4040_defs.h"

#define VCNL4040_I2C_ADDR  (0xC0u)

/**
 * @brief VCNL4040 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t vcnl4040I2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief VCNL4040 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t vcnl4040I2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief VCNL4040 proximity data acquisition
 * @param : uint16_t proximity: Pointer to acquired magnetic data [output]
 * 	     	I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t vcnl4040ProximityData(I2C_HandleTypeDef I2C_Handle , uint16_t *proximity_data);

#endif

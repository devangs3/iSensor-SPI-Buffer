/**
 ******************************************************************************
 * @file           : bh1750_i2c.h
 * @brief          : Header for API for light sensor calculations [I2C]
 ******************************************************************************
 **/


#ifndef __BH1750_I2C_H
#define __BH1750_I2C_H

#include "main.h"
#include "bh1750_defs.h"

#define BH1750_I2C_ADDR  (0x46u)


/**
 * @brief Light sensor data acquisition
 * @param : uint16_t: Pointer to acquired light data (in lux) [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t bh1750LightData(I2C_HandleTypeDef I2C_Handle , uint16_t *light_data);

/**
 * @brief Light sensor setup
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t bh1750I2CSetup(I2C_HandleTypeDef I2C_Handle);

#endif

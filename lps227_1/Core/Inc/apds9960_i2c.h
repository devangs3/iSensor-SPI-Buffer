/**
 ******************************************************************************
 * @file           : apds9960_i2c.h
 * @brief          : Header for API for proximity and gesture calculations [I2C]
 ******************************************************************************
 **/


#ifndef __APDS9960_I2C_H
#define __APDS9960_I2C_H

#include "apds9960_defs.h"
#include "main.h"

#define APDS9960_I2C_ADDR   (0x72u)


/**
 * @brief APDS9960 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t apds9960I2CWhoami(I2C_HandleTypeDef I2C_Handle);

uint8_t apds9960ProximitySetup(I2C_HandleTypeDef I2C_Handle);

uint8_t apds9960ProximityData(I2C_HandleTypeDef I2C_Handle , uint8_t *proximity);

#endif

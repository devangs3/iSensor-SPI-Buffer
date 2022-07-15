/**
 ******************************************************************************
 * @file           : bme680_i2c.h
 * @brief          : Header for API for pressure,temp and gas calculations [I2C]
 ******************************************************************************
 **/


#ifndef __BME680_I2C_H
#define __BME680_I2C_H

#include <bme680_defs.h>
#include "main.h"

#define BME680_I2C_ADDR  (0xECu)

typedef struct
{
	uint16_t temp_p1;
	int16_t temp_p2;
	int8_t temp_p3;
}Calibration_data_n;

uint8_t bme680I2CReset(I2C_HandleTypeDef I2C_Handle);


/**
 * @brief BME680 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t bme680I2CWhoami(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief BME680 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t bme680I2CSetup(I2C_HandleTypeDef I2C_Handle);

/**
 * @brief BME680 raw data acquisition
 * @param : uint8_t bme680_data[]: Pointer to acquired temperature, pressure,
 * 								    humidity and gas resistance data [output]
 * 	     	I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval  ret_status: Error status
 */
uint8_t bme680RawData(uint8_t bme680_data[], I2C_HandleTypeDef I2C_Handle);

/**
 * @brief BME680 Final data conversion
 * 		  Reference: Datasheet
 * @param : uint8_t *magn_raw_data: Pointer to acquired magnetic data [input]
 * 			uint8_t magn_size: Size of array of the magnetic data
 * 			float magn_final_data[]: Pointer to final magnetic data
 * @retval ret_status: Error status
 */
int16_t bme680FinalData(uint8_t *bme680_raw_data);

#endif

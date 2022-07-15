/**
 ******************************************************************************
 * @file           : tsl2591_i2c.c
 * @brief          : API for light/lux [I2C communication protocol]
 ******************************************************************************
 **/

#include "tsl2591_i2c.h"

/**
 * @brief TSL2591 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t tsl2591I2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, TSL2591_I2C_ADDR, (TSL2591_ID | TSL2591_CMD_BIT) , I2C_MEMADD_SIZE_8BIT , &buf, I2C_MEMADD_SIZE_8BIT, 100))
		ret_status = HAL_ERROR;
	else if(buf == TSL2591_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief TSL2591 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t tsl2591I2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf;
	uint8_t ret_status = HAL_OK;

	//Set medium gain
	//Set integration time as 600 milliseconds
//	buf = 0x00u;
//	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, TSL2591_I2C_ADDR, (TSL2591_CMD_BIT | TSL2591_CTRL), I2C_MEMADD_SIZE_8BIT, &buf, I2C_MEMADD_SIZE_8BIT, 100))
//		ret_status = HAL_ERROR;

	//Power On
	buf = 0x01u;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, TSL2591_I2C_ADDR, (TSL2591_CMD_BIT | TSL2591_ENABLE), I2C_MEMADD_SIZE_8BIT, &buf, I2C_MEMADD_SIZE_8BIT, 100))
		ret_status = HAL_ERROR;

	//Set medium gain
	//Set integration time as 600 milliseconds
	buf = 0x12u;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, TSL2591_I2C_ADDR, (TSL2591_CMD_BIT | TSL2591_CTRL), I2C_MEMADD_SIZE_8BIT, &buf, I2C_MEMADD_SIZE_8BIT, 100))
		ret_status = HAL_ERROR;

	//Set medium gain
	//Set integration time as 600 milliseconds
//	buf = 0x09u;
//	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, TSL2591_I2C_ADDR, (TSL2591_CMD_BIT | TSL2591_PERSIST), I2C_MEMADD_SIZE_8BIT, &buf, I2C_MEMADD_SIZE_8BIT, 100))
//		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief TSL2591 Sensor Data acquisition
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  float* : Light (in lux) data [output]
 * @retval ret_status: Error status
 */
uint8_t tsl2591LightData(I2C_HandleTypeDef I2C_Handle , float *light_lux)
{
	//	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;
	uint8_t ch_data[4] = {0 , 0 , 0 , 0};
	uint16_t ch0_c;
	uint32_t ch1_c;

	HAL_Delay(3600);

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle , TSL2591_I2C_ADDR , (TSL2591_CMD_BIT | TSL2591_C0DATAL) , 1 , &ch_data[0] , 4 , 100))
		ret_status = HAL_ERROR;

	ch0_c = (uint16_t)((ch_data[1] << 8) | (ch_data[0]));
	ch1_c = (uint16_t)((ch_data[3] << 8) | (ch_data[2]));

	ch1_c <<= 16;

	ch1_c |= ch0_c;

	//Reference: Adafruit library
	float cpl = (TSL2591_INT_TIME * TSL2591_GAIN_HIGH) / TSL2591_LUX_DF;

	*light_lux = (((float)ch0_c - (float)ch1_c)) * (1.0F - ((float)ch1_c / (float)ch0_c)) / cpl;

	return ret_status;

}

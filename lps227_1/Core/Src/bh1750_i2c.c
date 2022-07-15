/**
 ******************************************************************************
 * @file           : bh1750_i2c.c
 * @brief          : API for light sensor [I2C communication protocol]
 ******************************************************************************
 **/

#include "bh1750_i2c.h"

/**
 * @brief Light sensor setup
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t bh1750I2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t reg_addr;
	uint8_t ret_status = HAL_OK;

	//Continuous mode in High resolution (0.5lx)
	reg_addr = BH1750_CONT_H_RES_MODE;

	//Send command for continuous mode
	if(HAL_OK != transmitI2C(BH1750_I2C_ADDR, &reg_addr, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status  = HAL_ERROR;

	return ret_status;

}

/**
 * @brief Light sensor data acquisition
 * @param : uint16_t: Pointer to acquired light data (in lux) [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t bh1750LightData(I2C_HandleTypeDef I2C_Handle , uint16_t *light_data)
{
//	uint8_t reg_addr;
	uint8_t ret_status = HAL_OK;
	uint8_t l_data[2] = {0};
	float raw_data;

	//Fetch 2 bytes of light data
	if(HAL_OK != receiveI2C(BH1750_I2C_ADDR, &l_data[0], sizeof(l_data), I2C_Handle))
		ret_status = HAL_ERROR;

	//Concatenate data
	raw_data = ((l_data[0] << 8) | l_data[1]);

	//Multiply by offset
	*light_data = raw_data / 1.20f;

	return ret_status;

}



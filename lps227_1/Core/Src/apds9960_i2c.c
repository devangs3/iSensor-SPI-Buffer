/**
 ******************************************************************************
 * @file           : apds9960_i2c.c
 * @brief          : API for proximity [I2C communication protocol]
 ******************************************************************************
 **/

#include "apds9960_i2c.h"

/**
 * @brief APDS9960 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t apds9960I2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, APDS9960_I2C_ADDR, APDS9960_WHOAMI, I2C_MEMADD_SIZE_8BIT , &buf, I2C_MEMADD_SIZE_8BIT, 100))
		ret_status = HAL_ERROR;
	else if(buf == APDS9960_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;

}

uint8_t apds9960ProximitySetup(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf;
	uint8_t ret_status = HAL_OK;


	//Interrupt every proximity cycle proximity is beyond the threshold
	buf = 0x00u;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, APDS9960_I2C_ADDR, APDS9960_PERSISTENCE, I2C_MEMADD_SIZE_8BIT, &buf, I2C_MEMADD_SIZE_8BIT, 100))
		ret_status = HAL_ERROR;

	//	//Set lower threshold to 50
	//	buf = 0x32u;
	//	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, APDS9960_I2C_ADDR, APDS9960_LOW_THRESHOLD, I2C_MEMADD_SIZE_8BIT, &buf, I2C_MEMADD_SIZE_8BIT, 100))
	//		ret_status = HAL_ERROR;
	//
	//	//Set lower threshold to 60
	//	buf = 0x3Cu;
	//	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, APDS9960_I2C_ADDR, APDS9960_HIGH_THRESHOLD, I2C_MEMADD_SIZE_8BIT, &buf, I2C_MEMADD_SIZE_8BIT, 100))
	//		ret_status = HAL_ERROR;

	//Enable Proximity engine
	//Enable Proximity Interrupt
	//Enable Power On
	buf = 0x25u;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, APDS9960_I2C_ADDR, APDS9960_ENABLE, I2C_MEMADD_SIZE_8BIT, &buf, I2C_MEMADD_SIZE_8BIT, 100))
		ret_status = HAL_ERROR;


	return ret_status;

}

uint8_t apds9960ProximityData(I2C_HandleTypeDef I2C_Handle , uint8_t *proximity)
{
	uint8_t buf = 0;
	uint8_t reg_addr;
	uint8_t ret_status = HAL_OK;

	reg_addr = APDS9960_STATUS;

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, APDS9960_I2C_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT , &buf, I2C_MEMADD_SIZE_8BIT, 100))
		ret_status = HAL_ERROR;

	if((buf & 0x22) == 0x22)
	{
		if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, APDS9960_I2C_ADDR, APDS9960_PROXIMITY_DATA, I2C_MEMADD_SIZE_8BIT ,proximity, I2C_MEMADD_SIZE_8BIT, 100))
			ret_status = HAL_ERROR;

	}

	return ret_status;
}

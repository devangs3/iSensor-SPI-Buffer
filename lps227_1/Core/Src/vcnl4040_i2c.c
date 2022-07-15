/**
 ******************************************************************************
 * @file           : vcnl4040_i2c.c
 * @brief          : API for proximity sensor [I2C communication protocol]
 ******************************************************************************
 **/

#include "vcnl4040_i2c.h"


/**
 * @brief VCNL4040 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t vcnl4040I2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf[2];
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, VCNL4040_I2C_ADDR, VCNL4040_WHOAMI, I2C_MEMADD_SIZE_8BIT , buf, 2, 100))
		ret_status = HAL_ERROR;
	else if((buf[0] == VCNL4040_DEV_ID_LSB) && (buf[1] == VCNL4040_DEV_ID_MSB))
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief  VCNL4040 Sensor Initialization
 * @param  I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t vcnl4040I2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf[2];
	uint8_t ret_status = HAL_OK;

	//Enable proximity sensor
	buf[0] = 0x00;
	//16 bits output, interrupt when too close
	buf[1] = 0x09;

	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, VCNL4040_I2C_ADDR, VCNL4040_PS_CONF1, I2C_MEMADD_SIZE_8BIT, buf, 2, 100))
		ret_status = HAL_ERROR;

	//Normal operation without interrupt
	buf[0] = 0x00;
	buf[1] = 0xC0;

	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, VCNL4040_I2C_ADDR, VCNL4040_PS_CONF3, I2C_MEMADD_SIZE_8BIT, buf, 2, 100))
		ret_status = HAL_ERROR;

	buf[0] = 0x01;
	buf[1] = 0x00;

	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, VCNL4040_I2C_ADDR, VCNL4040_PS_LOW_THR, I2C_MEMADD_SIZE_8BIT, buf, 2, 100))
		ret_status = HAL_ERROR;

	buf[0] = 0x50;
	buf[1] = 0x00;

	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, VCNL4040_I2C_ADDR, VCNL4040_PS_HIGH_THR, I2C_MEMADD_SIZE_8BIT, buf, 2, 100))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief   VCNL4040 proximity data acquisition
 * @param : uint16_t proximity: Pointer to acquired proximity data [output]
 * 	     	I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval  ret_status: Error status
 */
uint8_t vcnl4040ProximityData(I2C_HandleTypeDef I2C_Handle , uint16_t *proximity_data)
{
	uint8_t buf[2] = {0 , 0};
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, VCNL4040_I2C_ADDR, VCNL4040_INT_FLAGS, I2C_MEMADD_SIZE_8BIT, &buf[0], 2 , 100))
		ret_status = HAL_ERROR;

	if((buf[1] & 0x01))
	{

		if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, VCNL4040_I2C_ADDR, VCNL4040_PS_DATA, I2C_MEMADD_SIZE_8BIT, &buf[0], 2 , 100))
			ret_status = HAL_ERROR;

		*proximity_data = ((buf[1] << 8) | (buf[0]));
	}

	return ret_status;
}



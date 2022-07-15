/**
 ******************************************************************************
 * @file           : lis3mdl_i2c.c
 * @brief          : API for magnetometer [I2C communication protocol]
 ******************************************************************************
 **/

#include "lis3mdl_i2c.h"

/**
 * @brief LIS3MDL Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis3mdlI2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != readRegI2C(LIS3MDL_I2C_ADDR, LIS3MDL_WHOAMI , &buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;
	else if(buf == LIS3MDL_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief LIS3MDL Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis3mdlI2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t val = 0;
	uint8_t ret_status = HAL_OK;

	//80 Hz ODR
	//Ultra-high performance
	val = (m3_odr_80Hz | m3_op_mode_UHP);
	if(HAL_OK != writeRegI2C(LIS3MDL_I2C_ADDR, LIS3MDL_CTRL1,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//Full scale: +- 8 Gauss
	val = m3_fs_8gauss;
	if(HAL_OK != writeRegI2C(LIS3MDL_I2C_ADDR, LIS3MDL_CTRL2,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//Continuous conversion mode
	val = m3_cont_mode;
	if(HAL_OK != writeRegI2C(LIS3MDL_I2C_ADDR, LIS3MDL_CTRL3,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//Ultra-high performance
	val = m3_omz_UHP;
	if(HAL_OK != writeRegI2C(LIS3MDL_I2C_ADDR, LIS3MDL_CTRL4,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//To clear the data ready interrupt, the data registers have to be read
#if(LIS3MDL_DRDY_EN == 1)
	{
		int16_t dummy_data[3];
		lis3mdlMagneticData(dummy_data, I2C_Handle);
	}
#endif

	return ret_status;
}

/**
 * @brief LIS3MDL Magnetic data acquisition
 * @param : uint8_t magn_data[]: Pointer to acquired magnetic data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis3mdlMagneticData(int16_t magn_data[], I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;
	uint8_t raw_mag_data[6];

	//Status register - Polling for new data
	while(!(buf & M3_ZYXDA))
	{
		if(HAL_OK != readRegI2C(LIS3MDL_I2C_ADDR, LIS3MDL_STATUS, &buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
			ret_status = HAL_ERROR;
	}

	//Read 6 bytes of data(2 for each X, Y and Z axes)
	if(HAL_OK != readRegI2C(LIS3MDL_I2C_ADDR, LIS3MDL_OUT_X_L , &raw_mag_data[0], sizeof(raw_mag_data), I2C_Handle))
		ret_status = HAL_ERROR;

	magn_data[0] = (int16_t)(((int16_t)raw_mag_data[1] << 8) | (int16_t)raw_mag_data[0]);
	magn_data[1] = (int16_t)(((int16_t)raw_mag_data[3] << 8) | (int16_t)raw_mag_data[2]);
	magn_data[2] = (int16_t)(((int16_t)raw_mag_data[5] << 8) | (int16_t)raw_mag_data[4]);

	return ret_status;
}



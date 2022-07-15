/**
 ******************************************************************************
 * @file           : lsm6dsox_i2c.c
 * @brief          : API for IMU LSM6DSOX [I2C communication protocol]
 ******************************************************************************
 **/

#include "lsm6dsox_i2c.h"


/**
 * @brief LSM6DSOX Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != readRegI2C(LSM6DSOX_I2C_ADDR, LSM6DSOX_WHOAMI , &buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;
	else if(buf == LSM6DSOX_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief LSM6DSOX Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	//	uint8_t buf;
	uint8_t val = 0;
	uint8_t ret_status;

	//Enable interrupt for accelerometer data ready on INT1 pin
	val = DSOX_INT1_DRDY_XL;
	if(HAL_OK != writeRegI2C(LSM6DSOX_I2C_ADDR, LSM6DSOX_INT1_CTRL,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//Enable interrupt for gyroscope data ready on INT2 pin
	val = DSOX_I3C_DISABLE;
	if(HAL_OK != writeRegI2C(LSM6DSOX_I2C_ADDR, LSM6DSOX_CTRL9_C,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//Disable I3C interface [IMPORTANT]
	val = DSOX_INT2_DRDY_GYRO;
	if(HAL_OK != writeRegI2C(LSM6DSOX_I2C_ADDR, LSM6DSOX_INT2_CTRL,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//Accelerometer ODR: 208 Hz
	//              Full scale selection: 4g
	//				High-resolution selection: Output from first stage dig filtering selected
	val = (dsox_odr_xl_208Hz | dsox_fs_xl_4g);
	if(HAL_OK != writeRegI2C(LSM6DSOX_I2C_ADDR, LSM6DSOX_CTRL1_XL,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//Gyroscope ODR: 208 Hz
	//              Full scale selection: 250 dps
	val = (dsox_odr_g_208Hz | dsox_fs_g_250);
	if(HAL_OK != writeRegI2C(LSM6DSOX_I2C_ADDR, LSM6DSOX_CTRL2_G,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//To clear the data ready interrupt, the data registers have to be read
#if(LSM6DSOX_DRDY_EN == 1)
	{
		int16_t dummy_data[3];
		lsm6dsoxI2CAccData(I2C_Handle ,dummy_data);
		lsm6dsoxI2CGyroData(I2C_Handle ,dummy_data);

	}
#endif

	return ret_status;

}

/**
 * @brief LSM6DSOX Sensor Accelerometer Data acquisition
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  Pointer to acceleration data (3 axes) (output)
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CAccData(I2C_HandleTypeDef I2C_Handle , int16_t acc_data[])
{
	//	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;
	uint8_t raw_data[6];

	//Status register - polling for new data
	//	while(!(buf & 0x01))
	//	{
	//		if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, LSM6DSOX_I2C_ADDR, LSM6DSOX_STATUS, 1, &buf, 1, 100))
	//			ret_status = HAL_ERROR;
	//	}

	//Read 6 bytes of data (2 bytes for each X, Y and Z axes)
	if(HAL_OK != readRegI2C(LSM6DSOX_I2C_ADDR, LSM6DSOX_OUTX_L_ACC,
			&raw_data[0], sizeof(raw_data), I2C_Handle))
		ret_status = HAL_ERROR;

	//Concatenate data
	acc_data[0] = (int16_t)(((int16_t)raw_data[1] << 8) | (int16_t)raw_data[0]);
	acc_data[1] = (int16_t)(((int16_t)raw_data[3] << 8) | (int16_t)raw_data[2]);
	acc_data[2] = (int16_t)(((int16_t)raw_data[5] << 8) | (int16_t)raw_data[4]);


	return ret_status;
}

/**
 * @brief LSM6DSOX Sensor Gyroscope Data acquisition
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  Pointer to gyroscope data (3 axes) (output)
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CGyroData(I2C_HandleTypeDef I2C_Handle , int16_t gyro_data[])
{
	//	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;
	uint8_t raw_data[6];

	//Status register - Polling for new data
	//	while(!(buf & 0x02))
	//	{
	//		if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, LSM6DSOX_I2C_ADDR, LSM6DSOX_STATUS, 1, &buf, 1, 100))
	//			ret_status = HAL_ERROR;
	//	}

	//Read 6 bytes of data(2 bytes for each X, Y and Z axes)
	if(HAL_OK != readRegI2C(LSM6DSOX_I2C_ADDR, LSM6DSOX_OUTX_L_GYRO,
			&raw_data[0], sizeof(raw_data), I2C_Handle))
		ret_status = HAL_ERROR;

	//Concatenate data
	gyro_data[0] = (int16_t)(((int16_t)raw_data[1] << 8) | (int16_t)raw_data[0]);
	gyro_data[1] = (int16_t)((int16_t)(raw_data[3] << 8) | (int16_t)raw_data[2]);
	gyro_data[2] = (int16_t)(((int16_t)raw_data[5] << 8) | (int16_t)raw_data[4]);

	return ret_status;

}

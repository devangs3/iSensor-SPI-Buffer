/**
 ******************************************************************************
 * @file           : lis2mdl_i2c.c
 * @brief          : API for magnetometer [I2C communication protocol]
 ******************************************************************************
 **/

#include "lis2mdl_i2c.h"


/**
 * @brief LIS2MDL Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlI2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != readRegI2C(LIS2MDL_I2C_ADDR, LIS2MDL_WHOAMI,
			&buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;
	else if(buf == LIS2MDL_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;
}


/**
 * @brief LIS2MDL Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlI2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t val = 0;
	uint8_t ret_status = HAL_OK;

	//Low Power Mode
	//Continuous mode
	//10 Hz ODR
	val = (m2_cont_mode | M2_LOW_PWR);
	if(HAL_OK != writeRegI2C(LIS2MDL_I2C_ADDR, LIS2MDL_CFG_A,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//LPF enabled
	val = M2_LPF;
	if(HAL_OK != writeRegI2C(LIS2MDL_I2C_ADDR, LIS2MDL_CFG_B,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief LIS2MDL Magnetic raw data acquisition
 * @param : uint8_t magn_data[]: Pointer to acquired magnetic data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlMagneticRawData(uint8_t magn_data[], I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf;
	uint8_t ret_status = HAL_OK;

	//Status register - Polling for new data
	while(!(buf & M2_ZYXDA))
	{
		if(HAL_OK != readRegI2C(LIS2MDL_I2C_ADDR, LIS2MDL_STATUS ,
				&buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
			ret_status = HAL_ERROR;
	}

	//Magnetic data - multi-byte read
	if(HAL_OK != readRegI2C(LIS2MDL_I2C_ADDR, LIS2MDL_OUT_X_L,
			&magn_data[0], 6 , I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief LIS2MDL Magnetic raw data acquisition
 * @param : uint8_t magn_data[]: Pointer to acquired magnetic data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlMagneticData(float mag_data[], I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf;
	uint8_t ret_status = HAL_OK;
	uint8_t mag_raw_data[3];

	//Status register - Polling for new data
	while(!(buf & M2_ZYXDA))
	{
		if(HAL_OK != readRegI2C(LIS2MDL_I2C_ADDR, LIS2MDL_STATUS ,
				&buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
			ret_status = HAL_ERROR;
	}

	//Magnetic data - multi-byte read
	if(HAL_OK != readRegI2C(LIS2MDL_I2C_ADDR, LIS2MDL_OUT_X_L,
			&mag_raw_data[0], 6 , I2C_Handle))
		ret_status = HAL_ERROR;

	lis2mdlI2CMagneticFinalData(mag_raw_data, sizeof(mag_raw_data), mag_data);

	return ret_status;
}

/**
 * @brief LIS2MDL Magnetic final data conversion
 * 		  Reference: Application Note AN5069
 * @param : uint8_t *magn_raw_data: Pointer to acquired magnetic data [input]
 * 			uint8_t magn_size: Size of array of the magnetic data
 * 			float magn_final_data[]: Pointer to final magnetic data
 * @retval ret_status: Error status
 */
uint8_t lis2mdlI2CMagneticFinalData(uint8_t *magn_raw_data , uint8_t magn_size , float magn_final_data[])
{
	uint8_t magn_data[6];

	float lis2mdl_sens = 1.50f;

	for (int i = 0 ; i < magn_size ; i++)
	{
		magn_data[i] = magn_raw_data[i];
	}

	//X axis raw concatenated data
	int16_t X_concat = (int16_t)((magn_data[1] << 8) | magn_data[0]);

	//Y axis raw concatenated data
	int16_t Y_concat = (int16_t)((magn_data[3] << 8) | magn_data[2]);

	//Z axis raw concatenated data
	int16_t Z_concat = (int16_t)((magn_data[5] << 8) | magn_data[4]);

	//Multiply the magnetic data with sensitivity
	magn_final_data[0] = (X_concat * lis2mdl_sens);
	magn_final_data[1] = (Y_concat * lis2mdl_sens);
	magn_final_data[2] = (Z_concat * lis2mdl_sens);

	return 0;
}

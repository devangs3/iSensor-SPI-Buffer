/**
 ******************************************************************************
 * @file           : aht20_i2c.c
 * @brief          : API for temperature and humidity [I2C communication protocol]
 ******************************************************************************
 **/

#include "aht20_i2c.h"


/**
 * @brief   Temperature and Humidity data acquisition
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval  ret_status: Error status
 */
uint8_t aht20TempHumiditySetup(I2C_HandleTypeDef I2C_Handle)
{
	//	uint8_t reg_addr;
	uint8_t buf[2] = {0};
	uint8_t ret_status = HAL_OK;
	//	float raw_data;

	//Wait for 40 milliseconds after power-on
	HAL_Delay(AHT20_POWERON_TIME);

	//	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, AHT20_I2C_ADDR, AHT20_STATUS, I2C_MEMADD_SIZE_8BIT, buf, I2C_MEMADD_SIZE_8BIT, 100))
	if(HAL_OK != readRegI2C(AHT20_I2C_ADDR, AHT20_STATUS, buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	if(!(buf[0] & AHT20_IS_CALIB))
	{
		//Write the initialization sequence
		buf[0] = 0x08u;
		buf[1] = 0x00u;

		//		if (HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, AHT20_I2C_ADDR, AHT20_INIT, I2C_MEMADD_SIZE_8BIT, buf, sizeof(buf), 100))
		if(HAL_OK != writeRegI2C(AHT20_I2C_ADDR, AHT20_INIT, buf, sizeof(buf), I2C_Handle))
			ret_status = HAL_ERROR;

		//Wait for 10 milliseconds for the sequence to be written
		HAL_Delay(AHT20_SEQ_TIME);
	}

	return ret_status;
}


/**
 * @brief   Temperature and Humidity data acquisition
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 			float: Pointer to acquired temperature data (in degC) [output]
 * 			float: Pointer to acquired humidity data (in RH) [output]
 * @retval  ret_status: Error status
 */
uint8_t aht20TempHumidityData(I2C_HandleTypeDef I2C_Handle , float *temp_C , float *humidity)
{
	uint8_t buf[2] = {0};
	uint8_t status_bit = 0;
	uint8_t ret_status = HAL_OK;
	uint8_t sensor_data[6];

	//Sequence to start measurement
	buf[0] = 0x33u;
	buf[1] = 0x00u;

	//	if (HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, AHT20_I2C_ADDR, AHT20_MEASURE, I2C_MEMADD_SIZE_8BIT, buf, sizeof(buf), 100))
	if(HAL_OK != writeRegI2C(AHT20_I2C_ADDR, AHT20_MEASURE, buf, sizeof(buf), I2C_Handle))
		ret_status = HAL_ERROR;

	//Wait for measurements to complete
	HAL_Delay(AHT20_CONV_TIME);

	while(status_bit & AHT20_STATUS_BIT)
	{
		//		if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, AHT20_I2C_ADDR, AHT20_STATUS, I2C_MEMADD_SIZE_8BIT, &status_bit, I2C_MEMADD_SIZE_8BIT, 100))
		if(HAL_OK != readRegI2C(AHT20_I2C_ADDR, AHT20_STATUS, &status_bit, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
			ret_status = HAL_ERROR;
	}

	//	if(HAL_OK != HAL_I2C_Master_Receive(&I2C_Handle, AHT20_I2C_ADDR, &sensor_data[0], sizeof(sensor_data), 100))
	if(HAL_OK != receiveI2C(AHT20_I2C_ADDR, &sensor_data[0], sizeof(sensor_data), I2C_Handle))
		ret_status = HAL_ERROR;

	//Raw data to final data [temperature and humidity]
	//	uint32_t h_data = ((sensor_data[1] << 8) | (sensor_data[2] << 4) | (sensor_data[3] >> 4));
	//
	//	*humidity = ((float)h_data / 0x100000) * 100;
	//
	//	uint32_t t_data = (((sensor_data[3] & 0x0F) << 16) | (sensor_data[4] << 8) | (sensor_data[5]));
	//
	//	*temp_C = (((float)t_data / 0x100000) * 200) - 50;

	return ret_status;
}

/**
 * @brief   Temperature and Humidity raw data acquisition
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 			uint8_t raw_sensor data[]: Returns raw sensor data
 * @retval  ret_status: Error status
 */
uint8_t aht20TempHumidityRawData(I2C_HandleTypeDef I2C_Handle , uint8_t raw_data[])
{
	uint8_t buf[2] = {0};
	uint8_t status_bit = 0;
	uint8_t ret_status = HAL_OK;

	//Sequence to start measurement
	buf[0] = 0x33u;
	buf[1] = 0x00u;

	if(HAL_OK != writeRegI2C(AHT20_I2C_ADDR, AHT20_MEASURE, buf, sizeof(buf), I2C_Handle))
		ret_status = HAL_ERROR;

	//Wait for measurements to complete
	HAL_Delay(AHT20_CONV_TIME);

	while(status_bit & AHT20_STATUS_BIT)
	{
		if(HAL_OK != readRegI2C(AHT20_I2C_ADDR, AHT20_STATUS, &status_bit, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
			ret_status = HAL_ERROR;
	}
	if(HAL_OK != receiveI2C(AHT20_I2C_ADDR, &raw_data[0], 6, I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief   Temperature data acquisition
 * @param : uint8_t raw_data[] : raw temperature data
 * @retval  float temp: Temperature data
 * 			ret_status: Error status
 */
uint8_t aht20TempData(float *temp , I2C_HandleTypeDef I2C_Handle)
{
	uint8_t raw_data[6];
	uint8_t ret_status = HAL_OK;
	if (HAL_OK != aht20TempHumidityRawData(I2C_Handle, raw_data))
		ret_status = HAL_ERROR;

	uint32_t t_data = (((raw_data[3] & 0x0F) << 16) | (raw_data[4] << 8) | (raw_data[5]));

	*temp = (((float)t_data / 0x100000) * 200) - 50;

	return ret_status;
}

/**
 * @brief   Humiidty data acquisition
 * @param : uint8_t raw_data[] : raw temperature data
 * @retval  float temp: Temperature data
 * 			ret_status: Error status
 */
uint8_t aht20HumidityData(float *humidity, I2C_HandleTypeDef I2C_Handle)
{
	uint8_t raw_data[6];
	uint8_t ret_status = HAL_OK;
	if(HAL_OK != aht20TempHumidityRawData(I2C_Handle, raw_data))
		ret_status = HAL_ERROR;
	//Raw data to final data
	uint32_t h_data = ((raw_data[1] << 8) | (raw_data[2] << 4) | (raw_data[3] >> 4));

	*humidity = ((float)h_data / 0x100000) * 100;

	return ret_status;
}




/**
 * @brief   Soft reset
 * @param : I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval  ret_status: Error status
 */
uint8_t aht20SoftReset(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;
	uint8_t val = 0;

	val = AHT20_SOFT_RESET;
	//	if(HAL_OK != HAL_I2C_Master_Transmit(&I2C_Handle, AHT20_I2C_ADDR, AHT20_SOFT_RESET, I2C_MEMADD_SIZE_8BIT, 100))
	if(HAL_OK != transmitI2C(AHT20_I2C_ADDR, &val , sizeof(val), I2C_Handle))
		ret_status = HAL_ERROR;

	//Wait for 20 milliseconds for soft reset to complete
	HAL_Delay(AHT20_SOFT_RESET_TIME);

	return ret_status;
}

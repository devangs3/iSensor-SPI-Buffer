/**
 ******************************************************************************
 * @file           : bme680_i2c.c
 * @brief          : API for pressure, temperature and gas [I2C communication protocol]
 ******************************************************************************
 **/

#include "bme680_i2c.h"

Calibration_data_n calib_data;

static uint8_t bme680GetCalib(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t reg_addr;
	uint8_t ret_status;
	uint8_t calib_raw_data[6] = {0};

	reg_addr = BME680_TEMP_CALIB1_MSB;

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, BME680_I2C_ADDR, reg_addr, sizeof(reg_addr), &calib_raw_data[0], 2, 100))
		ret_status = HAL_ERROR;

	reg_addr = BME680_TEMP_CALIB2_MSB;

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, BME680_I2C_ADDR, reg_addr, sizeof(reg_addr), &calib_raw_data[2], 3, 100))
		ret_status = HAL_ERROR;

	calib_data.temp_p1 = (uint16_t)((calib_raw_data[0] << 8) | (calib_raw_data[1]));

	calib_data.temp_p2 = (int16_t)((calib_raw_data[2] << 8) | (calib_raw_data[3]));

	calib_data.temp_p3 = (int8_t)calib_raw_data[4];

	return ret_status;

}
/**
 * @brief BME680 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t bme680I2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, BME680_I2C_ADDR, BME680_WHOAMI, 1 , &buf, 1, 100))
		ret_status = HAL_ERROR;
	else if(buf == BME680_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;

}

uint8_t bme680I2CReset(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf;
	uint8_t ret_status = HAL_OK;

	//Over-sampling - humidity (over-sampling X 1)
	buf = 0xB6;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, BME680_I2C_ADDR, 0xE0, 1, &buf, 1, 100))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief BME680 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t bme680I2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf;
	uint8_t ret_status = HAL_OK;

	//Over-sampling - humidity (over-sampling X 1)
	buf = 0x01;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, BME680_I2C_ADDR, BME680_CTRL_HUM, 1, &buf, 1, 100))
		ret_status = HAL_ERROR;

	//Over-sampling for temperature - (over-sampling X 2)
	//and pressure (over-sampling X 16)
	buf = 0x54;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, BME680_I2C_ADDR, BME680_CTRL_MEAS, 1, &buf, 1, 100))
		ret_status = HAL_ERROR;

	//Enabled gas conversions
	buf = 0x10;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, BME680_I2C_ADDR, BME680_CTRL_GAS_1, 1, &buf, 1, 100))
		ret_status = HAL_ERROR;

	if(HAL_OK != bme680GetCalib(I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief BME680 raw data acquisition
 * @param : uint8_t bme680_data[]: Pointer to acquired temperature, pressure,
 * 								    humidity and gas resistance data [output]
 * 	     	I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval  ret_status: Error status
 */
uint8_t bme680RawData(uint8_t bme680_data[], I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;
	uint8_t reg_addr;
	uint8_t forced_mode;
	uint8_t temp_data[6];


	if(HAL_OK != bme680I2CReset(I2C_Handle))
		return HAL_ERROR;

	HAL_Delay(10);

	forced_mode = 0x55;
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, BME680_I2C_ADDR, BME680_CTRL_MEAS, 1, &forced_mode, 1, 100))
		ret_status = HAL_ERROR;
	else
	{
		reg_addr = BME680_STATUS;

		while(!(buf == 0x80))
		{
			if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, BME680_I2C_ADDR, reg_addr, sizeof(reg_addr), &buf, 1, 100))
				ret_status = HAL_ERROR;
		}

		buf = 0;

		reg_addr = BME680_TEMP_MSB;

		if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, BME680_I2C_ADDR, reg_addr, sizeof(reg_addr), &temp_data[0], 3, 100))
			ret_status = HAL_ERROR;

		bme680FinalData(temp_data);

	}

	return ret_status;
}

/**
 * @brief BME680 Final data conversion
 * 		  Reference: Data-sheet
 * @param : uint8_t *bme680_raw_data: Pointer to acquired magnetic data [input]
 *
 * @retval ret_status: Final Data
 */
int16_t bme680FinalData(uint8_t *bme680_raw_data)
{
	int64_t var1 , var2 , var3;
	int32_t tfine;
	int16_t temp_comp;

	uint32_t temp_data1 = (uint32_t)(((uint32_t)bme680_raw_data[0] << 12) | ((uint32_t)bme680_raw_data[1] << 4)|
			((uint32_t)bme680_raw_data[2] >> 4));

	var1 = ((int32_t)temp_data1 >> 3) - ((int32_t)calib_data.temp_p1 << 1);

	var2 = (var1 * (int32_t)calib_data.temp_p2) >> 11;

	var3 = ((var1 >> 1) * (var1 >> 1)) >> 12;

	var3 = ((var3) * ((int32_t)calib_data.temp_p3 << 4)) >> 14;

	tfine = (int32_t)(var2 + var3);

	temp_comp = (int16_t)(((tfine * 5) + 128) >> 8);

	return temp_comp;

}





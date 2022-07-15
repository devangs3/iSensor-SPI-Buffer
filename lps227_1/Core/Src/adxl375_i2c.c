/**
 ******************************************************************************
 * @file           : axdl375_i2c.c
 * @brief          : API for accelerometer [I2C communication protocol]
 ******************************************************************************
 **/

#include"adxl375_i2c.h"

/**
 * @brief ADXl375 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375I2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != readRegI2C(ADXL375_I2C_ADDR, ADXL375_WHOAMI , &buf, sizeof(buf),
			I2C_Handle))
		ret_status = HAL_ERROR;
	else if(buf == ADXL375_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief ADXL375 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375I2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;
	uint8_t val = 0;

	//Standby mode
	val = 0x00u;
	if(HAL_OK != writeRegI2C(ADXL375_I2C_ADDR, ADXL375_POWER_CTL, &val,
			I2C_MEMADD_SIZE_8BIT , I2C_Handle))
		ret_status = HAL_ERROR;

	//100 kHz -> 200 Hz bandwidth
	val = a375_output_freq_200Hz;
	if(HAL_OK != writeRegI2C(ADXL375_I2C_ADDR, ADXL375_BW_RATE, &val,
			I2C_MEMADD_SIZE_8BIT , I2C_Handle))
		ret_status = HAL_ERROR;

	//Interrupt pins active low
	//Data is right shifted
	val = (a375_justify_rightLSB | a375_INT_PIN_ACT_LOW);
	if(HAL_OK != writeRegI2C(ADXL375_I2C_ADDR, ADXL375_DATA_FMT, &val,
			I2C_MEMADD_SIZE_8BIT , I2C_Handle))
		ret_status = HAL_ERROR;

	//Data ready signal to INT1 pin
	//Rest of the interrupts to INT2 pin
	val = (A375_INT2_OVERRUN |
			A375_INT2_ACTIVITY | A375_INT2_DOUBLE_SHOCK | A375_INT2_SINGLE_SHOCK |
			A375_INT2_WATERMARK | A375_INT2_INACTIVITY);
	if(HAL_OK != writeRegI2C(ADXL375_I2C_ADDR, ADXL375_INT_MAP, &val,
			I2C_MEMADD_SIZE_8BIT ,
			I2C_Handle))
		ret_status = HAL_ERROR;

	//Enable interrupts for data ready
	val = A375_DATA_READY;
	if(HAL_OK != writeRegI2C(ADXL375_I2C_ADDR, ADXL375_INT_ENABLE, &val,
			I2C_MEMADD_SIZE_8BIT ,
			I2C_Handle))
		ret_status = HAL_ERROR;

	//Measurement mode
	val = A375_MEASURE;
	if(HAL_OK != writeRegI2C(ADXL375_I2C_ADDR, ADXL375_POWER_CTL, &val
			, I2C_MEMADD_SIZE_8BIT ,I2C_Handle))
		ret_status = HAL_ERROR;

#if (ADXL375_DRDY_EN == 1)
	//TO clear the data ready interrupt, the data registers have to be read
	//Refer ADXL375 data-sheet Page 13
	int16_t dummy_data[3];
	if(HAL_OK != adxl375I2CAccData(dummy_data, I2C_Handle))
		ret_status = HAL_ERROR;
#endif

	return ret_status;

}

/**
 * @brief ADXL375 Acceleration data acquisition
 * @param : int16_t acc_data[]: Pointer to acquired magnetic data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375I2CAccData(int16_t acc_data[], I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;
	uint8_t acc_raw_data[6];

	if(HAL_OK != readRegI2C(ADXL375_I2C_ADDR, ADXL375_DATA_X_0, &acc_raw_data[0],
			sizeof(acc_raw_data), I2C_Handle))
		ret_status = HAL_ERROR;

	for(int i = 0; i < 3 ; i++)
	{
		acc_data[i] = (int16_t)(((int16_t) acc_raw_data[(2*i) + 1] << 8)
				| ((int16_t) acc_raw_data[(2*i)]));
	}

	return ret_status;
}

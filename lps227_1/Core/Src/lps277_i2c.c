/**
 ******************************************************************************
 * @file           : lps277_i2c.c
 * @brief          : API for pressure calculations [I2C communication protocol]
 ******************************************************************************
 **/

#include "lps277_i2c.h"


/**
 * @brief LPS27 Device Identification
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps227I2CWhoami(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t buf = 0;
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != readRegI2C(LPS277_I2C_ADDR, LPS277_WHOAMI, &buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;
	else if(buf == LPS277_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief LPS27 Sensor Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277I2CSetup(I2C_HandleTypeDef I2C_Handle)
{
	//	uint8_t buf;
	uint8_t val = 0;
	uint8_t ret_status = HAL_OK;

	//Enable pull ups for SDA, SCL lines
	//Enable I2C interface
	val = (LPS_SDO_PU_EN | LPS_SDA_PU_EN);
	if(HAL_OK != writeRegI2C(LPS277_I2C_ADDR, LPS277_IF_CTRL
			,&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//ODR = 25 Hz
	//BDU enabled
	//LPF enabled -> ODR/20
	val = (lps_25Hz | LPS_BDU | lps_lpf_odr_20);
	if(HAL_OK != writeRegI2C(LPS277_I2C_ADDR, LPS277_CTRL1,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//Enable the data ready signal hardware pin to trigger when new data set available
	//The interrupt is active high.
	val = LPS_DRDY;
	if(HAL_OK != writeRegI2C(LPS277_I2C_ADDR, LPS277_CTRL3,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	//To clear the data ready interrupt, the data registers have to be read
#if(LPS27_DRDY_EN == 1)
	{
		uint8_t dummy_data[3];
		lps277I2CPressureRawData(dummy_data , I2C_Handle);
	}
#endif

	return ret_status;

}

/**
 * @brief LPS27 Pressure raw data acquisition
 * @param : uint8_t pres_data[]: Pointer to acquired pressure data [output]
 * 	     I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277I2CPressureRawData(uint8_t pres_data[], I2C_HandleTypeDef I2C_Handle)
{
	//	uint8_t buf;
	uint8_t ret_status = HAL_OK;

	//	reg_addr = LPS277_STATUS;

	//Status register - Polling for new data
	//	while(!(buf & LPS_P_DA))
	//	{
	//		//		if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, LPS277_I2C_ADDR, reg_addr, sizeof(reg_addr), &buf, 1, 100))
	//		if(HAL_OK != readRegI2C(LPS277_I2C_ADDR, LPS277_STATUS,
	//				&buf, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
	//			ret_status = HAL_ERROR;
	//	}

	//LSB data
	if(HAL_OK != readRegI2C(LPS277_I2C_ADDR, LPS277_PRESS_LOW,
			&pres_data[0], 3, I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;


}

/**
 * @brief LPS27 Pressure final data conversion
 * 		  Concatenate the 24 bit data acquired from the data registers and divide by the sensitivity to get the pressure in hPa
 * 		  Reference: Application Note AN5837
 * @param : uint8_t *pres_raw_data: Pointer to acquired pressure data [input]
 * 			uint8_t pres_size: Size of array of the pressure data
 * @retval ret_status: Error status
 */
uint32_t lps277I2CPressureFinalData(uint8_t *pres_raw_data , uint8_t pres_size)
{
	uint32_t pres_final_data;

	uint8_t pres_data[3];

	for (int i = 0 ; i < pres_size ; i++)
	{
		pres_data[i] = pres_raw_data[i];
	}

	//Concatenate the data into a 24 bit number
	pres_final_data = ((pres_data[2] << 16) | (pres_data[1] << 8) | (pres_data[0]));

	//Divide the value by sensitivity
	pres_final_data = pres_final_data/4096u;

	return pres_final_data;
}

/**
 * @brief LPS27 Sensor De-initialization [I2C]
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277I2CDeinit(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t val = 0;
	uint8_t ret_status = HAL_OK;

	//Enable both I2C and SPI peripherals
	val  = 0x00u;
	if(HAL_OK != writeRegI2C(LPS277_I2C_ADDR, LPS277_IF_CTRL,
			&val, I2C_MEMADD_SIZE_8BIT, I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;

}

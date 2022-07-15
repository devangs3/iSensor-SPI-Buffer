/**
 ******************************************************************************
 * @file           : lsm6dso32_spi.c
 * @brief          : API for acceleration calculations [SPI communication protocol]
 ******************************************************************************
 **/

#include "lsm6dso32_spi.h"
#include "string.h"

/**
 * @brief LSM6DSO32 Device Identification
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32SPIWhoami(SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;
	uint8_t rx_buf[2];

	if(HAL_OK != readRegSPI(LSM6DSO32_WHOAMI, rx_buf, SPI_Handle))
		ret_status  = HAL_ERROR;
	else if(rx_buf[1] == LSM6DSO32_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;


	return ret_status;
}


/**
 * @brief LSM6DSO32 Sensor Initialization
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32SPISetup(SPI_HandleTypeDef SPI_Handle)
{

	uint8_t ret_status = HAL_OK;

	//Enable data ready interrupt for acceleration on INT1 pin
	if(HAL_OK != writeRegSPI(LSM6DSO32_INT1_CTRL,
			DSO32_INT1_DRDY_XL, SPI_Handle))
		ret_status = HAL_ERROR;

	//Enable data ready interrupt for gyroscope on INT2 pin
	if(HAL_OK != writeRegSPI(LSM6DSO32_INT2_CTRL,
			DSO32_INT2_DRDY_GYRO, SPI_Handle))
		ret_status = HAL_ERROR;

	//Disable I3C interface
	if(HAL_OK != writeRegSPI(LSM6DSO32_CTRL9_C,
			DSO32_I3C_DISABLE, SPI_Handle))
		ret_status = HAL_ERROR;

	//Accelerometer ODR: 208 Hz
	//Full scale selection: 2g
	if(HAL_OK != writeRegSPI(LSM6DSO32_CTRL1_XL,
			(dso32_odr_xl_208Hz | dso32_fs_xl_4g), SPI_Handle))
		ret_status = HAL_ERROR;

	//Gyroscope ODR: 208 Hz
	//Full scale selection: 250 dps
	if(HAL_OK != writeRegSPI(LSM6DSO32_CTRL2_G,
			(dso32_odr_g_208Hz | dso32_fs_g_250), SPI_Handle))
		ret_status = HAL_ERROR;

	//To clear the data ready interrupt, the data registers have to be read
#if(LSM6DSO32_DRDY_EN == 1)
	{
		int16_t dummy_data[3];
		lsm6dso32SPIAccData(SPI_Handle , dummy_data);
		lsm6dso32SPIGyroData(SPI_Handle , dummy_data);

	}
#endif

	return ret_status;

}

/**
 * @brief LSM6DSO32 Acceleration data acquisition
 * @param : int16_t acc_data[]: Pointer to acquired acceleration data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32SPIAccData(SPI_HandleTypeDef SPI_Handle , int16_t acc_data[])
{
	uint8_t rx_buf[2];
	int8_t temp_data[8];
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTX_L_ACC, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[0] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTX_H_ACC, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[1] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTY_L_ACC, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[2] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTY_H_ACC, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[3] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTZ_L_ACC, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[4] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTZ_H_ACC, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[5] = (int8_t)rx_buf[1];

	acc_data[0] = (int16_t)((temp_data[1] << 8) | temp_data[0]);
	acc_data[1] = (int16_t)((temp_data[3] << 8) | temp_data[2]);
	acc_data[2] = (int16_t)((temp_data[5] << 8) | temp_data[4]);

	return ret_status;

}

/**
 * @brief LSM6DSO32 Gyroscope data acquisition
 * @param : int16_t gyro_data[]: Pointer to acquired acceleration data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dso32SPIGyroData(SPI_HandleTypeDef SPI_Handle , int16_t gyro_data[])
{
	//	uint8_t tx_buf[2];
	uint8_t rx_buf[2];
	int8_t temp_data[8];
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTX_L_GYRO, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[0] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTX_H_GYRO, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[1] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTY_L_GYRO, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[2] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTY_H_GYRO, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[3] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTZ_L_GYRO, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[4] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(LSM6DSO32_OUTZ_H_GYRO, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		temp_data[5] = (int8_t)rx_buf[1];

	gyro_data[0] = (int16_t)((temp_data[1] << 8) | temp_data[0]);
	gyro_data[1] = (int16_t)((temp_data[3] << 8) | temp_data[2]);
	gyro_data[2] = (int16_t)((temp_data[5] << 8) | temp_data[4]);

	return ret_status;

}

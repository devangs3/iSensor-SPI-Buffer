/**
 ******************************************************************************
 * @file           : adxl375_spi.c
 * @brief          : API for acceleration calculations [SPI communication protocol]
 ******************************************************************************
 **/

#include "adxl375_spi.h"
#include "string.h"

/**
 * @brief ADXL375 Device Identification
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375SPIWhoami(SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;
	uint8_t rx_buf[2];

	if(HAL_OK != readRegSPI(ADXL375_WHOAMI, rx_buf, SPI_Handle))
		ret_status  = HAL_ERROR;
	else if(rx_buf[1] == ADXL375_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief ADXL375 Sensor Initialization
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375SPISetup(SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;

	//Standby mode
	if(HAL_OK != writeRegSPI(ADXL375_POWER_CTL, 00u, SPI_Handle))
		ret_status = HAL_ERROR;

	//	//Set baud rate to 1600 Hz
	if(HAL_OK != writeRegSPI(ADXL375_BW_RATE, a375_output_freq_1600Hz, SPI_Handle))
		ret_status = HAL_ERROR;

	//Interrupt pins active low
	//Data is right shifted
	if(HAL_OK != writeRegSPI(ADXL375_DATA_FMT, (a375_justify_rightLSB | a375_INT_PIN_ACT_LOW), SPI_Handle))
		ret_status = HAL_ERROR;

	//Data ready signal to INT1 pin
	//Rest of the interrupts to INT2 pin
	if(HAL_OK != writeRegSPI(ADXL375_INT_MAP, (A375_INT2_OVERRUN |
			A375_INT2_ACTIVITY | A375_INT2_DOUBLE_SHOCK | A375_INT2_SINGLE_SHOCK |
			A375_INT2_WATERMARK | A375_INT2_INACTIVITY), SPI_Handle))
		ret_status = HAL_ERROR;

	//Enable interrupts for data ready
	if(HAL_OK != writeRegSPI(ADXL375_INT_ENABLE, A375_DATA_READY, SPI_Handle))
		ret_status = HAL_ERROR;

	//Measurement mode
	if(HAL_OK != writeRegSPI(ADXL375_POWER_CTL, A375_MEASURE, SPI_Handle))
		ret_status = HAL_ERROR;

#if (ADXL375_DRDY_EN == 1)
	//TO clear the data ready interrupt, the data registers have to be read
	//Refer ADXL375 data-sheet Page 13
	int16_t dummy_data[3];
	if(HAL_OK != adxl375SPIAccData(SPI_Handle, dummy_data))
		ret_status = HAL_ERROR;
#endif

	return ret_status;

}


/**
 * @brief ADXL375 Acceleration raw data acquisition
 * @param : int16_t acc_data[]: Pointer to acquired acceleration data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t adxl375SPIAccData(SPI_HandleTypeDef SPI_Handle , int16_t acc_data[])
{
	uint8_t rx_buf[2];
	int8_t acc_raw_data[8];
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != readRegSPI(ADXL375_DATA_X_0, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		acc_raw_data[0] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(ADXL375_DATA_X_1, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		acc_raw_data[1] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(ADXL375_DATA_Y_0, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		acc_raw_data[2] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(ADXL375_DATA_Y_1, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		acc_raw_data[3] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(ADXL375_DATA_Z_0, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		acc_raw_data[4] = (int8_t)rx_buf[1];

	if(HAL_OK != readRegSPI(ADXL375_DATA_Z_1, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		acc_raw_data[5] = (int8_t)rx_buf[1];

	acc_data[0] = (int16_t)((acc_raw_data[1] << 8) | acc_raw_data[0]);
	acc_data[1] = (int16_t)((acc_raw_data[3] << 8) | acc_raw_data[2]);
	acc_data[2] = (int16_t)((acc_raw_data[5] << 8) | acc_raw_data[4]);

	return ret_status;

}


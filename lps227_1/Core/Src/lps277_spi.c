/**
 ******************************************************************************
 * @file           : lps277_spi.c
 * @brief          : API for pressure calculations [SPI communication protocol]
 ******************************************************************************
 **/

#include "lps277_spi.h"

extern volatile uint8_t data_rdy_flag;

/**
 * @brief LPS27 Device Identification
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps227SPIWhoami(SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;
	uint8_t rx_buf[2];

	if(HAL_OK != readRegSPI(LPS277_WHOAMI, rx_buf, SPI_Handle))
		ret_status  = HAL_ERROR;
	else if(rx_buf[1] == LPS277_DEV_ID)
		ret_status = HAL_OK;
	else
		ret_status = HAL_ERROR;


	return ret_status;
}


/**
 * @brief LPS27 Sesnsor Initialization
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277SPISetup(SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;


	//Enable SPI interface
	if(HAL_OK != writeRegSPI(LPS277_IF_CTRL,
			(LPS_I2C_DISABLE | LPS_I3C_DISABLE | LPS_PD_DIS_INT1), SPI_Handle))
		ret_status = HAL_ERROR;

	//ODR = 10 Hz
	//BDU enabled
	//LPF enabled -> ODR/20
	if(HAL_OK != writeRegSPI(LPS277_CTRL1,
			(lps_10Hz | LPS_BDU | lps_lpf_odr_20), SPI_Handle))
		ret_status = HAL_ERROR;

	//Enable the data ready signal hardware pin to trigger when new data set available
	//The interrupt is active high.
	if(HAL_OK != writeRegSPI(LPS277_CTRL3, LPS_DRDY, SPI_Handle))
		ret_status = HAL_ERROR;

	//To clear the data ready interrupt, the data registers have to be read
#if(LPS27_DRDY_EN == 1)
	{
		uint8_t dummy_data[3];
		lps277SPIPressureRawData(dummy_data , SPI_Handle);
	}
#endif

	return ret_status;

}


/**
 * @brief LPS27 Pressure raw data acquisition
 * @param : uint8_t pres_data[]: Pointer to acquired pressure data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * 			uint8_t *conv_flag: User-defined flag to check if data ready pin was triggered
 * @retval ret_status: Error status
 */
uint8_t lps277SPIPressureRawData(uint8_t pres_data[], SPI_HandleTypeDef SPI_Handle)
{
	//	uint8_t tx_buf[2];
	uint8_t rx_buf[2] = {0 , 0};
	uint8_t ret_status = HAL_OK;


	//Wait for new pressure data [Polling method]
	//	tx_buf[0] = LPS277_STATUS | SPI_READ_BIT;
	//	tx_buf[1] = 0;

	//	if(HAL_OK != HAL_SPI_TransmitReceive(&SPI_Handle, tx_buf, rx_buf, 2, 500))
	//		ret_status = HAL_ERROR;
	//	while(!((rx_buf[1] & 0x01) == 0x01))
	//	{
	//		if(HAL_OK != HAL_SPI_TransmitReceive(&SPI_Handle, tx_buf, rx_buf, 2, 500))
	//			ret_status = HAL_ERROR;
	//	}

	//LSB data
	if(HAL_OK != readRegSPI(LPS277_PRESS_LOW, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		pres_data[0] = rx_buf[1];

	//Middle data
	if(HAL_OK != readRegSPI(LPS277_PRESS_MIDDLE, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		pres_data[1] = rx_buf[1];

	//MSB data
	if(HAL_OK != readRegSPI(LPS277_PRESS_HIGH, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		pres_data[2] = rx_buf[1];

	return ret_status;

}

/**
 * @brief LPS27 Pressure data acquisition
 * @param : uint32_t pres_data: Pointer to acquired pressure data [output]
 * 			SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * 			uint8_t *conv_flag: User-defined flag to check if data ready pin was triggered
 * @retval ret_status: Error status
 */
uint8_t lps277SPIPressureData(uint32_t *pres_data, SPI_HandleTypeDef SPI_Handle)
{
	//	uint8_t tx_buf[2];
	uint8_t rx_buf[2] = {0 , 0};
	uint8_t ret_status = HAL_OK;
	uint8_t pres_raw_data[3];

	//Wait for new pressure data [Polling method]
	//	tx_buf[0] = LPS277_STATUS | SPI_READ_BIT;
	//	tx_buf[1] = 0;

	//	if(HAL_OK != HAL_SPI_TransmitReceive(&SPI_Handle, tx_buf, rx_buf, 2, 500))
	//		ret_status = HAL_ERROR;
	//	while(!((rx_buf[1] & 0x01) == 0x01))
	//	{
	//		if(HAL_OK != HAL_SPI_TransmitReceive(&SPI_Handle, tx_buf, rx_buf, 2, 500))
	//			ret_status = HAL_ERROR;
	//	}

	//LSB data
	if(HAL_OK != readRegSPI(LPS277_PRESS_LOW, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		pres_raw_data[0] = rx_buf[1];

	//Middle data
	if(HAL_OK != readRegSPI(LPS277_PRESS_MIDDLE, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		pres_raw_data[1] = rx_buf[1];

	//MSB data
	if(HAL_OK != readRegSPI(LPS277_PRESS_HIGH, rx_buf, SPI_Handle))
		ret_status = HAL_ERROR;
	else
		pres_raw_data[2] = rx_buf[1];

	*pres_data = lps277SPIPressureFinalData(pres_raw_data, sizeof(pres_raw_data));

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
uint32_t lps277SPIPressureFinalData(uint8_t *pres_raw_data , uint8_t pres_size)
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
 * @brief LPS27 Sesnsor De-initialization
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277SPIDeinit(SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;


	//Enable both I2C and SPI interface
	if(HAL_OK != writeRegSPI(LPS277_IF_CTRL, 0x00u, SPI_Handle))
		ret_status = HAL_ERROR;

	return ret_status;
}

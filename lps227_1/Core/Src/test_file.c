/**
 ******************************************************************************
 * @file           : test_file.c
 * @brief          : API for test functions
 ******************************************************************************
 **/

/**
 * @brief Test function for testing individual sensors
 * @param void * output: Output for sensor
 * @retval ret_status: Error status
 */
#include "test_file.h"
#include "sensor_headers.h"
#include "set_drdy.h"

uint8_t test_fnc(void *output)
{
	uint8_t ret_status = HAL_OK;

	return ret_status;
}


/**
 * @brief  Initializes all sensors to test
 * @param  I2C_HandleTypeDef I2C_Periph1: The I2C1 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph2: The I2C2 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph3: The I2C3 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph4: The I2C4 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph1: The SPI1 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph2: The SPI2 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph3: The SPI3 peripheral on the micro-controller
 * 		   ADC_HandleTypeDef ADC_Perpiph1: The ADC4 peripheral on the micro-controller
 * @retval Error status
 */
uint8_t sensorsInit(I2C_HandleTypeDef I2C_Periph1 , I2C_HandleTypeDef I2C_Periph2 ,
		I2C_HandleTypeDef I2C_Periph3 , I2C_HandleTypeDef I2C_Periph4 ,
		SPI_HandleTypeDef SPI_Periph1 , SPI_HandleTypeDef SPI_Periph2 ,
		SPI_HandleTypeDef SPI_Periph3 , ADC_HandleTypeDef ADC_Perpiph1 )
{
	uint8_t ret_status = HAL_OK;

	//Get an instance of the pointer of structure holding the
	//data-ready flags
	getFlagPtr();

	//LIS3MDL initialization
	if(HAL_OK != lis3mdlI2CWhoami(I2C_Periph1))
		ret_status = HAL_ERROR;
	if(HAL_OK != lis3mdlI2CSetup(I2C_Periph1))
		ret_status = HAL_ERROR;

	//LSMDSOX initialization
	if(HAL_OK != lsm6dsoxI2CWhoami(I2C_Periph1))
		ret_status = HAL_ERROR;
	if(HAL_OK != lsm6dsoxI2CSetup(I2C_Periph1))
		ret_status = HAL_ERROR;

	//AHT20 initialization
	if(HAL_OK != aht20TempHumiditySetup(I2C_Periph2))
		ret_status = HAL_ERROR;

	//LIS2MDL initialization
	if(HAL_OK != lis2mdlI2CWhoami(I2C_Periph3))
		ret_status = HAL_ERROR;
	if(HAL_OK != lis2mdlI2CSetup(I2C_Periph3))
		ret_status = HAL_ERROR;

	//BH1750 initialization
	if(HAL_OK != bh1750I2CSetup(I2C_Periph4))
		ret_status = HAL_ERROR;

	//LPS27HHW initialization
	if(HAL_OK != lps227SPIWhoami(SPI_Periph1))
		ret_status = HAL_ERROR;
	if(HAL_OK != lps277SPISetup(SPI_Periph1))
		ret_status = HAL_ERROR;

	//LSM6DS032 initialization
	if(HAL_OK != lsm6dso32SPIWhoami(SPI_Periph2))
		ret_status = HAL_ERROR;
	if(HAL_OK != lsm6dso32SPISetup(SPI_Periph2))
		ret_status = HAL_ERROR;

	//ADXL375 initialization
	if(HAL_OK != adxl375SPIWhoami(SPI_Periph3))
		ret_status = HAL_ERROR;
	if(HAL_OK != adxl375SPISetup(SPI_Periph3))
		ret_status = HAL_ERROR;

	//Trigger ADC connected to the internal temperature sensor channel
	triggerADCIRQ(ADC_Perpiph1);

	return ret_status;

}

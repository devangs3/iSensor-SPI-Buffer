/**
 ******************************************************************************
 * @file           : comm_abstraction.c
 * @brief          : API for abstraction layer for communication [I2C and SPI]
 ******************************************************************************
 **/

#include "comm_abstraction.h"

/**
 * @brief Abstraction layer for I2C register write
 * @param : uint8_t reg: Register to write value
 *  		uint8_t value: Value to write to the register
 *  		uint8_t data_bytes: Amount of data to be written
 *  		uint8_ dev_addr: Slave address for I2C device
 * 	        I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t writeRegI2C(uint8_t dev_addr ,uint8_t reg , uint8_t *value , uint8_t data_bytes , I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;
	//	uint8_t clr_bit = CLR_REG;

	//Clear the register before writing the actual value
	//	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, dev_addr, reg, I2C_MEMADD_SIZE_8BIT, &clr_bit, I2C_MEMADD_SIZE_8BIT, I2C_TIMEOUT))
	//		ret_status = HAL_ERROR;

	//Write the desired value to the register
	if(HAL_OK != HAL_I2C_Mem_Write(&I2C_Handle, dev_addr, reg, I2C_MEMADD_SIZE_8BIT, value, data_bytes, I2C_TIMEOUT))
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief Abstraction layer for SPI register write
 * @param : uint8_t reg: Register to write value
 *  		uint8_t value: Value to write to the register
 *  		SPI_HandleTypeDef SPI_Handle: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t writeRegSPI(uint8_t reg , uint8_t value , SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;
	uint8_t tx_buf[SPI_TX_SIZE];
	tx_buf[0] = tx_buf[1] = (CLR_REG | SPI_WR_BIT) ;

	//Clear the register before writing to the register
	if(HAL_OK != HAL_SPI_Transmit(&SPI_Handle, tx_buf, SPI_TX_SIZE, SPI_TIMEOUT))
		ret_status = HAL_ERROR;

	tx_buf[0] = (reg | SPI_WR_BIT);
	tx_buf[1] = value;

	//Write the value to the SPI register
	if(HAL_OK != HAL_SPI_Transmit(&SPI_Handle, tx_buf , SPI_TX_SIZE, SPI_TIMEOUT))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief Abstraction layer for I2C register read
 * @param : uint8_t reg: Register to write value
 *  		uint8_t *value: Value to read from the register [Output]
 *  		uint8_t data_bytes: Amount of data to be read
 *  		uint8_t dev_addr: Slave address for I2C device
 *  		I2C_HandleTypeDef I2C_Handle: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t readRegI2C(uint8_t dev_addr ,uint8_t reg , uint8_t *value , uint8_t data_bytes ,  I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;

	//Read the specified number of bytes from the device
	if(HAL_OK != HAL_I2C_Mem_Read(&I2C_Handle, dev_addr, reg, I2C_MEMADD_SIZE_8BIT, value, data_bytes, I2C_TIMEOUT))
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief Abstraction layer for SPI register read
 * @param : uint8_t reg: Register to write value
 *  		uint8_t *value: Value to read from the register [Output]
 *  		uint8_t data_bytes: Amount of data to be read
 *  		SPI_HandleTypeDef SPI_Handle: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t readRegSPI(uint8_t reg , uint8_t *value  , SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;
	uint8_t tx_buf[SPI_TX_SIZE];

	tx_buf[0] = reg | SPI_RD_BIT;
	tx_buf[1] = 0;

	//Read from register using SPI
	if(HAL_OK != HAL_SPI_TransmitReceive(&SPI_Handle, tx_buf, value, SPI_TX_SIZE , SPI_TIMEOUT))
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief Abstraction layer for I2C slave device read
 * @param : uint8_t dev_addr: Slave address for I2C device
 * 			uint8_t *value: Value to read from the register [Output]
 *  		uint8_t data_bytes: Amount of data to be read
 *  		I2C_HandleTypeDef I2C_Handle: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t receiveI2C(uint8_t dev_addr , uint8_t *value , uint8_t data_bytes , I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;
	if(HAL_OK != HAL_I2C_Master_Receive(&I2C_Handle, dev_addr, value, data_bytes, 100))
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief Abstraction layer for I2C slave device write
 * @param : uint8_t dev_addr: Slave address for I2C device
 * 			uint8_t *value: Value to read from the register [Output]
 *  		uint8_t data_bytes: Amount of data to be written
 *  		I2C_HandleTypeDef I2C_Handle: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t transmitI2C(uint8_t dev_addr , uint8_t *value , uint8_t data_bytes , I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;
	if(HAL_OK != HAL_I2C_Master_Transmit(&I2C_Handle, dev_addr, value, data_bytes, 100))
		ret_status = HAL_ERROR;

	return ret_status;
}

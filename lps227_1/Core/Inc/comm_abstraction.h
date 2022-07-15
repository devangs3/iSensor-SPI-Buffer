/**
 ******************************************************************************
 * @file           : comm_abstraction.h
 * @brief          : Header for abstraction layer for communication [I2C and SPI]
 ******************************************************************************
 **/


#ifndef __COMM_ABSTRACTION_H
#define __COMM_ABSTRACTION_H

#include "main.h"

#define I2C_TIMEOUT   (100)
#define SPI_TIMEOUT   (100)
#define SPI_TX_SIZE   (2)
#define SPI_WR_BIT    (0x00)
#define SPI_RD_BIT    (0x80)
#define CLR_REG       (0x00)

/**
 * @brief Abstraction layer for I2C register write
 * @param : uint8_t reg: Register to write value
 *  		uint8_t value: Value to write to the register
 *  		uint8_t data_bytes: Amount of data to be written
 *  		uint8_ dev_addr: Slave address for I2C device
 * 	        I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t writeRegI2C(uint8_t dev_addr ,uint8_t reg , uint8_t *value , uint8_t data_bytes , I2C_HandleTypeDef I2C_Handle);

/**
 * @brief Abstraction layer for SPI register write
 * @param : uint8_t reg: Register to write value
 *  		uint8_t value: Value to write to the register
 *  		SPI_HandleTypeDef SPI_Handle: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t writeRegSPI(uint8_t reg , uint8_t value , SPI_HandleTypeDef SPI_Handle);

/**
 * @brief Abstraction layer for I2C register read
 * @param : uint8_t dev_addr: Slave address for I2C device
 * 			uint8_t reg: Register to write value
 *  		uint8_t *value: Value to read from the register [Output]
 *  		uint8_t size: Amount of data to be written
 *  		I2C_HandleTypeDef I2C_Handle: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t readRegI2C(uint8_t dev_addr ,uint8_t reg , uint8_t *value , uint8_t data_bytes ,  I2C_HandleTypeDef I2C_Handle);

/**
 * @brief Abstraction layer for SPI register read
 * @param : uint8_t reg: Register to write value
 *  		uint8_t *value: Value to read from the register [Output]
 *  		uint8_t size: Amount of data to be written
 *  		SPI_HandleTypeDef SPI_Handle: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t readRegSPI(uint8_t reg , uint8_t *value , SPI_HandleTypeDef SPI_Handle);

/**
 * @brief Abstraction layer for I2C slave device read
 * @param : uint8_t dev_addr: Slave address for I2C device
 * 			uint8_t *value: Value to read from the register [Output]
 *  		uint8_t data_bytes: Amount of data to be read
 *  		I2C_HandleTypeDef I2C_Handle: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t receiveI2C(uint8_t dev_addr , uint8_t *value , uint8_t data_bytes , I2C_HandleTypeDef I2C_Handle);

/**
 * @brief Abstraction layer for I2C slave device write
 * @param : uint8_t dev_addr: Slave address for I2C device
 * 			uint8_t *value: Value to read from the register [Output]
 *  		uint8_t data_bytes: Amount of data to be written
 *  		I2C_HandleTypeDef I2C_Handle: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t transmitI2C(uint8_t dev_addr , uint8_t *value , uint8_t data_bytes , I2C_HandleTypeDef I2C_Handle);

#endif

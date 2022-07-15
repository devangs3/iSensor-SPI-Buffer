/**
 ******************************************************************************
 * @file           : sensor_framework.h
 * @brief          : Header for sensor framework
 ******************************************************************************
 **/


#ifndef __SENSOR_FRAMEWORK_H
#define __SENSOR_FRAMEWORK_H

#include "main.h"

#define SEQ_DONE        (0u)
#define DATA_LEN        (16u)
#define MAX_BUFFER_SIZE (1024u)

typedef uint32_t   (Sensor_no_t);

typedef struct
{
	//Merge data_rdy and time_rdy
	//User defined data ready pin register
	volatile Sensor_no_t data_rdy_reg;

	//TODO: Maybe an 8 bit value will do? Since only 2 ADC
	volatile Sensor_no_t adc_irq_reg;

	//Other than DMA irq
	//TODO: Check if I2S and I3C fall under this category
	volatile Sensor_no_t dig_irq_reg;

	//TODO: How does this exactly work?
	volatile Sensor_no_t reconfig_reg;
}User_reg_bank_n;

//Enum for defining various communication protocols
typedef enum
{
	SPI_protocol = 1,
	I2C_protocol = 2,
	I2S_protocol = 3,
	I3C_protocol = 4,
	UART_protocol = 5,
	ADC_sensor = 6,
	Digital_sensor = 7,
	Reconfig_sensors = 8,
	SD_Card = 9,
}Comm_protocol_t;


//TODO: Syntax for using function for assigning the values

//Enum for data ready pin for SPI sensors
typedef enum
{
	SPI_sensor_1 = 0x01,
	SPI_sensor_2 = 0x02,
	SPI_sensor_3 = 0x04,
	SPI_sensor_4 = 0x08,
}SPI_Sensor_t;


//Enum for data ready pin for I2C sensors
typedef enum
{
	I2C_sensor_1 = 0x10,
	I2C_sensor_2 = 0x20,
	I2C_sensor_3 = 0x40,
	I2C_sensor_4 = 0x80,
	//Temporary, need to either
	//a. Introduce CS per SPI sensor (staright-forward)
	//b. Solder pins on CN12 connecter
	I2C_sensor_5 = 0x100,
}I2C_sensor_t;

//Enum for data ready pin for I2S sensor
//These will change based on whether data ready[DMA] or normal interrupt
//Change if digital sensors enum if changed
typedef enum
{
	I2S_sensor_1 = 0x1000,
}I2S_sensor_t;

//Enum for data ready pin for I3C sensor
//These will change based on whether data ready[DMA] or normal interrupt
//Change if digital sensors enum if changed
typedef enum
{
	I3C_sensor_1 = 0x10000,
}I3C_sensor_t;

//Enum for ADC sensors IRQ
typedef enum
{
	ADC_sensor_1 = 0x01,
	ADC_sensor_2 = 0x02,
}ADC_sensor_t;

//Change if I2S and I3C are also irq based
typedef enum
{
	Digital_sensor_1 = 0x01,
	Digital_sensor_2 = 0x02,
}Digital_sensor_t;

/**
 * @brief  Sensor framework
 * @param   I2C_HandleTypeDef I2C_Periph1: The I2C1 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph2: The I2C2 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph3: The I2C3 peripheral on the micro-controller
 * 		   I2C_HandleTypeDef I2C_Periph4: The I2C4 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph1: The SPI1 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph2: The SPI2 peripheral on the micro-controller
 * 		   SPI_HandleTypeDef SPI_Periph3: The SPI3 peripheral on the micro-controller
 * 		   ADC_HandleTypeDef ADC_Perpiph1: The ADC4 peripheral on the micro-controller
 * 		   UART_HandleTypeDef UART_Periph1: The UART1 peripheral on the micro-controller
 * 		   RTC_HandleTypeDef RTC_Periph1: The RTC1 peripheral on the micro-controller
 * @retval Error status
 */
uint8_t sensor_framework(I2C_HandleTypeDef I2C_Periph1 , I2C_HandleTypeDef I2C_Periph2 ,
		I2C_HandleTypeDef I2C_Periph3 , I2C_HandleTypeDef I2C_Periph4 ,
		SPI_HandleTypeDef SPI_Periph1 , SPI_HandleTypeDef SPI_Periph2 ,
		SPI_HandleTypeDef SPI_Periph3 , ADC_HandleTypeDef ADC_Perpiph1 ,
		UART_HandleTypeDef UART_Periph1, RTC_HandleTypeDef RTC_Periph1);

/**
 * @brief  Returns global instance of the pointer
 * @param  None
 * @retval User_reg_bank_n* : Instance of the user_reg structure
 */
User_reg_bank_n* getSensorPtr();


#endif

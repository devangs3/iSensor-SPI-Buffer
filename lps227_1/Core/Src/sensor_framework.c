/**
 ******************************************************************************
 * @file           : sensor_framework.c
 * @brief          : API for sensor framework
 ******************************************************************************
 **/

#include "main.h"
#include "sensor_framework.h"
#include "malloc.h"
#include "sensor_headers.h"
#include "rtc_timestamp.h"
#include "string.h"
#include "stdio.h"


/*Global instance of the user structure for data ready flags*/
User_reg_bank_n a;

/**
 * @brief  Returns global instance of the pointer
 * @param  None
 * @retval User_reg_bank_n* : Instance of the user_reg structure
 */
User_reg_bank_n* getSensorPtr()
{
	return (&a);
}


/**
 * @brief  Updates the next sensor based on the user registers
 * @param  Sensor_no_t new_state: The state to go to next
 * 		   Sensor_no_t curr_state: The current state
 * 		   Sensor_no_t last_state: The last state aka the count for number of sensors for that peripheral
 * 		   uint32_t user_reg: The user defined register that indicates the new incoming data for a particular peripheral
 * @retval Sensor_no_t: next state to go to
 */
static Sensor_no_t nextSensor(Sensor_no_t new_state , Sensor_no_t curr_state , Sensor_no_t last_state , uint32_t user_reg)
{
	if(new_state == 0)
	{
		for(int i = curr_state; i <= last_state; i*=2)
		{
			new_state = (user_reg & i);
			if(new_state != 0)
				break;
			else
				new_state = SEQ_DONE;
		}
	}
	else if(curr_state == last_state)
		new_state = last_state;
	return new_state;
}

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
		SPI_HandleTypeDef SPI_Periph3 , ADC_HandleTypeDef ADC_Perpiph1,
		UART_HandleTypeDef UART_Periph1, RTC_HandleTypeDef RTC_Periph1)
{
	//TODO: Memory block - Need more clarification
	//Or Use one of the SRAM blocks?
	uint32_t data_buffer[MAX_BUFFER_SIZE];
	static uint32_t dataIndex = 0;
	Comm_protocol_t periph = SPI_protocol;
	Sensor_no_t sensor_no;
	uint8_t time_stamp[9], date_stamp[12];
	uint8_t ret_status = HAL_OK;

	switch(periph)
	{
	case SPI_protocol:
		periph = I2C_protocol;

		sensor_no = (a.data_rdy_reg & SPI_sensor_1);

		if(sensor_no == 0)
			sensor_no = nextSensor(sensor_no, SPI_sensor_1 , SPI_sensor_4 ,
					a.data_rdy_reg);

		/*Continue looping till all the data ready are covered*/
		while(sensor_no != SEQ_DONE)
		{
			switch(sensor_no)
			{
			case SPI_sensor_1:
				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = (a.data_rdy_reg & SPI_sensor_2);
				a.data_rdy_reg &= ~SPI_sensor_1;
				sensor_no = nextSensor(sensor_no , SPI_sensor_2 , SPI_sensor_4 ,
						a.data_rdy_reg);

				/*Get data from the sensor and the current timestamp*/
				uint32_t temp_pres;
				if (HAL_OK != lps277SPIPressureData(&temp_pres, SPI_Periph1))
					ret_status = HAL_ERROR;
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Store data into the local buffer and print it to UART*/
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				sprintf((char *)&data_buffer[dataIndex],"%s LPS27 P:%lu\r\n",
						time_stamp , temp_pres);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				dataIndex += DATA_LEN;
				//				if (dataIndex == MAX_BUFFER_SIZE)
				//					dataIndex = 0;
				break;

			case SPI_sensor_2:
				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = (a.data_rdy_reg & SPI_sensor_3);
				a.data_rdy_reg &= ~SPI_sensor_2;
				sensor_no = nextSensor(sensor_no , SPI_sensor_3 , SPI_sensor_3 ,
						a.data_rdy_reg);

				//Get data from the sensor and the current timestamp
				int16_t temp_acc1[3], temp_gyro1[3];
				if (HAL_OK != lsm6dso32SPIAccData(SPI_Periph2, temp_acc1))
					ret_status = HAL_ERROR;
				if (HAL_OK != lsm6dso32SPIGyroData(SPI_Periph2, temp_gyro1))
					ret_status = HAL_ERROR;
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				sprintf((char *)&data_buffer[dataIndex],"%s LSM632 A:%.3d,%.3d,%.3d "
						"G:%.3d,%.3d,%.3d\r\n",
						time_stamp , temp_acc1[0], temp_acc1[1] , temp_acc1[2],
						temp_gyro1[0], temp_gyro1[1], temp_gyro1[2]);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				dataIndex += DATA_LEN;
				//				if (dataIndex == MAX_BUFFER_SIZE)
				//					dataIndex = 0;

				break;

			case SPI_sensor_3:
				//				temp = (a.data_rdy_reg & SPI_sensor_4);
				//				sensor_no = nextSensor(temp , SPI_sensor_4 , SPI_sensor_4 , a.data_rdy_reg);

				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = SEQ_DONE;
				a.data_rdy_reg &= ~SPI_sensor_3;

				/*Get data from the sensor and the current timestamp*/
				int16_t temp_acc2[3];
				if (HAL_OK != adxl375SPIAccData(SPI_Periph3, temp_acc2))
					ret_status = HAL_ERROR;
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Store data into the local buffer and print it to UART*/
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				sprintf((char *)&data_buffer[dataIndex],"%s AD375 A:%.3d,%.3d,%.3d\r\n",
						time_stamp , temp_acc2[0], temp_acc2[1] , temp_acc2[2]);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				dataIndex += DATA_LEN;

				break;

			case SPI_sensor_4:
				sensor_no = SEQ_DONE;
				//Attach time-stamp
				//Write data to local memory block[SRAM] using DMA
				break;

			default:
				//Not valid
				sensor_no = SEQ_DONE;
				break;
			}

		}


	case I2C_protocol:
		periph = I2S_protocol;

		sensor_no = (a.data_rdy_reg & I2C_sensor_1);

		if(sensor_no == 0)
			sensor_no = nextSensor(sensor_no, I2C_sensor_1 , I2C_sensor_5 ,
					a.data_rdy_reg);

		/*Continue looping till all the data ready are covered*/
		while(sensor_no != SEQ_DONE)
		{
			switch(sensor_no)
			{
			case I2C_sensor_1:
				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = (a.data_rdy_reg & I2C_sensor_2);
				a.data_rdy_reg &= ~I2C_sensor_1;
				sensor_no = nextSensor(sensor_no, I2C_sensor_2, I2C_sensor_5 ,
						a.data_rdy_reg);

				/*Get data from the sensor and the current timestamp*/
				int16_t temp_acc[3], temp_gyro[3];
				if (HAL_OK != lsm6dsoxI2CAccData(I2C_Periph1, temp_acc))
					ret_status = HAL_ERROR;
				if (HAL_OK != lsm6dsoxI2CGyroData(I2C_Periph1, temp_gyro))
					ret_status = HAL_ERROR;
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Store data into the local buffer and print it to UART*/
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				sprintf((char *)&data_buffer[dataIndex],"%s LSM6X A:%.3d,%.3d,%.3d "
						"G:%.3d,%.3d,%.3d\r\n",
						time_stamp , temp_acc[0], temp_acc[1] , temp_acc[2],
						temp_gyro[0], temp_gyro[1], temp_gyro[2]);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				//Increment the local buffer by 8 [Each data packet is 64 bytes]
				dataIndex += DATA_LEN;
				//				if (dataIndex == MAX_BUFFER_SIZE)
				//					dataIndex = 0;
				//Attach time-stamp [RTC function]
				//Write to the local memory block[SRAM] using DMA
				break;

			case I2C_sensor_2:
				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = (a.data_rdy_reg & I2C_sensor_3);
				a.data_rdy_reg &= ~I2C_sensor_1;
				sensor_no = nextSensor(sensor_no, I2C_sensor_3, I2C_sensor_5 ,
						a.data_rdy_reg);

				/*Get data from the sensor and the current timestamp*/
				int16_t temp_mag[3];
				if (HAL_OK != lis3mdlMagneticData(temp_mag, I2C_Periph1))
					ret_status = HAL_ERROR;
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Store data into the local buffer and print it to UART*/
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				sprintf((char *)&data_buffer[dataIndex],"%s LIS3M M:%.3d,%.3d,%.3d\r\n",
						time_stamp , temp_mag[0] ,
						temp_mag[1] , temp_mag[2]);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				dataIndex += DATA_LEN;
				//				if (dataIndex == MAX_BUFFER_SIZE)
				//					dataIndex = 0;

				//Attach time-stamp [RTC function]
				//Write to the local memory block[SRAM] using DMA
				break;

			case I2C_sensor_3:
				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = (a.data_rdy_reg & I2C_sensor_4);
				a.data_rdy_reg &= ~I2C_sensor_3;
				sensor_no = nextSensor(sensor_no, I2C_sensor_4, I2C_sensor_5 ,
						a.data_rdy_reg);

				/*Get data from the sensor and the current timestamp*/
				float tempC, hum_RH;
				if (HAL_OK != aht20TempData(&tempC ,I2C_Periph2))
					ret_status = HAL_ERROR;
				if (HAL_OK != aht20HumidityData(&hum_RH, I2C_Periph2))
					ret_status = HAL_ERROR;
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Store data into the local buffer and print it to UART*/
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				sprintf((char *)&data_buffer[dataIndex],"%s AHT20 T:%.2f H:%.2f\r\n",
						time_stamp , tempC , hum_RH);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				dataIndex += DATA_LEN;
				//				if (dataIndex == MAX_BUFFER_SIZE)
				//					dataIndex = 0;

				//Attach time-stamp [RTC function]
				//Write to the local memory block[SRAM] using DMA
				break;

			case I2C_sensor_4:
				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = (a.data_rdy_reg & I2C_sensor_5);
				a.data_rdy_reg &= ~I2C_sensor_4;
				sensor_no = nextSensor(sensor_no, I2C_sensor_5, I2C_sensor_5 ,
						a.data_rdy_reg);

				/*Get data from the sensor and the current timestamp*/
				float temp_mag2[3];
				if (HAL_OK != lis2mdlMagneticData(temp_mag2, I2C_Periph3))
					ret_status = HAL_ERROR;
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Store data into the local buffer and print it to UART*/
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				sprintf((char *)&data_buffer[dataIndex],"%s LIS2M M:%.3f,%.3f,%.3f\r\n",
						time_stamp , temp_mag2[0] ,
						temp_mag2[1] , temp_mag2[2]);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				dataIndex += DATA_LEN;
				//				if (dataIndex == MAX_BUFFER_SIZE)
				//					dataIndex = 0;
				//Attach time-stamp [RTC function]
				//Write to the local memory block[SRAM] using DMA
				break;

			case I2C_sensor_5:
				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = SEQ_DONE;
				a.data_rdy_reg &= ~I2C_sensor_5;

				/*Get data from the sensor and the current timestamp*/
				uint16_t temp_light;
				if (HAL_OK != bh1750LightData(I2C_Periph4, &temp_light))
					ret_status = HAL_ERROR;
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Store data into the local buffer and print it to UART*/
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				sprintf((char *)&data_buffer[dataIndex],"%s BH175 L:%d\r\n",
						time_stamp , temp_light);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				dataIndex += DATA_LEN;
				//				if (dataIndex == MAX_BUFFER_SIZE)
				//					dataIndex = 0;
				//Attach time-stamp [RTC function]
				//Write to the local memory block[SRAM] using DMA
				break;


			default:
				//Not valid
				sensor_no = SEQ_DONE;
				break;
			}
		}


	case I2S_protocol:
		periph = I3C_protocol;

		//Depending on whether DMA available for I3C or not
		sensor_no = a.data_rdy_reg & I2S_sensor_1;   // Or (a.dig_irq_reg & I2S_sensor_1)

		/*Continue looping till all the data ready are covered*/
		while(sensor_no != SEQ_DONE)
		{
			switch(sensor_no)
			{
			case I2S_sensor_1:
				sensor_no = SEQ_DONE;
				//Attach time-stamp [RTC function]
				//Write to the local memory block [SRAM] using DMA
				break;

			default:
				//Not valid
				sensor_no = SEQ_DONE;
				break;
			}
		}


	case I3C_protocol:
		periph = UART_protocol;

		//Depending on whether DMA available for I3C or not
		sensor_no = a.data_rdy_reg & I3C_sensor_1;     // Or (a.dig_irq_reg & I3C_sensor_1))

		/*Continue looping till all the data ready are covered*/
		while(sensor_no != SEQ_DONE)
		{
			switch(sensor_no)
			{
			case I3C_sensor_1:
				sensor_no = SEQ_DONE;
				//Attach time-stamp [RTC function]
				//Write to the local memory block[SRAM] using DMA
				break;

			default:
				//Not valid
				sensor_no = SEQ_DONE;
				break;
			}

		}

		//TODO: More clarity
	case UART_protocol:
		periph = ADC_sensor;
		//Do something


	case ADC_sensor:
		periph = Digital_sensor;

		sensor_no = (a.adc_irq_reg & ADC_sensor_1);

		if(sensor_no == 0)
			sensor_no = nextSensor(sensor_no, ADC_sensor_1, ADC_sensor_2 ,
					a.adc_irq_reg);

		/*Continue looping till all the data ready are covered*/
		while(sensor_no != SEQ_DONE)
		{
			switch(sensor_no)
			{
			case ADC_sensor_1:
				//				temp = (a.adc_irq_reg & ADC_sensor_2);
				//				sensor_no = nextSensor(temp, ADC_sensor_2, ADC_sensor_2 , a.adc_irq_reg);

				/*Fetch next data-ready and clear the data ready flag*/
				sensor_no = SEQ_DONE;
				a.adc_irq_reg &= ~ ADC_sensor_1;

				/*Get data from the sensor and the current timestamp*/
				int16_t tempADC;
				adcTempSensor(&tempADC, ADC_4, ADC_Perpiph1);
				RTCTimestamp(time_stamp, date_stamp, RTC_Periph1);

				/*Store data into the local buffer and print it to UART*/
				memset(&data_buffer[dataIndex] , 0,
						DATA_LEN * sizeof(data_buffer[dataIndex]));
				if (dataIndex == MAX_BUFFER_SIZE)
					dataIndex = 0;
				sprintf((char *)&data_buffer[dataIndex],"%s ADC_4 T:%d\r\n",
						time_stamp , tempADC);
				HAL_UART_Transmit(&UART_Periph1,(uint8_t *)&data_buffer[dataIndex],
						DATA_LEN * sizeof(data_buffer[dataIndex]), 100);

				/*Increment the local buffer by 8 [Each data packet is 64 bytes]*/
				dataIndex += DATA_LEN;
				//				if (dataIndex == MAX_BUFFER_SIZE)
				//					dataIndex = 0;
				break;

			case ADC_sensor_2:
				sensor_no = SEQ_DONE;
				//Attach time-stamp [RTC function]
				//Write to the local memory block[SRAM] using DMA
				break;

			default:
				//Not valid
				sensor_no = SEQ_DONE;
				break;
			}
		}

	case Digital_sensor:
		periph = Reconfig_sensors;
		//Get data
		//Attach time-stamp [RTC function]
		//Write to the local memory block[SRAM] using DMA

	case Reconfig_sensors:
		//If data buffer[SRAM] is full, then next state is SPI or SD card
		periph = SD_Card;
		//FIXME: Clarity?
		sensor_no = (a.reconfig_reg & SPI_sensor_1);

		//Will the entire flow be repeated?

	case SD_Card:
		periph = SPI_protocol;
		//Push data to SD card if the buffer[SRAM] is full

	default:
		break;

	}

	return ret_status;

}

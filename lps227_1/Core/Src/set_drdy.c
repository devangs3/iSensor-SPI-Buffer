/**
 ******************************************************************************
 * @file           : set_drdy.c
 * @brief          : API for setting Data Ready flags [GPIO Interrupts + Timer IRQ]
 ******************************************************************************
 **/

#include <set_drdy.h>
#include "sensor_framework.h"
#include "timers.h"

volatile static uint32_t sysTimeCnt1 = 0;

User_reg_bank_n *b;

/*Helper functions*/

/**
 * @brief  Generates a pointer to structure having sensor flags
 * @param  None
 * @retval None
 */
void getFlagPtr()
{
	b = getSensorPtr();
}


/**
 * @brief  Sets the user-specified bit in the user defined data ready flag
 * @param  uint32_t userReg: The user defined flag variable
 * 		   uint32_t bit: The bit to be set in the flag variable
 * @retval None
 */
void setFlag(uint32_t userReg , uint32_t bit)
{
	userReg |= bit;
}

/**
 * @brief  Clears the user-specified bit in the user defined data ready flag
 * @param  uint32_t userReg: The user defined flag variable
 * 		   uint32_t bit: The bit to be set in the flag variable
 * @retval None
 */
void clearFlag(uint32_t userReg , uint32_t bit)
{
	userReg &= ~(bit);
}

/**
 * @brief Interrupt callback for INT_DRDY pin from sensor (PC-6)
 * @param uint16_t GPIO_Pin: GPIO Pin number where interrupt is triggered
 * @retval None
 */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	/*LPS27HHW data ready pin*/
	if(GPIO_Pin == DRDY_LPS27HHW_Pin)
		b->data_rdy_reg |= SPI_sensor_1;

	/*LSM6DSOX data ready pin accelerometer*/
	if(GPIO_Pin == DRDY_LSM6DSOX_INT1_Pin)
		b->data_rdy_reg |= I2C_sensor_1;

	/*LSM6DSOX data ready pin gyroscope*/
	if(GPIO_Pin == DRDY_LSM6DSOX_INT2_Pin)
		b->data_rdy_reg |= I2C_sensor_1;

	/*LSM6DSO32 data ready pin accelerometer*/
	if(GPIO_Pin == DRDY_LSM6DSO32_INT1_Pin)
		b->data_rdy_reg |= SPI_sensor_2;

	/*LSM6DSO32 data ready pin gyroscope*/
	if(GPIO_Pin == DRDY_LSM6DSO32_INT2_Pin)
		b->data_rdy_reg |= SPI_sensor_2;

	/*LISM3DL data ready pin magnetometer*/
	if(GPIO_Pin == DRDY_LIS3MDL_Pin)
		b->data_rdy_reg |= I2C_sensor_2;

}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{

	/*ADXL375 Data ready pin accelerometer*/
	if(GPIO_Pin == DRDY_ADXL375_Pin)
		b->data_rdy_reg |= SPI_sensor_3;

}

/**
 * @brief ADC IRQ Handler
 * @param ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	/*ADC4 ADC IRQ pin for internal temperature sensor channel*/
	b->adc_irq_reg |= ADC_sensor_1;
}

/**
 * @brief Systick ISR
 * @note Refer to stm32u5xx_hal.c for default implementation
 * @retval None
 */
void HAL_IncTick(void)
{
	/*Ticks for 1 millisecond delay*/
	time_ticks += (uint32_t)tick_freq;

	/*For temperature sensor, magnetometer (LIS2MDL)
	 * and light sensor(BH1750) and temperature sensor(AHT20)
	 *  every 10 milliseconds*/
	if(TICKS_10_MS== sysTimeCnt1)
	{
		/*Reset the counter*/
		sysTimeCnt1 = 0u;
		b->data_rdy_reg |= I2C_sensor_3;
		b->data_rdy_reg |= I2C_sensor_4;
		b->data_rdy_reg |= I2C_sensor_5;
	}

	/*Increment the counter for data ready for timer-triggered sensors*/
	sysTimeCnt1++;
}

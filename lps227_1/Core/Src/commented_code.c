////
////
//////		RTCTimestamp(time_stamp, date_stamp, hrtc);
//////		if(HAL_OK != tsl2591LightData(hi2c1, &light_lux))
//////			return HAL_ERROR;
//////		else
//////		{
//////			RTCTimestamp(time_stamp, date_stamp, hrtc);
//////			sprintf((char *)print_string ,"%s In lux:%f\r\n", time_stamp,light_lux);
//////			HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//////			memset(print_string , 0 , sizeof(print_string));
//////		}
//////
//////		if (HAL_OK != vcnl4040I2CWhoami(hi2c1))
//////			return HAL_ERROR;
//////
//////		if(HAL_OK != vcnl4040I2CSetup(hi2c1))
//////			return HAL_ERROR;
//////		if(HAL_OK != lsm6dsoxI2CTestFunction(acc_data, gyro_data, hi2c1 , &acc_flag , &gyro_flag))
//////			return HAL_ERROR;
//////		else
//////		{
//////			RTCTimestamp(time_stamp, date_stamp, hrtc);
//////			if(lsm_acc_drdy == 1)
//////			{
//////				lsm_acc_drdy = 0;
//////				sprintf((char *)print_string ,"%s ACC: X:%.3d Y:%.3d Z:%.3d\r\n", time_stamp,acc_data[0], acc_data[1], acc_data[2]);
//////				HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//////				memset(print_string , 0 , sizeof(print_string));
//////			}
//////			if(lsm_gyro_drdy == 1)
//////			{
//////				lsm_gyro_drdy = 0;
//////				sprintf((char *)print_string ,"%s GYRO: X:%.3d Y:%.3d Z:%.3d\r\n", time_stamp,gyro_data[0], gyro_data[1], gyro_data[2]);
//////				HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//////				memset(print_string , 0 , sizeof(print_string));
//////			}
//////
//////
//////
//////
//////		}
////
//////		if(vcnl4040_int == 1)
//////		{
//////		RTCTimestamp(time_stamp, date_stamp, hrtc);
//////		vcnl4040_int = 0;
//////		if(HAL_OK != vcnl4040ProximityData(hi2c1, &proximity))
//////			return HAL_ERROR;
//////		else
//////		{
//////			sprintf((char *)print_string ,"%s P: %u\r\n", time_stamp, proximity);
//////			HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//////			memset(print_string , 0 , sizeof(print_string));
//////
//////		}
//////		HAL_Delay(100);
//////		}
////
//////		if(HAL_OK != adcTempSensor(&temp_c, ADC_4, hadc4))
//////			return HAL_ERROR;
////uint16_t ms;
////triggerADCIRQ(hadc4);
////if(adc_irq == 1)
////{
////	adc_irq = 0;
////	if(HAL_OK != adcTempSensor(&temp_c, ADC_4, hadc4))
////		return HAL_ERROR;
////	RTCTimestamp(time_stamp, &ms ,date_stamp, hrtc);
//////			uint16_t ms = (time_stamp[3] << 8) | time_stamp[4];
////	sprintf((char *)print_string ,"%.2hu:%.2hu:%.2hu:%.3hu %hu\r\n", time_stamp[0], time_stamp[1], time_stamp[2] , ms/*((time_stamp[3] << 8) | time_stamp[4])*/, temp_c);
////	HAL_UART_Transmit(&huart1, print_string, 11, 100);
////	memset(print_string , 0 , sizeof(print_string));
////
////}
////
//////		char buffer[30];
//////		int a = 10, b = 20, c;
//////		c = a + b;
//////		sprintf(buffer, "Sum of %d and %d is %d\r\n", a, b, c);
//////		HAL_UART_Transmit(&huart1, (uint8_t *)buffer, sizeof(buffer), 100);
//////		memset(buffer , 0 , sizeof(buffer));
////
////
////
////}
////
////
//////
//////			if(lism3dl_drdy == 1)
//////			{
//////				RTCTimestamp(time_stamp, date_stamp, hrtc);
//////				lism3dl_drdy = 0;
//////				if(HAL_OK != lis3mdlMagneticData(mag_data, hi2c3))
//////					return HAL_ERROR;
//////				else
//////				{
//////					sprintf((char *)print_string ,"%s X:%.3d Y:%.3d Z:%.3d\r\n", time_stamp, mag_data[0], mag_data[1], mag_data[2]);
//////					HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//////					memset(print_string , 0 , sizeof(print_string));
//////
//////				}
//////				HAL_Delay(100);
//////			}
////
//////
////
////
//////		if(HAL_OK == bh1750LightData(hi2c3, &bh1750_data))
//////		{
//////			RTCTimestamp(time_stamp, date_stamp, hrtc);
//////			sprintf((char *)print_string ,"%s In lux:%u\r\n", time_stamp,bh1750_data);
//////			HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//////			memset(print_string , 0 , sizeof(print_string));
//////		}
////
////
////
////
////
////
//////		if(HAL_OK != lis2mdlI2CTestFunction(mag_data , hi2c2))
//////			return HAL_ERROR;
//////		else
//////		{
//////			RTCTimestamp(time_stamp, date_stamp, hrtc);
//////			//			sprintf((char *)print_string , "%s Pressure in hPa[SPI]:%lu\r\n", time_stamp, pres_data_i2c);
////////			sprintf((char *)print_string , "%s Temp:%d\r\n", time_stamp, final_temp);
//////			sprintf((char *)print_string ,"%s X:%.3f Y:%.3f Z:%.3f\r\n", time_stamp, mag_data[0], mag_data[1], mag_data[2]);
//////			HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//////			memset(print_string , 0 , sizeof(print_string));
//////
//////
//////
//////		}
//////		}
//
//	//	uint8_t ret_status_i2c;
//	uint8_t print_string[18];
//	//	int16_t acc_data[3], gyro_data[3];
//	//	float temp = 0, humidity = 0 , t = 0 , h = 0;
//	//	uint8_t acc_flag = 0, gyro_flag = 0;
//	//	float light_lux;
//	//	//	//  uint32_t pres_data_i2c;
//	uint8_t time_stamp[3], date_stamp[12];
//	//	int16_t final_temp = 0;
//	int16_t temp_c = 0;
//	//	float mag_data[3];
//	//	int16_t mag_data[3];
//	//	uint16_t proximity;
//	//	uint16_t bh1750_data;
//
//	//	bh1750LightData(hi2c3, &bh1750_data);
//
//	//	if(HAL_OK != tsl2591I2CWhoami(hi2c1))
//	//		return HAL_ERROR;
//	//
//	//	if(HAL_OK != tsl2591I2CSetup(hi2c1))
//	//		return HAL_ERROR;
//
//	//	if(HAL_OK != lsm6dsoxI2CTestInit(hi2c1))
//	//		return HAL_ERROR;
//
//	//	if(HAL_OK != lsm6dso32SPIWhoami(hspi1))
//	//		return HAL_ERROR;
//	//
//	//	if(HAL_OK != lsm6dso32SPISetup(hspi1))
//	//		return HAL_ERROR;
//	//	if(HAL_OK != lis3mdlI2CWhoami(hi2c3))
//	//		return HAL_ERROR;
//	//
//	//	if(HAL_OK != lis3mdlI2CSetup(hi2c3))
//	//		return HAL_ERROR;
//
//	//	if(HAL_OK != apds9960I2CWhoami(hi2c1))
//	//		return HAL_ERROR;
//
//	//	if(HAL_OK != adxl375SPIWhoami(hspi1))
//	//		return HAL_ERROR;
//	//
//	//	if(HAL_OK != adxl375SPISetup(hspi1))
//	//		return HAL_ERROR;
//
//	//	if(HAL_OK != adxl375I2CWhoami(hi2c1))
//	//		return HAL_ERROR;
//	//
//	//	if(HAL_OK != adxl375I2CSetup(hi2c1))
//	//		return HAL_ERROR;
//	//	if(HAL_OK != apds9960ProximitySetup(hi2c1))
//	//		return HAL_ERROR;









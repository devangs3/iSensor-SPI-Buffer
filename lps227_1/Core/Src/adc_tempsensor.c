/**
 ******************************************************************************
 * @file           : adc_tempsensor.c
 * @brief          : API for temperature data from on-board ADC
 ******************************************************************************
 **/

#include "adc_tempsensor.h"

/**
 * @brief ADC internal temperature sensor data acquisition
 * @param ADC_Periph_t ADC_no: The ADC peripheral (ADC1 or ADC4)
 * 		  ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: Error status
 */
uint8_t adcTempSensor(int16_t* temp_C, ADC_Periph_t ADC_no, ADC_HandleTypeDef ADC_Handle)
{
	int32_t rawTemp;
	uint8_t ret_status = HAL_OK;

	//	HAL_ADC_Start(&ADC_Handle);

	//	if(HAL_OK != HAL_ADC_PollForConversion(&ADC_Handle, 1))
	//		ret_status = HAL_ERROR;

	rawTemp = HAL_ADC_GetValue(&ADC_Handle);

	if(ADC_no == ADC_4)
		*temp_C = __LL_ADC_CALC_TEMPERATURE(ADC4, VDD_REF, rawTemp, LL_ADC_RESOLUTION_12B);
	else if(ADC_no == ADC_1)
		*temp_C = __LL_ADC_CALC_TEMPERATURE(ADC1, VDD_REF, rawTemp, LL_ADC_RESOLUTION_12B);

	HAL_Delay(2);


	return ret_status;
}


/**
 * @brief ADC internal temperature sensor trigger polling
 * @param ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: None
 */
void triggerADCPolling(ADC_HandleTypeDef ADC_Handle)
{
	HAL_ADC_Start(&ADC_Handle);
}

/**
 * @brief ADC internal temperature sensor polling
 * 		  Check if the temperature conversion is complete - polling
 * @param ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: None
 */
uint8_t isConversionADCPolling(ADC_HandleTypeDef ADC_Handle)
{
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != HAL_ADC_PollForConversion(&ADC_Handle, 1))
		ret_status = HAL_ERROR;

	return ret_status;
}

/**
 * @brief ADC internal temperature sensor trigger for IRQ
 * @param ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: None
 */
void triggerADCIRQ(ADC_HandleTypeDef ADC_Handle)
{
	HAL_ADC_Start_IT(&ADC_Handle);
}





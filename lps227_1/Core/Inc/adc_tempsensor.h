/**
 ******************************************************************************
 * @file           : adc_tempsensor.h
 * @brief          : Header for API for temperature data from on-board ADC
 ******************************************************************************
 **/


#ifndef __ADC_TEMPSENSOR_H
#define __ADC_TEMPSENSOR_H

#include "main.h"

#define VDD_REF   (3300U)

//Enum for temperature calculations for different ADC peripherals
typedef enum
{
	ADC_1 = 1,
	ADC_4 = 4,
}ADC_Periph_t;


/**
 * @brief ADC internal temperature sensor data acquisition
 * @param ADC_Periph_t ADC_no: The ADC peripheral (ADC1 or ADC4)
 * 		  ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: Error status
 */
uint8_t adcTempSensor(int16_t* temp_C, ADC_Periph_t ADC_no, ADC_HandleTypeDef ADC_Handle);

/**
 * @brief ADC internal temperature sensor trigger polling
 * @param ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: None
 */
void triggerADCPolling(ADC_HandleTypeDef ADC_Handle);

/**
 * @brief ADC internal temperature sensor polling
 * 		  Check if the temperature conversion is complete - polling
 * @param ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: Error status
 */
uint8_t isConversionADCPolling(ADC_HandleTypeDef ADC_Handle);

/**
 * @brief ADC internal temperature sensor trigger for IRQ
 * @param ADC_HandleTypeDef: The ADC peripheral structure instance on the micro-controller (ADC1 or ADC4)
 * @retval ret_status: None
 */
void triggerADCIRQ(ADC_HandleTypeDef ADC_Handle);

#endif

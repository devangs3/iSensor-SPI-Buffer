/**
 ******************************************************************************
 * @file           : rtc_timestamp.h
 * @brief          : Header for RTC (Time-stamping)
 ******************************************************************************
 **/


#ifndef __RTC_TIMESTAMP_H
#define __RTC_TIMESTAMP_H

#include "main.h"

/**
 * @brief  Display the current time and date.
 * @param  time : pointer to buffer
 * 	  	   date : pointer to buffer
 * 	  	   RTC_HandleTypeDef: RTC instance to be used
 *
 * @retval None
 */
void RTCTimestamp(uint8_t* time, uint8_t* date, RTC_HandleTypeDef RTC_Handle);


#endif

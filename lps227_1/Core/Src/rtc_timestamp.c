/**
 ******************************************************************************
 * @file           : rtc_timestamp.c
 * @brief          : API for RTC (Time-stamping)[hh:mm:ss:mss]
 ******************************************************************************
 **/

#include "rtc_timestamp.h"
#include "main.h"
#include "stdio.h"


/**
 * @brief  Display the current time and date.
 * @param  time : pointer to buffer
 * 	  	   date : pointer to buffer
 * 	  	   RTC_HandleTypeDef: RTC instance to be used
 *
 * @retval None
 */
void RTCTimestamp(uint8_t* time , uint8_t* date, RTC_HandleTypeDef RTC_Handle)
{
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;

	//Get the RTC current Time
	HAL_RTC_GetTime(&RTC_Handle, &stimestructureget, RTC_FORMAT_BIN);

	//Convert sub-seconds into milliseconds
	uint32_t millisec = (1000 * (stimestructureget.SecondFraction - stimestructureget.SubSeconds)) / (stimestructureget.SecondFraction + 1);

	//Get the RTC current Date
	HAL_RTC_GetDate(&RTC_Handle, &sdatestructureget, RTC_FORMAT_BIN);

//	time[0] = stimestructureget.Hours;
//	time[1] = stimestructureget.Minutes;
//	time[2] = stimestructureget.Seconds;
//	time[3] = (uint8_t)millisec;
//	time[4] = (uint8_t)millisec >> 8;


	//Display time Format : hh:mm:ss:mss
	sprintf((char *)time, "%.2hu:%.2hu:%.2hu:%.3lu", stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds, millisec);
	//Display date Format : mm-dd-yy
	sprintf((char *)date, "%.2d-%.2d-%.2d ", sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);
}

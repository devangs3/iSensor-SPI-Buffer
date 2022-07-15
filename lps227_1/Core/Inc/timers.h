/**
 ******************************************************************************
 * @file           : timers.h
 * @brief          : Header file for systick timer
 ******************************************************************************
 **/

#ifndef __TIMERS_H
#define __TIMERS_H

#include "main.h"

extern volatile uint32_t time_ticks;
extern HAL_TickFreqTypeDef tick_freq;

/**
  * @brief User implementation of the _weak HAL_Delay().
  * 	   Provides a delay of 1 millisecond
  * @note Refer to stm32u5xx_hal.c for default implementation
  * @retval uint32_t tick value
*/
void HAL_Delay(uint32_t Delay);

#endif

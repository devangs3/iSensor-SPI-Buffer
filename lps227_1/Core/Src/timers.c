/**
 ******************************************************************************
 * @file           : timers.c
 * @brief          : API for systick timer
 ******************************************************************************
 **/

#include "timers.h"

//Global variable for ticks of the Systick timer (each tick is 1 millisecond)
volatile uint32_t time_ticks;
HAL_TickFreqTypeDef tick_freq = HAL_TICK_FREQ_DEFAULT;


/**
  * @brief User implementation of the _weak HAL_GetTick()
  * @note Refer to stm32u5xx_hal.c for default implementation
  * @retval uint32_t tick value
*/
uint32_t HAL_GetTick(void)
{
  return time_ticks;
}


/**
  * @brief User implementation of the _weak HAL_Delay().
  * 	   Provides a delay of 1 millisecond
  * @note Refer to stm32u5xx_hal.c for default implementation
  * @retval uint32_t tick value
*/
void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(tick_freq);
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
}

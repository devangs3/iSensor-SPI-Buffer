/**
 ******************************************************************************
 * @file           : set_drdy.h
 * @brief          : Header for setting Data Ready flags
 ******************************************************************************
 **/


#ifndef __SET_DRDY_H
#define __SET_DRDY_H

#include "main.h"

#define TICKS_10_MS      (10u)

/**
 * @brief  Generates a pointer to structure having sensor flags
 * @param  None
 * @retval None
 */
void getFlagPtr();


/**
 * @brief  Sets the user-specified bit in the user defined data ready flag
 * @param  uint32_t userReg: The user defined flag variable
 * 		   uint32_t bit: The bit to be set in the flag variable
 * @retval None
 */
void setFlag(uint32_t userReg , uint32_t bit);

/**
 * @brief  Clears the user-specified bit in the user defined data ready flag
 * @param  uint32_t userReg: The user defined flag variable
 * 		   uint32_t bit: The bit to be set in the flag variable
 * @retval None
 */
void clearFlag(uint32_t userReg , uint32_t bit);

#endif

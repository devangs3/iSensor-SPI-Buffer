/**
 ******************************************************************************
 * @file           : bh1750_defs.h
 * @brief          : Header for configuration registers for light sensor
 ******************************************************************************
 **/



#ifndef __BH1750_DEFS_H
#define __BH1750_DEFS_H

#include "comm_abstraction.h"

//Operating modes for the sensor
//Continuous High resolution (1lx)
#define BH1750_CONT_H_RES_MODE            (0x10u)
//Continuous Higher resolution (0.5lx)
#define BH1750_CONT_H_RES_MODE2           (0x11u)
//Continuous Low resolution (4lx)
#define BH1750_CONT_L_RES_MODE            (0x13u)
//One time High resolution (1lx)
#define BH1750_SINGLE_H_RES_MODE          (0x20u)
//One time Higher resolution (0.5lx)
#define BH1750_SINGLE_H_RES_MODE2         (0x21u)
//One time Low resolution (4lx)
#define BH1750_SINGLE_L_RES_MODE          (0x23u)

//Measurement time in milliseconds
#define BH1750_H_RES_MEAS_TIME            (120u)
#define BH1750_H_RES_2_MEAS_TIME		  (120u)
#define BH1750_L_RES_MEAS_TIME			  (16u)



#endif

/**
 ******************************************************************************
 * @file           : bme680_reg.h
 * @brief          : Header for configuration registers for the BME680
 ******************************************************************************
 **/



#ifndef __BME680_REG_H
#define __BME680_REG_H


#define BME680_WHOAMI          (0xD0)
#define BME680_DEV_ID          (0x61)
#define BME680_CTRL_MEAS       (0x74)
#define BME680_CTRL_HUM        (0x72)
#define BME680_CONFIG          (0x75)
#define BME680_CTRL_GAS_1      (0x71)
#define BME680_PRES_MSB        (0x1F)
#define BME680_PRES_LSB        (0x20)
#define BME680_PRES_XLSB       (0x21)
#define BME680_TEMP_MSB        (0x22)
#define BME680_TEMP_LSB        (0x23)
#define BME680_TEMP_XLSB       (0x24)
#define BME680_HUM_MSB         (0x25)
#define BME680_HUM_LSB         (0x26)
#define BME680_GAS_MSB         (0x2A)
#define BME680_GAS_LSB         (0x2B)
#define BME680_TEMP_CALIB1_MSB (0xE9)
#define BME680_TEMP_CALIB1_LSB (0xEA)
#define BME680_TEMP_CALIB2_MSB (0x8A)
#define BME680_TEMP_CALIB2_LSB (0x8B)
#define BME680_TEMP_CALIB3     (0x8C)
#define BME680_STATUS          (0x1D)


#endif

/**
 ******************************************************************************
 * @file           : lis2mdl_reg.h
 * @brief          : Header for configuration registers for the magnetometer
 ******************************************************************************
 **/



#ifndef __LIS2MDL_REG_H
#define __LIS2MDL_REG_H

#include "comm_abstraction.h"

#define LIS2MDL_OFFSET_X_REG_L          (0x45u)
#define LIS2MDL_OFFSET_X_REG_H          (0x46u)
#define LIS2MDL_OFFSET_Y_REG_L          (0x47u)
#define LIS2MDL_OFFSET_Y_REG_H          (0x48u)
#define LIS2MDL_OFFSET_Z_REG_L          (0x49u)
#define LIS2MDL_OFFSET_Z_REG_H          (0x4Au)
#define LIS2MDL_WHOAMI                  (0x4Fu)
#define LIS2MDL_DEV_ID                  (0x40u)
#define LIS2MDL_CFG_A                   (0x60u)
#define LIS2MDL_CFG_B                   (0x61u)
#define LIS2MDL_CFG_C                   (0x62u)
#define LIS2MDL_INT_CTRL                (0x63u)
#define LIS2MDL_INT_SRC                 (0x64u)
#define LIS2MDL_INT_THS_L               (0x65u)
#define LIS2MDL_INT_THS_H               (0x66u)
#define LIS2MDL_STATUS                  (0x67u)
#define LIS2MDL_OUT_X_L                 (0x68u)
#define LIS2MDL_OUT_X_H                 (0x69u)
#define LIS2MDL_OUT_Y_L                 (0x6Au)
#define LIS2MDL_OUT_Y_H                 (0x6Bu)
#define LIS2MDL_OUT_Z_L                 (0x6Cu)
#define LIS2MDL_OUT_Z_H                 (0x6Du)
#define LIS2MDL_TEMP_OUT_L              (0x6Eu)
#define LIS2MDL_TEMP_OUT_H              (0x6Fu)


/*Register Bit Map*/

//CFG_A Register bit Map
typedef enum
{
	m2_cont_mode = 0b00000000,
	m2_single_mode = 0b00000001,
	m2_idle_mode = 0b00000011,
}m2_mode_op;

typedef enum
{
	m2_odr_10Hz =  0b00000000,
	m2_odr_20Hz =  0b00000100,
	m2_odr_50Hz =  0b00001000,
	m2_odr_100Hz = 0b00001100,
}m2_odr;

#define M2_LOW_PWR                         (0b00010000)
#define M2_SOFT_RST                        (0b00100000)
#define M2_REBOOT                          (0b01000000)
#define M2_COMP_TEMP_EN                    (0b10000000)

//CFG_B Register bit Map
#define M2_LPF                             (0b00000001)
#define M2_OFF_CANC                        (0b00000010)
#define M2_SET_FREQ                        (0b00000100)
#define M2_INT_ON_DATAOFF                  (0b00001000)
#define M2_OFF_CANC_ONE_SHOT               (0b00010000)

//CFG_C Register bit Map
#define M2_DRDY_ON_PIN                     (0b00000001)
#define M2_SELF_TEST                       (0b00000010)
#define M2_SPI_4_WIRE                      (0b00000100)
#define M2_BLE                             (0b00001000)
#define M2_BDU                             (0b00010000)
#define M2_I2C_DIS                         (0b00100000)
#define M2_INT_ON_PIN                      (0b01000000)

//INT_CTRL Register map
#define M2_IEN                             (0b00000001)
#define M2_IEL                             (0b00000010)
#define M2_IEA                             (0b00000100)
#define M2_ZIEN                            (0b00100000)
#define M2_YIEN                            (0b01000000)
#define M2_XIEN                            (0b10000000)

//INT_SRC Register Bit map
#define M2_P_THS_S_X                       (0b00000001)
#define M2_P_THS_S_Y                       (0b00000010)
#define M2_P_THS_S_Z                       (0b00000100)
#define M2_N_THS_S_X                       (0b00001000)
#define M2_N_THS_S_Y                       (0b00010000)
#define M2_N_THS_S_Z                       (0b00100000)
#define M2_MROI                            (0b01000000)
#define M2_INT                             (0b10000000)

//STATUS Register Bit amp
#define M2_XDA                             (0b00000001)
#define M2_YDA                             (0b00000010)
#define M2_ZDA                             (0b00000100)
#define M2_ZYXDA                           (0b00001000)
#define M2_XOR                             (0b00010000)
#define M2_YOR                             (0b00100000)
#define M2_ZOR                             (0b01000000)
#define M2_ZYXOR                           (0b10000000)

#endif

/**
 ******************************************************************************
 * @file           : lis3mdl_defs.h
 * @brief          : Header for configuration registers for the magnetometer
 ******************************************************************************
 **/



#ifndef __LIS3MDL_REG_H
#define __LIS3MDL_REG_H

#include "comm_abstraction.h"

#define LIS3MDL_WHOAMI      (0x0Fu)
#define LIS3MDL_DEV_ID      (0x3Du)
#define LIS3MDL_CTRL1       (0x20u)
#define LIS3MDL_CTRL2       (0x21u)
#define LIS3MDL_CTRL3       (0x22u)
#define LIS3MDL_CTRL4       (0x23u)
#define LIS3MDL_CTRL5       (0x24u)
#define LIS3MDL_STATUS      (0x27u)
#define LIS3MDL_INT_CFG     (0x30u)
#define LIS3MDL_OUT_X_L     (0x28u)
#define LIS3MDL_OUT_X_H     (0x29u)
#define LIS3MDL_OUT_Y_L     (0x2Au)
#define LIS3MDL_OUT_Y_H     (0x2Bu)
#define LIS3MDL_OUT_Z_L     (0x2Cu)
#define LIS3MDL_OUT_Z_H     (0x2Du)

#define LIS3MDL_DRDY_EN     (1u)

/*Register Bit map*/

//CTRL1 Register bit map
#define M3_ST                              (0b00000001)
#define M3_FAST_ODR                        (0b00000010)
typedef enum
{
	m3_odr_0_625Hz = 0b00000000,
	m3_odr_1_25Hz =  0b00000100,
	m3_odr_2_5Hz =   0b00001000,
	m3_odr_5Hz =     0b00001100,
	m3_odr_10Hz =    0b00010000,
	m3_odr_20Hz =    0b00010100,
	m3_odr_40Hz =    0b00011000,
	m3_odr_80Hz =    0b00011100,
}m3_odr;

typedef enum
{
	m3_op_mode_LP =   0b00000000,
	m3_op_mode_MP =   0b00100000,
	m3_op_mode_HP =   0b01000000,
	m3_op_mode_UHP =  0b01100000,

}m3_op_mode;
#define M3_TEMP_EN                          (0b10000000)

//CTRL2 Register bit map
#define M3_SOFT_RESET                       (0b00000100)
#define M3_REBOOT                           (0b00001000)
typedef enum
{
	m3_fs_4gauss =  0b00000000,
	m3_fs_8gauss =  0b00100000,
	m3_fs_12gauss = 0b01000000,
	m3_fs_16gauss = 0b01100000,
}m3_full_scale;

//CTRL2 Register Bit Map
typedef enum
{
	m3_cont_mode =     0b00000000,
	m3_single_mode =   0b00000001,
	m3_pwr_down_mode = 0b00000011
}m3_md;

typedef enum
{
	m3_SPI_4_wire = 0b00000000,
	m3_SPI_3_wire = 0b00000100,
}m3_sim;
#define M3_LOW_PWR                          (0b00100000)

//CTRL4 Register Bit Map
#define M3_BLE                              (0b00000010)
typedef enum
{
	m3_omz_LP =  0b00000000,
	m3_omz_MP =  0b00000100,
	m3_omz_HP =  0b00001000,
	m3_omz_UHP = 0b00001100,
}m3_omz;

//CTRL5 Register Bit Map
#define M3_BDU                             (0b01000000)
#define M3_FAST_READ                       (0b10000000)

//STATUS Register Bit amp
#define M3_XDA                             (0b00000001)
#define M3_YDA                             (0b00000010)
#define M3_ZDA                             (0b00000100)
#define M3_ZYXDA                           (0b00001000)
#define M3_XOR                             (0b00010000)
#define M3_YOR                             (0b00100000)
#define M3_ZOR                             (0b01000000)
#define M3_ZYXOR                           (0b10000000)

//INT_CFG Register map
#define M3_IEN                             (0b00000001)
#define M3_IEL                             (0b00000010)
#define M3_IEA                             (0b00000100)
#define M3_ZIEN                            (0b00100000)
#define M3_YIEN                            (0b01000000)
#define M3_XIEN                            (0b10000000)

//INT_SRC Register Bit map
#define M3_PTH_X                           (0b00000001)
#define M3_PTH_Y                           (0b00000010)
#define M3_PTH_Z                           (0b00000100)
#define M3_NTH_X                           (0b00001000)
#define M3_NTH_Y                           (0b00010000)
#define M3_NTH_Z                           (0b00100000)
#define M3_MROI                            (0b01000000)
#define M3_INT                             (0b10000000)


#endif

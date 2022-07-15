/**
 ******************************************************************************
 * @file           : lps277_defs.h
 * @brief          : Header for configuration registers
 ******************************************************************************
 **/


#ifndef __LPS277_REG_H
#define __LPS277_REG_H

#include "comm_abstraction.h"


#define LPS277_WHOAMI         (0x0Fu)
#define LPS277_DEV_ID         (0xB3u)
#define LPS277_INT_CTRL       (0x0Bu)
#define LPS277_THS_P_L        (0x0Cu)
#define LPS277_THS_P_H        (0x0Du)
#define LPS277_IF_CTRL        (0x0Eu)
#define LPS277_CTRL1          (0x10u)
#define LPS277_CTRL2          (0x11u)
#define LPS277_CTRL3          (0x12u)
#define LPS277_FIFO_CTRL      (0x13u)
#define LPS277_FIFO_WTM       (0x14u)
#define LPS277_REF_P_L        (0x15u)
#define LPS277_REF_P_H        (0x16u)
#define LPS277_RPDS_L         (0x18u)
#define LPS277_RPDS_H         (0x19u)
#define LPS277_INT_SRC        (0x24u)
#define LPS277_FIFO_STAT1     (0x25u)
#define LPS277_FIFO_STAT2     (0x26u)
#define LPS277_STATUS         (0x27u)
#define LPS277_PRESS_LOW      (0x28u)
#define LPS277_PRESS_MIDDLE   (0x29u)
#define LPS277_PRESS_HIGH     (0x2Au)
#define LPS277_TEMP_OUT_L     (0x2Bu)
#define LPS277_TEMP_OUT_H     (0x2Cu)
#define LPS277_LPFP_RES       (0X3Cu)
#define LPS277_FIFO_PRESS_XL  (0x78u)
#define LPS277_FIFO_PRESS_L   (0x79u)
#define LPS277_FIFO_PRESS_H   (0x7Au)
#define LPS277_FIFO_TEMP_L    (0x7Bu)
#define LPS277_FIFO_TEMP_H    (0x7Cu)

#define LPS27_DRDY_EN         (1u)



/*Register Bit Map*/

//INT_CFG Register Bit Map
#define LPS_PHE                         (0b00000001)
#define LPS_PLE                         (0b00000010)
#define LPS_LIR                         (0b00000100)
#define LPS_DIFF_EN                     (0b00001000)
#define LPS_RESET_AZ                    (0b00010000)
#define LPS_AUTOZERO                    (0b00100000)
#define LPS_RESET_ARP                   (0b01000000)
#define LPS_AUTOREFP                    (0b10000000)

//IF_CTRL Register Bit Map
#define LPS_I2C_DISABLE                 (0b00000001)
#define LPS_I3C_DISABLE                 (0b00000010)
#define LPS_PD_DIS_INT1                 (0b00000100)
#define LPS_SDO_PU_EN                   (0b00001000)
#define LPS_SDA_PU_EN                   (0b00010000)
#define LPS_INT_EN_I3C                  (0b10000000)

//CTRL1 Register Bit Map
typedef enum
{
	lps_spi_4_wire = 0b00000000,
	lps_spi_3_wire = 0b00000001,
}lps_sim;
#define LPS_BDU                         (0b00000010)
typedef enum
{
	lps_no_lpf =     0b00000000,
	lps_lpf_odr_9 =  0b00001000,
	lps_lpf_odr_20 = 0b00001100,
}lps_lpf;

typedef enum
{
	lps_one_shot =   0b00000000,
	lps_1Hz =        0b00010000,
	lps_10Hz =       0b00100000,
	lps_25Hz =       0b00110000,
	lps_50Hz =       0b01000000,
	lps_75Hz =       0b01010000,
	lps_100Hz =      0b01100000,
	lps_200Hz =      0b01110000,
}lps_odr;

//CTRL2 Register Bit Map
#define LPS_ONESHOT                     (0b00000001)
#define LPS_LOW_NOISE_EN                (0b00000010)
#define LPS_SWRESET                     (0b00000100)
#define LPS_IF_ADD_INC                  (0b00010000)
#define LPS_PP_OD                       (0b00100000)
#define LPS_INT_H_L                     (0b01000000)
#define LPS_BOOT                        (0b10000000)

//CTR3 Register Bit Map
typedef enum
{
	lps_data_signal =      0b00000000,
	lps_high_press =       0b00000001,
	lps_low_press =        0b00000010,
	lps_low_or_high_pres = 0b00000011,
}lps_int_s;
#define LPS_DRDY                        (0b00000100)
#define LPS_INT_F_OVR                   (0b00001000)
#define LPS_INT_F_WTM                   (0b00010000)
#define LPS_INT_F_FULL                  (0b00100000)

//FIFO_CTRL Register Bit Map
typedef enum
{
	lps_bypass =        (0b00000000 | 0b00000001),
	lps_FIFO =           0b00000001,
	lps_cont =          (0b00000010 | 0b00000011),
	lps_bypass_to_FIFO = 0b00000101,
	lps_bypass_to_cont = 0b00000110,
	lps_cont_to_FIFO =   0b00000111,
}lps_f_mode;
#define LPS_STOP_ON_WTM                (0b00001000)

//INT_SOURCE Register Bit map
#define LPS_PH                          (0b00000001)
#define LPS_PL                          (0b00000010)
#define LPS_IA                          (0b00000100)
#define LPS_BOOT_ON                     (0b10000000)

//FIFO_STATUS2 Register Bit Map
#define LPS_FIFO_FULL_IA                (0b00100000)
#define LPS_FIFO_OVR_IA                 (0b01000000)
#define LPS_FIFO_WTM_IA                 (0b10000000)

//STATUS Register Bit Map
#define LPS_P_DA                        (0b00000001)
#define LPS_T_DA                        (0b00000010)
#define LPS_P_OR                        (0b00010000)
#define LPS_T_OR                        (0b00100000)

#endif

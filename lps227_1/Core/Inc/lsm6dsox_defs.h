/**
 ******************************************************************************
 * @file           : lsm6dsox_defs.h
 * @brief          : Header for configuration registers for the IMU
 ******************************************************************************
 **/



#ifndef __LSM6DSOX_DEFS_H
#define __LSM6DSOX_DEFS_H

#include "comm_abstraction.h"

#define LSM6DSOX_WHOAMI            (0x0Fu)
#define LSM6DSOX_DEV_ID            (0x6Cu)
#define LSM6DSOX_FUNC_CFG          (0x01u)
#define LSM6DSOX_PIN_CTRL          (0x02u)
#define LSM6DSOX_FIFO_CTRL1        (0x07u)
#define LSM6DSOX_FIFO_CTRL2        (0x08u)
#define LSM6DSOX_FIFO_CTRL3        (0x09u)
#define LSM6DSOX_FIFO_CTRL4        (0x0Au)
#define LSM6DSOX_CNTR_BDR1         (0x0Bu)
#define LSM6DSOX_CNTR_BDR2         (0x0Cu)
#define LSM6DSOX_INT1_CTRL         (0x0Du)
#define LSM6DSOX_INT2_CTRL         (0x0Eu)
#define LSM6DSOX_CTRL1_XL          (0x10u)
#define LSM6DSOX_CTRL2_G           (0x11u)
#define LSM6DSOX_CTRL3_C           (0x12u)
#define LSM6DSOX_CTRL4_C           (0x13u)
#define LSM6DSOX_CTRL5_C           (0x14u)
#define LSM6DSOX_CTRL6_C           (0x15u)
#define LSM6DSOX_CTRL7_C           (0x16u)
#define LSM6DSOX_CTRL8_C           (0x17u)
#define LSM6DSOX_CTRL9_C           (0x18u)
#define LSM6DSOX_CTRL10_C          (0x19u)
#define LSM6DSOX_ALL_INT_SRC       (0x1Au)
#define LSM6DSOX_WAKE_UP_SRC       (0x1Bu)
#define LSM6DSOX_TAP_SRC           (0x1Cu)
#define LSM6DSOX_D6D_SRC           (0x1Du)
#define LSM6DSOX_STATUS            (0x1Eu)
#define LSM6DSOX_OUT_L_TEMP        (0x20u)
#define LSM6DSOX_OUT_H_TEMP        (0x21u)
#define LSM6DSOX_OUTX_L_GYRO       (0x22u)
#define LSM6DSOX_OUTX_H_GYRO       (0x23u)
#define LSM6DSOX_OUTY_L_GYRO       (0x24u)
#define LSM6DSOX_OUTY_H_GYRO       (0x25u)
#define LSM6DSOX_OUTZ_L_GYRO       (0x26u)
#define LSM6DSOX_OUTZ_H_GYRO       (0x27u)
#define LSM6DSOX_OUTX_L_ACC        (0x28u)
#define LSM6DSOX_OUTX_H_ACC        (0x29u)
#define LSM6DSOX_OUTY_L_ACC        (0x2Au)
#define LSM6DSOX_OUTY_H_ACC        (0x2Bu)
#define LSM6DSOX_OUTZ_L_ACC        (0x2Cu)
#define LSM6DSOX_OUTZ_H_ACC        (0x2Du)

//Embedded functions registers
#define LSM6DSOX_EMB_FNC_STAT_MNPG (0x35u)
#define LSM6DSOX_FSM_STATA_MNPG    (0x36u)
#define LSM6DSOX_FSM_STATB_MNPG    (0x37u)
#define LSM6DSOX_STAT_MASTER_MNPG  (0x39u)
#define LSM6DSOX_FIFO_STATUS1      (0x3Au)
#define LSM6DSOX_FIFO_STATUS2      (0x3Bu)
#define LSM6DSOX_TIMESTAMP0        (0x40u)
#define LSM6DSOX_TIMESTAMP1        (0x41u)
#define LSM6DSOX_TIMESTAMP2        (0x42u)
#define LSM6DSOX_TIMESTAMP3        (0x43u)
#define LSM6DSOX_TAP_CFG0          (0x56u)
#define LSM6DSOX_TAP_CFG1          (0x57u)
#define LSM6DSOX_TAP_CFG2          (0x58u)
#define LSM6DSOX_TAP_THS_6D        (0x59u)
#define LSM6DSOX_INT_DUR2          (0x5Au)
#define LSM6DSOX_WAKE_UP_THS       (0x5Bu)
#define LSM6DSOX_WAKE_UP_DUR       (0x5Cu)
#define LSM6DSOX_FREE_FALL         (0x5Du)
#define LSM6DSOX_MD1_CFG           (0x5Eu)
#define LSM6DSOX_MD2_CFG           (0x5Fu)
#define LSM6DSOX_I3C_BUS_AVB       (0x62u)
#define LSM6DSOX_INTERNAL_FREQ     (0x63u)
#define LSM6DSOX_X_OFS_USR         (0x73u)
#define LSM6DSOX_Y_OFS_USR         (0x74u)
#define LSM6DSOX_Z_OFS_USR         (0x75u)
#define LSM6DSOX_FIFO_DATA_OUT_TAG (0x78u)
#define LSM6DSOX_FIFO_DATA_X_L     (0x79u)
#define LSM6DSOX_FIFO_DATA_X_H     (0x7Au)
#define LSM6DSOX_FIFO_DATA_Y_L     (0x7Bu)
#define LSM6DSOX_FIFO_DATA_Y_H     (0x7Cu)
#define LSM6DSOX_FIFO_DATA_Z_L     (0x7Du)
#define LSM6DSOX_FIFO_DATA_Z_H     (0x7Eu)

#define LSM6DSOX_DRDY_EN           (1u)


/*Register Bit map*/

//FUNC_CFG_ACCESS Register Bit map
#define DSOX_SHUB_REG_ACC                   (0b01000000)
#define DSOX_FUNC_CFG_ACC                   (0b10000000)

//PIN_CTRL Register Bit map
#define DSOX_SDO_PU_EN                      (0b01111111)

//FIFO_CTRL2 Register Bit map
#define DSOX_WTM8                           (0b00000001)
typedef enum
{
	DSOX_uncoptr_rate_not_forced = 0b00000000,
	DSOX_uncoptr_rate_8 =          0b00000010,
	DSOX_uncoptr_rate_16 =         0b00000100,
	dsox_uncoptr_rate_32 =         0b00000110,

}dsox_uncoptr_rate;
#define DSOX_ODRCHG_EN                      (0b00010000)
#define DSOX_FIFO_COMPR_RT_EN               (0b01000000)
#define DSOX_STOP_ON_WTM                    (0b10000000)


//FIFO_CTRL3 Register Bit map
typedef enum
{
	dsox_bdr_gy_no_batch = 0b00000000,
	dsox_bdr_gy_12_5 = 0b00010000,
	dsox_bdr_gy_26 =   0b00100000,
	dsox_bdr_gy_52 =   0b00110000,
	dsox_bdr_gy_104 =  0b01000000,
	dsox_bdr_gy_208 =  0b01010000,
	dsox_bdr_gy_417 =  0b01100000,
	dsox_bdr_gy_833 =  0b01110000,
	dsox_bdr_gy_1667 = 0b10000000,
	dsox_bdr_gy_3333 = 0b10010000,
	dsox_bdr_gy_6667 = 0b10100000,
	dsox_bdr_gy_6_5 =  0b10110000,
}dsox_bdr_gy;

typedef enum
{
	dsox_bdr_xl_no_batch = 0b00000000,
	dsox_bdr_xl_12_5 = 0b00000001,
	dsox_bdr_xl_26 =   0b00000010,
	dsox_bdr_xl_52 =   0b00000011,
	dsox_bdr_xl_104 =  0b00000100,
	dsox_bdr_xl_208 =  0b00000101,
	dsox_bdr_xl_417 =  0b00000110,
	dsox_bdr_xl_833 =  0b00000111,
	dsox_bdr_xl_1667 = 0b00001000,
	dsox_bdr_xl_3333 = 0b00001001,
	dsox_bdr_xl_6667 = 0b00001010,
	dsox_bdr_xl_1_6 =  0b00001011,
}dsox_bdr_xl;

//FIFO_CTRL4 Register Bit map
typedef enum
{
	dsox_fifo_mode_bypass =    0b00000000,
	dsox_fifo_mode_fifo =      0b00000001,
	dsox_fifo_mode_cont_fifo = 0b00000011,
	dsox_fifo_mode_bypass_cont = 0b00000100,
	dsox_fifo_mode_cont =       0b00000110,
	dsox_fifo_mode_bypass_fifo = 0b00000111,

}dsox_fifo_mode;
typedef enum
{
	dsox_odr_t_no_batch =     0b00000000,
	dsox_odr_t_batch_1_6Hz =  0b00010000,
	dsox_odr_t_batch_12_5Hz = 0b00100000,
	dsox_odr_t_batch_52Hz =   0b00110000,
}dsox_odr_t_batch;
typedef enum
{
	dsox_dec_ts_batch_no_ts = 0b00000000,
	dsox_dec_ts_1 =           0b01000000,
	dsox_dec_ts_8 =           0b10000000,
	dsox_dec_ts_32 =          0b11000000,

}dsox_dec_ts_batch;


//INT1_CTRL Register Bit map
#define DSOX_INT1_DRDY_XL                   (0b00000001)
#define DSOX_INT1_DRDY_GYRO                 (0b00000010)
#define DSOX_INT1_BOOT                      (0b00000100)
#define DSOX_INT1_FIFO_TH                   (0b00001000)
#define DSOX_INT1_FIFO_OVR                  (0b00010000)
#define DSOX_INT1_FIFO_FULL                 (0b00100000)
#define DSOX_INT1_CNT_BDR                   (0b01000000)
#define DSOX_DEN_DRDY_FLAG                  (0b10000000)

//INT2_CTRL Register Bit map
#define DSOX_INT2_DRDY_XL                   (0b00000001)
#define DSOX_INT2_DRDY_GYRO                 (0b00000010)
#define DSOX_INT2_DRDY_TEMP                 (0b00000100)
#define DSOX_INT2_FIFO_TH                   (0b00001000)
#define DSOX_INT2_FIFO_OVR                  (0b00010000)
#define DSOX_INT2_FIFO_FULL                 (0b00100000)
#define DSOX_INT2_CNT_BDR                   (0b01000000)

//CTRL1_XL Register Bit map
#define DSOX_LPF2_XL_EN                     (0b00000010)
typedef enum
{
	dsox_fs_xl_4g =  0b00000000,
	dsox_fs_xl_32g = 0b00000100,
	dsox_fs_xl_8g =  0b00001000,
	dsox_fs_xl_16g = 0b00001100,
}dsox_fs_xl;
typedef enum
{
	dsox_odr_xl_pd =      0b00000000,
	dsox_odr_xl_1_6Hz =   0b10110000,
	dsox_odr_xl_12_5Hz =  0b00010000,
	dsox_odr_xl_26Hz =    0b00100000,
	dsox_odr_xl_52Hz =    0b00110000,
	dsox_odr_xl_104Hz =   0b01000000,
	dsox_odr_xl_208Hz =   0b01010000,
	dsox_odr_xl_416Hz =   0b01100000,
	dsox_odr_xl_833Hz =   0b01110000,
	dsox_odr_xl_1_66kHz = 0b10000000,
	dsox_odr_xl_3_33kHz = 0b10010000,
	dsox_odr_xl_6_66kHz = 0b10100000,
}dsox_odr_xl;


//CTRL2_G Register Bit map
#define DSOX_FS_125                        (0b00000010)
typedef enum
{
	dsox_fs_g_250 =  0b00000000,
	dsox_fs_g_500 = 0b00000100,
	dsox_fs_g_1000 =  0b00001000,
	dsox_fs_g_2000 = 0b00001100,
}dsox_fs_g;
typedef enum
{
	dsox_odr_g_pd =      0b00000000,
	dsox_odr_g_12_5Hz =  0b00010000,
	dsox_odr_g_26Hz =    0b00100000,
	dsox_odr_g_52Hz =    0b00110000,
	dsox_odr_g_104Hz =   0b01000000,
	dsox_odr_g_208Hz =   0b01010000,
	dsox_odr_g_416Hz =   0b01100000,
	dsox_odr_g_833Hz =   0b01110000,
	dsox_odr_g_1_66kHz = 0b10000000,
	dsox_odr_g_3_33kHz = 0b10010000,
	dsox_odr_g_6_66kHz = 0b10100000,
}dsox_odr_g;

//CTRL_3 Register bit map
#define DSOX_SW_RESET                       (0b00000001)
#define DSOX_IF_INC                         (0b00000100)
#define DSOX_SIM_SPI_3_WIRE                 (0b00001000)
#define DSOX_PP_OD                          (0b00010000)
#define DSOX_H_LACTIVE                      (0b00100000)
#define DSOX_BDU                            (0b01000000)
#define DSOX_BOOT                           (0b10000000)

//CTRL4_C Register Bit map
#define DSOX_LPF1_SEL_G                     (0b00000010)
#define DSOX_I2C_DISABLE                    (0b00000100)
#define DSOX_DRDY_MASK                      (0b00001000)
typedef enum
{
	dsox_int_div_int1_int2 = 0b00000000,
	dsox_int_on_int1 =       0b00100000,
}dsox_int2_on_int1;
#define DSOX_SLEEP_G                        (0b01000000)

//CTRL5_C Register Bit map
typedef enum
{
	dsox_st_g_normal = 0b00000000,
	dsox_st_g_pos =    0b00000001,
	dsox_st_g_neg =    0b00000011,
}dsox_st_g;
typedef enum
{
	dsox_st_xl_normal = 0b00000000,
	dsox_st_xl_pos =    0b00000001,
	dsox_st_xl_neg =    0b00000010,
}dsox_st_xl;
typedef enum
{
	dsox_rounding_no =   0b00000000,
	dsox_rounding_xl =   0b00100000,
	dsox_rounding_g =    0b01000000,
	dsox_rounding_xl_g = 0b01100000,
}dsox_rounding;
#define DSOX_XL_ULP_EN                      (0b10000000)

//CTRL_9 Register Bit map
#define DSOX_I3C_DISABLE                    (0b00000010)
#define DSOX_DEN_XL_LH                      (0b00000100)
#define DSOX_DEN_XL_EN                      (0b00001000)
#define DSOX_DEN_XL_G                       (0b00010000)
#define DSOX_DEN_Z                          (0b00100000)
#define DSOX_DEN_Y                          (0b01000000)
#define DSOX_DEN_X                          (0b10000000)

//CTRL10_C Register Bit map
#define DSOX_TIMESTAMP_EN                   (0b00100000)

//ALL_INT_SRC Register Bit map
#define DSOX_FF_IA_INT                      (0b00000001)
#define DSOX_WU_IA_INT                      (0b00000010)
#define DSOX_SINGLE_TAP_INT                 (0b00000100)
#define DSOX_DOUBLE_TAP_INT                 (0b00001000)
#define DSOX_D6D_IA_INT                     (0b00010000)
#define DSOX_SLEEP_CHANGE_IA_INT            (0b00100000)
#define DSOX_TIMESTAMP_END_CNT_INT          (0b10000000)

//WAKE_UP_SRC Register Bit map
#define DSOX_Z_WU                           (0b00000001)
#define DSOX_Y_WU                           (0b00000010)
#define DSOX_X_WU                           (0b00000100)
#define DSOX_WU_IA                          (0b00001000)
#define DSOX_SLEEP_STATE                    (0b00010000)
#define DSOX_FF_IA                          (0b00100000)
#define DSOX_SLEEP_CHANGE_IA                (0b01000000)

//TAP_SRC Register Bit Map
#define DSOX_Z_TAP                          (0b00000001)
#define DSOX_Y_TAP                          (0b00000010)
#define DSOX_X_TAP                          (0b00000100)
#define DSOX_TAP_SIGN                       (0b00001000)
#define DSOX_DOUBLE_TAP                     (0b00010000)
#define DSOX_SINGLE_TAP                     (0b00100000)
#define DSOX_TAP_IA                         (0b01000000)

//D6D_SRC Register Bit map
#define DSOX_XL                             (0b00000001)
#define DSOX_XH                             (0b00000010)
#define DSOX_YL                             (0b00000100)
#define DSOX_YH                             (0b00001000)
#define DSOX_ZL                             (0b00010000)
#define DSOX_ZH                             (0b00100000)
#define DSOX_D6D_IA                         (0b01000000)
#define DSOX_DEN_DRDY                       (0b10000000)

//STATUS Register Bit map
#define DSOX_TDA                            (0b00100000)
#define DSOX_GDA                            (0b01000000)
#define DSOX_XLDA                           (0b10000000)


#endif

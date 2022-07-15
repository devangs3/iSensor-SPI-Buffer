/**
 ******************************************************************************
 * @file           : apds9960_reg.h
 * @brief          : Header for configuration registers for the proximity sensor
 ******************************************************************************
 **/



#ifndef __APDS9960_REG_H
#define __APDS9960_REG_H

/*Register addresses*/
#define APDS9960_WHOAMI                     (0x92u)
#define APDS9960_DEV_ID                     (0xABu)
#define APDS9960_ENABLE                     (0x80u)
#define APDS9960_ADC_INT_TIME               (0x81u)
#define APDS9960_WAIT_TIME                  (0x83u)
#define APDS9960_AILTL                      (0x84u)
#define APDS9960_AILTH                      (0x85u)
#define APDS9960_AIHTL                      (0x86u)
#define APDS9960_AIHTH                      (0x87u)
#define APDS9960_PILT                       (0x89u)
#define APDS9960_PIHT                       (0x8Bu)
#define APDS9960_PERSISTENCE                (0x8Cu)
#define APDS9960_CONF1                      (0x8Du)
#define APDS9960_PROX_PULSE                 (0x8Eu)
#define APDS9960_CTL1                       (0x8Fu)
#define APDS9960_CONF2                      (0x90u)
#define APDS9960_STATUS                     (0x93u)
#define APDS9960_PROXIMITY_DATA             (0x9Cu)
#define APDS9960_POFFSET_UR                 (0x9Du)
#define APDS9960_POFFSET_DL                 (0x9Eu)
#define APDS9960_CONF3                      (0x9Fu)
#define APDS9960_LOW_THRESHOLD              (0x89u)
#define APDS9960_HIGH_THRESHOLD             (0x8Bu)
#define APDS9960_PROXIMITY_INT_CLEAR        (0xE5u)

/*Register Bit Maps*/

//ENABLE Register Bit map
#define APDS_POWER_ON                        (0b00000001)
#define APDS_ALS_ENABLE                      (0b00000010)
#define APDS_PROXIMITY_ENABLE                (0b00000100)
#define APDS_WAIT_ENABLE                     (0b00001000)
#define APDS_ALS_INT_ENABLE                  (0b00010000)
#define APDS_PROX_INT_ENABLE                 (0b00100000)
#define APDS_GESTURE_ENABLE                  (0b01000000)

//PERSISTENCE Register bit map
typedef enum
{
	apds_p_int_every_cycle       = 0b00000000,
	apds_p_any_outside_threshold = 0b00010000,
	apds_p_out_range_2         = 0b00100000,
	apds_p_out_range_3         = 0b00110000,
	apds_p_out_range_4         = 0b01000000,
	apds_p_out_range_5         = 0b01010000,
	apds_p_out_range_6         = 0b01100000,
	apds_p_out_range_7         = 0b01110000,
	apds_p_out_range_8         = 0b10000000,
	apds_p_out_range_9         = 0b10010000,
	apds_p_out_range_10         = 0b10100000,
	apds_p_out_range_11         = 0b10110000,
	apds_p_out_range_12         = 0b11000000,
	apds_p_out_range_13         = 0b11010000,
	apds_p_out_range_14         = 0b11100000,
	apds_p_out_range_15         = 0b11110000,
}apds_ppers;

typedef enum
{
	apds_a_int_every_cycle       = 0b00000000,
	apds_a_any_outside_threshold = 0b00010000,
	apds_a_out_range_2         = 0b00100000,
	apds_a_out_range_3         = 0b00110000,
	apds_a_out_range_5         = 0b01000000,
	apds_a_out_range_10         = 0b01010000,
	apds_a_out_range_15         = 0b01100000,
	apds_a_out_range_20         = 0b01110000,
	apds_a_out_range_25         = 0b10000000,
	apds_a_out_range_30         = 0b10010000,
	apds_a_out_range_35         = 0b10100000,
	apds_a_out_range_40         = 0b10110000,
	apds_a_out_range_45         = 0b11000000,
	apds_a_out_range_50         = 0b11010000,
	apds_a_out_range_55         = 0b11100000,
	apds_a_out_range_60         = 0b11110000,
}apds_apers;

//CONF1 Register Bit map
#define APDS_WLONG                      (0b01100010)

//PROX_PULSE Register Bit map
typedef enum
{
	apds_pulse_4us =  0b00000000,
	apds_pulse_8us =  0b01000000,
	apds_pulse_16us = 0b10000000,
	apds_pulse_32us = 0b11000000,
}apds_pplen;

//CTRL1 Register Bit map
typedef enum
{
	apds_led_drive_curr_100  = 0b00000000,
	apds_led_drive_curr_50   = 0b01000000,
	apds_led_drive_curr_25   = 0b10000000,
	apds_led_drive_curr_12_5 = 0b11000000,
}apds_led_drive_curr;

typedef enum
{
	apds_pgain_1x   = 0b00000000,
	apds_pgain_2x   = 0b00000100,
	apds_pgain_4x   = 0b00001000,
	apds_pgain_8x   = 0b00001100,
}apds_pgain;

typedef enum
{
	apds_again_1x   = 0b00000000,
	apds_again_2x   = 0b00000001,
	apds_again_4x   = 0b00000010,
	apds_again_8x   = 0b00000011,
}apds_again;

//CONF2 Register Bit map
#define APDS_PSIEN                   (0b10000001)
#define APDS_CPSIEN                  (0b01000001)
typedef enum
{
	apds_led_boost_100 = 0b00000001,
	apds_led_boost_150 = 0b00010001,
	apds_led_boost_200 = 0b00100001,
	apds_led_boost_300 = 0b00110001,
}apds_led_curr_boost;

//STATUS Register Bit map
#define APDS_AVALID                           (0b00000001)
#define APDS_PVALID                           (0b00000010)
#define APDS_GINT                             (0b00000100)
#define APDS_AINT                             (0b00010000)
#define APDS_PINT                             (0b00100000)
#define APDS_PGSAT                            (0b01000000)
#define APDS_CPSAT                            (0b10000000)

//CONF3 Register Bit Map
#define APDS_PMASK_R                          (0b00000001)
#define APDS_PMASK_L                          (0b00000010)
#define APDS_PMASK_D                          (0b00000100)
#define APDS_PMASK_U                          (0b00001000)
#define APDS_SAI                              (0b00010000)
#define APDS_PCMP                             (0b00100000)


#endif

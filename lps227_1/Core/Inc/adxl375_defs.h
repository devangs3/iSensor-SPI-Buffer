/**
 ******************************************************************************
 * @file           : asxl375_defs.h
 * @brief          : Header for configuration registers
 ******************************************************************************
 **/


#ifndef __ADXL375_DEFS_H
#define __ADXL375_DEFS_H

#include "comm_abstraction.h"

//Configuration and data registers
#define ADXL375_WHOAMI          (0x00u)
#define ADXL375_DEV_ID          (0xE5u)
#define ADXL375_THRESH_SHOCK    (0x1Du)
#define ADXL375_OFF_X           (0x1Eu)
#define ADXL375_OFF_Y           (0x1Fu)
#define ADXL375_OFF_Z           (0x20u)
#define ADXL375_DUR             (0x21u)
#define ADXL375_LATENT          (0x22u)
#define ADXL375_WINDOW          (0x23u)
#define ADXL375_THRESH_ACT      (0x24u)
#define ADXL375_THRESH_INACT    (0x25u)
#define ADXL375_TIME_INACT      (0x26u)
#define ADXL375_ACT_INACT_CTL   (0x27u)
#define ADXL375_SHOCK_AXES      (0x2Au)
#define ADXL375_ACT_SHOCK_STAT  (0x2Bu)
#define ADXL375_BW_RATE         (0x2Cu)
#define ADXL375_POWER_CTL       (0x2Du)
#define ADXL375_INT_ENABLE      (0x2Eu)
#define ADXL375_INT_MAP         (0X2Fu)
#define ADXL375_INT_SRC         (0x30u)
#define ADXL375_DATA_FMT        (0x31u)
#define ADXL375_DATA_X_0        (0x32u)
#define ADXL375_DATA_X_1        (0x33u)
#define ADXL375_DATA_Y_0        (0x34u)
#define ADXL375_DATA_Y_1        (0x35u)
#define ADXL375_DATA_Z_0        (0x36u)
#define ADXL375_DATA_Z_1        (0x37u)
#define ADXL375_FIFO_CTL        (0x38u)
#define ADXL375_FIFO_STATUS     (0x39u)

#define ADXL375_DRDY_EN     (1)

/*Register maps*/


//ACT_INACT_CTL Register Bit map
#define A375_INACT_Z_ENABLE                  (0b00000001)
#define A375_INACT_Y_ENABLE                  (0b00000010)
#define A375_INACT_X_ENABLE                  (0b00000100)
#define A375_INACT_AC_DC                     (0b00001000)
#define A375_ACT_Z_ENABLE                    (0b00010000)
#define A375_ACT_Y_ENABLE                    (0b00100000)
#define A375_ACT_X_ENABLE                    (0b01000000)
#define A375_ACT_AC_DC                       (0b10000000)


//SHOCK_AXES Register Bit map
#define A375_SHOCK_Z_ENABLE                  (0b00000001)
#define A375_SHOCK_Y_ENABLE                  (0b00000010)
#define A375_SHOCK_X_ENABLE                  (0b00000100)
#define A375_SUPPRESS                        (0b00001000)

//ACT_SHOCK_STATUS Register Bit map
#define A375_SHOCK_Z_SOURCE                  (0b00000001)
#define A375_SHOCK_Y_SOURCE                  (0b00000010)
#define A375_SHOCK_X_SOURCE                  (0b00000100)
#define A375_ASLEEP                          (0b00001000)
#define A375_ACT_Z_SOURCE                    (0b00010000)
#define A375_ACT_Y_SOURCE                    (0b00100000)
#define A375_ACT_X_SOURCE                    (0b01000000)

//BW_RATE Register bit map
typedef enum
{
	a375_output_freq_3200Hz = 0b00001111,
	a375_output_freq_1600Hz = 0b00001110,
	a375_output_freq_800Hz =  0b00001101,
	a375_output_freq_400Hz =  0b00001100,
	a375_output_freq_200Hz =  0b00001011,
	a375_output_freq_100Hz =  0b00001010,
	a375_output_freq_50Hz =   0b00001001,
	a375_output_freq_25Hz =   0b00001000,
	a375_output_freq_12_5Hz = 0b00000111,
	a375_output_freq_6_25Hz = 0b00000110,
	a375_output_freq_3_13Hz = 0b00000101,
	a375_output_freq_1_56Hz = 0b00000100,
	a375_output_freq_0_78Hz = 0b00000011,
	a375_output_freq_0_39Hz = 0b00000010,
	a375_output_freq_0_20Hz = 0b00000001,
	a375_output_freq_0_10Hz = 0b00000000,

}a375_rate;
#define A375_LOW_POWER                       (0b00010000)


//POWER_CTL Register Bit map
//Wake-up bit (bit 0 and 1)
typedef enum
{
	a375_freq_8Hz = 0b00000000,
	a375_freq_4Hz = 0b00000001,
	a375_freq_2Hz = 0b00000010,
	a375_freq_1Hz = 0b00000011

}a375_wakeup;
#define A375_SLEEP                           (0b00000100)
#define A375_MEASURE                         (0b00001000)
#define A375_AUTO_SLEEP                      (0b00010000)
#define A375_LINK                            (0b00100000)

//INT_ENABLE Register Bit Map
#define A375_OVERRUN                         (0b00000001)
#define A375_WATERMARK                       (0b00000010)
#define A375_INACTIVITY                      (0b00001000)
#define A375_ACTIVITY                        (0b00010000)
#define A375_DOUBLE_SHOCK                    (0b00100000)
#define A375_SINGLE_SHOCK                    (0b01000000)
#define A375_DATA_READY                      (0b10000000)

//INT_MAP Register Bit Map
//Setting a bit to 1 directs the interrupts to INT Pin 2
#define A375_INT2_OVERRUN                    (0b00000001)
#define A375_INT2_WATERMARK                  (0b00000010)
#define A375_INT2_INACTIVITY                 (0b00001000)
#define A375_INT2_ACTIVITY                   (0b00010000)
#define A375_INT2_DOUBLE_SHOCK               (0b00100000)
#define A375_INT2_SINGLE_SHOCK               (0b01000000)
#define A375_INT2_DATA_READY                 (0b10000000)

//INT_SOURCE Register Bit Map
#define A375_OVERRUN_S                       (0b00000001)
#define A375_WATERMARK_S                     (0b00000010)
#define A375_INACTIVITY_S                    (0b00001000)
#define A375_ACTIVITY_S                      (0b00010000)
#define A375_DOUBLE_SHOCK_S                  (0b00100000)
#define A375_SINGLE_SHOCK_S                  (0b01000000)
#define A375_DATA_READY_S                    (0b10000000)

//DATA_FORMAT Register Bit Map
typedef enum
{
	a375_justify_leftMSB =  0b00001111,
	a375_justify_rightLSB = 0b00001011,

}a375_justify;

typedef enum
{
	a375_INT_PIN_ACT_HIGH = 0b00001011,
	a375_INT_PIN_ACT_LOW =  0b00101011,
}a375_int_invert;

typedef enum
{
	a375_SPI_3_WIRE_MODE = 0b01001011,
	a375_SPI_4_WIRE_MODE = 0b00001011,
}a375_spi_mode;
#define SELF_TST                            (0b10001011)

//FIFO_CTL Register Bit map
typedef enum
{
	a375_trigger_INT1_pin = 0b00000000,
	a375_trigger_INT2_pin = 0b00100000,
}a375_trigger;
typedef enum
{
	a375_mode_bypass =  0b00000000,
	a375_mode_FIFO =    0b01000000,
	a375_mode_stream =  0b10000000,
	a375_mode_trigger = 0b11000000
}a375_fifo_mode;


//FIFO_STATUS Register Bit map
#define A375_TRIGGER_EVENT                  (0b10000000)

#endif

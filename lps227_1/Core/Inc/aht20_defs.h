/**
 ******************************************************************************
 * @file           : aht20_defs.h
 * @brief          : Header for configuration registers
 ******************************************************************************
 **/


#ifndef __AHT20_DEFS_H
#define __AHT20_DEFS_H

#include "comm_abstraction.h"

/*Configuration registers*/
#define AHT20_STATUS          (0x71u)
#define AHT20_INIT            (0xBEu)
#define AHT20_MEASURE         (0xACu)
#define AHT20_SOFT_RESET      (0xBAu)

#define AHT20_POWERON_TIME    (40u)
#define AHT20_IS_CALIB        (0x08u)
#define AHT20_SEQ_TIME        (10u)
#define AHT20_SOFT_RESET_TIME (20u)
#define AHT20_CONV_TIME       (80u)
#define AHT20_STATUS_BIT      (0x01u)

#endif

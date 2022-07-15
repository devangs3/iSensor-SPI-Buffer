/**
 ******************************************************************************
 * @file           : vcnl4040_defs.h
 * @brief          : Header for configuration registers for the proximity
 ******************************************************************************
 **/



#ifndef __VCNL4040_DEFS_H
#define __VCNL4040_DEFS_H

#include "comm_abstraction.h"

#define VCNL4040_ALS_CONF          (0x00u)
#define VCNL4040_ALS_THDH          (0x01u)
#define VCNL4040_ALS_THDL          (0x02u)
#define VCNL4040_PS_CONF1          (0x03u)
#define VCNL4040_PS_CONF2          (0x03u)
#define VCNL4040_PS_CONF3          (0x04u)
#define VCNL4040_PS_LOW_THR        (0x06u)
#define VCNL4040_PS_HIGH_THR       (0x07u)
#define VCNL4040_PS_DATA           (0x08u)
#define VCNL4040_ALS_DATA          (0x09u)
#define VCNL4040_WHITE_DATA        (0x0Au)
#define VCNL4040_INT_FLAGS         (0x0Bu)
#define VCNL4040_WHOAMI            (0x0Cu)
#define VCNL4040_DEV_ID_LSB        (0x86u)
#define VCNL4040_DEV_ID_MSB        (0x01u)



#endif

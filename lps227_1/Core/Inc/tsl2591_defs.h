/**
 ******************************************************************************
 * @file           : tsl2591_defs.h
 * @brief          : Header for configuration registers
 ******************************************************************************
 **/


#ifndef __TSl2591_DEFS_H
#define __TSl2591_DEFS_H

#define TSL2591_CMD_BIT   (0xA0u)
#define TSL2591_ENABLE    (0x00u)
#define TSL2591_CTRL      (0x01u)
#define TSL2591_AILTL     (0x04u)
#define TSL2591_AILTH     (0x05u)
#define TSL2591_AIHTL     (0x06u)
#define TSL2591_AIHTH     (0x07u)
#define TSL2591_NPAILTL   (0x08u)
#define TSL2591_NPAILTH   (0x09u)
#define TSL2591_NPAIHTL   (0x0Au)
#define TSL2591_NPAIHTH   (0x0Bu)
#define TSL2591_PERSIST   (0x0Cu)
#define TSL2591_PID       (0x11u)
#define TSL2591_ID        (0x12u)
#define TSL2591_STATUS    (0x13u)
#define TSL2591_C0DATAL   (0x14u)
#define TSL2591_C0DATAH   (0x15u)
#define TSL2591_C1DATAL   (0x16u)
#define TSL2591_C1DATAH   (0x17u)
#define TSL2591_DEV_ID    (0x50u)
#define TSL2591_PID_NO    (0x00u)
#define TSL2591_LUX_DF    (408.0F)
#define TSL2591_GAIN_HIGH (428.0F)
#define TSL2591_INT_TIME  (100.0F)

#endif

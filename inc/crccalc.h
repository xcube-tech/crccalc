/******************* Copyright *********************
        Copyright (C) 2020 lhmagic
        lhmagic@139.com
        All right reserved.
 **************************************************/

#ifndef __CRCCALC_H__
#define __CRCCALC_H__

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#include "common.h"

/**************************************************
  Select a CRC parameter.
 **************************************************/
//#define CRC_16_MODBUS

/**************************************************
  CRC parameter template.
 **************************************************/
#if defined CRC_8
	#define	CRC_POLY		0x07
	#define	CRC_INIT		0x00
	#define	CRC_OUT_XOR		0x00
	#define	CRC_BIT_REV		false
#elif defined CRC_8_ITU
	#define	CRC_POLY		0x07
	#define	CRC_INIT		0x00
	#define	CRC_OUT_XOR		0x55
	#define	CRC_BIT_REV		false
#elif defined CRC_8_ROHC
	#define	CRC_POLY		0x07
	#define	CRC_INIT		0xFF
	#define	CRC_OUT_XOR		0x00
	#define	CRC_BIT_REV		true
#elif defined CRC_8_MAXIM
	#define	CRC_POLY		0x31
	#define	CRC_INIT		0x00
	#define	CRC_OUT_XOR		0x00
	#define	CRC_BIT_REV		true
#elif defined CRC_16_IBM
	#define	CRC_POLY		0x8005
	#define	CRC_INIT		0x0000
	#define	CRC_OUT_XOR		0x0000
	#define	CRC_BIT_REV		true
#elif defined CRC_16_MAXIM
	#define	CRC_POLY		0x8005
	#define	CRC_INIT		0x0000
	#define	CRC_OUT_XOR		0xFFFF
	#define	CRC_BIT_REV		true
#elif defined CRC_16_USB
	#define	CRC_POLY		0x8005
	#define	CRC_INIT		0xFFFF
	#define	CRC_OUT_XOR		0xFFFF
	#define	CRC_BIT_REV		true
#elif defined CRC_16_MODBUS
	#define	CRC_POLY		0x8005
	#define	CRC_INIT		0xFFFF
	#define	CRC_OUT_XOR		0x0000
	#define	CRC_BIT_REV		true
#elif defined CRC_16_CCITT
	#define	CRC_POLY		0x1021
	#define	CRC_INIT		0x0000
	#define	CRC_OUT_XOR		0x0000
	#define	CRC_BIT_REV		true
#elif defined CRC_16_CCITT_FALSE
	#define	CRC_POLY		0x1021
	#define	CRC_INIT		0xFFFF
	#define	CRC_OUT_XOR		0x0000
	#define	CRC_BIT_REV		false
#elif defined CRC_16_X25
	#define	CRC_POLY		0x1021
	#define	CRC_INIT		0xFFFF
	#define	CRC_OUT_XOR		0xFFFF
	#define	CRC_BIT_REV		true
#elif defined CRC_16_XMODEM
	#define	CRC_POLY		0x1021
	#define	CRC_INIT		0x0000
	#define	CRC_OUT_XOR		0x0000
	#define	CRC_BIT_REV		false
#elif defined CRC_16_DNP
	#define	CRC_POLY		0x3D65
	#define	CRC_INIT		0x0000
	#define	CRC_OUT_XOR		0xFFFF
	#define	CRC_BIT_REV		true
#elif defined CRC_32
	#define	CRC_POLY		0x04C11DB7
	#define	CRC_INIT		0xFFFFFFFF	
	#define	CRC_OUT_XOR		0xFFFFFFFF
	#define	CRC_BIT_REV		true
#elif defined CRC_32_MPEG_2
	#define	CRC_POLY		0x04C11DB7
	#define	CRC_INIT		0xFFFFFFFF	
	#define	CRC_OUT_XOR		0x00000000
	#define	CRC_BIT_REV		false
#else
	#error "undefined crc type!"
#endif



void CreateCrcTable(void);
uint8_t Crc8Calc(uint8_t *buff, uint32_t len);
uint16_t Crc16Calc(uint8_t *buff, uint32_t len);
uint32_t Crc32Calc(uint8_t *buff, uint32_t len);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif	//__CRCCALC_H__ 

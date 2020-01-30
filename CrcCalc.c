#include "crccalc.h"
#include <stdio.h>

/******************* Generic Cyclic Redundancy Check Calculate *********************
 * @brief Generic cyclic redundancy check calculate.
 *        To avoid bit reverse for every byte, we just reverse the polymorphic.
 *		  The calculated result should be swaped by byte before return.
 * @param buff : character buff start address.
 *		  cnt : character buff count.
 * @retval CRC calculate result, MSB first.
 **********************************************************************************/

#if defined	(CRC_8) || defined (CRC_8_ITU) || defined (CRC_8_ROHC) || defined(CRC_8_MAXIM)
uint8_t Crc8Calc(uint8_t *buff, uint32_t len) {
uint8_t crc = CRC_INIT;

	while(len--) {
#if (CRC_BIT_REV == true)
		for(uint8_t i=0x01; i!=0; i<<=1) {
			crc = (crc & 0x01) ? ((crc >> 1) ^ ReverseUint8(CRC_POLY)) : (crc >> 1);
			crc = (*buff & i) ? (crc ^ ReverseUint8(CRC_POLY)) : crc;
		}
#else
		for(uint8_t i=0x80; i!=0; i>>=1) {
			crc = (crc & 0x80) ? ((crc << 1) ^ CRC_POLY) : (crc << 1);
			crc = (*buff & i) ? (crc ^ CRC_POLY) : crc;
		}
#endif		
		buff++;
	}

	return crc ^= CRC_OUT_XOR;
}

#elif defined (CRC_16_IBM) || defined (CRC_16_MAXIM) || defined (CRC_16_USB) || \
      defined (CRC_16_MODBUS) || defined (CRC_16_CCITT) ||defined (CRC_16_CCITT_FALSE) || \
      defined (CRC_16_X25) || defined (CRC_16_XMODEM) || defined (CRC_16_DNP)
uint16_t Crc16Calc(uint8_t *buff, uint32_t len) {
uint16_t crc = CRC_INIT;

	while(len--) {
#if (CRC_BIT_REV == true)
		for(uint8_t i=1; i!=0; i<<=1) {
			crc = (crc & 0x0001) ? ((crc >> 1) ^ ReverseUint16(CRC_POLY)) : (crc >> 1);
			crc = (*buff & i) ? (crc ^ ReverseUint16(CRC_POLY)) : crc;
		}
#else
		for(uint8_t i=0x80; i!=0; i>>=1) {
			crc = (crc & 0x8000) ? ((crc << 1) ^ CRC_POLY) : (crc << 1);
			crc = (*buff & i) ? (crc ^ CRC_POLY) : crc;
		}
#endif		
		buff++;
	}

	crc ^= CRC_OUT_XOR;

	return SwapUint16(crc);
}

#elif defined (CRC_32) || defined (CRC_32_MPEG_2)
uint32_t Crc32Calc(uint8_t *buff, uint32_t len) {
uint32_t crc = CRC_INIT;

	while(len--) {
#if (CRC_BIT_REV == true)
		for(uint8_t i=1; i!=0; i<<=1) {
			crc = (crc & 0x00000001) ? ((crc >> 1) ^ ReverseUint32(CRC_POLY)) : (crc >> 1);
			crc = (*buff & i) ? (crc ^ ReverseUint32(CRC_POLY)) : crc;
		}
#else
		for(uint8_t i=0x80; i!=0; i>>=1) {
			crc = (crc & 0x80000000) ? ((crc << 1) ^ CRC_POLY) : (crc << 1);
			crc = (*buff & i) ? (crc ^ CRC_POLY) : crc;
		}
#endif		
		buff++;
	}

	crc ^= CRC_OUT_XOR;

	return SwapUint32(crc);
}
#endif

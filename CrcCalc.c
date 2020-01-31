/******************* Copyright *********************
        Copyright (C) 2020 lhmagic
        lhmagic@139.com
        All right reserved.
 **************************************************/

#include "crccalc.h"
#include <stdio.h>

#if defined	(CRC_8) || defined (CRC_8_ITU) || defined (CRC_8_ROHC) || defined(CRC_8_MAXIM)
//crc-8 fast lookup table.
static uint8_t crcTable[256] = {0};

#elif defined (CRC_16_IBM) || defined (CRC_16_MAXIM) || defined (CRC_16_USB) || \
      defined (CRC_16_MODBUS) || defined (CRC_16_CCITT) ||defined (CRC_16_CCITT_FALSE) || \
      defined (CRC_16_X25) || defined (CRC_16_XMODEM) || defined (CRC_16_DNP)
//crc-16 fast lookup table.
static uint16_t crcTable[256] = {0};

#elif defined (CRC_32) || defined (CRC_32_MPEG_2)
//crc-32 fast lookup table.
static uint32_t crcTable[256] = {0};

#endif

/******************* Construct CRC fast lookup table *********************
 * @brief Generic cyclic redundancy check fast lookup table.
 *        To avoid bit reverse for every byte, we just reverse the polymorphic.
 *		  The calculated result stored in the crcTable array by MSB first.
 * @param none.
 * @retval none.
 ************************************************************************/
void CreateCrcTable(void) {
#if defined	(CRC_8) || defined (CRC_8_ITU) || defined (CRC_8_ROHC) || defined(CRC_8_MAXIM)
#if (CRC_BIT_REV == true)
uint8_t poly = ReverseUint8(CRC_POLY);
#else
uint8_t poly = CRC_POLY;
uint8_t msb = 0x80;
#endif
uint8_t crc = 0;
#elif defined (CRC_16_IBM) || defined (CRC_16_MAXIM) || defined (CRC_16_USB) || \
      defined (CRC_16_MODBUS) || defined (CRC_16_CCITT) ||defined (CRC_16_CCITT_FALSE) || \
      defined (CRC_16_X25) || defined (CRC_16_XMODEM) || defined (CRC_16_DNP)
#if (CRC_BIT_REV == true)
uint16_t poly = ReverseUint16(CRC_POLY);
#else
uint16_t poly = CRC_POLY;
uint16_t msb = 0x8000;
#endif
uint16_t crc = 0;
#elif defined (CRC_32) || defined (CRC_32_MPEG_2)
#if (CRC_BIT_REV == true)
uint32_t poly = ReverseUint32(CRC_POLY);
#else
uint32_t poly = CRC_POLY;
uint32_t msb = 0x80000000;
#endif
uint32_t crc = 0;
#endif

    for(uint16_t i=0; i<256; i++) {
        crc = 0;
#if (CRC_BIT_REV == true)
        for(uint8_t j=0x01; j!=0; j<<=1) {
            crc = (crc & 0x01) ? ((crc >> 1) ^ poly) : (crc >> 1);
            crc = (i & j) ? (crc ^ poly) : crc;
        }
#if defined (CRC_8) || defined (CRC_8_ITU) || defined (CRC_8_ROHC) || defined(CRC_8_MAXIM)
        crcTable[i] = crc;
#elif defined (CRC_16_IBM) || defined (CRC_16_MAXIM) || defined (CRC_16_USB) || \
      defined (CRC_16_MODBUS) || defined (CRC_16_CCITT) ||defined (CRC_16_CCITT_FALSE) || \
      defined (CRC_16_X25) || defined (CRC_16_XMODEM) || defined (CRC_16_DNP)             
        crcTable[i] = SwapUint16(crc);
#elif defined (CRC_32) || defined (CRC_32_MPEG_2)
        crcTable[i] = SwapUint32(crc);
#endif
#else
        for(uint8_t j=0x80; j!=0; j>>=1) {
            crc = (crc & msb) ? ((crc << 1) ^ poly) : (crc << 1);
            crc = (i & j) ? (crc ^ poly) : crc;
        }
#if defined (CRC_8) || defined (CRC_8_ITU) || defined (CRC_8_ROHC) || defined(CRC_8_MAXIM)
        crcTable[i] = crc;
#elif defined (CRC_16_IBM) || defined (CRC_16_MAXIM) || defined (CRC_16_USB) || \
      defined (CRC_16_MODBUS) || defined (CRC_16_CCITT) ||defined (CRC_16_CCITT_FALSE) || \
      defined (CRC_16_X25) || defined (CRC_16_XMODEM) || defined (CRC_16_DNP)             
        crcTable[i] = crc;
#elif defined (CRC_32) || defined (CRC_32_MPEG_2)
        crcTable[i] = crc;
#endif        
#endif
    }
}

#if defined	(CRC_8) || defined (CRC_8_ITU) || defined (CRC_8_ROHC) || defined(CRC_8_MAXIM)
/******************* Cyclic Redundancy Check Calculate *********************
 * @brief Generic crc-8 calculate.
 *        To avoid bit reverse for every byte, we reverse the polymorphic.
 * @param buff : character buff start address.
 *		  cnt : character buff count.
 * @retval CRC calculate result.
 **************************************************************************/
uint8_t Crc8Calc(uint8_t *buff, uint32_t len) {
uint8_t crc = CRC_INIT;

	while(len--) {
        crc = crcTable[crc ^ (*buff++)];
	}

	return crc ^ CRC_OUT_XOR;
}

#elif defined (CRC_16_IBM) || defined (CRC_16_MAXIM) || defined (CRC_16_USB) || \
      defined (CRC_16_MODBUS) || defined (CRC_16_CCITT) ||defined (CRC_16_CCITT_FALSE) || \
      defined (CRC_16_X25) || defined (CRC_16_XMODEM) || defined (CRC_16_DNP)
/******************* Cyclic Redundancy Check Calculate *********************
 * @brief Generic crc-16 calculate.
 *		  The calculated result already be swaped in the fast lookup table.
 * @param buff : character buff start address.
 *		  cnt : character buff count.
 * @retval CRC calculate result, MSB first.
 **************************************************************************/
uint16_t Crc16Calc(uint8_t *buff, uint32_t len) {
uint16_t crc = CRC_INIT;

    while(len--) {
        crc = (crc << 8) ^ crcTable[(crc >> 8) ^ (*buff++)];
	}

#if (CRC_BIT_REV == true)
  return (crc ^ CRC_OUT_XOR);
#else
  return SwapUint16(crc ^ CRC_OUT_XOR);
#endif
}

#elif defined (CRC_32) || defined (CRC_32_MPEG_2)
/******************* Cyclic Redundancy Check Calculate *********************
 * @brief Generic crc-32 calculate.
 *		  The calculated result already be swaped in the fast lookup table.
 * @param buff : character buff start address.
 *		  cnt : character buff count.
 * @retval CRC calculate result, MSB first.
 **************************************************************************/
uint32_t Crc32Calc(uint8_t *buff, uint32_t len) {
uint32_t crc = CRC_INIT;

	while(len--) {
        crc = (crc << 8) ^ crcTable[(crc >> 24) ^ (*buff++)];
	}

#if (CRC_BIT_REV == true)
  return (crc ^ CRC_OUT_XOR);
#else
  return SwapUint32(crc ^ CRC_OUT_XOR);
#endif
}
#endif

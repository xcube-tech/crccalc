/******************* Copyright *********************
        Copyright (C) 2020 lhmagic
        lhmagic@139.com
        All right reserved.
 **************************************************/

#include <stdio.h>
#include "crccalc.h"

int main(void) {
    CreateCrcTable();
#if defined	(CRC_8) || defined (CRC_8_ITU) || defined (CRC_8_ROHC) || defined(CRC_8_MAXIM)    
    printf("\r\nTest result:%#x\r\n", Crc8Calc((uint8_t *)"0123456789", 10));
#elif defined (CRC_16_IBM) || defined (CRC_16_MAXIM) || defined (CRC_16_USB) || \
      defined (CRC_16_MODBUS) || defined (CRC_16_CCITT) ||defined (CRC_16_CCITT_FALSE) || \
      defined (CRC_16_X25) || defined (CRC_16_XMODEM) || defined (CRC_16_DNP)
    printf("\r\nTest result:%#x\r\n", Crc16Calc((uint8_t *)"0123456789", 10));
#elif defined (CRC_32) || defined (CRC_32_MPEG_2)
    printf("\r\nTest result:%#x\r\n", Crc32Calc((uint8_t *)"0123456789", 10));
#endif          
}

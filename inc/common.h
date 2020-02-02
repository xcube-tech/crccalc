/******************* Copyright *********************
        Copyright (C) 2020 lhmagic
        lhmagic@139.com
        All right reserved.
 **************************************************/

#ifndef	__COMMON_H__
#define	__COMMON_H__

#ifdef __cplusplus
 extern "C" {
#endif //__cplusplus

#include <stdint.h>
#include <stdbool.h>

uint16_t SwapUint16(uint16_t val);
uint32_t SwapUint32(uint32_t val);
uint8_t ReverseUint8(uint8_t val);
uint16_t ReverseUint16(uint16_t val);
uint32_t ReverseUint32(uint32_t val) ;

#ifdef __cplusplus
}
#endif //__cplusplus

#endif	//__COMMON_H__

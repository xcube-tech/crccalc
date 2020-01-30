#include "common.h"

/******************* swap half word *********************
 * @brief swap a half word high byte n low byte.
 * @param val : half word value to be swapped.
 * @retval swapped value.
 *******************************************************/
uint16_t SwapUint16(uint16_t val) {
	return (val << 8) | (val >> 8);
}

/******************* swap hole word *********************
 * @brief swap hole word.
 * @param val : word value to be swapped.
 * @retval swapped value.
 *******************************************************/
uint32_t SwapUint32(uint32_t val) {
	return (SwapUint16(val & 0xFFFF) << 16) | SwapUint16(val >> 16);
}

/******************* byte bit reverse *********************
 * @brief reverse a byte with bit level.
 * @param val : byte value to be reversed.
 * @retval reversed value.
 *********************************************************/
uint8_t ReverseUint8(uint8_t val) {
	val = ((val & 0x55) << 1) | ((val & 0xAA) >> 1);
	val = ((val & 0x33) << 2) | ((val & 0xCC) >> 2);
	val = ((val & 0x0F) << 4) | ((val & 0xF0) >> 4);
	return val;
}

/******************* half word bit reverse *********************
 * @brief reverse a half word with bit level.
 * @param val : half word value to be reversed.
 * @retval reversed value.
 **************************************************************/
uint16_t ReverseUint16(uint16_t val) {
	return (ReverseUint8(val & 0xFF) << 8) | (ReverseUint8(val >> 8));
}

/******************* word bit reverse *********************
 * @brief reverse a word with bit level.
 * @param val : word value to be reversed.
 * @retval reversed value.
 *********************************************************/
uint32_t ReverseUint32(uint32_t val) {
	return (ReverseUint16(val & 0xFFFF) << 16) | (ReverseUint16(val >> 16));
}
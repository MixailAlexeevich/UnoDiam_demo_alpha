// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Utils.h"


#ifdef INVERSE_BYTE_ORDER
uint32_t byteswapUINT32(uint32_t bytes4) {
	return (bytes4 >> 24) | (bytes4 << 24) | ((bytes4 << 8) & 0xff0000) | ((bytes4 >> 8) & 0xff00);
}

uint16_t byteswapUINT16(uint16_t bytes2) {
	return (bytes2 >> 8) | (bytes2 << 8);
}
#endif

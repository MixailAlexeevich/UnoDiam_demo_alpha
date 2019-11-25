#ifndef Utils_h
#define Utils_h
#include "Platform.h"

#ifdef INVERSE_BYTE_ORDER
uint32_t byteswapUINT32(uint32_t bytes4);
uint16_t byteswapUINT16(uint16_t bytes2);
#endif

#endif
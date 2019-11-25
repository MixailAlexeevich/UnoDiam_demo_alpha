#ifndef PlatformBasic_h
#define PlatformBasic_h
#include "Compiler.h"

#if defined(COMPILER_MS)

#if defined(_M_IX86) || defined(_M_X64) || defined(_M_IA64) || defined(_M_ARM)
// Big-endian
#elif defined(_M_PPC)
// Little-endian
#define INVERSE_BYTE_ORDER
#else
#error "Unknown endianes!"
#endif

#if defined(WIN32)
	//Windows 32
	#define PLATFORM_WIN32
#elif defined(_WIN64)
	//Windows 64
	#define PLATFORM_WIN64
#else
	//Unknown
	#error "Unknown OS platform and achitecture."
#endif

#else

#endif

#endif

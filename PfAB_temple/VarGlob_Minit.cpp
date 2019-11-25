// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Platform.h"

//Size of path of bin folder in bytes
uint16_t directory_Working_btlen;

#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)

wchar_t directory_Working[FOLDER_MAX_PATH];
//Size of path of bin folder in wchar_t
uint16_t directory_Working_wcharlen;

#else

char directory_Working[FOLDER_MAX_PATH];

#endif
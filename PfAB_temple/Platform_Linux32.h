#ifndef Platform_Linux32_h
#define Platform_Linux32_h
#include "PlatformBasic.h"
#ifdef PLATFORM_LINUX32

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FOLDER_MAX_PATH PATH_MAX

/*
 *	CORE DEBUG AREA
 */
#ifdef PLATFORM_API_ESCAPING
 //Escaped (MEMAPI)
void* __cdecl memcpy(void* _Dst, void const* _Src, size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void* __cdecl malloc(size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void* __cdecl calloc(size_t _Count, size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void* __cdecl realloc(void* _Block, size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void __cdecl free(void* _Block) { }

//Escaped (C-STR)
wchar_t* wcscat(wchar_t* dst, const wchar_t* src) { return nullptr; }
//Escaped (C-STR)
wchar_t* wcscpy(wchar_t _Destination, const wchar_t* _Source) { return nullptr; }
//Escaped (C-STR)
size_t wcslen(wchar_t const* _String) { return 0; }

//Escaped (FILESYSTEM)
FILE* fopen(const char *path, const char *mode) { return nullptr; }
//Escaped (FILESYSTEM)
int fclose(FILE* stream) { return 0; }

#endif
#endif
#endif

#ifndef Platform_Win32_h
#define Platform_Win32_h
#include "PlatformBasic.h"
#ifdef PLATFORM_WIN32

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

#define FOLDER_MAX_PATH MAX_PATH

/*
 *	CORE DEBUG AREA
 */
#ifdef PLATFORM_API_ESCAPING
 //Escaped (MEMAPI)
void *__cdecl memcpy(void* _Dst, void const* _Src, size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void *__cdecl malloc(size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void *__cdecl calloc(size_t _Count, size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void *__cdecl realloc(void *_Block, size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void __cdecl free(void* _Block) { }

//Escaped (LOADERAPI)
HMODULE WINAPI LoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) { return NULL; }

//Escaped (C-STR)
wchar_t* wcscat(wchar_t* dst, const wchar_t* src) { return nullptr; }
//Escaped (C-STR)
wchar_t* wcscpy(wchar_t _Destination, const wchar_t* _Source) { return nullptr; }
//Escaped (C-STR)
size_t wcslen( wchar_t const* _String) { return 0; }

//Escaped (FILESYSTEM)
FILE* _wfopen(const wchar_t* path, const wchar_t* mode) { return nullptr; }
//Escaped (FILESYSTEM)
int fclose(FILE* stream) { return 0; }

//Escaped (FILESYSTEM)
DWORD WINAPI GetCurrentDirectoryW(DWORD nBufferLength, LPWSTR lpBuffer) { return 0; }
//Escaped (SYNCAPI)
HANDLE WINAPI CreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName) { return NULL; }
//Escaped (SYNCAPI)
HANDLE WINAPI OpenMutexA(DWORD dwDesiredAccess, BOOL bInheritHandle, LPCSTR lpName) { return NULL; }
//Escaped (WINBASE)
BOOL WINAPI CloseHandle(HANDLE hObject) { return TRUE; }

//Escaped (THAPI)
HANDLE WINAPI CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) { return 0; }

#endif
#endif
#endif
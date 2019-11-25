#ifndef Platform_Win64_h
#define Platform_Win64_h
#include "PlatformBasic.h"
#ifdef PLATFORM_WIN64

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
void* memcpy(void* _Dst, void const* _Src, size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void* malloc(size_t _Size) { return nullptr; }
//Escaped (MEMAPI)
void free(void* _Block) { }


//Escaped (C-STR)
wchar_t* wcscat(wchar_t* dst, const wchar_t* src) { return nullptr; }
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
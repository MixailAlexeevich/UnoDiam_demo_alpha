// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Platform.h"
#include "Error.h"

#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS

void (*UnoDiam_core_ErrorCallback)(void* errorinfo) = nullptr;
void PostTextError(const char *errtext, uint8_t generation, uint8_t place) {
	if (UnoDiam_core_ErrorCallback) {
		if (place) {
			UnoDiam_core_ErrorHandle_ecgt estr = { 2, place, generation, errtext };
			UnoDiam_core_ErrorCallback(&estr);
		} else {
			UnoDiam_core_ErrorHandle_text estr = { 1, errtext };
			UnoDiam_core_ErrorCallback(&estr);
		}
	}
	exit(EXIT_FAILURE);
}

void PostTextError(const char *errtext, const char *addictional, uint8_t place, uint8_t generation) {
	char *errstr = new char[strlen(errtext) + strlen(addictional) + 1]; //delete[] not need because program is exit
	strcpy(errstr, errtext); strcat(errstr, addictional);
	if (UnoDiam_core_ErrorCallback) {
		if (place) {
			UnoDiam_core_ErrorHandle_ecgt estr = { 2, place, generation, errstr };
			UnoDiam_core_ErrorCallback(&estr);
		} else {
			UnoDiam_core_ErrorHandle_text estr = { 1, errstr };
			UnoDiam_core_ErrorCallback(&estr);
		}
	}
	exit(EXIT_FAILURE);
}

void PostTextError(const char *errtext, const wchar_t *addictional, uint8_t place, uint8_t generation) {
	uint8_t errtextlen = strlen(errtext); //-V1029
	uint8_t msize = (wcslen(addictional) * sizeof(wchar_t) << 1) + 1;
	char *errstr = new char[errtextlen + msize]; //delete[] not need because program is exit
	strcpy(errstr, errtext); wcstombs(errstr + errtextlen, addictional, msize);
	if (UnoDiam_core_ErrorCallback) {
		if (place) {
			UnoDiam_core_ErrorHandle_ecgt estr = { 2, place, generation, errstr };
			UnoDiam_core_ErrorCallback(&estr);
		} else {
			UnoDiam_core_ErrorHandle_text estr = { 1, errstr };
			UnoDiam_core_ErrorCallback(&estr);
		}
	}
	exit(EXIT_FAILURE);
}

#endif
#if !defined(Error_h) && defined(ENABLE_INPUTDATA_CORRECT_CHECKS)
#define Error_h
#include "Platform.h"

struct UnoDiam_core_ErrorHandle_text {
	uint8_t type; //0 - unknown error, 1 - text description, 2 - error code, error generation type, text description
	const char *description;
};

struct UnoDiam_core_ErrorHandle_ecgt {
	uint8_t type; //0 - unknown error, 1 - text description, 2 - error code, error generation type, text description
	uint8_t place; //Pseudo-posoition of exception
	uint8_t generation; //0 - critical, 1 - uninformed launcher (path length problem or else), 2 - broken core technical files, 3 - broken data in program, 4 - broken module
	const char *description;
};
//latests place (non-free!) - 8

void PostTextError(const char *errtext, uint8_t place = 0, uint8_t generation = 0);
void PostTextError(const char *errtext, const char *addictional, uint8_t place = 0, uint8_t generation = 0);
void PostTextError(const char *errtext, const wchar_t *addictional, uint8_t place = 0, uint8_t generation = 0);

#endif
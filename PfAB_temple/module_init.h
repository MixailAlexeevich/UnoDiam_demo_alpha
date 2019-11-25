#ifndef module_init_h
#define module_init_h
#include "Platform.h"
#include "ModuleBasic.h"

//TODO: add processing for uninitialized modules (iterative loading) - "hidden" stage of initialising - compability processing

struct Module_temp { //TODO: Add other starage for others like Notify, ExtAPI, etc.
	bool init_success;

#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64) //Platform with "wchar_t" system standart (windows-like)
	HMODULE library;
	wchar_t *module_path;
#elif defined(PLATFORM_LINUX32)) //Platform with "char" system standart (unix-like)
	void *library;
	char *module_path;
#endif
	//TODO: add extended parameters storing (ext_params)
};

extern Module_temp *module_init_storage, *module_init_storage_end;

#endif

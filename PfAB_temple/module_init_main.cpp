// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Platform.h"
#include "module_init.h"
#include "Error.h"

Module_temp *module_init_storage, *module_init_storage_end;



struct Intarface_SCI_reg_struct {
	void *context;
	uint8_t(*SCI_checkbytes)(const void *context, const uint8_t *bytes, uint8_t count);
	uint8_t(*SCI_receivebytes)(const void *context, uint8_t *bytes, uint8_t count);
};

static uint8_t fnIntarface_SCI_reg(const void *context, const Intarface_SCI_reg_struct *struct_SCI_reg) {
	return 0;
}

/*interaction - "flag mode" only
0x1 - sync, 0x2 - async, 0x3 - sync & async, 0x0 not supported
0x4 - onethread, 0x8 - multithread, 0xC - onethread & multithread, 0x0 not supported
0x10 - send, 0x20 - receive, 0x00 - process, 0x30 not supported
0x40 == 0 - call, 0x40 == 1 - stream

//"process" can't be executed neither with "async" call mode nor by "stream" mode
//also feilds "groupID" and "pseudoFunction" will be ignored
*/
/*tags - help for linker. Filled in at the discretion of the programmer. Recomended.
description - help for linker. Someday it will be analyzed by the neural network (natural language parser) for contextually more accurate connection of interfaces.
*/
struct Intarface_UCI_reg_struct {
	uint8_t interaction; //0x3 - sync/async possibilites, 0xC - onethread/multithread possibilites, 0x30 - direction, 0x40 - call/stream
	uint8_t groupID; //groupid, gpoups only for send/receive interfaces
	uint8_t pseudoFunction; //0 - processing, 1 - receiving (from external system), 2 - sending (to external system), 3 - generating (create call/stream without external), 4 - terminating (receive call/stream like branch of main process track)
	uint16_t viftual_interfaces_count;
	void *viftual_interfaces;
	void *meta;
	void *special_linker_instructions; 
	void *context;
	const char *tags; //ANSI-C string, words-divided by '\n'. Word may contain only: space, uppercase and lowercase latin letters, digits 0-9, symbols: ./
	const char *description; //ANSI-C string
	
};

static uint8_t fnIntarface_UCI_reg(const void *context, const Intarface_UCI_reg_struct *struct_UCI_reg) {
	return 0;
}

const struct Module_init_main_reg_struct {
	uint8_t (*Intarface_SCI_reg)(const void *context, const Intarface_SCI_reg_struct *struct_SCI_reg) = &fnIntarface_SCI_reg;
	//TODO: Add others functions
} Module_init_main_reg;

typedef void(*Module_init_main)(const void *, const Module_init_main_reg_struct *); //module_init_main

#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
DWORD WINAPI ModuleM_init(CONST LPVOID lpParam)
#else
#error "Haven't main thread entry point!"
#endif
{

#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
	Module_init_main libcurrent = reinterpret_cast<Module_init_main>(GetProcAddress(module_init_storage_end->library, "module_init_main"));
	if (!libcurrent)
		PostTextError("UnoDiem core can't find 'module_init_main' entrypoint in module: ", module_init_storage_end->module_path, 8, 4);
	libcurrent(lpParam, &Module_init_main_reg);
#else
	reinterpret_cast<Module_init_first>(GetProcAddress(module_init_storage_end->library, "module_init_first"))(lpParam, &Module_init_main_reg);
#endif
	return 0;
}
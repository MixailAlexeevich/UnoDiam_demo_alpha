#ifndef ModuleBasic_h
#define ModuleBasic_h
#include "Platform.h"

struct Module {
	void *UCI_start, *UCI_end;
	void *SCI_start, *SCI_end;
};

extern uint16_t modules_count;
extern Module *modules;

#endif

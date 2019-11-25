#ifndef Platform_h
#define Platform_h

//Forward all system API function calls to the debug side.
//#define PLATFORM_API_ESCAPING 

//0 - without check (dangerous! by faster), 1 - only one instance per system, 2 - only one instance per Working Directory (only for current system) (slower), 3 - only one instance per Work Directory (for all systems)
#define WORKFOLDER_INSTANCE_CHECK 3

//If defined, it will disable UnoDiam file/folder structure check and checking size of the names (longest name must be shorter than FOLDER_MAX_PATH); it increases speed of core starting
//#define LAUNCHER_INFORMED

//If defined, core will expect current working directory is "UnoDiam_root/bin" (otherwise - "UnoDiam_root"). Depends on launcher! Recommended.
#define WORKING_DIRECTORY_IS_BIN

//Enable checks like file existing, filestructure, etc. (without that checke uncorrect params may crash core!). Recomended on building assembly. In daily use is not required - slows down loading a bit.
#define ENABLE_INPUTDATA_CORRECT_CHECKS

//Include all platforms
#include "Platform_Win32.h"
#include "Platform_Win64.h"

#endif
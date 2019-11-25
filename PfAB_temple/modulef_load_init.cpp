// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Platform.h"
#include "Global.h"
#include "module_init.h"
#include "Error.h"
#include "Utils.h"


extern Module_temp *module_init_storage, *module_init_storage_end; //Global variable for RequestSpecial access

static struct struct_PossibleVersions {
	uint8_t pr_release, pr_beta, pr_alpha; //Previous version
	uint8_t nx_release, nx_beta, nx_alpha; //Next version
} PossibleVersions;

static void* module_init_RequeslSpecialVersion(uint8_t release, uint8_t beta, uint8_t alpha, uint8_t evp) {
	return 0;
}

static const struct struct_CurrentVersion {
	const uint8_t release = RELEASE;
	const uint8_t beta = BETA;
	const uint8_t alpha = ALPHA;
	const uint8_t evp = 0;
	void* (*RequeslSpecialVersion)(uint8_t release, uint8_t beta, uint8_t alpha, uint8_t evp) = &module_init_RequeslSpecialVersion;
} CurrentVersion;

typedef uint8_t(*Module_init_first)(const struct_CurrentVersion*); //module_init_first

extern uint16_t directory_Working_btlen;

/*MLFv1 specification
|2|2|4|{1}|{...}|[...]
first - count of stored paths
second - size of extended params in bytes
third - size of stored paths in bytes
fourth - count of cells (1 byte) by first param value. Represetns count of bytes in concrete path.
fifth - path's bytes
sixth - extended param bytes
*/

#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
extern wchar_t *directory_Working;
extern uint16_t directory_Working_wcharlen;
extern DWORD WINAPI ModuleM_init(CONST LPVOID lpParam);

DWORD WINAPI ModuleF_load_init(CONST LPVOID lpParam)
#else
#error "Haven't main thread entry point!"
#endif
{
	//TODO: Add VMF (version management file)
	wchar_t fmodlist_path[FOLDER_MAX_PATH];
	memcpy(fmodlist_path, directory_Working, directory_Working_btlen);
	memcpy(fmodlist_path + directory_Working_wcharlen, L"load_mdlist.bin", sizeof(wchar_t) * 16);

	//TODO: Add compability modules list file (also add table to load compability first)
	FILE *fmodlist = _wfopen(fmodlist_path, L"r");

#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
	if (!fmodlist)
		PostTextError("Module List File (MLFv1) does not exist!", 1, 2);
#endif

	struct MLFv1_header {
		uint16_t path_count;
		uint16_t ext_data_bytes_count;
		uint32_t path_bytes_count;
	} mlf1;
#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
	if (fread(&mlf1, sizeof(MLFv1_header), 1, fmodlist) != 8 || !mlf1.path_count) { //-V1004
		fclose(fmodlist);
		return 0;
	}
#else
	fread(&mlf1, sizeof(MLFv1_header), 1, fmodlist);
#endif
#ifdef INVERSE_BYTE_ORDER
	mlf1.path_count = byteswapUINT16(mlf1.path_count);
	mlf1.ext_data_bytes_count = byteswapUINT16(mlf1.ext_data_bytes_count);
	mlf1.path_bytes_count = byteswapUINT32(mlf1.path_bytes_count);
#endif //TODO: Think abount checking "nullptr" after malloc, calloc, realloc
	uint8_t *path_sizes = reinterpret_cast<uint8_t *>(malloc(mlf1.path_count));
#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
	if (fread(path_sizes, 1, mlf1.path_count, fmodlist) != mlf1.path_count) //-V575
		PostTextError("Module List File (MLFv1) was uncorrect!", 2, 2);
#else
	fread(path_sizes, 1, mlf1.path_count, fmodlist);
#endif

	char *pathes_unix = reinterpret_cast<char *>(malloc(mlf1.path_bytes_count)); //Array of pathes (all pathes here)
#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
	if (fread(pathes_unix, 1, mlf1.path_bytes_count, fmodlist) != mlf1.path_bytes_count) //-V575
		PostTextError("Module List File (MLFv1) was uncorrect!", 3, 2);
#else
	fread(pathes, 1, mlf1.path_bytes_count, fmodlist);
#endif
	Module_temp *modpointer_e = module_init_storage_end = (Module_temp *)calloc(mlf1.path_count, sizeof(Module_temp));

	{ //This block only to isolate temple variables
		register uint8_t *psizes = path_sizes;
#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
		//Process unix-like paths to windows-like paths
		char *pathes_unx_temp = pathes_unix;
		wchar_t *pathes_win = reinterpret_cast<wchar_t *>(malloc(mlf1.path_bytes_count * sizeof(wchar_t)));
		for (uint8_t *psizes_e = path_sizes + mlf1.path_count; psizes != psizes_e; ++psizes) {
			(modpointer_e++)->module_path = pathes_win; //Postfix Inc //-V769
			pathes_win += mbstowcs(pathes_win, pathes_unx_temp, *psizes) + sizeof(wchar_t); //-V522 //-V575 //-V769
			pathes_unx_temp += *psizes;
		}
		//module_init_storage_end->module_path = reinterpret_cast<wchar_t *>(realloc(module_init_storage_end->module_path, (pathes_win - module_init_storage_end->module_path) * sizeof(wchar_t))); //-V701
		free(pathes_unix);
		free(path_sizes);
#elif defined(PLATFORM_LINUX32)
		for (uint8_t *psizes_e = path_sizes + mlf1.path_count; psizes != psizes_e; ++psizes) {
			(modpointer_e++)->module_path = pathes_unix; //Postfix Inc
			pathes_unix += *psizes;
		}
#else
#error "Haven't paths load rule!"
#endif
	}
	
	if (mlf1.ext_data_bytes_count) {
		uint8_t *ext_params = reinterpret_cast<uint8_t *>(malloc(mlf1.ext_data_bytes_count));
#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
		if (fread(ext_params, 1, mlf1.ext_data_bytes_count, fmodlist) != mlf1.ext_data_bytes_count) //-V575
			PostTextError("Module List File (MLFv1) was uncorrect!", 4, 2);
#else
		fread(pathes, 1, mlf1.path_bytes_count, fmodlist);
#endif
		//TODO: Add exteded module params parsing and passing to ModuleInitPretendent
		free(ext_params);
	}
	fclose(fmodlist);


#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
	wchar_t path_buffer[FOLDER_MAX_PATH], *path_buffer_write;
	
	memcpy(path_buffer, directory_Working, directory_Working_btlen);
	path_buffer_write = path_buffer + directory_Working_wcharlen;
	memcpy(path_buffer_write, L"modules\\", sizeof(wchar_t) * 8);
	path_buffer_write += 8;
#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
	Module_init_first libcurrent;
	uint8_t namesize;
	uint16_t inputstrsize = directory_Working_wcharlen + 8;
#endif
#elif defined(PLATFORM_LINUX32)
	char path_buffer[FOLDER_MAX_PATH], *path_buffer_write;

	memcpy(path_buffer, directory_Working, directory_Working_btlen);
	path_buffer_write = path_buffer + directory_Working_btlen;
	memcpy(path_buffer_write, "modules/", 8);
	path_buffer_write += 8;
#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
	Module_init_first libcurrent;
	uint8_t namesize;
	uint16_t inputstrsize = directory_Working_wcharlen + 8;
#endif
#error "Haven't prepare fo loading libaries"
#else
#error "Haven't prepare fo loading libaries"
#endif
	module_init_storage = module_init_storage_end;
	for (; module_init_storage_end != modpointer_e; ++module_init_storage_end) {
#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
	#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
		namesize = wcslen(module_init_storage_end->module_path); //-V1029
		if (inputstrsize + namesize + 5 > FOLDER_MAX_PATH) //4 - size of ".dll" + 1 (null-term)
			PostTextError("UnoDiem core can't process module path - too long!\n", module_init_storage_end->module_path, 5, 1);
		memcpy(path_buffer_write, module_init_storage_end->module_path, (namesize + 1) * sizeof(wchar_t));
		memcpy(path_buffer_write + namesize, L".dll", 5 * sizeof(wchar_t));

		module_init_storage_end->library = LoadLibraryExW(path_buffer, NULL, LOAD_IGNORE_CODE_AUTHZ_LEVEL);
		if (!module_init_storage_end->library)
			PostTextError("UnoDiem core can't load module: ", module_init_storage_end->module_path, 6, 4);
		if (!(libcurrent = reinterpret_cast<Module_init_first>(GetProcAddress(module_init_storage_end->library, "module_init_first"))))
			PostTextError("UnoDiem core can't find 'module_init_first' entrypoint in module: ", module_init_storage_end->module_path, 7, 4);
		if (libcurrent(&CurrentVersion))
			module_init_storage_end->init_success = true;
	#else
		wcscpy(path_buffer_write, module_init_storage_end->module_path);
		wcscat(path_buffer_write, L".dll");
		module_init_storage_end->library = LoadLibraryExW(path_buffer, NULL, LOAD_IGNORE_CODE_AUTHZ_LEVEL);
		if (reinterpret_cast<Module_init_first>(GetProcAddress(module_init_storage_end->library, "module_init_first"))(&CurrentVersion))
			module_init_storage_end->init_success = true;
	#endif
#elif defined(PLATFORM_LINUX32) //UNIX
	//Copy and change code above for unix
	//Use path sizes from "pathes_unix" array
	#error "Haven't known load library function!"
#else
	#error "Haven't known load library function!"
#endif
	}
	
#if defined(PLATFORM_LINUX32)
	free(pathes_unix);
#endif

	for (module_init_storage_end = module_init_storage; module_init_storage_end != modpointer_e; ++module_init_storage_end)
		if (module_init_storage_end->init_success)
	#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
			CloseHandle(CreateThread(NULL, STACK_SIZE_MML, &ModuleM_init, module_init_storage_end, 0, NULL));
	#endif

	//TODO: Tech loop
	return 0;
}

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "Platform.h"
#include "Global.h"

extern uint16_t directory_Working_btlen;

static const uint8_t COREFILE_FILENAME_MAX_LEN_ABIN = COREFILE_FILENAME_MAX_LEN + 4; //4 - size of "\bin"

//LIBRARY INIT ON SYSTEM LEVEL
#if WORKFOLDER_INSTANCE_CHECK != 0

#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
extern wchar_t* directory_Working;
extern uint16_t directory_Working_wcharlen;

#if WORKFOLDER_INSTANCE_CHECK == 3 //Lock file processing
static FILE *fileLock = nullptr;
#else //Mutex processing
static HANDLE mutexStart = NULL;

#include <accctrl.h>
#include <aclapi.h>

#ifdef PLATFORM_API_ESCAPING //Create mutex funcs escape
//Escaped (SECAPI)
BOOL WINAPI AllocateAndInitializeSid(PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority, BYTE nSubAuthorityCount, DWORD nSubAuthority0, DWORD nSubAuthority1, DWORD nSubAuthority2, DWORD nSubAuthority3, DWORD nSubAuthority4, DWORD nSubAuthority5, DWORD nSubAuthority6, DWORD nSubAuthority7, PSID* pSid) { return TRUE; }
//Escaped (SECAPI)
DWORD WINAPI SetEntriesInAclA(ULONG cCountOfExplicitEntries, PEXPLICIT_ACCESS_A  pListOfExplicitEntries, PACL OldAcl, PACL* NewAcl) { return ERROR_SUCCESS; }
//Escaped (SECAPI)
BOOL WINAPI InitializeSecurityDescriptor(PSECURITY_DESCRIPTOR pSecurityDescriptor, DWORD dwRevision) { return TRUE; }
//Escaped (SECAPI)
BOOL WINAPI SetSecurityDescriptorDacl(PSECURITY_DESCRIPTOR pSecurityDescriptor, BOOL bDaclPresent, PACL pDacl, BOOL bDaclDefaulted) { return TRUE; }
//Escaped (SECAPI)
PVOID WINAPI FreeSid(PSID pSid) { return nullptr; }
//Escaped (WINBASE)
HLOCAL WINAPI LocalFree(HLOCAL hMem) { return 0; }
#endif

#if WORKFOLDER_INSTANCE_CHECK == 2 //Check by mutex on directory
#include "wincrypt.h"

#ifdef PLATFORM_API_ESCAPING //Wincrypt escape
//WINCRYPT SECTOR

//Escaped (WINCRYPT)
BOOL WINAPI CryptAcquireContextA(HCRYPTPROV* phProv, LPCSTR szContainer, LPCSTR szProvider, DWORD dwProvType, DWORD dwFlags) { return TRUE; };
//Escaped (WINCRYPT)
BOOL WINAPI CryptCreateHash(HCRYPTPROV hProv, ALG_ID Algid, HCRYPTKEY hKey, DWORD dwFlags, HCRYPTHASH* phHash) { return TRUE; }
//Escaped (WINCRYPT)
BOOL WINAPI CryptHashData(HCRYPTHASH hHash, CONST BYTE* pbData, DWORD dwDataLen, DWORD dwFlags) { return TRUE; }
//Escaped (WINCRYPT)
BOOL WINAPI CryptGetHashParam(HCRYPTHASH hHash, DWORD dwParam, BYTE* pbData, DWORD* pdwDataLen, DWORD dwFlags) { return TRUE; }
//Escaped (WINCRYPT)
BOOL WINAPI CryptReleaseContext(HCRYPTPROV hProv, DWORD dwFlags) { return TRUE; }
//Escaped (WINCRYPT)
BOOL WINAPI CryptDestroyHash(HCRYPTHASH hHash) { return TRUE; }
#endif
#endif

#endif

#ifdef PLATFORM_API_ESCAPING
BOOL APIENTRY DebugEP_DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
#else
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
#endif
{
#if WORKFOLDER_INSTANCE_CHECK == 3
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		directory_Working_wcharlen = static_cast<uint16_t>(GetCurrentDirectoryW(FOLDER_MAX_PATH, directory_Working));
#ifdef LAUNCHER_INFORMED
		if (!directory_Working_wcharlen) return FALSE;
#else
	#ifdef WORKING_DIRECTORY_IS_BIN
		if (!directory_Working_wcharlen || directory_Working_wcharlen + COREFILE_FILENAME_MAX_LEN > FOLDER_MAX_PATH) return FALSE;
	#else
		if (!directory_Working_wcharlen || directory_Working_wcharlen + COREFILE_FILENAME_MAX_LEN_ABIN > FOLDER_MAX_PATH) return FALSE;
	#endif
#endif
	#ifdef WORKING_DIRECTORY_IS_BIN
		memcpy(directory_Working + directory_Working_wcharlen, L"\\", sizeof(wchar_t));
		directory_Working_btlen = (directory_Working_wcharlen += 1) * sizeof(wchar_t);
	#else
		memcpy(directory_Working + directory_Working_wcharlen, L"\\bin\\", sizeof(wchar_t) * 5);
		directory_Working_btlen = (directory_Working_wcharlen += 5) * sizeof(wchar_t);
	#endif
		wchar_t folderPath[FOLDER_MAX_PATH];
		memcpy(folderPath, directory_Working, directory_Working_btlen);
		memcpy(folderPath + directory_Working_wcharlen, L"core_session.lock", sizeof(wchar_t) * 18);
		if (!(fileLock = _wfopen(folderPath, L"w")))
			return FALSE;
	} break;
	case DLL_PROCESS_DETACH:
		fclose(fileLock);
		break;
	}
#else
#if WORKFOLDER_INSTANCE_CHECK == 2
	directory_Working_wcharlen = static_cast<uint16_t>(GetCurrentDirectoryW(FOLDER_MAX_PATH, directory_Working));
#ifdef LAUNCHER_INFORMED
	if (!directory_Working_wcharlen) return FALSE;
#else
	#ifdef WORKING_DIRECTORY_IS_BIN
		if (!directory_Working_wcharlen || directory_Working_wcharlen + COREFILE_FILENAME_MAX_LEN > FOLDER_MAX_PATH) return FALSE;
	#else
		if (!directory_Working_wcharlen || directory_Working_wcharlen + COREFILE_FILENAME_MAX_LEN_ABIN > FOLDER_MAX_PATH) return FALSE;
	#endif
#endif
#ifdef WORKING_DIRECTORY_IS_BIN
	memcpy(directory_Working + directory_Working_wcharlen, L"\\", sizeof(wchar_t));
	directory_Working_btlen = (directory_Working_wcharlen += 1) * sizeof(wchar_t);
#else
	memcpy(directory_Working + directory_Working_wcharlen, L"\\bin\\", sizeof(wchar_t) * 5);
	directory_Working_btlen = (directory_Working_wcharlen += 5) * sizeof(wchar_t);
#endif

	char mutexName[58] = "Global\\UnoDiam_core_", * mutexNameP;

	char rgbDigits[] = "0123456789abcdef"; //For hexadecimal representation of bytes in hash
	HCRYPTPROV hProv = NULL;
	HCRYPTHASH hHash = NULL;
	BYTE rgbHash[20], *rgbHp, *rgbHe;

	//Hash generator by WinCrypt
	if (!CryptAcquireContextA(&hProv, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) return FALSE;
	if (!CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash)) {
		CryptReleaseContext(hProv, 0);
		return FALSE;
	}
	if (!CryptHashData(hHash, reinterpret_cast<BYTE*>(directory_Working), directory_Working_btlen, 0)) {
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		return FALSE;
	}
	DWORD cbHash = 20;
	if (!CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0)) {
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		return FALSE;
	}
	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);

	for (rgbHp = rgbHash, rgbHe = rgbHash + 20, mutexNameP = mutexName + 16; rgbHp != rgbHe; ++rgbHp) {
		*(++mutexNameP) = rgbDigits[*rgbHp >> 4];
		*(++mutexNameP) = rgbDigits[*rgbHp & 0xf];
	}
	*(++mutexNameP) = '\0';

#else
	char mutexName[] = "Global\\UnoDiam_core_{643B1194-6342-4D35-87B2-1A46AC0572ED}";
#endif
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		mutexStart = OpenMutexA(SYNCHRONIZE, FALSE, mutexName);
		if (!mutexStart) {
			PSID pEveryoneSid = NULL;
			SID_IDENTIFIER_AUTHORITY sia = SECURITY_WORLD_SID_AUTHORITY;
			if (!AllocateAndInitializeSid(&sia, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pEveryoneSid))
				return FALSE;

			EXPLICIT_ACCESS_A ea[1] = { 0 };
			(*ea).grfAccessMode = SET_ACCESS; //Equvivalent of "->" used bacause "operator->" raise warning.
			ea->grfAccessPermissions = SYNCHRONIZE;
			ea->grfInheritance = NO_INHERITANCE;
			ea->Trustee.TrusteeForm = TRUSTEE_IS_SID;
			ea->Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
			ea->Trustee.ptstrName = (LPSTR)pEveryoneSid;

			PACL pDacl = NULL;
			if (SetEntriesInAclA(1, ea, NULL, &pDacl) != ERROR_SUCCESS) {
				FreeSid(pEveryoneSid);
				return FALSE;
			}

			SECURITY_DESCRIPTOR sd;
			if (!(InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION) && SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE))) {
				FreeSid(pEveryoneSid);
				LocalFree(pDacl);
				return FALSE;
			}

			SECURITY_ATTRIBUTES sa;
			sa.nLength = sizeof(sa);
			sa.lpSecurityDescriptor = &sd;
			sa.bInheritHandle = FALSE;
			mutexStart = CreateMutexA(&sa, TRUE, mutexName); //-V718

			FreeSid(pEveryoneSid);
			LocalFree(pDacl);
		} else return FALSE;
		break;
	case DLL_PROCESS_DETACH:
		if (mutexStart) CloseHandle(mutexStart);
		break;
	}
#endif
    return TRUE;
}
#else //OTHER PLATFORMS
#error "Haven't library entry point!"
#endif //PLATFORM_WIN32
#endif //WORKFOLDER_INSTANCE_CHECK != 0

#include "Global.h"

#if defined(PLATFORM_WIN32) || defined(PLATFORM_WIN64)
DWORD WINAPI ModuleF_load_init(CONST LPVOID lpParam);

extern wchar_t* directory_Working;

extern "C" uint8_t LIBRARY_EXPORT UnoDiam_core_start() {
#if WORKFOLDER_INSTANCE_CHECK != 2 && WORKFOLDER_INSTANCE_CHECK != 3
	directory_Working_wcharlen = static_cast<uint16_t>(GetCurrentDirectoryW(FOLDER_MAX_PATH, directory_Working));
#ifdef LAUNCHER_INFORMED
	if (!directory_Working_wcharlen) return FALSE;
#else
	#ifdef WORKING_DIRECTORY_IS_BIN
		if (!directory_Working_wcharlen || directory_Working_wcharlen + COREFILE_FILENAME_MAX_LEN > FOLDER_MAX_PATH) return FALSE;
	#else
		if (!directory_Working_wcharlen || directory_Working_wcharlen + COREFILE_FILENAME_MAX_LEN_ABIN > FOLDER_MAX_PATH) return FALSE;
	#endif
#endif
#ifdef WORKING_DIRECTORY_IS_BIN
	memcpy(directory_Working + directory_Working_wcharlen, L"\\", sizeof(wchar_t));
	directory_Working_btlen = (directory_Working_wcharlen += 1) * sizeof(wchar_t);
#else
	memcpy(directory_Working + directory_Working_wcharlen, L"\\bin\\", sizeof(wchar_t) * 5);
	directory_Working_btlen = (directory_Working_wcharlen += 5) * sizeof(wchar_t);
#endif

#endif
	HANDLE handle_mainTechThread = CreateThread(NULL, STACK_SIZE_TECH, &ModuleF_load_init, NULL, 0, NULL);

	if (handle_mainTechThread) CloseHandle(handle_mainTechThread);
	else return 1;

	return 0;
}
#else
#error "Haven't UnoDiam main entry point"
#endif


extern "C" uint8_t LIBRARY_EXPORT UnoDiam_core_LIO(void *LIO_init) {
	//LIO register
	return 0;
}

#ifdef ENABLE_INPUTDATA_CORRECT_CHECKS
extern void (*UnoDiam_core_ErrorCallback)(void *errorinfo);
extern "C" void LIBRARY_EXPORT UnoDiam_core_ErrorCallback_reg(void (*ErrorCallback)(void* errorinfo)) {
	UnoDiam_core_ErrorCallback = ErrorCallback;
}
#endif
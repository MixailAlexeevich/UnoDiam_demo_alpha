#ifndef Compiler_h
#define Compiler_h

/*#include "PfAB.project"*/

//More compilers:
//https://sourceforge.net/p/predef/wiki/Compilers/
//https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html

#if defined(_MSC_VER)
	//MSVC
	#define LIBRARY_EXPORT __declspec(dllexport)
	#define COMPILER_MS
#elif defined(__GNUC__)
	//GCC
	#define LIBRARY_EXPORT __attribute__((visibility("default")))
	#define COMPILER_GCC
#elif defined(__MINGW64__) || defined(__MINGW32__)
	//MinGW compilers
	#error "MinGW compilers are not supported yet!"
#elif defined(__clang__)
	//Clang
	#error "Clang is not supported yet!"
#else
	//Unknown
	#error "Unknown compiler!"
#endif

#endif
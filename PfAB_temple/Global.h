#ifndef Glob_h
#define Glob_h
#include <stdint.h>

const uint8_t RELEASE = 0, BETA = 0, ALPHA = 1;

const size_t STACK_SIZE_TECH = 4 << 20; //TODO: This parameter must be loaded from the configuration file
const size_t STACK_SIZE_MML = 1 << 20; //TODO: This parameter must be loaded from the configuration file

const uint8_t COREFILE_FILENAME_MAX_LEN = 18 + 1; //18 (max len of fiename) + 1 ("\" to end of folder path) + 1 (null-term)

#endif
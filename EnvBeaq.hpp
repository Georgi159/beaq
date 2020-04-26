#ifndef ENBBEAQ_HPP
#define ENBBEAQ_HPP

#include <iostream>
#include <filesystem>
#include <string>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <limits>
#include <iterator>
#include <vector>
#include <algorithm>
#include <regex> 
#include <fstream>
#include <cstdio>
#include <sstream>
#include <numeric>
#include <ctime>
#include <cmath>



//macros

#define E_OK    ((StdRet)0u)
#define E_ERROR ((StdRet)1u)
#define E_NO_TARGET ((StdRet)2u)
#define E_NO_SOURCE ((StdRet)4u)
#define E_NO_COUNT ((StdRet)8u)




#define NUMBER_OF_OPTIONS (10u)

//types
typedef enum 
{
	DIR=0,
	FILEE=1,
	OTHER=3,
	ERROR=4
}eFileType;

typedef enum 
{
	HELP=0,
	COUNT=1,
	AUTOUPDATE=2,
	TIMEUPDATE=3,
	TAR=4,
	GZIP=5,
	XZ=6,
	RSYNC=7,
	FILE_NAME=8,
	TARGET=9,
	EMPTY = 666
} eOptions;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef float 		float32;
typedef double 		float64;
typedef long double float128;


typedef uint8 StdRet;

typedef StdRet (*option_t)(char const**);






#endif 
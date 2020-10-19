#ifndef __HYPERWIN_UTILS_H_
#define __HYPERWINS_UTILS_H_

#include <Windows.h>
#include <debugapi.h>

VOID DebugOutA(PCHAR fmt, ...);

#define hvPrint(str, ...) DebugOutA("WIN32 HyperWin :: " \
												str, \
												__VA_ARGS__)
#define DEBUG_LEVEL_INFO 1
#define DEBUG_LEVEL_WARNING 2
#define DEBUG_LEVEL_DEBUG 3

#define DEBUG_LEVEL DEBUG_LEVEL_DEBUG

#endif
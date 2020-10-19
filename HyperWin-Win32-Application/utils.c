#include "utils.h"

VOID DebugOutA(PCHAR fmt, ...)
{
	CHAR str[1025];
	va_list args;
	va_start(args, fmt);
	wvsprintfA(str, fmt, args);
	va_end(args);
	OutputDebugStringA(str);
}
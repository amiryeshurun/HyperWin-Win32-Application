#include "hwops.h"
#include "hwtypes.h"
#include "utils.h"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, INT nCmdShow)
{
	HANDLE hDevice = CreateFileA("\\\\Device\\HyperWin", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		hvPrint("CreateFile failed: %d\n", GetLastError());
		return 1;
	}
	GENERIC_COM_STRUCT Request;
	Request.Operation = OPERATION_INIT;
	Request.ArgumentsUnion.InitArgs.IsMessageAvailable = TRUE;
	Request.ArgumentsUnion.InitArgs.MessageLength = strlen("HELLO!");
	strcpy_s(Request.ArgumentsUnion.InitArgs.Message, strlen("HELLO!"), "HELLO!");
	INT Dummy;
	if (!DeviceIoControl(hDevice, CTL_CODE_HW, &Request, sizeof(Request), NULL, 0, &Dummy, NULL))
	{
		hvPrint("DeviceIoControl failed: %d\n", GetLastError());
		return 2;
	}
	hvPrint("Operation complete\n");
	return 0;
}

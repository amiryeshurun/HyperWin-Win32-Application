#include "utils.h"
#include "comops.h"
#include "hwstatus.h"

#ifndef UNICODE
#define UNICODE
#endif 

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

APPLICATION_DATA appData;

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, INT nCmdShow)
{
    WCHAR ClassName = L"HypwerWin Window Class";
    WNDCLASS WindowClass;
    memset(&WindowClass, 0, sizeof(WNDCLASS));
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = hInstance;
    WindowClass.lpszClassName = ClassName;
    RegisterClass(&WindowClass);

    HWND hwnd;
    if((hwnd = CreateWindowEx(
        0,
        ClassName,
        L"HyperWin Controller",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        )) == NULL) 
    {
        hvPrint("Failed to create the main application window\n");
        return HYPERWIN_CREATE_WINDOW_FAILED;
    }
    ShowWindow(hwnd, nCmdShow);
    /*
    HANDLE Handle = CreateFileA("\\\\.\\HyperWin", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (Handle == INVALID_HANDLE_VALUE)
    {
        hvPrint("CreateFile failed: %d\n", GetLastError());
        return HYPERWIN_CREATE_FAILED;
    }
    GENERIC_COM_STRUCT Request;
    if (MarkProcessProtected(Handle, &Request) != HYPERWIN_STATUS_SUCCUESS)
        return HYPERWIN_INIT_FAILED;
    */
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    exit(0);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
        {
            if ((hwnd = CreateWindowEx(WS_EX_APPWINDOW,
                L"Edit",
                L"", // An empty textbox
                WS_BORDER | WS_CHILD | WS_VISIBLE, 
                20, 20, 310, 20, 
                hwnd, 
                NULL, 
                NULL, 
                NULL)) == NULL)
            {
                hvPrint("Could not create a textbox to store process name: %d\n", GetLastError());
                return HYPERWIN_CREATE_WINDOW_FAILED;
            }
            break;
        }
        case WM_QUIT:
        {
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

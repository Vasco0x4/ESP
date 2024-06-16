#include "Menu.h"
#include <iostream>

void SetWindowTransparency(HWND hwnd) {
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
}

HWND CreateOverlayWindow(HINSTANCE hInstance, const wchar_t* className, int nCmdShow) {
    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
        className,
        L"ESP Overlay",
        WS_POPUP,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd) {
        std::cerr << "Failed to create window.\n";
        return nullptr;
    }

    SetWindowTransparency(hwnd);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return hwnd;
}

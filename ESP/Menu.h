#pragma once
#ifndef WINDOW_INTERACTION_H
#define WINDOW_INTERACTION_H

#include <windows.h>

HWND CreateOverlayWindow(HINSTANCE hInstance, const wchar_t* className, int nCmdShow);

#endif // WINDOW_INTERACTION_H

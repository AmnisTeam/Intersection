#pragma once
#include <windows.h>

class WindowBase
{
public:
	HWND hwnd;
	static LRESULT wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void create(
        LPCWSTR lpWindowName,
        DWORD dwStyle = WS_OVERLAPPEDWINDOW,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        int X = CW_USEDEFAULT,
        int Y = CW_USEDEFAULT,
        DWORD dwExStyle = NULL,
        HWND hWndParent = NULL,
        HMENU hMenu = NULL,
        HINSTANCE hInstance = NULL);
private:
	LRESULT virtual handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	LPCWSTR virtual getClassName() = 0;
};


#include "pch.h"
#include "WindowBase.h"

LRESULT WindowBase::wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WindowBase* pThis;
	if (uMsg == WM_NCCREATE)
	{
		CREATESTRUCT* cs = (CREATESTRUCT*)lParam;
		pThis = (WindowBase*)cs->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
		return pThis->handleMessage(hwnd, uMsg, wParam, lParam);
	}
	else
	{
		pThis = (WindowBase*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if(pThis)
			return pThis->handleMessage(hwnd, uMsg, wParam, lParam);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void WindowBase::create(LPCWSTR lpWindowName, DWORD dwStyle, int nWidth, int nHeight, int X, int Y, DWORD dwExStyle, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance)
{
	WNDCLASS wc{};
	wc.lpszClassName = getClassName();
	wc.lpfnWndProc = wndProc;

	RegisterClass(&wc);

	hwnd = CreateWindowEx(dwExStyle, wc.lpszClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, this);
}

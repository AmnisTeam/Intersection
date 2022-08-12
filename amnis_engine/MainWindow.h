#pragma once
#include "WindowBase.h"
#include <windowsx.h>
#include "mymath.h"
#include <vector>
#include "decl.h"

class MainWindow : public WindowBase
{
public:
	long2 rawMouseDelta;
	float2 mousePos;
	DECL virtual LRESULT handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual LPCWSTR getClassName() override { return L"MAIN_WINDOW";};
	DECL void activateCursor(bool state);
	DECL void confineCursor();
	DECL void freeCursor();
	DECL void hideCursor();
	DECL void showCursor();
private:
	std::vector<char> rawInputBuffer;
};


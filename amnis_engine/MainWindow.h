#pragma once
#include "WindowBase.h"
#include "mymath.h"
#include <vector>

class MainWindow : public WindowBase
{
public:
	long2 rawMouseDelta;
	virtual LRESULT handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual LPCWSTR getClassName() override { return L"MAIN_WINDOW";};
	void activateCursor(bool state);
	void confineCursor();
	void freeCursor();
	void hideCursor();
	void showCursor();
private:
	std::vector<char> rawInputBuffer;
};


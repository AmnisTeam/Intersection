#include "pch.h"
#include "MainWindow.h"

LRESULT MainWindow::handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INPUT:
        {
            UINT size;
            if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)) == -1)
                throw;
            rawInputBuffer.resize(size);
            if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, rawInputBuffer.data(), &size, sizeof(RAWINPUTHEADER)) != size)
                throw;

            const RAWINPUT* rawInput = (RAWINPUT*)rawInputBuffer.data();
            if (rawInput->header.dwType == RIM_TYPEMOUSE)
            {
                if (rawInput->data.mouse.lLastX != 0 || rawInput->data.mouse.lLastY != 0)
                {
                    rawMouseDelta.x += rawInput->data.mouse.lLastX;
                    rawMouseDelta.y += rawInput->data.mouse.lLastY;
                }

            }
            else if (rawInput->header.dwType == RIM_TYPEKEYBOARD)
            {
                if (rawInput->data.keyboard.VKey == 'c')
                {
                    confineCursor();
                    hideCursor();
                }
            }
            break;
        }
        case WM_KEYDOWN:
        {
            int check = 0;
            if (wParam == 'C')
            {
                confineCursor();
                hideCursor();
            }
            if (wParam == VK_ESCAPE)
            {
                freeCursor();
                showCursor();
            }
            break;
        }
        case WM_CLOSE:
        {
            PostQuitMessage(0);
            break;
        }
        case WM_QUIT:
        {
            DestroyWindow(hwnd);
            break;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void MainWindow::activateCursor(bool state)
{
    if (state)
    {
        freeCursor();
        showCursor();
    }
    else
    {
        hideCursor();
        confineCursor();
    }
}

void MainWindow::confineCursor()
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    MapWindowPoints(hwnd, nullptr, (POINT*)&rect, 2);
    ClipCursor(&rect);
}

void MainWindow::freeCursor()
{
    ClipCursor(nullptr);
}

void MainWindow::hideCursor()
{
    while (ShowCursor(false) >= 0);
}

void MainWindow::showCursor()
{
    while (ShowCursor(true) <= 0);
}

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

                if (rawInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)
                {
                    rawMouseLeftButtonDown = true;
                    rawMouseLeftButtonPressed = true;
                }

                if (rawInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)
                {
                    rawMouseRightButtonDown = true;
                    rawMouseRightButtonPressed = true;
                }

                if (rawInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)
                {
                    rawMouseLeftButtonUp = true;
                    rawMouseLeftButtonPressed = false;
                }

                if (rawInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)
                {
                    rawMouseRightButtonUp = true;
                    rawMouseRightButtonPressed = false;
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

            isButtonPressed[wParam] = true;
            break;
        }
        case WM_KEYUP:
        {
            isButtonPressed[wParam] = false;
            break;
        }
        case WM_MOUSEMOVE:
        {
            mousePos = { (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) };
            break;
        }

        case WM_MOUSEWHEEL:
        {
           wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
           return 0;
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
    //while (ShowCursor(false) >= 0);
}

void MainWindow::showCursor()
{
    while (ShowCursor(true) <= 0);
}

bool MainWindow::getKeyState(char key)
{
    return isButtonPressed[key];
}

#include "pch.h"
#include "MainWindow.h"

MainWindow::MainWindow()
{
    keyboard = Keyboard();
    mouse = Mouse(this);
    
}

LRESULT MainWindow::handleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INPUT:
    {
        UINT size;
        if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &size, sizeof(RAWINPUTHEADER)) == -1)
            throw;
        //rawInputBuffer.resize(size);
        /*if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, rawInputBuffer.data(), &size, sizeof(RAWINPUTHEADER)) != size)
            throw;*/
        mouse.ResizeRawInputData(lParam, size);

        //const RAWINPUT* rawInput = (RAWINPUT*)rawInputBuffer.data();
        mouse.rawInput = (RAWINPUT*)mouse.rawInputBuffer.data();
        if (mouse.rawInput->header.dwType == RIM_TYPEMOUSE)
        {
            if (mouse.rawInput->data.mouse.lLastX != 0 || mouse.rawInput->data.mouse.lLastY != 0)
            {
                //rawMouseDelta.x += rawInput->data.mouse.lLastX;
                //rawMouseDelta.y += rawInput->data.mouse.lLastY;
                mouse.SetRawMouseDelta(mouse.rawInput->data.mouse.lLastX, mouse.rawInput->data.mouse.lLastY);
            }

            if (mouse.rawInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)
            {
                mouse.rawMouseLButtonDown = true;
                mouse.rawMouseLButtonPressed = true;
            }

            if (mouse.rawInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)
            {
                mouse.rawMouseRButtonDown = true;
                mouse.rawMouseRButtonPressed = true;
            }

            if (mouse.rawInput->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)
            {
                mouse.rawMouseLButtonUp = true;
                mouse.rawMouseLButtonPressed = false;
            }

            if (mouse.rawInput->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)
            {
                mouse.rawMouseRButtonUp = true;
                mouse.rawMouseRButtonPressed = false;
            }

        }
        break;
    }
    //case WM_KEYDOWN:
    //{
    //    int check = 0;
    //    /*if (wParam == 'C')
    //    {
    //        confineCursor();
    //        hideCursor();
    //    }
    //    if (wParam == VK_ESCAPE)
    //    {
    //        freeCursor();
    //        showCursor();
    //    }*/
    //    /*if (keyboard.KeyIsPressed('C'))
    //    {
    //        confineCursor();
    //        hideCursor();
    //    }
    //    if (keyboard.KeyIsPressed(VK_ESCAPE))
    //    {
    //        freeCursor();
    //        showCursor();
    //    }*/
    //    isButtonPressed[wParam] = true;
    //    break;
    //}
    case WM_SETFOCUS:
    {
        mouse.captureCursor(true);
        break;
    }
    case WM_KEYDOWN:
    {
        keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));

        if (keyboard.KeyIsPressed(VK_ESCAPE) && !mouse.getCursorState())
            mouse.captureCursor(true);
        else if (keyboard.KeyIsPressed(VK_ESCAPE))
            mouse.captureCursor(false);

        break;
    }

    case WM_KEYUP:
    {
        keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
        break;
    }

    case WM_CHAR:
    {
        keyboard.OnChar(static_cast<unsigned char>(wParam));
        break;
    }

    case WM_MOUSEMOVE:
    {
        //mousePos = { (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) };
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnMouseMove(pt.x, pt.y);

        break;
    }
    case WM_LBUTTONDOWN:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnLeftPressed(pt.x, pt.y);
        break;
    }
    case WM_RBUTTONDOWN:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnRightPressed(pt.x, pt.y);
        break;
    }
    case WM_LBUTTONUP:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnLeftReleased(pt.x, pt.y);
        break;
    }
    case WM_RBUTTONUP:
    {
        const POINTS pt = MAKEPOINTS(lParam);
        mouse.OnRightReleased(pt.x, pt.y);
        break;
    }

    case WM_MOUSEWHEEL:
    {
        //wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        const POINTS pt = MAKEPOINTS(lParam);
        const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        mouse.OnWheelDelta(pt.x, pt.y, delta);
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

//void MainWindow::activateCursor(bool state)
//{
//    if (state)
//    {
//        confineCursor();
//        hideCursor();
//    }
//    else
//    {
//        freeCursor();
//        showCursor();
//
//    }
//}
//
//void MainWindow::confineCursor()
//{
//    RECT rect;
//    GetClientRect(hwnd, &rect);
//    MapWindowPoints(hwnd, nullptr, (POINT*)&rect, 2);
//    ClipCursor(&rect);
//}
//
//void MainWindow::freeCursor()
//{
//    ClipCursor(nullptr);
//}
//
//void MainWindow::hideCursor()
//{
//    //while (ShowCursor(false) >= 0);
//}
//
//void MainWindow::showCursor()
//{
//    while (ShowCursor(true) <= 0);
//}
//
//bool MainWindow::getKeyState(char key)
//{
//    return keyboard.KeyIsPressed(key);
//}
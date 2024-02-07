#include "Windows.h"
#include <windowsx.h>
#include "tchar.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    WCHAR className[] = L"FirstWindow";

    WNDCLASSEX wndClass;
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wndClass.hInstance = hInstance;
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hIconSm = NULL;
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = className;

    wndClass.lpfnWndProc = WindowProc;

    if (!RegisterClassEx(&wndClass)) {
        return 0;
    }

    HWND hWnd = CreateWindowEx(
        0,
        className,
        L"My first window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        300, 300,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd) {
        return 0;
    }

    ShowWindow(hWnd, nShowCmd);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        DispatchMessage(&msg);
    }

    return msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rect;

    GetWindowRect(hwnd, &rect);

    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
   
    case WM_KEYDOWN:
        if (wParam == VK_RETURN)
            MoveWindow(hwnd, 0, 0, 300, 300, true);
        else if (wParam == VK_LEFT)
            MoveWindow(hwnd, rect.left - 5, rect.top, 300, 300, 1);
        else if (wParam == VK_RIGHT)
            MoveWindow(hwnd, rect.left + 5, rect.top, 300, 300, 1);
        else if (wParam == VK_UP)
            MoveWindow(hwnd, rect.left, rect.top - 5, 300, 300, 1);
        else if (wParam == VK_DOWN)
            MoveWindow(hwnd, rect.left, rect.top + 5, 300, 300, 1);
        else if (wParam == VK_ESCAPE)
            PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}



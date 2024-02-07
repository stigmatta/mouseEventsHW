#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>

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
        CW_USEDEFAULT, CW_USEDEFAULT, // x, y
        CW_USEDEFAULT, CW_USEDEFAULT, // width, height
        NULL,
        NULL,
        hInstance,
        NULL
    );

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
    static int nLeftClicks = 0, nRightClicks = 0, nMiddleClicks = 0;
    TCHAR szEveryClick[100] = { 0 };

    switch (uMsg) {
    case WM_DESTROY://
        PostQuitMessage(0); 
        break;
    case WM_LBUTTONDOWN:
        nLeftClicks++;
        break;
    case WM_RBUTTONDOWN:
        nRightClicks++;
        break;
    case WM_MBUTTONDOWN:
        nMiddleClicks++;
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
        break;
    }

    wsprintf(szEveryClick, L"Left clicks: %d, Right clicks: %d, Middle clicks: %d", nLeftClicks, nRightClicks, nMiddleClicks);
    SetWindowText(hwnd, szEveryClick);

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

#include "pch.h"
#include "Window.h"

// 초기화
HRESULT Window::Init(const IWND& iWnd)
{
    if (FAILED(InitWindow(iWnd)))
    {
        return E_FAIL;
    }

    return TRUE;
}

// 프레임
HRESULT Window::Frame()
{
    return TRUE;
}

// 렌더
HRESULT Window::Render()
{
    return TRUE;
}

// 메모리 해제
HRESULT Window::Release()
{
    return TRUE;
}

// 윈도우 초기화
HRESULT Window::InitWindow(const IWND& iWnd)
{
    // 윈도우 클래스를 등록한다.
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = iWnd.hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = iWnd.title;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    if (!RegisterClassEx(&wcex))
    {
        return E_FAIL;
    }

    // 윈도우 객체를 생성한다.
    RECT rect = { 0, 0, iWnd.width, iWnd.height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    hWnd = CreateWindowEx(WS_EX_TOPMOST, iWnd.title, iWnd.title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, iWnd.hInstance, NULL);
    if (FAILED(hWnd))
    {
        return E_FAIL;
    }

    // 윈도우 영역과 클라이언트 영역을 얻는다.
    GetWindowRect(hWnd, &_rtWindow);
    GetClientRect(hWnd, &_rtClient);

    // 윈도우를 출력한다.
    ShowWindow(hWnd, SW_SHOW);
    ShowCursor(TRUE);
    CenterWindow();

    return TRUE;
}

// 윈도우 중앙으로 이동
void Window::CenterWindow()
{
    // 화면 스크린의 해상도(넓이와 높이)을 얻는다.
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // 윈도우 클라이언트 중앙과 화면 스크린 중앙을 맞춘다.
    int x = (width - (_rtWindow.right - _rtWindow.left)) / 2;
    int y = (height - (_rtWindow.bottom - _rtWindow.top)) / 2;

    // 윈도우를 화면 중앙으로 이동한다.
    MoveWindow(hWnd, x, y, _rtWindow.right - _rtWindow.left, _rtWindow.bottom - _rtWindow.top, true);
}

// 윈도우 프로시저
LRESULT Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

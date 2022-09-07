#include "pch.h"
#include "Window.h"

// ������ ���ν���
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// �ʱ�ȭ
HRESULT Window::Init()
{
    return TRUE;
}

// ������
HRESULT Window::Frame()
{
    return TRUE;
}

// ����
HRESULT Window::Render()
{
    return TRUE;
}

// ������
HRESULT Window::Release()
{
    return TRUE;
}

HRESULT Window::Run()
{
    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
#ifdef CORE
        else
        {
            return TRUE;
        }
#endif
    }
    return E_FAIL;
}

// ������ �ʱ�ȭ
HRESULT Window::SetWindow(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height)
{
    // ������ Ŭ������ ����Ѵ�.
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = title;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
    if (!RegisterClassEx(&wcex)) return E_FAIL;

    // ����� �����츦 �����Ѵ�.
    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    _hWnd = CreateWindowEx(WS_EX_TOPMOST, title, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
    if (FAILED(_hWnd)) return E_FAIL;

    // ������ ������ Ŭ���̾�Ʈ ������ ��´�.
    GetWindowRect(_hWnd, &_rtWindow);
    GetClientRect(_hWnd, &_rtClient);
    ShowWindow(_hWnd, SW_SHOW);
    ShowCursor(TRUE);
    CenterWindow();

    return TRUE;
}

// ������ �߾����� �̵�
void Window::CenterWindow()
{
    // ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�.
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
    int x = (width - (_rtWindow.right - _rtWindow.left)) / 2;
    int y = (height - (_rtWindow.bottom - _rtWindow.top)) / 2;

    // �����츦 ȭ�� �߾����� �̵��Ѵ�.
    MoveWindow(_hWnd, x, y, _rtWindow.right - _rtWindow.left, _rtWindow.bottom - _rtWindow.top, true);
}

// ������ �ڵ�
const HWND Window::GetHWND() const
{
    return _hWnd;
}

const RECT Window::GetRECT() const
{
    return _rtClient;
}

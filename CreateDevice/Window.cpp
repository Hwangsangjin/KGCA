#include "pch.h"
#include "Window.h"

// �ʱ�ȭ
HRESULT Window::Init(const WindowInfo& info)
{
    if (FAILED(InitWindow(info)))
    {
        return E_FAIL;
    }

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

// �޸� ����
HRESULT Window::Release()
{
    return TRUE;
}

// ������ ���ν���
Window* gWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(gWindow);
    return gWindow->MsgProc(hWnd, message, wParam, lParam);
}

// �޽��� ���ν���
LRESULT Window::MsgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

// ������
Window::Window()
{
    gWindow = this;
}

// ������ �ʱ�ȭ
HRESULT Window::InitWindow(const WindowInfo& info)
{
    // ������ Ŭ������ ����Ѵ�.
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEX));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = info.hInstance;
    wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = info.title;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        return E_FAIL;
    }

    // ����� �����츦 �����Ѵ�.
    _hInstance = info.hInstance;
    RECT rect = { 0, 0, info.width, info.height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    HWND hWnd = CreateWindowEx(WS_EX_TOPMOST, info.title, info.title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, _hInstance, NULL);
    if (FAILED(gHandle))
    {
        return E_FAIL;
    }

    _hWnd = hWnd;
    gHandle = hWnd;

    // ������ ������ Ŭ���̾�Ʈ ������ ��´�.
    GetWindowRect(gHandle, &_rtWindow);
    GetClientRect(gHandle, &_rtClient);
    ShowWindow(gHandle, SW_SHOW);
    ShowCursor(TRUE);
    UpdateWindow(gHandle);
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

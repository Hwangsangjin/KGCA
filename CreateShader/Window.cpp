#include "pch.h"
#include "Window.h"

// �ʱ�ȭ
HRESULT Window::Init(const IWND& iWnd)
{
    if (FAILED(InitWindow(iWnd)))
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

// ������ �ʱ�ȭ
HRESULT Window::InitWindow(const IWND& iWnd)
{
    // ������ Ŭ������ ����Ѵ�.
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

    // ������ ��ü�� �����Ѵ�.
    RECT rect = { 0, 0, iWnd.width, iWnd.height };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    hWnd = CreateWindowEx(WS_EX_TOPMOST, iWnd.title, iWnd.title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, iWnd.hInstance, NULL);
    if (FAILED(hWnd))
    {
        return E_FAIL;
    }

    // ������ ������ Ŭ���̾�Ʈ ������ ��´�.
    GetWindowRect(hWnd, &_rtWindow);
    GetClientRect(hWnd, &_rtClient);

    // �����츦 ����Ѵ�.
    ShowWindow(hWnd, SW_SHOW);
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
    MoveWindow(hWnd, x, y, _rtWindow.right - _rtWindow.left, _rtWindow.bottom - _rtWindow.top, true);
}

// ������ ���ν���
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

#include "Window.h"
#include <assert.h>

// ���� ������ ���ν���
Window* _gpWindow = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(_gpWindow);
    return _gpWindow->MsgProc(hWnd, message, wParam, lParam);
}

// ������ ���ν���
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

Window::Window()
{
    _gpWindow = this;
}

bool Window::InitWindow(HINSTANCE hInstance, int nCmdShow, const TCHAR* strWindowTitle)
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
    wcex.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Client";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

    if (!RegisterClassEx(&wcex))
    {
        return false;
    }

    _hInstance = hInstance;
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    // �ü���� ����� �����츦 �����Ѵ�.
    _hWnd = CreateWindowEx(WS_EX_TOPMOST, L"Client", strWindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
    if (!_hWnd)
    {
        return false;
    }

    ShowWindow(_hWnd, nCmdShow);

    return true;
}

void Window::CenterWindow(HWND hwnd)
{
    // ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�.
    const int width = GetSystemMetrics(SM_CXFULLSCREEN);
    const int height = GetSystemMetrics(SM_CYFULLSCREEN);

    // ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
    int x = (width - (bound.right - bound.left)) / 2;
    int y = (height - (bound.bottom - bound.top)) / 2;

    // �����츦 ȭ�� �߾����� �̵��Ѵ�.
    MoveWindow(hwnd, x, y, bound.right - bound.left, bound.bottom - bound.top, true);
}

bool Window::Init()
{
    return true;
}

bool Window::Frame()
{
    return true;
}

bool Window::Render()
{
    return true;
}

bool Window::Release()
{
    return true;
}

// ����
bool Window::Run()
{
    if (!Init())
    {
        return false;
    }

    MSG msg = { 0 };
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Frame();
            Render();
        }
    }

    return false;
}

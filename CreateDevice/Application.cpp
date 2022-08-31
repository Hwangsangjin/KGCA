#include "pch.h"
#include "Application.h"

HWND gHandle;
WindowInfo info;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    info.hInstance = hInstance;
    info.title = L"Client";
    info.width = 800;
    info.height = 600;

    Application app;
    if (FAILED(app.Init(info)))
    {
        return E_FAIL;
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
            if (FAILED(app.Frame()) || FAILED(app.Render()))
            {
                break;
            }
        }
    }

    if (FAILED(app.Release()))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Application::Init(const WindowInfo& info)
{
    if (FAILED(_window.Init(info)))
    {
        return E_FAIL;
    }

    if (FAILED(_graphics.Init(info)))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Application::Frame()
{
    return TRUE;
}

HRESULT Application::Render()
{
    if (FAILED(_graphics.Render()))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Application::Release()
{
    return TRUE;
}

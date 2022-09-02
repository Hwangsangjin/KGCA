#include "pch.h"
#include "Application.h"

IWND iWnd;
HWND hWnd;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    iWnd.hInstance = hInstance;
    iWnd.nCmdShow = nCmdShow;
    iWnd.title = L"Client";
    iWnd.width = 800;
    iWnd.height = 600;

    Application* app = new Application;
    if (FAILED(app->Init(iWnd)))
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
            if (FAILED(app->Frame()) || FAILED(app->Render()))
            {
                break;
            }
        }
    }

    if (FAILED(app->Release()))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Application::Init(const IWND& iWnd)
{
    _pWindow = new Window;
    if (FAILED(_pWindow->Init(iWnd)))
    {
        return E_FAIL;
    }

    _pGraphics = new Graphics;
    if (FAILED(_pGraphics->Init(iWnd)))
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
    if (FAILED(_pGraphics->Render()))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Application::Release()
{
    if (_pGraphics != nullptr)
    {
        delete _pGraphics;
        _pGraphics = nullptr;
    }

    if (_pWindow != nullptr)
    {
        delete _pWindow;
        _pWindow = nullptr;
    }

    if (_pApplication != nullptr)
    {
        delete _pApplication;
        _pApplication = nullptr;
    }

    return TRUE;
}

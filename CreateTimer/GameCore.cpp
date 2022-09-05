#include "pch.h"
#include "GameCore.h"

HRESULT GameCore::Init(HINSTANCE hInstance, const WCHAR* title, UINT width, UINT height)
{
    if (FAILED(Window::Init(hInstance, title, width, height))) return E_FAIL;
 
    _pGraphics = new Graphics;
    if (FAILED(_pGraphics->Init(hInstance, this->GetHWND(), width, height))) return E_FAIL;

    _pTimer = new Timer;
    if (FAILED(_pTimer->Init())) return E_FAIL;

    return TRUE;
}

HRESULT GameCore::Frame()
{
    if (FAILED(_pTimer->Frame()))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT GameCore::Render()
{
    if (FAILED(_pGraphics->Render())) return E_FAIL;
    if (FAILED(_pTimer->Render())) return E_FAIL;

    return TRUE;
}

HRESULT GameCore::Release()
{
    if (FAILED(_pGraphics->Release())) return E_FAIL;
    if (FAILED(_pTimer->Release())) return E_FAIL;

    return TRUE;
}

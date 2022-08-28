#include "pch.h"
#include "Graphics.h"

HRESULT Graphics::Init(const WindowInfo& info)
{
    if (FAILED(CreateDXGIDevice())) return E_FAIL;
    if (FAILED(CreateDevice())) return E_FAIL;
    if (FAILED(CreateSwapChain())) return E_FAIL;
    if (FAILED(CreateRenderTargetView())) return E_FAIL;

    CreateViewport();
	return TRUE;
}

HRESULT Graphics::Frame()
{
	return TRUE;
}

HRESULT Graphics::Render()
{
	return TRUE;
}

HRESULT Graphics::Release()
{
	return TRUE;
}

HRESULT Graphics::CreateDevice()
{
	return TRUE;
}

HRESULT Graphics::CreateDXGIDevice()
{
	return TRUE;
}

HRESULT Graphics::CreateSwapChain()
{
	return TRUE;
}

HRESULT Graphics::CreateRenderTargetView()
{
	return TRUE;
}

void Graphics::CreateViewport()
{
}

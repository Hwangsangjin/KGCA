#include "pch.h"
#include "Core.h"

HRESULT Core::CoreInit()
{
	Device::Init();

	return Init();
}

HRESULT Core::CoreFrame()
{
	return Frame();
}

HRESULT Core::CorePreRender()
{
	// 후면 버퍼 클리어
	float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);

	return TRUE;
}

HRESULT Core::CoreRender()
{
	CorePreRender();
	Render();
	CorePostRender();

	return TRUE;
}

HRESULT Core::CorePostRender()
{
	// 플릿핑
	_pSwapChain->Present(0, 0);

	return TRUE;
}

HRESULT Core::CoreRelease()
{
	Release();
	Device::Release();

	return Release();
}

HRESULT Core::Init()
{
	return TRUE;
}

HRESULT Core::Frame()
{
	return TRUE;
}

HRESULT Core::Render()
{
	return TRUE;
}

HRESULT Core::Release()
{
	return TRUE;
}

HRESULT Core::Run()
{
	if (FAILED(Device::SetDevice(Window::GetHWND(), Window::GetRECT()))) return E_FAIL;
	if (FAILED(CoreInit())) return E_FAIL;

	while (_isRunning)
	{
		if (Window::Run() == TRUE)
		{
			CoreFrame();
			CoreRender();
		}
		else
		{
			_isRunning = false;
		}
	}

	if (FAILED(CoreRelease())) return E_FAIL;

	return TRUE;
}

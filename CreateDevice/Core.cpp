#include "pch.h"
#include "Core.h"

HRESULT Core::CInit()
{
	Device::Init();
	return Init();
}

HRESULT Core::CFrame()
{
	return Frame();
}

HRESULT Core::CPreRender()
{
	// 후면 버퍼 클리어
	float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);

	return TRUE;
}

HRESULT Core::CRender()
{
	CPreRender();
	Render();
	CPostRender();

	return TRUE;
}

HRESULT Core::CPostRender()
{
	// 플릿핑
	_pSwapChain->Present(0, 0);

	return TRUE;
}

HRESULT Core::CRelease()
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
	if (FAILED(CInit())) return E_FAIL;

	while (_isRun)
	{
		if (Window::Run() == TRUE)
		{
			CFrame();
			CRender();
		}
		else
		{
			_isRun = false;
		}
	}

	if (FAILED(CRelease())) return E_FAIL;

	return TRUE;
}

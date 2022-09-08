#include "pch.h"
#include "Core.h"

HRESULT Core::CoreInit()
{
	if (FAILED(Device::Init())) return E_FAIL;
	if (FAILED(TIMER->Init())) return E_FAIL;
	if (FAILED(_font.Init())) return E_FAIL;

	_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
		(void**)&_pBackBuffer);
	_font.SetSurface(_pBackBuffer);

	return Init();
}

HRESULT Core::CoreFrame()
{
	TIMER->Frame();
	_font.Frame();

	return Frame();
}

HRESULT Core::CorePreRender()
{
	// �ĸ� ���� Ŭ����
	float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);

	return TRUE;
}

HRESULT Core::CoreRender()
{
	CorePreRender();

	Render();
	TIMER->Render();
	_font.Render();

	CorePostRender();

	return TRUE;
}

HRESULT Core::CorePostRender()
{
	// �ø���
	_pSwapChain->Present(0, 0);

	return TRUE;
}

HRESULT Core::CoreRelease()
{
	_pBackBuffer->Release();
	Release();
	_font.Release();
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
	// �׷��Ƚ� ���������� ���ε�
    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, NULL);
    _pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return TRUE;
}

HRESULT Core::Release()
{
	return TRUE;
}

HRESULT Core::Run()
{
	if (FAILED(CoreInit())) return E_FAIL;

	while (_isRun)
	{
		if (Window::Run() == TRUE)
		{
			CoreFrame();
			CoreRender();
		}
		else
		{
			_isRun = false;
		}
	}

	if (FAILED(CoreRelease())) return E_FAIL;

	return TRUE;
}

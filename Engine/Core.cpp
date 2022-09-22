#include "pch.h"
#include "Core.h"

HRESULT Core::CoreInit()
{
	HR(Device::Init());
	HR(DxState::SetSamplerState(_pd3dDevice));
	HR(_font.Init());
	HR(_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&_pBackBuffer));
	HR(_font.SetSurface(_pBackBuffer));
	HR(SHADER->SetDevice(_pd3dDevice, _pImmediateContext));
	HR(SPRITE->SetDevice(_pd3dDevice, _pImmediateContext));
	HR(TEXTURE->SetDevice(_pd3dDevice, _pImmediateContext));
	HR(INPUT->Init());
	HR(TIMER->Init());
	HR(SOUND->Init());
	HR(Init());

	return TRUE;
}

HRESULT Core::CoreFrame()
{
	INPUT->Frame();
	TIMER->Frame();
	SOUND->Frame();
	_font.Frame();
	Frame();

	return TRUE;
}

HRESULT Core::CorePreRender()
{
	// 그래픽스 파이프라인 바인딩
	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, NULL);
	_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 후면 버퍼 클리어
	float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);
	_pImmediateContext->PSSetSamplers(0, 1, &DxState::_pDefaultSamplerState);

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
	// 플리핑
	_pSwapChain->Present(0, 0);

	return TRUE;
}

HRESULT Core::CoreRelease()
{
	SAFE_RELEASE(_pBackBuffer);
	Release();
	_font.Release();
	TIMER->Release();
	INPUT->Release();
	SOUND->Release();
	DxState::Release();
	Device::Release();

	return TRUE;
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
	HR(CoreInit());

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

	HR(CoreRelease());

	return TRUE;
}

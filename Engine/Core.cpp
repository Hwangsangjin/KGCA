#include "pch.h"
#include "Core.h"

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

HRESULT Core::CreateDXResource()
{
	_font.Init();
	IDXGISurface1* pBackBuffer;
	_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackBuffer);
	_font.SetSurface(pBackBuffer);
	pBackBuffer->Release();

	return TRUE;
}

HRESULT Core::DeleteDXResource()
{
	_font.DeleteDXResource();

	return TRUE;
}

HRESULT Core::CoreInit()
{
	HR(Device::Init());
	HR(DxState::SetSamplerState(_pd3dDevice));
	HR(SHADER->SetDevice(_pd3dDevice, _pImmediateContext));
	HR(SPRITE->SetDevice(_pd3dDevice, _pImmediateContext));
	HR(TEXTURE->SetDevice(_pd3dDevice, _pImmediateContext));
	HR(INPUT->Init());
	HR(TIMER->Init());
	HR(SOUND->Init());
	HR(_font.Init());
	IDXGISurface1* pBackBuffer;
	HR(_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackBuffer));
	HR(_font.SetSurface(pBackBuffer));
	pBackBuffer->Release();

	HR(Init());

	return TRUE;
}

HRESULT Core::CoreFrame()
{
	INPUT->Frame();
	TIMER->Frame();
	SOUND->Frame();
	_font.SetText(TIMER->GetText());
	_font.Frame();
	Frame();

	return TRUE;
}

HRESULT Core::CorePreRender()
{
	// 그래픽스 파이프라인 바인딩
	_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_pImmediateContext->RSSetViewports(1, &_viewport);
	_pImmediateContext->RSSetState(DxState::_pDefaultRSSolid);
	_pImmediateContext->PSSetSamplers(0, 1, &DxState::_pDefaultSSWrap);
	_pImmediateContext->OMSetBlendState(DxState::_pAlphaBlend, 0, -1);
	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);
	_pImmediateContext->OMSetDepthStencilState(DxState::_pDefaultDepthStencil, 0xff);

	// 후면 버퍼 클리어
	float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);
	_pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

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
	Release();
	_font.Release();
	TIMER->Release();
	INPUT->Release();
	SOUND->Release();
	DxState::Release();
	Device::Release();

	return TRUE;
}

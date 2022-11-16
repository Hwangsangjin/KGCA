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
	_writer.Init();
	IDXGISurface1* pBackBuffer;
	_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackBuffer);
	_writer.SetSurface(pBackBuffer);
	pBackBuffer->Release();

	return TRUE;
}

HRESULT Core::DeleteDXResource()
{
	_writer.DeleteDXResource();

	return TRUE;
}

HRESULT Core::Tool()
{
	if (FAILED(CoreFrame()) || FAILED(CoreRender()))
	{
		_isRun = false;

		return E_FAIL;
	}

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
	HR(_writer.Init());
	IDXGISurface1* pBackBuffer;
	HR(_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), (void**)&pBackBuffer));
	HR(_writer.SetSurface(pBackBuffer));
	pBackBuffer->Release();
	
	HR(_background.CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/RenderTarget.hlsl", L"../../Resource/Background/Background.png"));
	HR(_rendertarget.CreateRenderTarget(_pd3dDevice, _pImmediateContext, 1920.0f, 1080.0f));
	
	HR(Init());

	return TRUE;
}

HRESULT Core::CoreFrame()
{
	INPUT->Frame();
	TIMER->Frame();
	SOUND->Frame();
	_writer.SetText(TIMER->GetText());
	_writer.Frame();
	Frame();

	return TRUE;
}

HRESULT Core::CorePreRender()
{
	// 그래픽스 파이프라인 바인딩
	_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_pImmediateContext->RSSetViewports(1, &_viewport);
	_pImmediateContext->RSSetState(DxState::_pDefaultRSSolid);
	_pImmediateContext->PSSetSamplers(0, 1, &DxState::_pDefaultSSMirror);
	_pImmediateContext->OMSetBlendState(DxState::_pAlphaBlend, 0, -1);
	_pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, _pDepthStencilView);
	_pImmediateContext->OMSetDepthStencilState(DxState::_pDefaultDepthStencil, 0xff);

	// 후면 버퍼 클리어
	const float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // Red, Green, Blue, Alpha
	_pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);
	_pImmediateContext->ClearDepthStencilView(_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return TRUE;
}

HRESULT Core::CoreRender()
{
	CorePreRender();
	
	// 렌더타겟 지정
	_rendertarget._pOldRenderTargetView = _pRenderTargetView;
	_rendertarget._pOldDepthStencilView = _pDepthStencilView;
	_rendertarget._oldViewport[0] = _viewport;
	
	if (SUCCEEDED(_rendertarget.Begin(_pImmediateContext)))
	{
		Render();
	
		_rendertarget.End(_pImmediateContext);
	}
	
	if (_rendertarget._pShaderResourceView)
	{
		_background._pShaderResourceView = _rendertarget._pShaderResourceView.Get();
	}
	
	CorePostRender();

	return TRUE;
}

HRESULT Core::CorePostRender()
{
	// 배경
	_background.SetMatrix(nullptr, nullptr, nullptr);
	_background.Render();
	
	// 폰트
	_writer.Render();

	// 플리핑
	_pSwapChain->Present(0, 0);

	return TRUE;
}

HRESULT Core::CoreRelease()
{
	_rendertarget.Release();
	_background.Release();
	_writer.Release();
	Release();
	SHADER->Release();
	SPRITE->Release();
	TEXTURE->Release();
	TIMER->Release();
	INPUT->Release();
	SOUND->Release();
	DxState::Release();
	Device::Release();

	return TRUE;
}

#include "pch.h"
#include "DxRT.h"

HRESULT DxRT::Init()
{
	return TRUE;
}

HRESULT DxRT::Frame()
{
	return TRUE;
}

HRESULT DxRT::Render()
{
	return TRUE;
}

HRESULT DxRT::Release()
{
	return TRUE;
}

HRESULT DxRT::CreateRenderTarget(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pDeviceContext, float width, float height)
{
	_viewport.Width = width;
	_viewport.Height = height;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;

	_textureDesc.Width = (UINT)width;
	_textureDesc.Height = (UINT)height;
	_textureDesc.MipLevels = 1;
	_textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_textureDesc.SampleDesc.Count = 1;
	_textureDesc.SampleDesc.Quality = 0;
	_textureDesc.Usage = D3D11_USAGE_DEFAULT;
	_textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	_textureDesc.CPUAccessFlags = 0;
	_textureDesc.MiscFlags = 0;
	_textureDesc.ArraySize = 1;

	HR(pd3dDevice->CreateTexture2D(&_textureDesc, nullptr, _pTexture.GetAddressOf()));
	HR(pd3dDevice->CreateShaderResourceView(_pTexture.Get(), nullptr, _pShaderResourceView.GetAddressOf()));
	HR(pd3dDevice->CreateRenderTargetView(_pTexture.Get(), nullptr, _pRenderTargetView.GetAddressOf()));

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDSTexture = nullptr;
	D3D11_TEXTURE2D_DESC depthDesc;
	depthDesc.Width = width;
	depthDesc.Height = height;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	HR(pd3dDevice->CreateTexture2D(&depthDesc, nullptr, &pDSTexture));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	HR(pd3dDevice->CreateDepthStencilView(pDSTexture.Get(), &dsvDesc, &_pDepthStencilView));

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;

	HR(pd3dDevice->CreateShaderResourceView(pDSTexture.Get(), &srvDesc, &_pDSShaderResourceView));

	return TRUE;
}

HRESULT DxRT::Begin(ID3D11DeviceContext* pDeviceContext)
{
	pDeviceContext->RSSetViewports(1, &_viewport);
	ID3D11RenderTargetView* pRenderTargetView = nullptr;
	pDeviceContext->OMSetRenderTargets(1, &pRenderTargetView, nullptr);
	pDeviceContext->OMSetRenderTargets(1, _pRenderTargetView.GetAddressOf(), _pDepthStencilView.Get());

	const float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
	pDeviceContext->ClearRenderTargetView(_pRenderTargetView.Get(), color);
	pDeviceContext->ClearDepthStencilView(_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	return TRUE;
}

HRESULT DxRT::End(ID3D11DeviceContext* pDeviceContext)
{
	pDeviceContext->RSSetViewports(1, _oldViewport);
	pDeviceContext->OMSetRenderTargets(1, &_pOldRenderTargetView, _pOldDepthStencilView);

	return TRUE;
}

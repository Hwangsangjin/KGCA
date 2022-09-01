#include "pch.h"
#include "Graphics.h"

HRESULT Graphics::CreateDevice()
{
    HRESULT hr;
    D3D_FEATURE_LEVEL pFeatureLevel;
    UINT Flags = 0;
    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT FeatureLevels = 1;
    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, pFeatureLevels, 1, D3D11_SDK_VERSION, &_pd3dDevice, &pFeatureLevel, &_pImmediateContext);

    return hr;
}

HRESULT Graphics::CreateFactory()
{
    HRESULT hr;
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pFactory);

    return hr;
}

HRESULT Graphics::CreateSwapChain(const IWND& iWnd)
{
    HRESULT hr;
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = iWnd.width;
    sd.BufferDesc.Height = iWnd.height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.Windowed = true;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    hr =  _pFactory->CreateSwapChain(_pd3dDevice, &sd, &_pSwapChain);

    return hr;
}

HRESULT Graphics::CreateRenderTargetView()
{
    HRESULT hr;
    ID3D11Texture2D* pBackBuffer = nullptr;
    _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &_pRenderTargetView);
    pBackBuffer->Release();

    _pImmediateContext->OMSetRenderTargets(1, &_pRenderTargetView, NULL);

    return hr;
}

HRESULT Graphics::CreateViewport(const IWND& iWnd)
{
    D3D11_VIEWPORT vp;
    vp.Width = iWnd.width;
    vp.Height = iWnd.height;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    _pImmediateContext->RSSetViewports(1, &vp);

    return TRUE;
}

HRESULT Graphics::Init(const IWND& iWnd)
{
    if (FAILED(InitDevice(iWnd)))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Graphics::InitDevice(const IWND& iWnd)
{
    if (FAILED(CreateDevice()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateFactory()))
    {
        return E_FAIL;
    }

    if (FAILED(CreateSwapChain(iWnd)))
    {
        return E_FAIL;
    }

    if (FAILED(CreateRenderTargetView()))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Graphics::Frame()
{
    return TRUE;
}

HRESULT Graphics::Render()
{
    float color[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; //red,green,blue,alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView, color);

    _pSwapChain->Present(0, 0);

    return TRUE;
}

HRESULT Graphics::Release()
{
    if (_pImmediateContext)
    {
        _pImmediateContext->ClearState();
    }

    if (_pRenderTargetView)
    {
        _pRenderTargetView->Release();
    }

    if (_pSwapChain)
    {
        _pSwapChain->Release();
    }

    if (_pFactory)
    {
        _pFactory->Release();
    }

    if (_pImmediateContext)
    {
        _pImmediateContext->Release();
    }

    if (_pd3dDevice)
    {
        _pd3dDevice->Release();
    }

    _pd3dDevice = nullptr;
    _pFactory = nullptr;
    _pSwapChain = nullptr;
    _pRenderTargetView = nullptr;
    _pImmediateContext = nullptr;

    return TRUE;
}

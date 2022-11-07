#include "pch.h"
#include "Device.h"

// �ʱ�ȭ
HRESULT Device::Init()
{
    HR(CreateDevice());
    HR(CreateFactory());
    HR(CreateSwapChain());
    HR(CreateRenderTargetView());
    HR(CreateDepthStencilView());
    HR(CreateViewport());

    return TRUE;
}

// ������
HRESULT Device::Frame()
{
    return TRUE;
}

// ����
HRESULT Device::Render()
{
    return TRUE;
}

// ������
HRESULT Device::Release()
{
    SAFE_CLEARSTATE(_pImmediateContext);
    SAFE_RELEASE(_pBackBuffer);
    SAFE_RELEASE(_pDepthStencilView);
    SAFE_RELEASE(_pRenderTargetView);
    SAFE_RELEASE(_pSwapChain);
    SAFE_RELEASE(_pFactory);
    SAFE_RELEASE(_pImmediateContext);
    SAFE_RELEASE(_pd3dDevice);

    return TRUE;
}

// ����̽�
HRESULT Device::CreateDevice()
{
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        _driverType = driverTypes[driverTypeIndex];
        HRESULT hr = D3D11CreateDevice(NULL, _driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &_pd3dDevice, &_featureLevel, &_pImmediateContext);

        if (SUCCEEDED(hr))
        {
            break;
        }
    }

    return TRUE;
}

// ���丮
HRESULT Device::CreateFactory()
{
    HR(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pFactory));

    return TRUE;
}

// ����ü��
HRESULT Device::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = rtClient.right;
    sd.BufferDesc.Height = rtClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.Windowed = true;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    HR(_pFactory->CreateSwapChain(_pd3dDevice, &sd, &_pSwapChain));

    return TRUE;
}

// ����Ÿ�ٺ�
HRESULT Device::CreateRenderTargetView()
{
    ID3D11Texture2D* pBackBuffer = nullptr;
    _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    HR(_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &_pRenderTargetView));
    pBackBuffer->Release();

    return TRUE;
}

// �������ٽǺ�
HRESULT Device::CreateDepthStencilView()
{
    D3D11_RENDER_TARGET_VIEW_DESC rtvd;
    _pRenderTargetView->GetDesc(&rtvd);

    DXGI_SWAP_CHAIN_DESC scd;
    _pSwapChain->GetDesc(&scd);

    //Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencilTexture;
    ID3D11Texture2D* pDepthStencilTexture = nullptr;
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory(&td, sizeof(td));
    td.Width = scd.BufferDesc.Width;
    td.Height = scd.BufferDesc.Height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R24G8_TYPELESS;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    td.CPUAccessFlags = 0;
    td.MiscFlags = 0;

    //HR(_pd3dDevice->CreateTexture2D(&td, nullptr, pDepthSencilTexture.GetAddressOf()));
    HR(_pd3dDevice->CreateTexture2D(&td, nullptr, &pDepthStencilTexture));

    D3D11_DEPTH_STENCIL_VIEW_DESC dtvd;
    ZeroMemory(&dtvd, sizeof(dtvd));
    dtvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;    // ����ȭ ���� ���� ���̰� 24, ���ٽǰ� 8
    dtvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    //_pd3dDevice->CreateDepthStencilView(pDepthSencilTexture.Get(), &dtvd, &_pDepthStencilView);
    HR(_pd3dDevice->CreateDepthStencilView(pDepthStencilTexture, &dtvd, &_pDepthStencilView));
    pDepthStencilTexture->Release();
    return TRUE;
}

// ����Ʈ
HRESULT Device::CreateViewport()
{
    _viewport.Width = rtClient.right;
    _viewport.Height = rtClient.bottom;
    _viewport.TopLeftX = 0.0f;
    _viewport.TopLeftY = 0.0f;
    _viewport.MinDepth = 0.0f;
    _viewport.MaxDepth = 1.0f;

    return TRUE;
}

HRESULT Device::ResizeDevice(UINT width, UINT height)
{
    // ����̽��� �������� ���� ���
    if (_pd3dDevice == nullptr) return TRUE;

    // ���ҽ��� �����Ѵ�.
    DeleteDXResource();

    // ���� ������ ����Ÿ�ٰ� ����Ÿ�ٺ並 �����Ѵ�.
    _pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);
    SAFE_RELEASE(_pRenderTargetView);
    SAFE_RELEASE(_pDepthStencilView);

    // �ĸ� ������ ũ�⸦ �����Ѵ�.
    DXGI_SWAP_CHAIN_DESC current, after;
    _pSwapChain->GetDesc(&current);
    _pSwapChain->ResizeBuffers(current.BufferCount, width, height, current.BufferDesc.Format, 0);

    // ����� �ĸ� ������ ũ�⸦ ��´�.
    _pSwapChain->GetDesc(&after);
    GetClientRect(hWnd, &rtClient);
    rtClient.right = after.BufferDesc.Width;
    rtClient.bottom = after.BufferDesc.Height;

    // ����Ÿ�ٺ並 �����ϰ� �����Ѵ�.
    HR(CreateRenderTargetView());

    // �������ٽǺ並 �����ϰ� �����Ѵ�.
    HR(CreateDepthStencilView());

    // ����Ʈ�� �����ϰ� �����Ѵ�.
    HR(CreateViewport());

    // ���ҽ��� �����Ѵ�.
    CreateDXResource();

    return TRUE;
}

HRESULT Device::CreateDXResource()
{
    return TRUE;
}

HRESULT Device::DeleteDXResource()
{
    return TRUE;
}

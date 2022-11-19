#include "Device.h"

extern HWND gHandle;
extern RECT gClient;

// �ʱ�ȭ
HRESULT Device::Init()
{
    return TRUE;
}

// ������
HRESULT Device::Frame()
{
    return TRUE;
}

// ���� ����
HRESULT Device::PreRender()
{
    // �ĸ� ���� ����
    const float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView.Get(), ClearColor);

    return TRUE;
}

// ����
HRESULT Device::Render()
{
    return TRUE;
}

// ����Ʈ ����
HRESULT Device::PostRender()
{
    if (FAILED(_pSwapChain->Present(0, 0)))
    {
        return E_FAIL;
    }

    return TRUE;
}

// ������
HRESULT Device::Release()
{
    return TRUE;
}

// ����̽� ����
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
        D3D_DRIVER_TYPE_REFERENCE
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        HRESULT hr;
        _driverType = driverTypes[driverTypeIndex];
        if (SUCCEEDED(hr = D3D11CreateDevice(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, _pd3dDevice.GetAddressOf(), &_featureLevel, _pImmediateContext.GetAddressOf())));
        {
            if (FAILED(hr) || _featureLevel < D3D_FEATURE_LEVEL_11_1)
            {
                continue;
            }

            break;
        }
    }

    return TRUE;
}

// ���丮 ����
HRESULT Device::CreateFactory()
{
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pFactory)))
    {
        return E_FAIL;
    }

    return TRUE;
}

// ����ü�� ����
HRESULT Device::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.OutputWindow = gHandle;
    sd.Windowed = true;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferDesc.Width = gClient.right;
    sd.BufferDesc.Height = gClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    if (FAILED(_pFactory->CreateSwapChain(_pd3dDevice.Get(), &sd, _pSwapChain.GetAddressOf())))
    {
        return E_FAIL;
    }

    return TRUE;
}

// ����Ÿ�ٺ� ����
HRESULT Device::SetRenderTargetView()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
    _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

    if (FAILED(_pd3dDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, _pRenderTargetView.GetAddressOf())))
    {
        return E_FAIL;
    }
    
    _pImmediateContext->OMSetRenderTargets(1, _pRenderTargetView.GetAddressOf(), nullptr);

    return TRUE;
}

// ����Ʈ ����
HRESULT Device::SetViewport()
{
    // ����Ʈ ����
    _viewport.Width = gClient.right;
    _viewport.Height = gClient.bottom;
    _viewport.TopLeftX = 0.0f;
    _viewport.TopLeftY = 0.0f;
    _viewport.MinDepth = 0.0f;
    _viewport.MaxDepth = 1.0f;

    _pImmediateContext->RSSetViewports(1, &_viewport);

    return TRUE;
}

// ����̽� ��ü ����
HRESULT Device::CleanupDevice()
{
    // ����̽� ���ؽ�Ʈ�� �⺻ �������� �ʱ�ȭ
    if (_pImmediateContext)
    {
        _pImmediateContext->ClearState();
    }

    return TRUE;
}

HRESULT Device::ResizeDevice(UINT width, UINT height)
{
    // ����̽��� �������� ���� ���
    if (!_pd3dDevice)
    {
        return TRUE;
    }

    // Ŭ���̾�Ʈ ȭ�� ����
    gClient.right = width;
    gClient.bottom = height;

    // ���ҽ� ����
    DeleteResource();

    // ���ҽ��� �ʱ�ȭ
    _pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);

    // ����Ÿ�ٺ� ����
    if (_pRenderTargetView)
    {
        _pRenderTargetView->Release();
    }

    // �ĸ� ���� ũ�� ������
    DXGI_SWAP_CHAIN_DESC currentSD, afterSD;
    _pSwapChain->GetDesc(&currentSD);
    _pSwapChain->ResizeBuffers(currentSD.BufferCount, width, height, currentSD.BufferDesc.Format, 0);

    //// ����� �ĸ� ���� ũ��� Ŭ���̾�Ʈ ���� ����
    //_pSwapChain->GetDesc(&afterSD);
    //GetClientRect(gHandle, &gClient);
    //gClient.right = afterSD.BufferDesc.Width;
    //gClient.bottom = afterSD.BufferDesc.Height;

    // ����Ÿ�ٺ� ����
    if (FAILED(SetRenderTargetView()))
    {
        return E_FAIL;
    }

    // ����Ʈ ����
    if (FAILED(SetViewport()))
    {
        return E_FAIL;
    }

    // ���ҽ� ����
    CreateResource();

    return TRUE;
}

HRESULT Device::CreateResource()
{
    return TRUE;
}

HRESULT Device::DeleteResource()
{
    return TRUE;
}

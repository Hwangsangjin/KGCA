#include "pch.h"
#include "Device.h"

// �ʱ�ȭ
HRESULT Device::Init()
{
    assert(SUCCEEDED(CreateDevice()));
    assert(SUCCEEDED(CreateFactory()));
    assert(SUCCEEDED(CreateSwapChain()));
    assert(SUCCEEDED(SetRenderTargetView()));
    assert(SUCCEEDED(SetViewport()));
    
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
    assert(SUCCEEDED(CleanupDevice()));

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
        driver_type_ = driverTypes[driverTypeIndex];
        assert(SUCCEEDED(D3D11CreateDevice(nullptr, driver_type_, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, d3d11_device_.GetAddressOf(), &feature_level_, d3d11_device_context_.GetAddressOf())));
        {
            if (feature_level_ < D3D_FEATURE_LEVEL_11_1)
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
    assert(SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&dxgi_factory_)));

    return TRUE;
}

// ����ü�� ����
HRESULT Device::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.OutputWindow = g_handle;
    sd.Windowed = true;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferDesc.Width = g_client_rect.right;
    sd.BufferDesc.Height = g_client_rect.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    assert(SUCCEEDED(dxgi_factory_->CreateSwapChain(d3d11_device_.Get(), &sd, swap_chain_.GetAddressOf())));

    return TRUE;
}

// ����Ÿ�ٺ� ����
HRESULT Device::SetRenderTargetView()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
    assert(SUCCEEDED(swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer)));
    assert(SUCCEEDED(d3d11_device_->CreateRenderTargetView(pBackBuffer.Get(), nullptr, render_target_view_.GetAddressOf())));

    d3d11_device_context_->OMSetRenderTargets(1, render_target_view_.GetAddressOf(), nullptr);

    return TRUE;
}

// ����Ʈ ����
HRESULT Device::SetViewport()
{
    // ����Ʈ ����
    viewport_.Width = g_client_rect.right;
    viewport_.Height = g_client_rect.bottom;
    viewport_.TopLeftX = 0.0f;
    viewport_.TopLeftY = 0.0f;
    viewport_.MinDepth = 0.0f;
    viewport_.MaxDepth = 1.0f;

    d3d11_device_context_->RSSetViewports(1, &viewport_);

    return TRUE;
}

// ����̽� ��ü ����
HRESULT Device::CleanupDevice()
{
    // ����̽� ���ؽ�Ʈ�� �⺻ �������� �缳��
    if (d3d11_device_context_)
    {
        d3d11_device_context_->ClearState();
    }

    return TRUE;
}

HRESULT Device::ResizeDevice(UINT width, UINT height)
{
    // ����̽��� �������� ���� ���
    if (!d3d11_device_)
    {
        return TRUE;
    }

    // Ŭ���̾�Ʈ ȭ�� ����
    g_client_rect.right = width;
    g_client_rect.bottom = height;

    // ���ҽ� ����
    assert(SUCCEEDED(DeleteResource()));

    // ���� ������ ����Ÿ�� �ʱ�ȭ�� ����Ÿ�ٺ� ����
    d3d11_device_context_->OMSetRenderTargets(0, nullptr, nullptr);
    render_target_view_->Release();

    // �ĸ� ���� ũ�� ������
    DXGI_SWAP_CHAIN_DESC currentSD;
    assert(SUCCEEDED(swap_chain_->GetDesc(&currentSD)));
    assert(SUCCEEDED(swap_chain_->ResizeBuffers(currentSD.BufferCount, width, height, currentSD.BufferDesc.Format, 0)));

    // ����Ÿ�ٺ� ����
    assert(SUCCEEDED(SetRenderTargetView()));

    // ����Ʈ ����
    assert(SUCCEEDED(SetViewport()));

    // ���ҽ� ����
    assert(SUCCEEDED(CreateResource()));

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

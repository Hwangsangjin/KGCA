#include "pch.h"
#include "Device.h"

// 초기화
HRESULT Device::Init()
{
    assert(SUCCEEDED(CreateDevice()));
    assert(SUCCEEDED(CreateFactory()));
    assert(SUCCEEDED(CreateSwapChain()));
    assert(SUCCEEDED(SetRenderTargetView()));
    assert(SUCCEEDED(SetViewport()));

    return TRUE;
}

// 프레임
HRESULT Device::Frame()
{
    return TRUE;
}

// 렌더
HRESULT Device::Render()
{
    return TRUE;
}

// 릴리즈
HRESULT Device::Release()
{
    assert(SUCCEEDED(CleanupDevice()));

    return TRUE;
}

// 디바이스 생성
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
        _driverType = driverTypes[driverTypeIndex];
        assert(SUCCEEDED(D3D11CreateDevice(nullptr, _driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, _pd3dDevice.GetAddressOf(), &_featureLevel, _pImmediateContext.GetAddressOf())));
        {
            if (_featureLevel < D3D_FEATURE_LEVEL_11_1)
            {
                continue;
            }

            break;
        }
    }

    return TRUE;
}

// 팩토리 생성
HRESULT Device::CreateFactory()
{
    assert(SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pFactory)));

    return TRUE;
}

// 스왑체인 생성
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

    assert(SUCCEEDED(_pFactory->CreateSwapChain(_pd3dDevice.Get(), &sd, _pSwapChain.GetAddressOf())));

    return TRUE;
}

// 렌더타겟뷰 설정
HRESULT Device::SetRenderTargetView()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> pBackBuffer = nullptr;
    assert(SUCCEEDED(_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer)));
    assert(SUCCEEDED(_pd3dDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, _pRenderTargetView.GetAddressOf())));

    _pImmediateContext->OMSetRenderTargets(1, _pRenderTargetView.GetAddressOf(), nullptr);

    return TRUE;
}

// 뷰포트 설정
HRESULT Device::SetViewport()
{
    // 뷰포트 설정
    _viewport.Width = gClient.right;
    _viewport.Height = gClient.bottom;
    _viewport.TopLeftX = 0.0f;
    _viewport.TopLeftY = 0.0f;
    _viewport.MinDepth = 0.0f;
    _viewport.MaxDepth = 1.0f;

    _pImmediateContext->RSSetViewports(1, &_viewport);

    return TRUE;
}

// 디바이스 객체 정리
HRESULT Device::CleanupDevice()
{
    // 디바이스 컨텍스트를 기본 설정으로 재설정
    if (_pImmediateContext)
    {
        _pImmediateContext->ClearState();
    }

    return TRUE;
}

HRESULT Device::ResizeDevice(UINT width, UINT height)
{
    // 디바이스가 생성되지 않은 경우
    if (!_pd3dDevice)
    {
        return TRUE;
    }

    // 클라이언트 화면 설정
    gClient.right = width;
    gClient.bottom = height;

    // 리소스 삭제
    assert(SUCCEEDED(DeleteResource()));

    // 현재 설정된 렌더타겟 초기화와 렌더타겟뷰 해제
    _pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);
    _pRenderTargetView->Release();

    // 후면 버퍼 크기 재조정
    DXGI_SWAP_CHAIN_DESC currentSD;
    assert(SUCCEEDED(_pSwapChain->GetDesc(&currentSD)));
    assert(SUCCEEDED(_pSwapChain->ResizeBuffers(currentSD.BufferCount, width, height, currentSD.BufferDesc.Format, 0)));

    // 렌더타겟뷰 설정
    assert(SUCCEEDED(SetRenderTargetView()));

    // 뷰포트 설정
    assert(SUCCEEDED(SetViewport()));

    // 리소스 생성
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

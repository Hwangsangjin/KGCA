#include "Device.h"

extern HWND gHandle;
extern RECT gClient;

// 초기화
HRESULT Device::Init()
{
    return TRUE;
}

// 프레임
HRESULT Device::Frame()
{
    return TRUE;
}

// 프리 렌더
HRESULT Device::PreRender()
{
    // 후면 버퍼 삭제
    const float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // Red, Green, Blue, Alpha
    _pImmediateContext->ClearRenderTargetView(_pRenderTargetView.Get(), ClearColor);

    return TRUE;
}

// 렌더
HRESULT Device::Render()
{
    return TRUE;
}

// 포스트 렌더
HRESULT Device::PostRender()
{
    if (FAILED(_pSwapChain->Present(0, 0)))
    {
        return E_FAIL;
    }

    return TRUE;
}

// 릴리즈
HRESULT Device::Release()
{
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

// 팩토리 생성
HRESULT Device::CreateFactory()
{
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pFactory)))
    {
        return E_FAIL;
    }

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

    if (FAILED(_pFactory->CreateSwapChain(_pd3dDevice.Get(), &sd, _pSwapChain.GetAddressOf())))
    {
        return E_FAIL;
    }

    return TRUE;
}

// 렌더타겟뷰 설정
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
    // 디바이스 컨텍스트를 기본 설정으로 초기화
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
    DeleteResource();

    // 리소스뷰 초기화
    _pImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);

    // 렌더타겟뷰 해제
    if (_pRenderTargetView)
    {
        _pRenderTargetView->Release();
    }

    // 후면 버퍼 크기 재조정
    DXGI_SWAP_CHAIN_DESC currentSD, afterSD;
    _pSwapChain->GetDesc(&currentSD);
    _pSwapChain->ResizeBuffers(currentSD.BufferCount, width, height, currentSD.BufferDesc.Format, 0);

    //// 변경된 후면 버퍼 크기로 클라이언트 영역 설정
    //_pSwapChain->GetDesc(&afterSD);
    //GetClientRect(gHandle, &gClient);
    //gClient.right = afterSD.BufferDesc.Width;
    //gClient.bottom = afterSD.BufferDesc.Height;

    // 렌더타겟뷰 설정
    if (FAILED(SetRenderTargetView()))
    {
        return E_FAIL;
    }

    // 뷰포트 설정
    if (FAILED(SetViewport()))
    {
        return E_FAIL;
    }

    // 리소스 생성
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

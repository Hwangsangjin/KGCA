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
    UINT create_device_flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 

    D3D_DRIVER_TYPE driver_types[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE
    };
    UINT driver_types_count = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };
    UINT feature_Levels_count = ARRAYSIZE(feature_levels);

    for (UINT driver_type_index = 0; driver_type_index < driver_types_count; driver_type_index++)
    {
        driver_type_ = driver_types[driver_type_index];
        assert(SUCCEEDED(D3D11CreateDevice(nullptr, driver_type_, nullptr, create_device_flags, feature_levels, feature_Levels_count, D3D11_SDK_VERSION, device_.GetAddressOf(), &feature_level_, device_context_.GetAddressOf())));
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

// 팩토리 생성
HRESULT Device::CreateFactory()
{
    assert(SUCCEEDED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)factory_.GetAddressOf())));

    return TRUE;
}

// 스왑체인 생성
HRESULT Device::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC swap_chain_desc;
    ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
    swap_chain_desc.BufferCount = 1;
    swap_chain_desc.OutputWindow = g_handle;
    swap_chain_desc.Windowed = true;
    swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.BufferDesc.Width = g_client_rect.right;
    swap_chain_desc.BufferDesc.Height = g_client_rect.bottom;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
    swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
    swap_chain_desc.SampleDesc.Count = 1;
    swap_chain_desc.SampleDesc.Quality = 0;
    swap_chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    assert(SUCCEEDED(factory_->CreateSwapChain(device_.Get(), &swap_chain_desc, swap_chain_.GetAddressOf())));

    return TRUE;
}

// 렌더타겟뷰 설정
HRESULT Device::SetRenderTargetView()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> back_buffer;
    assert(SUCCEEDED(swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)back_buffer.GetAddressOf())));
    assert(SUCCEEDED(device_->CreateRenderTargetView(back_buffer.Get(), nullptr, render_target_view_.GetAddressOf())));

    device_context_->OMSetRenderTargets(1, render_target_view_.GetAddressOf(), nullptr);

    return TRUE;
}

// 뷰포트 설정
HRESULT Device::SetViewport()
{
    // 뷰포트 설정
    viewport_.Width = static_cast<float>(g_client_rect.right);
    viewport_.Height = static_cast<float>(g_client_rect.bottom);
    viewport_.TopLeftX = 0.0f;
    viewport_.TopLeftY = 0.0f;
    viewport_.MinDepth = 0.0f;
    viewport_.MaxDepth = 1.0f;

    device_context_->RSSetViewports(1, &viewport_);

    return TRUE;
}

// 디바이스 객체 정리
HRESULT Device::CleanupDevice()
{
    // 디바이스 컨텍스트를 기본 설정으로 재설정
    if (device_context_)
    {
        device_context_->ClearState();
    }

    return TRUE;
}

// 디바이스 컨텍스트 클리어
void Device::ClearDeviceContext(ID3D11DeviceContext* device_context)
{
    // Unbind all objects from the immediate context
    assert(device_context);

    ID3D11ShaderResourceView* pSRVs[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    ID3D11RenderTargetView* pRTVs[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    ID3D11DepthStencilView* pDSV = nullptr;
    ID3D11Buffer* pBuffers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    ID3D11SamplerState* pSamplers[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    UINT StrideOffset[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    // Shaders
    //device_context->VSSetShader(NULL, NULL, 0);
    //device_context->HSSetShader(NULL, NULL, 0);
    //device_context->DSSetShader(NULL, NULL, 0);
    //device_context->GSSetShader(NULL, NULL, 0);
    //device_context->PSSetShader(NULL, NULL, 0);

    // IA clear
    //device_context->IASetVertexBuffers(0, 16, pBuffers, StrideOffset, StrideOffset);
    //device_context->IASetIndexBuffer(NULL, DXGI_FORMAT_R16_UINT, 0);
    //device_context->IASetInputLayout(NULL);

    // Constant buffers
    //device_context->VSSetConstantBuffers(0, 14, pBuffers);
    //device_context->HSSetConstantBuffers(0, 14, pBuffers);
    //device_context->DSSetConstantBuffers(0, 14, pBuffers);
    //device_context->GSSetConstantBuffers(0, 14, pBuffers);
    //device_context->PSSetConstantBuffers(0, 14, pBuffers);

    // Resources
    device_context->VSSetShaderResources(0, 16, pSRVs);
    //device_context->HSSetShaderResources(0, 16, pSRVs);
    //device_context->DSSetShaderResources(0, 16, pSRVs);
    //device_context->GSSetShaderResources(0, 16, pSRVs);
    device_context->PSSetShaderResources(0, 16, pSRVs);

    // Samplers
    //device_context->VSSetSamplers(0, 16, pSamplers);
    //device_context->HSSetSamplers(0, 16, pSamplers);
    //device_context->DSSetSamplers(0, 16, pSamplers);
    //device_context->GSSetSamplers(0, 16, pSamplers);
    //device_context->PSSetSamplers(0, 16, pSamplers);

    // Render targets
    //device_context->OMSetRenderTargets(8, pRTVs, pDSV);

    // States
    //FLOAT blend_factor[4] = { 0,0,0,0 };
    //device_context->OMSetBlendState(nullptr, blend_factor, 0xFFFFFFFF);
    //device_context->OMSetDepthStencilState(nullptr, 0);
    //device_context->RSSetState(nullptr);
}

HRESULT Device::ResizeDevice(UINT width, UINT height)
{
    // 디바이스가 생성되지 않은 경우
    if (!device_)
    {
        return TRUE;
    }

    // 클라이언트 화면 설정
    g_client_rect.right = width;
    g_client_rect.bottom = height;

    // 리소스 삭제
    assert(SUCCEEDED(DeleteResource()));

    // 현재 설정된 렌더타겟 초기화와 렌더타겟뷰 해제
    device_context_->OMSetRenderTargets(0, nullptr, nullptr);
    render_target_view_->Release();

    // 후면 버퍼 크기 재조정
    DXGI_SWAP_CHAIN_DESC currentSD;
    assert(SUCCEEDED(swap_chain_->GetDesc(&currentSD)));
    assert(SUCCEEDED(swap_chain_->ResizeBuffers(currentSD.BufferCount, width, height, currentSD.BufferDesc.Format, 0)));

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

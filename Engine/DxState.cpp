#include "pch.h"
#include "DxState.h"

Microsoft::WRL::ComPtr<ID3D11BlendState> DxState::alpha_blend_;
Microsoft::WRL::ComPtr<ID3D11SamplerState> DxState::default_wrap_;
Microsoft::WRL::ComPtr<ID3D11SamplerState> DxState::default_mirror_;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> DxState::default_solid_;
Microsoft::WRL::ComPtr<ID3D11RasterizerState> DxState::default_wire_frame_;
Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DxState::default_depth_stencil_;
Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DxState::greater_depth_stencil_;

HRESULT DxState::Init()
{
    return TRUE;
}

HRESULT DxState::Frame()
{
    return TRUE;
}

HRESULT DxState::Render()
{
    return TRUE;
}

HRESULT DxState::Release()
{
    return TRUE;
}

HRESULT DxState::SetState(ID3D11Device* device)
{
    D3D11_SAMPLER_DESC sampler_desc;
    ZeroMemory(&sampler_desc, sizeof(sampler_desc));
    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    //sampler_desc.Borasterizer_descerColor[0] = 0.5f;
    //sampler_desc.Borasterizer_descerColor[1] = 0.5f;
    //sampler_desc.Borasterizer_descerColor[2] = 0.5f;
    //sampler_desc.Borasterizer_descerColor[3] = 1.0f;
    //FLOAT MipLODBias;
    //UINT MaxAnisotropy;
    //D3D11_COMPARISON_FUNC ComparisonFunc;
    //FLOAT Borasterizer_descerColor[4];
    //FLOAT MinLOD;
    //FLOAT MaxLOD;

    assert(SUCCEEDED(device->CreateSamplerState(&sampler_desc, default_wrap_.GetAddressOf())));

    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
    assert(SUCCEEDED(device->CreateSamplerState(&sampler_desc, default_mirror_.GetAddressOf())));

    D3D11_RASTERIZER_DESC rasterizer_desc;
    ZeroMemory(&rasterizer_desc, sizeof(rasterizer_desc));
    rasterizer_desc.DepthClipEnable = TRUE;
    rasterizer_desc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizer_desc.CullMode = D3D11_CULL_BACK;
    assert(SUCCEEDED(device->CreateRasterizerState(&rasterizer_desc, default_wire_frame_.GetAddressOf())));

    rasterizer_desc.FillMode = D3D11_FILL_SOLID;
    assert(SUCCEEDED(device->CreateRasterizerState(&rasterizer_desc, default_solid_.GetAddressOf())));

    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(blend_desc));
    //blend_desc.IndependentBlendEnable = TRUE;
    // 혼합 : 섞는다. 
    // 배경(목적지) d-RGBA : 후면 버퍼에 이미 랜더링 되어 있는 결과
    // 현재 소스 :  s-RGBA : 지금 랜더링 하려는 객체, 픽셀셰이더
    // RGB 성분을 혼합하는 명령
    // 알파블렌딩 공식
    // finalColor = SrcColor * SrcAlpha + DestColor * (1.0f - SrcAlpha);
    // alpha = 1.0f (불투명), alpha = 0.0f (투명), alpha 0~1 (반투명)
    // finalColor = SrcColor * 1.0f + DestColor*(1.0f - 1.0f);
    // finalColor = SrcColor * 0.0f + DestColor*(1.0f - 0.0f);
    // finalColor = SrcColor * 0.5f + DestColor*(1.0f - 0.5f);
    blend_desc.RenderTarget[0].BlendEnable = TRUE;
    blend_desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blend_desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blend_desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    // A 성분을 혼합하는 명령
    // finalAlpha = SrcAlpha * 1.0f + DestAlpha * 0.0f;
    blend_desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blend_desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    blend_desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    blend_desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    assert(SUCCEEDED(device->CreateBlendState(&blend_desc, alpha_blend_.GetAddressOf())));

    D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
    ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
    depth_stencil_desc.DepthEnable = true;
    depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    assert(SUCCEEDED(device->CreateDepthStencilState(&depth_stencil_desc, default_depth_stencil_.GetAddressOf())));

    depth_stencil_desc.DepthFunc = D3D11_COMPARISON_GREATER;
    assert(SUCCEEDED(device->CreateDepthStencilState(&depth_stencil_desc, greater_depth_stencil_.GetAddressOf())));

    return TRUE;
}

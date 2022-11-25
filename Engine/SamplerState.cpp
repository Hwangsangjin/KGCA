#include "pch.h"
#include "SamplerState.h"

HRESULT SamplerState::Init()
{
    return TRUE;
}

HRESULT SamplerState::Frame()
{
    return TRUE;
}

HRESULT SamplerState::Render()
{
    return TRUE;
}

HRESULT SamplerState::Release()
{
    return TRUE;
}

HRESULT SamplerState::SetSamplerState(ID3D11Device* device)
{
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    //sd.BorderColor[0] = 0.5f;
    //sd.BorderColor[1] = 0.5f;
    //sd.BorderColor[2] = 0.5f;
    //sd.BorderColor[3] = 1.0f;
    //FLOAT MipLODBias;
    //UINT MaxAnisotropy;
    //D3D11_COMPARISON_FUNC ComparisonFunc;
    //FLOAT BorderColor[4];
    //FLOAT MinLOD;
    //FLOAT MaxLOD;

    assert(SUCCEEDED(device->CreateSamplerState(&sd, &default_wrap_)));

    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
    assert(SUCCEEDED(device->CreateSamplerState(&sd, &default_mirror_)));

    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(rd));
    rd.DepthClipEnable = TRUE;
    rd.FillMode = D3D11_FILL_WIREFRAME;
    rd.CullMode = D3D11_CULL_BACK;
    assert(SUCCEEDED(device->CreateRasterizerState(&rd, &default_wire_frame_)));

    rd.FillMode = D3D11_FILL_SOLID;
    assert(SUCCEEDED(device->CreateRasterizerState(&rd, &default_solid_)));

    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    //bd.IndependentBlendEnable = TRUE;
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
    bd.RenderTarget[0].BlendEnable = TRUE;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    //  A 성분을 혼합하는 명령
    // finalAlpha = SrcAlpha * 1.0f + DestAlpha * 0.0f;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    assert(SUCCEEDED(device->CreateBlendState(&bd, &alpha_blend_)));

    D3D11_DEPTH_STENCIL_DESC dsd;
    ZeroMemory(&dsd, sizeof(dsd));
    dsd.DepthEnable = true;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    assert(SUCCEEDED(device->CreateDepthStencilState(&dsd, &default_depth_stencil_)));

    dsd.DepthFunc = D3D11_COMPARISON_GREATER;
    assert(SUCCEEDED(device->CreateDepthStencilState(&dsd, &greater_depth_stencil_)));

    return TRUE;
}

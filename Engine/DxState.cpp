#include "pch.h"
#include "DxState.h"

ID3D11BlendState* DxState::_pAlphaBlend = nullptr;
ID3D11SamplerState* DxState::_pDefaultSSWrap = nullptr;
ID3D11SamplerState* DxState::_pDefaultSSMirror = nullptr;
ID3D11RasterizerState* DxState::_pDefaultRSSolid = nullptr;
ID3D11RasterizerState* DxState::_pDefaultRSWireFrame = nullptr;
ID3D11DepthStencilState* DxState::_pDefaultDepthStencil = nullptr;
ID3D11DepthStencilState* DxState::_pGreaterDepthStencil = nullptr;

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
    SAFE_RELEASE(_pAlphaBlend);
    SAFE_RELEASE(_pDefaultSSWrap);
    SAFE_RELEASE(_pDefaultSSMirror);
    SAFE_RELEASE(_pDefaultRSSolid);
    SAFE_RELEASE(_pDefaultRSWireFrame);
    SAFE_RELEASE(_pDefaultDepthStencil);
    SAFE_RELEASE(_pGreaterDepthStencil);

    return TRUE;
}

HRESULT DxState::SetSamplerState(ID3D11Device* pd3dDevice)
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

    assert(SUCCEEDED(pd3dDevice->CreateSamplerState(&sd, &_pDefaultSSWrap)));

    sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
    assert(SUCCEEDED(pd3dDevice->CreateSamplerState(&sd, &_pDefaultSSMirror)));

    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(rd));
    rd.DepthClipEnable = TRUE;
    rd.FillMode = D3D11_FILL_WIREFRAME;
    rd.CullMode = D3D11_CULL_BACK;
    assert(SUCCEEDED(pd3dDevice->CreateRasterizerState(&rd, &_pDefaultRSWireFrame)));

    rd.FillMode = D3D11_FILL_SOLID;
    assert(SUCCEEDED(pd3dDevice->CreateRasterizerState(&rd, &_pDefaultRSSolid)));


    D3D11_BLEND_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    //bd.IndependentBlendEnable = TRUE;
    // ȥ�� : ���´�. 
    // ���(������) d-RGBA : �ĸ� ���ۿ� �̹� ������ �Ǿ� �ִ� ���
    // ���� �ҽ� :  s-RGBA : ���� ������ �Ϸ��� ��ü, �ȼ����̴�
    // RGB ������ ȥ���ϴ� ���
    // ���ĺ��� ����
    // finalColor = SrcColor * SrcAlpha + DestColor * (1.0f - SrcAlpha);
    // alpha = 1.0f (������), alpha = 0.0f (����), alpha 0~1 (������)
    // finalColor = SrcColor * 1.0f + DestColor*(1.0f - 1.0f);
    // finalColor = SrcColor * 0.0f + DestColor*(1.0f - 0.0f);
    // finalColor = SrcColor * 0.5f + DestColor*(1.0f - 0.5f);
    bd.RenderTarget[0].BlendEnable = TRUE;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    //  A ������ ȥ���ϴ� ���
    // finalAlpha = SrcAlpha*1.0f+DestAlpha*0.0f;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    assert(SUCCEEDED(pd3dDevice->CreateBlendState(&bd, &_pAlphaBlend)));

    D3D11_DEPTH_STENCIL_DESC dsd;
    ZeroMemory(&dsd, sizeof(dsd));
    dsd.DepthEnable = true;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsd.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    assert(SUCCEEDED(pd3dDevice->CreateDepthStencilState(&dsd, &_pDefaultDepthStencil)));

    dsd.DepthFunc = D3D11_COMPARISON_GREATER;
    assert(SUCCEEDED(pd3dDevice->CreateDepthStencilState(&dsd, &_pGreaterDepthStencil)));

    return TRUE;
}

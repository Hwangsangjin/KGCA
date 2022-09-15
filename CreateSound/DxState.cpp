#include "pch.h"
#include "DxState.h"

ID3D11SamplerState* DxState::_pDefaultSamplerState = nullptr;

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
    SAFE_RELEASE(_pDefaultSamplerState);

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

    HR(pd3dDevice->CreateSamplerState(&sd, &_pDefaultSamplerState));
    
    return TRUE;
}

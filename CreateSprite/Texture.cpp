#include "pch.h"
#include "Texture.h"

HRESULT Texture::Init()
{
    return TRUE;
}

HRESULT Texture::Frame()
{
    return TRUE;
}

HRESULT Texture::Render()
{
    return TRUE;
}

HRESULT Texture::Release()
{
    SAFE_RELEASE(_pResource);
    SAFE_RELEASE(_pShaderResourceView);

    return TRUE;
}

void Texture::SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext)
{
    _pd3dDevice = pd3dDevice;
    _pImmediateContext = pImmediateContext;
}

HRESULT Texture::CreateTexture(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring texturefile)
{
    // 디바이스 설정
    SetDevice(pd3dDevice, pImmediateContext);

    // 텍스처 생성
    HR(DirectX::CreateWICTextureFromFile(pd3dDevice, pImmediateContext, texturefile.c_str(), &_pResource, &_pShaderResourceView));

    return TRUE;
}

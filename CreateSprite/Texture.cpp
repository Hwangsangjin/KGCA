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
    SAFE_RELEASE(_pTexture2D);
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
    HR(DirectX::CreateWICTextureFromFile(pd3dDevice, pImmediateContext, texturefile.c_str(), (ID3D11Resource**)&_pTexture2D, &_pShaderResourceView));

    _pTexture2D->GetDesc(&_desc);

    return TRUE;
}

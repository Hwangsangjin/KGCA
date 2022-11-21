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
    device_ = pd3dDevice;
    device_context_ = pImmediateContext;
}

HRESULT Texture::CreateTexture(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring textureFile)
{
    // 디바이스 설정
    SetDevice(pd3dDevice, pImmediateContext);

    // 텍스처 생성
    HRESULT hr = DirectX::CreateWICTextureFromFile(pd3dDevice, pImmediateContext, textureFile.c_str(), (ID3D11Resource**)&_pTexture2D, &_pShaderResourceView);

    if (FAILED(hr))
    {
        hr = DirectX::CreateDDSTextureFromFile(pd3dDevice, pImmediateContext, textureFile.c_str(), (ID3D11Resource**)&_pTexture2D, &_pShaderResourceView);
    }

    if (_pTexture2D)
    {
        _pTexture2D->GetDesc(&_desc);
    }

    return TRUE;
}

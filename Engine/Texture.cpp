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
    return TRUE;
}

void Texture::SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context)
{
    device_ = device;
    device_context_ = device_context;
}

HRESULT Texture::CreateTexture(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring texture_file)
{
    // 디바이스 설정
    SetDevice(device, device_context);

    // 텍스처 생성
    HRESULT hr = DirectX::CreateWICTextureFromFile(device, device_context, texture_file.c_str(), (ID3D11Resource**)texture2D_.GetAddressOf(), shader_resource_view_.GetAddressOf());

    if (FAILED(hr))
    {
        hr = DirectX::CreateDDSTextureFromFile(device, device_context, texture_file.c_str(), (ID3D11Resource**)texture2D_.GetAddressOf(), shader_resource_view_.GetAddressOf());
    }

    if (texture2D_)
    {
        texture2D_->GetDesc(&texture2D_desc_);
    }

    return TRUE;
}

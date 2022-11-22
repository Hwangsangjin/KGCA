#include "pch.h"
#include "Sprite.h"
#include "TextureManager.h"

HRESULT Sprite::Init()
{
    return TRUE;
}

HRESULT Sprite::Frame()
{
    return TRUE;
}

HRESULT Sprite::Render()
{
    return TRUE;
}

HRESULT Sprite::Release()
{
    return TRUE;
}

HRESULT Sprite::Load(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring sprite_file)
{
    Texture* mask = TEXTURE->Load(mask_file_);

    assert(SUCCEEDED(CreateObject(device, device_context, shader_file_, texture_file_)));
    SetMask(mask);

    return TRUE;
}

HRESULT SpriteTexture::Load(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring sprite_file)
{
    textures_.resize(strings_.size());
    for (int i = 0; i < strings_.size(); i++)
    {
        textures_[i] = TEXTURE->Load(strings_[i]);
    }

    return Sprite::Load(device, device_context, sprite_file);
}

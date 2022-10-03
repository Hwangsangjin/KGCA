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

HRESULT Sprite::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring name)
{
    Texture* pMask = TEXTURE->Load(_maskPath);

    HR(CreateObject(pd3dDevice, pImmediateContext, _shaderPath, _texturePath));
    SetMask(pMask);

    return TRUE;
}

HRESULT SpriteTexture::Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring name)
{
    _pTextures.resize(_textures.size());
    for (int i = 0; i < _textures.size(); i++)
    {
        _pTextures[i] = TEXTURE->Load(_textures[i]);
    }

    return Sprite::Load(pd3dDevice, pImmediateContext, name);
}

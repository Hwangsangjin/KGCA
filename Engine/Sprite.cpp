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

HRESULT Sprite::CreateSprite(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring spriteFile)
{
    Texture* pMaskTexture = TEXTURE->Load(L"../../Resource/Pikachu/Image/Mask.png");

    CreateObject(pd3dDevice, pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
    SetMask(pMaskTexture);

    return TRUE;
}

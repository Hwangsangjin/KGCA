#pragma once

#include "Object2D.h"

class Sprite : public Object2D
{
public:
    std::vector<RECT> _uvs;
    std::vector<W_STR> _textures;
    std::vector<Texture*> _pTextures;
    std::vector<Sprite*> _pSprites;

    // 초기화
    HRESULT Init();
    // 프레임 계산
    HRESULT Frame();
    // 렌더
    HRESULT Render();
    // 메모리 해제
    HRESULT Release();

    // 스프라이트 생성
    virtual HRESULT Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring name);
};

class SpriteTexture : public Sprite
{
public:
    virtual HRESULT Load(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring name);
};
#pragma once

#include "Object2D.h"

class Sprite : public Object2D
{
public:
    std::vector<RECT> rects_;
    std::vector<W_STR> strings_;
    std::vector<std::shared_ptr<Texture>> textures_;
    std::vector<std::shared_ptr<Sprite>> sprites_;

    // 초기화
    HRESULT Init();
    // 프레임 계산
    HRESULT Frame();
    // 렌더
    HRESULT Render();
    // 메모리 해제
    HRESULT Release();

    // 스프라이트 생성
    virtual HRESULT Load(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring sprite_file);
};

class SpriteTexture : public Sprite
{
public:
    virtual HRESULT Load(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring sprite_file);
};
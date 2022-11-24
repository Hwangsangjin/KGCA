#pragma once

#include "Object2D.h"

class Sprite : public Object2D
{
public:
    std::vector<RECT> rects_;
    std::vector<W_STR> strings_;
    std::vector<std::shared_ptr<Texture>> textures_;
    std::vector<std::shared_ptr<Sprite>> sprites_;

    // �ʱ�ȭ
    HRESULT Init();
    // ������ ���
    HRESULT Frame();
    // ����
    HRESULT Render();
    // �޸� ����
    HRESULT Release();

    // ��������Ʈ ����
    virtual HRESULT Load(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring sprite_file);
};

class SpriteTexture : public Sprite
{
public:
    virtual HRESULT Load(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring sprite_file);
};
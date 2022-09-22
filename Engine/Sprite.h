#pragma once

#include "Object2D.h"

class Sprite : public Object2D
{
public:
    W_STR _name;
    UINT _index;
    std::vector<RECT> _uvs;

    // �ʱ�ȭ
    HRESULT Init();
    // ������ ���
    HRESULT Frame();
    // ����
    HRESULT Render();
    // �޸� ����
    HRESULT Release();

    // ��������Ʈ ����
    HRESULT CreateSprite(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring spriteFile);
};


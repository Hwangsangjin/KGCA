#pragma once

#include "Sprite.h"

class SpriteManager
{
	DECLARE_SINGLE(SpriteManager);

public:
    ID3D11Device* _pd3dDevice = nullptr;
    ID3D11DeviceContext* _pImmediateContext = nullptr;

    std::map<std::wstring, Sprite*> _sprites;
    std::vector<std::vector<RECT>> _rects;
    std::vector<W_STR> _names;

    // �ʱ�ȭ
    HRESULT Init();
    // ������ ���
    HRESULT Frame();
    // ����
    HRESULT Render();
    // �޸� ����
    HRESULT Release();

    // ����̽� ����
    HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

    HRESULT GameDataLoad(const TCHAR* spriteFile);
    HRESULT Load(std::wstring spriteFile);
    Sprite* Find(std::wstring spriteFile);

    Sprite& Get(W_STR str);
    Sprite* GetPtr(W_STR str);
};


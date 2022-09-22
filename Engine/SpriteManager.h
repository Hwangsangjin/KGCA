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

    // 초기화
    HRESULT Init();
    // 프레임 계산
    HRESULT Frame();
    // 렌더
    HRESULT Render();
    // 메모리 해제
    HRESULT Release();

    // 디바이스 설정
    HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

    HRESULT GameDataLoad(const TCHAR* spriteFile);
    HRESULT Load(std::wstring spriteFile);
    Sprite* Find(std::wstring spriteFile);

    Sprite& Get(W_STR str);
    Sprite* GetPtr(W_STR str);
};


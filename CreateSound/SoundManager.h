#pragma once

#include "Sound.h"

class SoundManager
{
    DECLARE_SINGLE(SoundManager);

public:
    FMOD::System* _pSystem = nullptr;
    std::list<std::wstring> _files;
    std::map<std::wstring, Sound*> _sounds;

public:
    // 초기화
    HRESULT Init();
    // 프레임 계산
    HRESULT Frame();
    // 렌더
    HRESULT Render();
    // 메모리 해제
    HRESULT Release();

    Sound* Load(std::wstring filename);
    void LoadDir(std::wstring path);
    void LoadAll(std::wstring path);

    Sound* GetPtr(W_STR name);
    T_STR GetSplitName(std::wstring filename);
};


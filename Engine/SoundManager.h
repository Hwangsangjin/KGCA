#pragma once

class SoundManager
{
    DECLARE_SINGLE(SoundManager);

public:
    FMOD::System* system_ = nullptr;
    std::list<std::wstring> files_;
    std::map<std::wstring, class Sound*> sounds_;

    // 초기화
    HRESULT Init();
    // 프레임 계산
    HRESULT Frame();
    // 렌더
    HRESULT Render();
    // 메모리 해제
    HRESULT Release();

    Sound* Load(std::wstring sound_file);
    void LoadDir(std::wstring file_path);
    void LoadAll(std::wstring file_path);

    Sound* GetPtr(W_STR sound_file);
    T_STR GetSplitName(std::wstring sound_file);
};


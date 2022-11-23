#pragma once

class SoundManager
{
private:
    FMOD::System* system_ = nullptr;
    std::list<std::wstring> files_;
    std::map<std::wstring, class Sound*> sounds_;

    SoundManager() = default;
    ~SoundManager() = default;

public:
    // �̱���
    static SoundManager* GetInstance()
    {
        static SoundManager instance;
        return &instance;
    }

    // �ʱ�ȭ
    HRESULT Init();
    // ������ ���
    HRESULT Frame();
    // ����
    HRESULT Render();
    // �޸� ����
    HRESULT Release();

    Sound* Load(std::wstring sound_file);
    void LoadDir(std::wstring file_path);
    void LoadAll(std::wstring file_path);

    Sound* GetPtr(W_STR sound_file);
    T_STR GetSplitName(std::wstring sound_file);
};


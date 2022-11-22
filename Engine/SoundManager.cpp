#include "pch.h"
#include "SoundManager.h"
#include "Sound.h"

HRESULT SoundManager::Init()
{
    FMOD::System_Create(&system_);
    system_->init(32, FMOD_INIT_NORMAL, 0);

    return TRUE;
}

HRESULT SoundManager::Frame()
{
    system_->update();

    for (auto& sound : sounds_)
    {
        if (sound.second)
        {
            sound.second->Frame();
        }
    }

    return TRUE;
}

HRESULT SoundManager::Render()
{
    return TRUE;
}

HRESULT SoundManager::Release()
{
    for (auto& sound : sounds_)
    {
        if (sound.second)
        {
            sound.second->Release();
            delete sound.second;
            sound.second = nullptr;
        }
    }

    system_->close();
    system_->release();
    sounds_.clear();

    return TRUE;
}

Sound* SoundManager::Load(std::wstring sound_file)
{
    HRESULT hr;
    W_STR split_name = GetSplitName(sound_file);

    // 중복 제거
    for (auto& sound : sounds_)
    {
        if (sound.first == sound_file)
        {
            return sound.second;
        }
    }

    Sound* new_sound = new Sound;
    new_sound->GetName() = sound_file;
    if (new_sound)
    {
        hr = new_sound->Load(system_, sound_file);
        if (SUCCEEDED(hr))
        {
            sounds_.insert(std::make_pair(split_name, new_sound));
        }
    }

    return nullptr;
}

void SoundManager::LoadDir(std::wstring file_path)
{
    W_STR dir = file_path + L"*.*";
    intptr_t handle;
    struct _wfinddata_t fd;
    
    handle = _wfindfirst(dir.c_str(), &fd);
    if (handle == -1L)
    {
        return;
    }

    do
    {
        if ((fd.attrib & _A_SUBDIR) && fd.name[0] != '.')
        {
            LoadDir(file_path + fd.name + L"/");
        }
        else if (fd.name[0] != '.')
        {
            files_.push_back(file_path + fd.name);
        }
    } while (_wfindnext(handle, &fd) == 0);

    _findclose(handle);
}

void SoundManager::LoadAll(std::wstring file_path)
{
    LoadDir(file_path);

    for (auto& file : files_)
    {
        Load(file);
    }
}

Sound* SoundManager::GetPtr(W_STR sound_file)
{
    for (auto& sound : sounds_)
    {
        if (sound.first == sound_file)
        {
            return sound.second;
        }
    }

    return nullptr;
}

T_STR SoundManager::GetSplitName(std::wstring sound_file)
{
    W_STR split_name;
    TCHAR dirve[MAX_PATH] = { 0 };
    TCHAR dir[MAX_PATH] = { 0 };
    TCHAR file[MAX_PATH] = { 0 };
    TCHAR ext[MAX_PATH] = { 0 };

    _tsplitpath_s(sound_file.c_str(), dirve, dir, file, ext);
    split_name = file;
    split_name += ext;

    return split_name;
}

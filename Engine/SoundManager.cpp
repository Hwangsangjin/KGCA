#include "pch.h"
#include "SoundManager.h"

HRESULT SoundManager::Init()
{
    FMOD::System_Create(&_pSystem);
    _pSystem->init(32, FMOD_INIT_NORMAL, 0);

    return TRUE;
}

HRESULT SoundManager::Frame()
{
    _pSystem->update();

    for (auto& sound : _sounds)
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
    for (auto& sound : _sounds)
    {
        SAFE_DELETE(sound.second);
    }

    _pSystem->close();
    _pSystem->release();
    _sounds.clear();

    return TRUE;
}

Sound* SoundManager::Load(std::wstring filename)
{
    HRESULT hr;
    W_STR splitName = GetSplitName(filename);

    // 중복 제거
    for (auto& sound : _sounds)
    {
        if (sound.first == filename)
        {
            return sound.second;
        }
    }

    Sound* pNewSound = new Sound;
    pNewSound->GetName() = filename;
    if (pNewSound)
    {
        hr = pNewSound->Load(_pSystem, filename);
        if (SUCCEEDED(hr))
        {
            _sounds.insert(std::make_pair(splitName, pNewSound));
        }
    }

    return nullptr;
}

void SoundManager::LoadDir(std::wstring path)
{
    W_STR dir = path + L"*.*";
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
            LoadDir(path + fd.name + L"/");
        }
        else if (fd.name[0] != '.')
        {
            _files.push_back(path + fd.name);
        }
    } while (_wfindnext(handle, &fd) == 0);

    _findclose(handle);
}

void SoundManager::LoadAll(std::wstring path)
{
    LoadDir(path);

    for (auto& file : _files)
    {
        Load(file);
    }
}

Sound* SoundManager::GetPtr(W_STR filename)
{
    for (auto& sound : _sounds)
    {
        if (sound.first == filename)
        {
            return sound.second;
        }
    }

    return nullptr;
}

T_STR SoundManager::GetSplitName(std::wstring filename)
{
    W_STR splitName;
    TCHAR dirve[MAX_PATH] = { 0 };
    TCHAR dir[MAX_PATH] = { 0 };
    TCHAR file[MAX_PATH] = { 0 };
    TCHAR ext[MAX_PATH] = { 0 };

    _tsplitpath_s(filename.c_str(), dirve, dir, file, ext);
    splitName = file;
    splitName += ext;

    return splitName;
}

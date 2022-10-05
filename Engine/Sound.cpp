#include "pch.h"
#include "Sound.h"

HRESULT Sound::Init()
{
    return TRUE;
}

HRESULT Sound::Frame()
{
    if (_pChannel)
    {
        UINT ms = 0;
        _pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
        TCHAR buffer[256] = { 0 };
        _stprintf_s(buffer, _T("경과 시간[%02d:%02d], 파일 크기[%02d:%02d:%02d]"), ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 60, _totalTime / 1000 / 60, _totalTime / 1000 % 60, _totalTime / 10 % 60);
        _buffer = buffer;
    }

    return TRUE;
}

HRESULT Sound::Render()
{
    return TRUE;
}

HRESULT Sound::Release()
{
    if (_pSound)
    {
        _pSound->release();
    }

    return TRUE;
}

HRESULT Sound::Load(FMOD::System* pSystem, std::wstring filename)
{
    _pSystem = pSystem;

    FMOD_RESULT hr = _pSystem->createStream(to_wm(filename).c_str(), FMOD_DEFAULT, nullptr, &_pSound);
    if (hr == FMOD_OK)
    {
        _pSound->getLength(&_totalTime, FMOD_TIMEUNIT_MS);
    }

    return TRUE;
}

HRESULT Sound::PlayBGM(bool isLoop)
{
    if (IsPlaying() == false)
    {
        FMOD_RESULT hr = _pSystem->playSound(_pSound, nullptr, false, &_pChannel);
        if (hr == FMOD_OK)
        {
            _volume = 0.5f;
            _pChannel->setVolume(_volume);
            SetLoop(isLoop);
        }
    }

    return TRUE;
}

HRESULT Sound::PlayEffect(bool isLoop)
{
    FMOD_RESULT hr = _pSystem->playSound(_pSound, nullptr, false, &_pChannel2);
    if (hr == FMOD_OK)
    {
        _volume = 1.0f;
        _pChannel2->setVolume(_volume);
        SetLoop(isLoop);
    }

    return TRUE;
}

bool Sound::IsPlaying()
{
    bool isPlaying = false;

    if (_pChannel != nullptr)
    {
        _pChannel->isPlaying(&isPlaying);
    }

    return isPlaying;
}

void Sound::SetLoop(bool isLoop)
{
    if (isLoop)
    {
        _pSound->setMode(FMOD_LOOP_NORMAL);
    }
    else
    {
        _pSound->setMode(FMOD_LOOP_OFF);
    }
}

void Sound::Paused()
{
    if (_pChannel == nullptr)
    {
        return;
    }

    bool isPaused;
    _pChannel->getPaused(&isPaused);
    _pChannel->setPaused(!isPaused);
}

void Sound::Stop()
{
    _pChannel->stop();
}

void Sound::VolumeUp(float volume)
{
    _volume += volume;
    _volume = max(0.0f, _volume);
    _pChannel->setVolume(_volume);
}

void Sound::VolumeDown(float volume)
{
    _volume -= volume;
    _volume = max(0.0f, _volume);
    _pChannel->setVolume(_volume);
}

std::wstring Sound::GetName()
{
    return _name;
}

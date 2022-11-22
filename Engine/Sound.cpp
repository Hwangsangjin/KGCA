#include "pch.h"
#include "Sound.h"

HRESULT Sound::Init()
{
    return TRUE;
}

HRESULT Sound::Frame()
{
    if (channel_)
    {
        UINT ms = 0;
        channel_->getPosition(&ms, FMOD_TIMEUNIT_MS);
        TCHAR buffer[256] = { 0 };
        _stprintf_s(buffer, _T("경과 시간[%02d:%02d], 파일 크기[%02d:%02d:%02d]"), ms / 1000 / 60, ms / 1000 % 60, ms / 10 % 60, total_time_ / 1000 / 60, total_time_ / 1000 % 60, total_time_ / 10 % 60);
        buffer_ = buffer;
    }

    return TRUE;
}

HRESULT Sound::Render()
{
    return TRUE;
}

HRESULT Sound::Release()
{
    if (sound_)
    {
        sound_->release();
    }

    return TRUE;
}

HRESULT Sound::Load(FMOD::System* system, std::wstring sound_file)
{
    system_ = system;

    FMOD_RESULT hr = system_->createStream(to_wm(sound_file).c_str(), FMOD_DEFAULT, nullptr, &sound_);
    if (hr == FMOD_OK)
    {
        sound_->getLength(&total_time_, FMOD_TIMEUNIT_MS);
    }

    return TRUE;
}

HRESULT Sound::PlayBGM(bool is_loop)
{
    if (IsPlaying() == false)
    {
        FMOD_RESULT hr = system_->playSound(sound_, nullptr, false, &channel_);
        if (hr == FMOD_OK)
        {
            volume_ = 0.5f;
            channel_->setVolume(volume_);
            SetLoop(is_loop);
        }
    }

    return TRUE;
}

HRESULT Sound::PlayEffect(bool is_loop)
{
    FMOD_RESULT hr = system_->playSound(sound_, nullptr, false, &channel2_);
    if (hr == FMOD_OK)
    {
        volume_ = 1.0f;
        channel2_->setVolume(volume_);
        SetLoop(is_loop);
    }

    return TRUE;
}

bool Sound::IsPlaying()
{
    bool is_playing = false;

    if (channel_ != nullptr)
    {
        channel_->isPlaying(&is_playing);
    }

    return is_playing;
}

void Sound::SetLoop(bool is_loop)
{
    if (is_loop)
    {
        sound_->setMode(FMOD_LOOP_NORMAL);
    }
    else
    {
        sound_->setMode(FMOD_LOOP_OFF);
    }
}

void Sound::Paused()
{
    if (channel_ == nullptr)
    {
        return;
    }

    bool is_paused;
    channel_->getPaused(&is_paused);
    channel_->setPaused(!is_paused);
}

void Sound::Stop()
{
    channel_->stop();
}

void Sound::VolumeUp(float volume)
{
    volume_ += volume;
    volume_ = max(0.0f, volume_);
    channel_->setVolume(volume_);
}

void Sound::VolumeDown(float volume)
{
    volume_ -= volume;
    volume_ = max(0.0f, volume_);
    channel_->setVolume(volume_);
}

std::wstring Sound::GetName()
{
    return name_;
}

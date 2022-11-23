#include "pch.h"
#include "Timer.h"

HRESULT Timer::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency_));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&prev_count_));

	return TRUE;
}

HRESULT Timer::Frame()
{
	__int64 current_count;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&current_count));

	delta_time_ = (current_count - prev_count_) / static_cast<float>(frequency_);
	prev_count_ = current_count;

	frame_count_++;
	frame_time_ += delta_time_;
	game_time_ += delta_time_;

	if (frame_time_ >= 1.0f)
	{
		fps_ = static_cast<int32>(frame_count_ / frame_time_);

		frame_count_ = 0;
		frame_time_ = 0.0f;
	}

#ifdef _DEBUG
	if (delta_time_ >= 1.0f / 60.0f)
	{
		delta_time_ = 1.0f / 60.0f;
	}
#endif

	return TRUE;
}

HRESULT Timer::Render()
{
	return TRUE;
}

HRESULT Timer::Release()
{
	return TRUE;
}

int32 Timer::GetFPS()
{
	return fps_;
}

float Timer::GetDeltaTime()
{
	return delta_time_;
}

float Timer::GetGameTime()
{
	return game_time_;
}

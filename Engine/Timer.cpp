#include "pch.h"
#include "Timer.h"

HRESULT Timer::Init()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount));

	return TRUE;
}

HRESULT Timer::Frame()
{
	uint64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime;
	_gameTime += _deltaTime;

	if (_frameTime >= 1.0f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		_frameTime = 0;
		_frameCount = 0;
	}

	_text = L"FPS: ";
	_text += std::to_wstring((int)_fps);

#ifdef _DEBUG
	if (_deltaTime >= 1.0f / 60.0f)
	{
		_deltaTime = 1.0f / 60.0f;
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

uint32 Timer::GetFPS()
{
	return _fps;
}

float Timer::GetDeltaTime()
{
	return _deltaTime;
}

std::wstring Timer::GetText()
{
	return _text;
}

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
		_fps = _frameCount;

		_frameCount = 0;
		_frameTime = 0;
	}

	_text = L"FPS: ";
	_text += std::to_wstring((int)_fps);

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

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

	if (_frameTime > 1.0f)
	{
		_fps = static_cast<uint32>(_frameCount / _frameTime);

		_frameTime = 0;
		_frameCount = 0;
	}

	return TRUE;
}

HRESULT Timer::Render()
{
	std::wstring fpsText = L"Client FPS : ";
	fpsText += std::to_wstring((int)_fps);
	SetWindowText(hWnd, fpsText.c_str());

	return TRUE;
}

HRESULT Timer::Release()
{
	return TRUE;
}

unsigned int Timer::GetFPS()
{
	return _fps;
}

float Timer::GetDeltaTime()
{
	return _deltaTime;
}


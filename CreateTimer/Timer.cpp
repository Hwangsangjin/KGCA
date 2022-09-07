#include "pch.h"
#include "Timer.h"

int Timer::_frameCnt = 0;
float Timer::_elapsed = 0.0f;

HRESULT Timer::Init()
{
	_start = clock::now();

	return TRUE;
}

HRESULT Timer::Frame()
{
	_end = clock::now();
	_duration = std::chrono::duration_cast<second>(_end - _start).count();

	_frameCnt++;

	// 1초 동안의 프레임 시간의 평균을 계산
	if ((_duration - _elapsed) >= 1.0f)
	{
		// 초당 프레임 수
		_fps = (float)_frameCnt;
		// 프레임당 밀리초 수
		_mspf = 1000.0f / _fps;

		// 다음 계산을 위해 리셋
		_frameCnt = 0;
		_elapsed += 1.0f;
	}

	return TRUE;
}

HRESULT Timer::Render()
{
	std::wstring fpsText = L"Client FPS: ";
	fpsText += std::to_wstring((int)_fps);
	SetWindowText(_hWnd, fpsText.c_str());

	return TRUE;
}

HRESULT Timer::Release()
{
	return TRUE;
}

HRESULT Timer::SetTimer(HWND hWnd)
{
	_hWnd = hWnd;

	return TRUE;
}

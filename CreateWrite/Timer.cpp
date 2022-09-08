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

	// 1�� ������ ������ �ð��� ����� ���
	if ((_duration - _elapsed) >= 1.0f)
	{
		// �ʴ� ������ ��
		_fps = (float)_frameCnt;
		// �����Ӵ� �и��� ��
		_mspf = 1000.0f / _fps;

		// ���� ����� ���� ����
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

#include "pch.h"
#include "Timer.h"

int Timer::_frameCnt = 0;
float Timer::_elapsed = 0.0f;

HRESULT Timer::Init()
{
	_start = clock::now();

	m_fGameTimer = 0.0f;
	m_fElapseTimer = 10.0f;
	m_dwBeforeTime = timeGetTime();

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

	DWORD dwCurrentTime = timeGetTime();
	DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
	m_fElapseTimer = dwElapseTime / 1000.0f;
	m_fGameTimer += m_fElapseTimer;
	{
		m_iFPSCounter++;
		m_fFPSTimer += m_fElapseTimer;
		if (m_fFPSTimer >= 1.0f)
		{
			m_iFPS = m_iFPSCounter;
			m_iFPSCounter = 0;
			m_fFPSTimer = m_fFPSTimer - 1.0f;
		}
	}

	m_dwBeforeTime = dwCurrentTime;

	return TRUE;
}

HRESULT Timer::Render()
{
	std::cout << "FPS: " << _fps << " " << "MSPF: " << _mspf << std::endl;

	m_szTimer = std::to_wstring(m_fGameTimer);
	m_szTimer += L"   ";
	m_szTimer += std::to_wstring(m_iFPS);
	m_szTimer += L"\n";
	OutputDebugString(m_szTimer.c_str());

	return TRUE;
}

HRESULT Timer::Release()
{
	return TRUE;
}

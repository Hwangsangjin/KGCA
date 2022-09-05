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

#include "pch.h"
#include "Timer.h"

HRESULT Timer::Init()
{
	if (FAILED(InitTimer()))
	{
		return E_FAIL;
	}

	return TRUE;
}

HRESULT Timer::InitTimer()
{
	Start();

	return TRUE;
}

HRESULT Timer::Frame()
{

	return TRUE;
}

HRESULT Timer::Render()
{
	std::wstring timer = std::to_wstring(_elapsed.count());
	timer += L"\n";

	//OutputDebugString(timer.c_str());

	return TRUE;
}

HRESULT Timer::Release()
{
	return TRUE;
}

HRESULT Timer::Start()
{
	if (isRun)
	{
		return E_FAIL;
	}
	else
	{
		_start = std::chrono::high_resolution_clock::now();
		isRun = true;

		return TRUE;
	}
}

HRESULT Timer::Stop()
{
	if (!isRun)
	{
		return E_FAIL;
	}
	else
	{
		_stop = std::chrono::high_resolution_clock::now();
		isRun = false;

		return TRUE;
	}
}

float Timer::GetElapsed()
{
	if (isRun)
	{
		_elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - _start);
		return _elapsed.count();
	}
	else
	{
		_elapsed = std::chrono::duration<double, std::milli>(_stop - _start);
		return _elapsed.count();
	}
}

void Timer::Reset()
{
	isRun = true;
	_start = std::chrono::high_resolution_clock::now();
}

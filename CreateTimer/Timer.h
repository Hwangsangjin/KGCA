#pragma once

class Timer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> _start;
	std::chrono::time_point<std::chrono::steady_clock> _stop;
	std::chrono::duration<float, std::milli> _elapsed;

	bool isRun = false;

public:
	HRESULT Init();
	HRESULT InitTimer();
	HRESULT Frame();
	HRESULT Render();
	HRESULT Release();

	HRESULT Start();
	HRESULT Stop();
	float GetElapsed();
	void Reset();
};
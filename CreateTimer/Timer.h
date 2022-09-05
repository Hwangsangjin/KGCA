#pragma once

class Timer
{
private:
    using clock = std::chrono::high_resolution_clock;
    using second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<clock> _start;
    std::chrono::time_point<clock> _end;

    static int _frameCnt;
    static float _elapsed;

    double _duration = 0;

    float _fps = 0;
    float _mspf = 0;

    float m_fGameTimer = 0.0f;
    float m_fElapseTimer = 10.0f;
    UINT  m_iFPS = 0;
    std::wstring m_szTimer;
    DWORD m_dwBeforeTime;
    UINT  m_iFPSCounter = 0;
    float m_fFPSTimer = 0.0f;

public:
    HRESULT Init();
    HRESULT Frame();
    HRESULT Render();
    HRESULT Release();
};


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

    float _duration = 0;
    float _fps = 0;
    float _mspf = 0;

    HWND _hWnd;

public:
    // 초기화
    HRESULT Init();
    // 프레임 계산
    HRESULT Frame();
    // 렌더
    HRESULT Render();
    // 메모리 해제
    HRESULT Release();

    // 설정
    HRESULT SetTimer(HWND hWnd);
};


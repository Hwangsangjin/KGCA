#pragma once

#include <Windows.h>
#include <string>

class Timer
{
private:
    __int64 _frequency = 0;
    __int64 _prevCount = 0;
    __int32 _frameCount = 0;
    float _frameTime = 0;
    float _deltaTime = 0;
    float _gameTime = 0;
    __int32 _fps = 0;

    std::wstring _text;

    Timer() {}
    ~Timer()
    {
        Release();
    }

public:
    // 싱글톤
    static Timer* GetInstance()
    {
        static Timer instance;
        return &instance;
    }

    // 초기화
    HRESULT Init();
    // 프레임 계산
    HRESULT Frame();
    // 렌더
    HRESULT Render();
    // 메모리 해제
    HRESULT Release();

    // 초당 프레임 수
    __int32 GetFPS();

    // 지연 시간
    float GetDeltaTime();
    // 게임 시간
    float GetGameTime();

    // 텍스트
    std::wstring GetText();
};


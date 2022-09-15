#pragma once

class Timer
{
    DECLARE_SINGLE(Timer);

private: 
    uint64 _frequency = 0;
    uint64 _prevCount = 0;
    float _deltaTime = 0;

    uint32 _frameCount = 0;
    float _frameTime = 0;
    float _gameTime = 0;
    uint32 _fps = 0;

    std::wstring _text;

public:
    // 초기화
    HRESULT Init();
    // 프레임 계산
    HRESULT Frame();
    // 렌더
    HRESULT Render();
    // 메모리 해제
    HRESULT Release();

    // 초당 프레임 수
    uint32 GetFPS();
    // 지연 시간
    float GetDeltaTime();

    // 텍스트
    std::wstring GetText();
};


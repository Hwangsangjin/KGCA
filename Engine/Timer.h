#pragma once

class Timer
{
    DECLARE_SINGLE(Timer);

private:
    int64 _frequency = 0;
    int64 _prevCount = 0;
    int32 _frameCount = 0;
    float _frameTime = 0;
    float _deltaTime = 0;
    float _gameTime = 0;
    int32 _fps = 0;

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
    int32 GetFPS();

    // 지연 시간
    float GetDeltaTime();
    // 게임 시간
    float GetGameTime();

    // 텍스트
    std::wstring GetText();
};


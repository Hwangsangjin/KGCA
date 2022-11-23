#pragma once

class Timer
{
private:
    int64 frequency_ = 0;
    int64 prev_count_ = 0;
    int32 frame_count_ = 0;
    float frame_time_ = 0;
    float delta_time_ = 0;
    float game_time_ = 0;
    int32 fps_ = 0;

    Timer() = default;
    ~Timer() = default;

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
    int32 GetFPS();

    // 지연 시간
    float GetDeltaTime();
    // 게임 시간
    float GetGameTime();
};


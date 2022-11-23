#pragma once

enum KEY_STATE
{
    NONE,
    UP,
    DOWN,
    HOLD
};

class Input
{
private:
    DWORD key_state_[256] = { 0 };
    POINT position_ = { 0, 0 };

    Input() = default;
    ~Input() = default;

public:
    // 싱글톤
    static Input* GetInstance()
    {
        static Input instance;
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

    // 키
    DWORD GetKey(DWORD key);
    // 위치
    POINT GetPosition();
};


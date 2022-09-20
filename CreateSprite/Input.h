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
    DECLARE_SINGLE(Input);

private:
    DWORD _keyState[256];
    POINT _position;

public:
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
    POINT GetPos();
};


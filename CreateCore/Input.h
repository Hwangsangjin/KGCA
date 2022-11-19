#pragma once

#include <Windows.h>

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
    DWORD _keyState[256];
    POINT _position;

    Input() {}
    ~Input()
    {
        Release();
    }

public:
    // �̱���
    static Input* GetInstance()
    {
        static Input instance;
        return &instance;
    }

    // �ʱ�ȭ
    HRESULT Init();
    // ������ ���
    HRESULT Frame();
    // ����
    HRESULT Render();
    // �޸� ����
    HRESULT Release();

    // Ű
    DWORD GetKey(DWORD key);
    // ��ġ
    POINT GetPosition();
};


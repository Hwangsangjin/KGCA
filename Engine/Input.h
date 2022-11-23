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


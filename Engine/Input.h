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
    DWORD _keyState[256] = { 0 };
    POINT _position = { 0, 0 };

public:
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


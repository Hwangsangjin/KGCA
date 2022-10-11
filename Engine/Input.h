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
    POINT GetPos();

private:
    DWORD _keyState[256];
    POINT _position;
};


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
    // �̱���
    static Timer* GetInstance()
    {
        static Timer instance;
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

    // �ʴ� ������ ��
    __int32 GetFPS();

    // ���� �ð�
    float GetDeltaTime();
    // ���� �ð�
    float GetGameTime();

    // �ؽ�Ʈ
    std::wstring GetText();
};


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
    // �ʱ�ȭ
    HRESULT Init();
    // ������ ���
    HRESULT Frame();
    // ����
    HRESULT Render();
    // �޸� ����
    HRESULT Release();

    // �ʴ� ������ ��
    int32 GetFPS();

    // ���� �ð�
    float GetDeltaTime();
    // ���� �ð�
    float GetGameTime();

    // �ؽ�Ʈ
    std::wstring GetText();
};


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
    int32 GetFPS();

    // ���� �ð�
    float GetDeltaTime();
    // ���� �ð�
    float GetGameTime();
};


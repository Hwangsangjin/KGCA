#pragma once

class Timer
{
    DECLARE_SINGLE(Timer);

private:
    int64 frequency_ = 0;
    int64 prev_count_ = 0;
    int32 frame_count_ = 0;
    float frame_time_ = 0;
    float delta_time_ = 0;
    float game_time_ = 0;
    int32 fps_ = 0;

    std::wstring text_;

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


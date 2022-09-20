#pragma once

class Sound
{
public:
	FMOD::System* _pSystem = nullptr;
	FMOD::Sound* _pSound = nullptr;
	FMOD::Channel* _pChannel = nullptr;

	std::wstring _name;
	std::wstring _buffer;
	UINT _totalTime;
	float _volume;

public:
	// �ʱ�ȭ
	HRESULT Init();
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();

	HRESULT Load(FMOD::System* pSystem, std::wstring filename);
	HRESULT PlayBGM(bool isLooping = false);
	HRESULT PlayEffect(bool isLooping = false);
	bool IsPlaying();
	void SetLoop(bool isLooping = false);
	void Paused();
	void Stop();
	void VolumeUp(float volume = 0.1f);
	void VolumeDown(float volume = 0.1f);

	std::wstring GetName();
};


#pragma once

class Sound
{
public:
	FMOD::System* system_ = nullptr;
	FMOD::Sound* sound_ = nullptr;
	FMOD::Channel* channel_ = nullptr;
	FMOD::Channel* channel2_ = nullptr;

	std::wstring name_;
	std::wstring buffer_;
	UINT total_time_;
	float volume_;

	// 초기화
	HRESULT Init();
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();

	HRESULT Load(FMOD::System* system, std::wstring sound_file);
	HRESULT PlayBGM(bool is_loop = false);
	HRESULT PlayEffect(bool is_loop = false);
	bool IsPlaying();
	void SetLoop(bool is_loop = false);
	void Paused();
	void Stop();
	void VolumeUp(float volume = 0.1f);
	void VolumeDown(float volume = 0.1f);

	std::wstring GetName();
};


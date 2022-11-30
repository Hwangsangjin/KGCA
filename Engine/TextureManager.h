#pragma once

class Texture;

class TextureManager
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

	std::shared_ptr<Texture> texture_;
	std::map<std::wstring, std::shared_ptr<Texture>> textures_;

	TextureManager() = default;
	~TextureManager() = default;

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

public:
	// 싱글톤
	static TextureManager* GetInstance()
	{
		static TextureManager instance;
		return &instance;
	}

	// 초기화
	HRESULT Init();
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();

	// 디바이스 설정
	HRESULT SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context);

	// 텍스처 파일 로드
	std::shared_ptr<Texture> LoadFile(std::wstring texture_file);
	// 텍스처 파일 검색
	std::shared_ptr<Texture> FindFile(std::wstring texture_file);

	// 파일명 분할
	T_STR GetSplitName(std::wstring texture_file);
	T_STR GetSplitName(std::string texture_file);
};


#pragma once

class TextureManager
{
	DECLARE_SINGLE(TextureManager);

private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

	std::map<std::wstring, class Texture*> textures_;

public:
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
	Texture* Load(std::wstring texture_file);
	// 텍스처 파일 검색
	Texture* Find(std::wstring texture_file);
	// 파일명 분할
	T_STR GetSplitName(std::wstring full_path);
	T_STR GetSplitName(std::string full_path);
};


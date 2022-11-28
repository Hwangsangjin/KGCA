#pragma once

class ShaderManager
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

	std::shared_ptr<class Shader> shader_;
	std::map<std::wstring, std::shared_ptr<class Shader>> shaders_;

	ShaderManager() = default;
	~ShaderManager() = default;

	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;

public:
	// 싱글톤
	static ShaderManager* GetInstance()
	{
		static ShaderManager instance;
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

	// 셰이더 파일 로드
	std::shared_ptr<Shader> LoadFile(std::wstring shader_file);
	// 셰이더 파일 검색
	std::shared_ptr<Shader> FindFile(std::wstring shader_file);
};


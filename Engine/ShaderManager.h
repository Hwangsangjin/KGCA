#pragma once

class ShaderManager
{
	DECLARE_SINGLE(ShaderManager);

private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

	std::map<std::wstring, class Shader*> shaders_;

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

	// 셰이더 파일 로드
	Shader* Load(std::wstring shader_file);
};


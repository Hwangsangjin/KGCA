#pragma once

class Shader
{
private:
	// 디바이스
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	// 디바이스 컨텍스트
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

public:
	// 정점 셰이더
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader_;
	// 정점 셰이더 코드
	Microsoft::WRL::ComPtr<ID3DBlob> vertex_shader_code_;
	// 픽셀 셰이더
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader_;
	// 픽셀 셰이더 코드
	Microsoft::WRL::ComPtr<ID3DBlob> pixel_shader_code_;

	// 초기화
	HRESULT Init();
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();

	// 디바이스 설정
	void SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context);

	// 셰이더 생성
	HRESULT CreateShader(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring shader_file);
};


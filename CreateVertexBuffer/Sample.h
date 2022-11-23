#pragma once

#include "Core.h"

// 정점 구조체
struct SampleVertex
{
	float x;
	float y;
	float z;
};

class Sample : public Core
{
private:
	// 정점 버퍼
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;

	// 정점 셰이더
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader_;
	// 정점 셰이더 코드
	Microsoft::WRL::ComPtr<ID3DBlob> vertex_shader_code_;

	// 픽셀 셰이더
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader_;
	// 픽셀 셰이더 코드
	Microsoft::WRL::ComPtr<ID3DBlob> pixel_shader_code_;

	// 입력 레이아웃
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;

public:
	// 생성자, 소멸자
	Sample() = default;
	virtual ~Sample() = default;

	// 초기화
	virtual HRESULT Init() override;
	// 프레임 계산
	virtual HRESULT Frame() override;
	// 렌더
	virtual HRESULT Render() override;
	// 메모리 해제
	virtual HRESULT Release() override;

	// 정점 버퍼 생성
	HRESULT CreateVertexBuffer();

	// 셰이더 컴파일 및 생성
	HRESULT CreateShader();

	// 입력 레이아웃 생성
	HRESULT CreateInputLayout();
};


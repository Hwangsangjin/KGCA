#pragma once

#include "Core.h"

// ���� ����ü
struct Vertex
{
	float x;
	float y;
	float z;
};

class Sample : public Core
{
private:
	// ���� ����
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;

	// ���� ���̴�
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader_;
	// ���� ���̴� �ڵ�
	Microsoft::WRL::ComPtr<ID3DBlob> vertex_shader_code_;

	// �ȼ� ���̴�
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader_;
	// �ȼ� ���̴� �ڵ�
	Microsoft::WRL::ComPtr<ID3DBlob> pixel_shader_code_;

	// �Է� ���̾ƿ�
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;

public:
	// ������, �Ҹ���
	Sample() = default;
	virtual ~Sample() = default;

	// �ʱ�ȭ
	virtual HRESULT Init() override;
	// ������ ���
	virtual HRESULT Frame() override;
	// ����
	virtual HRESULT Render() override;
	// �޸� ����
	virtual HRESULT Release() override;

	// ���� ���� ����
	HRESULT CreateVertexBuffer();

	// ���̴� ������ �� ����
	HRESULT CreateShader();

	// �Է� ���̾ƿ� ����
	HRESULT CreateInputLayout();
};

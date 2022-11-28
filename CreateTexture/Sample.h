#pragma once

#include "Core.h"

// ���� ����ü
struct SampleVertex
{
	float x;
	float y;
	float z;

	float u;
	float v;
};

class Sample : public Core
{
private:
	// ���� ����
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;
	// �ε��� ����
	Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer_;

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

	// �ؽ�ó
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D_;
	D3D11_TEXTURE2D_DESC texture2D_desc_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view_;

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
	// �ε��� ���� ����
	HRESULT CreateIndexBuffer();

	// ���̴� ������ �� ����
	HRESULT CreateShader();

	// �Է� ���̾ƿ� ����
	HRESULT CreateInputLayout();

	// �ؽ�ó ����
	HRESULT CreateTexture();
};


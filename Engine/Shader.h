#pragma once

class Shader
{
private:
	// ����̽�
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	// ����̽� ���ؽ�Ʈ
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

public:
	// ���� ���̴�
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader_;
	// ���� ���̴� �ڵ�
	Microsoft::WRL::ComPtr<ID3DBlob> vertex_shader_code_;
	// �ȼ� ���̴�
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader_;
	// �ȼ� ���̴� �ڵ�
	Microsoft::WRL::ComPtr<ID3DBlob> pixel_shader_code_;

	// �ʱ�ȭ
	HRESULT Init();
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();

	// ����̽� ����
	void SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context);

	// ���̴� ����
	HRESULT CreateShader(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring shader_file);
};


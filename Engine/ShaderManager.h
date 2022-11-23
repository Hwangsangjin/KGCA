#pragma once

class ShaderManager
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

	std::map<std::wstring, class Shader*> shaders_;

	ShaderManager() = default;
	~ShaderManager() = default;

public:
	// �̱���
	static ShaderManager* GetInstance()
	{
		static ShaderManager instance;
		return &instance;
	}

	// �ʱ�ȭ
	HRESULT Init();
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();

	// ����̽� ����
	HRESULT SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context);

	// ���̴� ���� �ε�
	Shader* Load(std::wstring shader_file);
};


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
	std::shared_ptr<Shader> LoadFile(std::wstring shader_file);
	// ���̴� ���� �˻�
	std::shared_ptr<Shader> FindFile(std::wstring shader_file);
};


#pragma once

class Texture;

class TextureManager
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

	std::shared_ptr<Texture> texture_;
	std::map<std::wstring, std::shared_ptr<Texture>> textures_;

	TextureManager() = default;
	~TextureManager() = default;

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

public:
	// �̱���
	static TextureManager* GetInstance()
	{
		static TextureManager instance;
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

	// �ؽ�ó ���� �ε�
	std::shared_ptr<Texture> LoadFile(std::wstring texture_file);
	// �ؽ�ó ���� �˻�
	std::shared_ptr<Texture> FindFile(std::wstring texture_file);

	// ���ϸ� ����
	T_STR GetSplitName(std::wstring texture_file);
	T_STR GetSplitName(std::string texture_file);
};


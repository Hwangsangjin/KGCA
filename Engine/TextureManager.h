#pragma once

class TextureManager
{
	DECLARE_SINGLE(TextureManager);

private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;

	std::map<std::wstring, class Texture*> textures_;

public:
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
	Texture* Load(std::wstring texture_file);
	// �ؽ�ó ���� �˻�
	Texture* Find(std::wstring texture_file);
	// ���ϸ� ����
	T_STR GetSplitName(std::wstring full_path);
	T_STR GetSplitName(std::string full_path);
};


#pragma once
class Texture
{
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device_;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D_;

public:
	D3D11_TEXTURE2D_DESC texture2D_desc_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shader_resource_view_;

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

	// �ؽ�ó ����
	HRESULT CreateTexture(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring texture_file);
};


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

	// 텍스처 생성
	HRESULT CreateTexture(ID3D11Device* device, ID3D11DeviceContext* device_context, std::wstring texture_file);
};


#pragma once
class Texture
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;
	ID3D11Texture2D* _pTexture2D = nullptr;

public:
	D3D11_TEXTURE2D_DESC _desc;
	ID3D11ShaderResourceView* _pShaderResourceView = nullptr;

	// 초기화
	HRESULT Init();
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();

	// 디바이스 설정
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	// 텍스처 생성
	HRESULT CreateTexture(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring texturefile);
};


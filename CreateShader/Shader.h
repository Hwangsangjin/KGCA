#pragma once
class Shader
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3DBlob* _pVertexShaderCode = nullptr;
	ID3DBlob* _pPixelShaderCode = nullptr;

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
	void SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	// ���̴� ����
	HRESULT CreateShader(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring filename);

	// ���� ���̴� �ڵ�
	ID3DBlob* GetVSCode();

	// ���� ���̴�
	ID3D11VertexShader* GetVS();
	// �ȼ� ���̴�
	ID3D11PixelShader* GetPS();
};

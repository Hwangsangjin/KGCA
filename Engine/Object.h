#pragma once

#include "Shader.h"
#include "Texture.h"

class Object
{
public:
	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT PreRender();
	virtual HRESULT Render();
	virtual HRESULT PostRender();
	// �޸� ����
	virtual HRESULT Release();

	// ���� ����
	virtual void SetMatrix(MyMatrix* world, MyMatrix* view, MyMatrix* projection);

	// ����̽� ����
	virtual HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	// ������Ʈ ����
	virtual HRESULT CreateObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shaderFile, std::wstring textureFile);

	// ���� ������ ����
	virtual void CreateVertexData();
	// ���� ���� ����
	virtual HRESULT CreateVertexBuffer();
	// �ε��� ������ ����
	virtual void CreateIndexData();
	// �ε��� ���� ����
	virtual HRESULT CreateIndexBuffer();
	// ��� ������ ����
	virtual void CreateConstantData();
	// ��� ���� ����
	virtual HRESULT CreateConstantBuffer();
	// ���̴� ����
	virtual HRESULT CreateShader(std::wstring shaderFile);
	// �Է� ���̾ƿ� ����
	virtual HRESULT CreateInputLayout();
	// �ؽ�ó ����
	virtual HRESULT CreateTexture(std::wstring textureFile);

	// ���� ���� ����
	virtual void UpdateVertexBuffer();
	// ��� ���� ����
	virtual void UpdateConstantBuffer();

	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	std::vector<Vertex> _init;
	std::vector<Vertex> _vertices;
	std::vector<DWORD> _indices;
	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11Buffer* _pIndexBuffer = nullptr;
	ConstantBuffer _constantBuffer;
	ID3D11Buffer* _pConstantBuffer = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr;

	Texture* _pTexture = nullptr;
	Shader* _pShader = nullptr;
	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3DBlob* _pVertexShaderCode = nullptr;
	ID3DBlob* _pPixelShaderCode = nullptr;
	ID3D11ShaderResourceView* _pShaderResourceView = nullptr;

	MyMatrix _World;
	MyMatrix _View;
	MyMatrix _Projection;
};


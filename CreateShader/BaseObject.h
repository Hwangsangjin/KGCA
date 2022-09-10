#pragma once

#include "Shader.h"

class BaseObject
{
private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	std::vector<Vertex> _vertices;
	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr;

	Shader* _pShader;
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
	HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	// ������Ʈ ����
	HRESULT CreateObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring filename);

	// ���� ���� ����
	HRESULT CreateVertexBuffer();
	// ���̴� ����
	HRESULT CreateShader(std::wstring filename);
	// �Է� ���̾ƿ� ����
	HRESULT CreateInputLayout();
};


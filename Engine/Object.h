#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Collision.h"

struct SimpleVertex
{
	DxVector3 position;
	DxVector4 color;
	DxVector2 uv;
};

struct DefaultVertex
{
	DxVector3 position;
	DxVector3 normal;
	DxVector4 color;
	DxVector2 uv;
};

struct IndexWeightVertex
{
	DxVector4 index;
	DxVector4 weight;
};

struct ConstantBuffer
{
	DxMatrix world;
	DxMatrix view;
	DxMatrix projection;
	float x;
	float y;
	float z;
	float timer;
};

struct BoneBuffer
{
	DxMatrix boneMatrix[255];
};

class Object
{
public:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	std::vector<DefaultVertex> _init;
	std::vector<DefaultVertex> _vertices;
	std::vector<DWORD> _indices;
	ID3D11Buffer* _pVertexBuffer = nullptr;
	ID3D11Buffer* _pIndexBuffer = nullptr;
	ConstantBuffer _constantBuffer;
	ID3D11Buffer* _pConstantBuffer = nullptr;
	ID3D11InputLayout* _pInputLayout = nullptr;

	std::wstring _textureName;
	std::wstring _shaderName;
	Texture* _pTexture = nullptr;
	Shader* _pShader = nullptr;
	ID3D11VertexShader* _pVertexShader = nullptr;
	ID3D11PixelShader* _pPixelShader = nullptr;
	ID3DBlob* _pVertexShaderCode = nullptr;
	ID3DBlob* _pPixelShaderCode = nullptr;
	ID3D11ShaderResourceView* _pShaderResourceView = nullptr;

	DxMatrix _world;
	DxMatrix _view;
	DxMatrix _projection;

	DxVector3 _position;

	DWORD _face;

	Object() {}
	virtual ~Object() {};

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
	virtual void SetMatrix(DxMatrix* pWorld, DxMatrix* pView, DxMatrix* pProjection);

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

	// �ؽ�ó �ε�
	virtual HRESULT LoadTexture(W_STR filename);
};

namespace DX
{
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* pd3dDevice, void* pDataAddress, UINT vertexCount, UINT vertexSize);
}
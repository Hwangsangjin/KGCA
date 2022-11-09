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

	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT PreRender();
	virtual HRESULT Render();
	virtual HRESULT PostRender();
	// 메모리 해제
	virtual HRESULT Release();

	// 공간 설정
	virtual void SetMatrix(DxMatrix* pWorld, DxMatrix* pView, DxMatrix* pProjection);

	// 디바이스 설정
	virtual HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	// 오브젝트 생성
	virtual HRESULT CreateObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shaderFile, std::wstring textureFile);

	// 정점 데이터 생성
	virtual void CreateVertexData();
	// 정점 버퍼 생성
	virtual HRESULT CreateVertexBuffer();
	// 인덱스 데이터 생성
	virtual void CreateIndexData();
	// 인덱스 버퍼 생성
	virtual HRESULT CreateIndexBuffer();
	// 상수 데이터 생성
	virtual void CreateConstantData();
	// 상수 버퍼 생성
	virtual HRESULT CreateConstantBuffer();
	// 셰이더 생성
	virtual HRESULT CreateShader(std::wstring shaderFile);
	// 입력 레이아웃 생성
	virtual HRESULT CreateInputLayout();
	// 텍스처 생성
	virtual HRESULT CreateTexture(std::wstring textureFile);

	// 정점 버퍼 설정 
	virtual void UpdateVertexBuffer();
	// 상수 버퍼 설정
	virtual void UpdateConstantBuffer();

	// 텍스처 로드
	virtual HRESULT LoadTexture(W_STR filename);
};

namespace DX
{
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* pd3dDevice, void* pDataAddress, UINT vertexCount, UINT vertexSize);
}
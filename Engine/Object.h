#pragma once

#include "Shader.h"
#include "Texture.h"

class Object
{
public:
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
	virtual void SetMatrix(MyMatrix* world, MyMatrix* view, MyMatrix* projection);

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


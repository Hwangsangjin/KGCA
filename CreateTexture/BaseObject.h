#pragma once

#include "Shader.h"
#include "Texture.h"

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
	Texture* _pTexture = nullptr;

public:

	// 초기화
	HRESULT Init();
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	HRESULT Release();

	// 디바이스 설정
	HRESULT SetDevice(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

	// 오브젝트 생성
	HRESULT CreateObject(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext, std::wstring shaderFile, std::wstring textureFile);

	// 정점 버퍼 생성
	HRESULT CreateVertexBuffer();
	// 셰이더 생성
	HRESULT CreateShader(std::wstring shaderFile);
	// 입력 레이아웃 생성
	HRESULT CreateInputLayout();
	// 텍스처 생성
	HRESULT CreateTexture(std::wstring textureFile);
};


#pragma once

#include "Shader.h"

class ShaderManager
{
	DECLARE_SINGLE(ShaderManager);

private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	std::map<std::wstring, Shader*> _shaders;
	
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

	// 셰이더 파일 로드
	Shader* Load(std::wstring shaderFile);
};


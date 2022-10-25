#pragma once

#include "Texture.h"

class TextureManager
{
	DECLARE_SINGLE(TextureManager);

private:
	ID3D11Device* _pd3dDevice = nullptr;
	ID3D11DeviceContext* _pImmediateContext = nullptr;

	std::map<std::wstring, Texture*> _textures;

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

	// 텍스처 파일 로드
	Texture* Load(std::wstring texturefile);
	// 텍스처 파일 검색
	Texture* Find(std::wstring texturefile);
};


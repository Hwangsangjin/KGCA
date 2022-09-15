#pragma once

class DxState
{
public:
	static ID3D11SamplerState* _pDefaultSamplerState;

	// 초기화
	HRESULT Init();
	// 프레임 계산
	HRESULT Frame();
	// 렌더
	HRESULT Render();
	// 메모리 해제
	static HRESULT Release();

	// 샘플러 설정
	static HRESULT SetSamplerState(ID3D11Device* pd3dDevice);
};


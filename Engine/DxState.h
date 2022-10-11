#pragma once

class DxState
{
public:
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

	static ID3D11SamplerState* _pDefaultSSWrap;
	static ID3D11SamplerState* _pDefaultSSMirror;
	static ID3D11RasterizerState* _pDefaultRSWireFrame;
	static ID3D11RasterizerState* _pDefaultRSSolid;
	static ID3D11BlendState* _pAlphaBlend;
};


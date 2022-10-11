#pragma once

class DxState
{
public:
	// �ʱ�ȭ
	HRESULT Init();
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	static HRESULT Release();

	// ���÷� ����
	static HRESULT SetSamplerState(ID3D11Device* pd3dDevice);

	static ID3D11SamplerState* _pDefaultSSWrap;
	static ID3D11SamplerState* _pDefaultSSMirror;
	static ID3D11RasterizerState* _pDefaultRSWireFrame;
	static ID3D11RasterizerState* _pDefaultRSSolid;
	static ID3D11BlendState* _pAlphaBlend;
};


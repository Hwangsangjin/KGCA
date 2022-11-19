#pragma once

#include <wrl.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <string>

#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

class Text
{
private:
	Microsoft::WRL::ComPtr<ID2D1Factory> _pd2dFactory;
	Microsoft::WRL::ComPtr<IDWriteFactory> _pWriteFactory;
	Microsoft::WRL::ComPtr<ID2D1RenderTarget> _pd2dRenderTarget;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> _pTextFormat;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> _pTextLayout;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> _pTextColor;

	std::wstring _text = L"KGCA Game Academy";
	POINT _point = { 0, 0 };

	Text() {}
	~Text()
	{
		Release();
	}

public:
	// �̱���
	static Text* GetInstance()
	{
		static Text instance;
		return &instance;
	}

	// �ʱ�ȭ
	virtual HRESULT Init();
	// ������ ���
	virtual HRESULT Frame();
	// ����
	virtual HRESULT Render();
	// �޸� ����
	virtual HRESULT Release();

	// ���ҽ� ����, ����
	virtual HRESULT CreateResource();
	virtual HRESULT DeleteResource();

	// ǥ�� ����
	HRESULT SetSurface(IDXGISurface1* pDXGISurface1);
	// �ؽ�Ʈ ����
	void SetText(std::wstring text);

	// �׸���
	HRESULT Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f });
};


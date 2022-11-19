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
	// 싱글톤
	static Text* GetInstance()
	{
		static Text instance;
		return &instance;
	}

	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT Render();
	// 메모리 해제
	virtual HRESULT Release();

	// 리소스 생성, 삭제
	virtual HRESULT CreateResource();
	virtual HRESULT DeleteResource();

	// 표면 설정
	HRESULT SetSurface(IDXGISurface1* pDXGISurface1);
	// 텍스트 설정
	void SetText(std::wstring text);

	// 그리기
	HRESULT Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f });
};


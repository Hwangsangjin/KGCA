#pragma once

class Font
{
public:
	// 초기화
	virtual HRESULT Init();
	// 프레임 계산
	virtual HRESULT Frame();
	// 렌더
	virtual HRESULT Render();
	// 메모리 해제
	virtual HRESULT Release();

	// 리소스 생성, 삭제
	virtual HRESULT CreateDXResource();
	virtual HRESULT DeleteDXResource();

	// 설정
	HRESULT SetSurface(IDXGISurface1* pDXGISurface1);
	// 그리기
	HRESULT Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f });
	// 텍스트
	void SetText(std::wstring text);

private:
	ID2D1Factory* _pd2dFactory = nullptr;
	IDWriteFactory* _pWriteFactory = nullptr;
	ID2D1RenderTarget* _pd2dRenderTarget = nullptr;
	IDWriteTextFormat* _pTextFormat = nullptr;
	IDWriteTextLayout* _pTextLayout = nullptr;
	ID2D1SolidColorBrush* _pTextColor = nullptr;

	std::wstring _text = L"KGCA Game Academy";
};


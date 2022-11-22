#pragma once

class Text
{
	DECLARE_SINGLE(Text);

private:
	Microsoft::WRL::ComPtr<ID2D1Factory> d2d1_factory_;
	Microsoft::WRL::ComPtr<IDWriteFactory> dwrite_factory_;
	Microsoft::WRL::ComPtr<ID2D1RenderTarget> d2d1_render_target_;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> dwrite_text_format_;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> dwrite_text_layout_;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> text_color_;

	std::wstring text_ = L"KGCA Game Academy";
	POINT point_ = { 0, 0 };

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
	virtual HRESULT CreateResource();
	virtual HRESULT DeleteResource();

	// 표면 설정
	HRESULT SetSurface(Microsoft::WRL::ComPtr<IDXGISurface1> pDXGISurface1);
	// 텍스트 설정
	void SetText(std::wstring text);

	// 그리기
	HRESULT Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f });
};


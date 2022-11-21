#pragma once

class Text
{
	DECLARE_SINGLE(Text);

private:
	Microsoft::WRL::ComPtr<ID2D1Factory> d2d_factory_;
	Microsoft::WRL::ComPtr<IDWriteFactory> dwrite_factory_;
	Microsoft::WRL::ComPtr<ID2D1RenderTarget> d2d_render_target_;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> dwrite_text_format_;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> dwrite_text_layout_;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> text_color_;

	std::wstring text_ = L"KGCA Game Academy";
	POINT point_ = { 0, 0 };

public:
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
	HRESULT SetSurface(Microsoft::WRL::ComPtr<IDXGISurface1> pDXGISurface1);
	// �ؽ�Ʈ ����
	void SetText(std::wstring text);

	// �׸���
	HRESULT Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f });
};


#pragma once

class Text
{
private:
	Microsoft::WRL::ComPtr<ID2D1Factory> d2d1_factory_;
	Microsoft::WRL::ComPtr<IDWriteFactory> dwrite_factory_;
	Microsoft::WRL::ComPtr<ID2D1RenderTarget> d2d1_render_target_;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> dwrite_text_format_;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> dwrite_text_layout_;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> text_color_;

	std::wstring default_text_ = L"KGCA Game Academy";
	std::wstring fps_text_ = L"FPS: ";
	std::wstring time_text_ = L"TIME: ";

	POINT point_ = { 0, 0 };

	Text() = default;
	~Text() = default;

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
	HRESULT SetSurface(Microsoft::WRL::ComPtr<IDXGISurface1> pDXGISurface1);
	// �ؽ�Ʈ ����
	void SetText();

	// �׸���
	HRESULT Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f });
};


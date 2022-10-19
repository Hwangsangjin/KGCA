#pragma once

class Font
{
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
	virtual HRESULT CreateDXResource();
	virtual HRESULT DeleteDXResource();

	// ����
	HRESULT SetSurface(IDXGISurface1* pDXGISurface1);
	// �׸���
	HRESULT Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0.0f, 0.0f, 0.0f, 1.0f });
	// �ؽ�Ʈ
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


#pragma once

class Write
{
private:
	ID2D1Factory* _pd2dFactory = nullptr;
	IDWriteFactory* _pWriteFactory = nullptr;
	ID2D1RenderTarget* _pd2dRenderTarget = nullptr;
	IDWriteTextFormat* _pTextFormat = nullptr;
	IDWriteTextLayout* _pTextLayout = nullptr;
	ID2D1SolidColorBrush* _pTextColor = nullptr;
	std::wstring _defaultText = L"KGCA Game Academy";

	RECT _rtClient;

public:
	// �ʱ�ȭ
	HRESULT Init();
	// ������ ���
	HRESULT Frame();
	// ����
	HRESULT Render();
	// �޸� ����
	HRESULT Release();

	// ����
	HRESULT SetWrite(IDXGISurface1* pDXGISurface1);
	// �׸���
	HRESULT Draw(float x, float y, std::wstring text, RECT rect, D2D1_COLOR_F color = { 0, 0, 0, 1 });
};


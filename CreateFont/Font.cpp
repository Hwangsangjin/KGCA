#include "pch.h"
#include "Font.h"

HRESULT Font::Init()
{
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pd2dFactory))) return E_FAIL;
    if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&_pWriteFactory))) return E_FAIL;
    if (FAILED(_pWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"en-us", &_pTextFormat))) return E_FAIL;
    if (FAILED(_pWriteFactory->CreateTextLayout(_defaultText.c_str(), _defaultText.size(), _pTextFormat, rtClient.right, rtClient.bottom, &_pTextLayout))) return E_FAIL;

    return TRUE;
}

HRESULT Font::Frame()
{
    return TRUE;
}

HRESULT Font::Render()
{
    Draw(0, 0, _defaultText, { 1, 1, 1, 1 });

    return TRUE;
}

HRESULT Font::Release()
{
    if (_pTextLayout) _pTextLayout->Release();
    if (_pTextColor) _pTextColor->Release();
    if (_pWriteFactory) _pWriteFactory->Release();
    if (_pd2dRenderTarget) _pd2dRenderTarget->Release();
    if (_pd2dFactory) _pd2dFactory->Release();

    _pd2dFactory = nullptr;
    _pd2dRenderTarget = nullptr;
    _pWriteFactory = nullptr;
    _pTextColor = nullptr;
    _pTextLayout = nullptr;

    return TRUE;
}

HRESULT Font::SetSurface(IDXGISurface1* pDXGISurface1)
{
    D2D1_RENDER_TARGET_PROPERTIES props;
    ZeroMemory(&props, sizeof(props));
    props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
    props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
    props.dpiX = 96;
    props.dpiY = 96;
    props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
    props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

    if (FAILED(_pd2dFactory->CreateDxgiSurfaceRenderTarget(pDXGISurface1, &props, &_pd2dRenderTarget))) return E_FAIL;
    if (FAILED(_pd2dRenderTarget->CreateSolidColorBrush({ 0, 0, 0, 1 }, &_pTextColor))) return E_FAIL;

    return TRUE;
}

HRESULT Font::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
    D2D1_RECT_F rect = { x, y, rtClient.right, rtClient.bottom };

    _pd2dRenderTarget->BeginDraw();

    _pTextColor->SetColor(color);
    _pTextColor->SetOpacity(1.0f);

    _pd2dRenderTarget->DrawText(text.c_str(), text.size(), _pTextFormat, rect, _pTextColor);

    _pTextLayout->SetFontSize(50, { 0, (UINT)_defaultText.size() });
    _pTextLayout->SetFontStyle(DWRITE_FONT_STYLE_ITALIC, { 0, (UINT)_defaultText.size() });

    _pd2dRenderTarget->DrawTextLayout({ 200, 250 }, _pTextLayout, _pTextColor);

    _pd2dRenderTarget->EndDraw();

    return TRUE;
}

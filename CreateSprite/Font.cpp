#include "pch.h"
#include "Font.h"

HRESULT Font::Init()
{
    HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pd2dFactory));
    HR(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&_pWriteFactory));
    HR(_pWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"en-us", &_pTextFormat));
    HR(_pWriteFactory->CreateTextLayout(_text.c_str(), _text.size(), _pTextFormat, rtClient.right, rtClient.bottom, &_pTextLayout));

    return TRUE;
}

HRESULT Font::Frame()
{
    return TRUE;
}

HRESULT Font::Render()
{
    Draw(0, 0, _text, { 1, 1, 1, 1 });

    return TRUE;
}

HRESULT Font::Release()
{
    SAFE_RELEASE(_pTextColor);
    SAFE_RELEASE(_pTextLayout);
    SAFE_RELEASE(_pTextFormat);
    SAFE_RELEASE(_pd2dRenderTarget);
    SAFE_RELEASE(_pWriteFactory);
    SAFE_RELEASE(_pd2dFactory);

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

    HR(_pd2dFactory->CreateDxgiSurfaceRenderTarget(pDXGISurface1, &props, &_pd2dRenderTarget));
    HR(_pd2dRenderTarget->CreateSolidColorBrush({ 0, 0, 0, 1 }, &_pTextColor));

    return TRUE;
}

HRESULT Font::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
    D2D1_RECT_F rect = { x, y, rtClient.right, rtClient.bottom };

    _pd2dRenderTarget->BeginDraw();

    _pTextColor->SetColor(color);
    _pTextColor->SetOpacity(1.0f);

    _pd2dRenderTarget->DrawText(text.c_str(), text.size(), _pTextFormat, rect, _pTextColor);

    //_pTextLayout->SetFontSize(50, { 0, (UINT)_defaultText.size() });
    //_pTextLayout->SetFontStyle(DWRITE_FONT_STYLE_ITALIC, { 0, (UINT)_defaultText.size() });

   // _pd2dRenderTarget->DrawTextLayout({ 200, 250 }, _pTextLayout, _pTextColor);

    _pd2dRenderTarget->EndDraw();

    return TRUE;
}

void Font::SetText(std::wstring text)
{
    _text = text;
}

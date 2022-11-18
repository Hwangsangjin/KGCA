#include "Text.h"

extern RECT gClient;

HRESULT Text::Init()
{
    // Direct2D 객체 생성(ID2D1Factory)
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, _pd2dFactory.GetAddressOf())))
    {
        return E_FAIL;
    }

    // DirectWrite 객체 생성(DWriteFactory)
    if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)_pWriteFactory.GetAddressOf())))
    {
        return E_FAIL;
    }

    // 텍스트 포맷 객체 생성(IDWriteTextFormat)
    if (FAILED(_pWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"en-us", _pTextFormat.GetAddressOf())))
    {
        return E_FAIL;
    }

    // 텍스트 레이아웃 지정(IDWriteTextLayout)
    if (FAILED(_pWriteFactory->CreateTextLayout(_text.c_str(), _text.size(), _pTextFormat.Get(), gClient.right, gClient.bottom, _pTextLayout.GetAddressOf())))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Text::Frame()
{
    return TRUE;
}

HRESULT Text::Render()
{
    Draw(0, 0, _text, { 1.0f, 1.0f, 1.0f, 1.0f });

    return TRUE;
}

HRESULT Text::Release()
{
    return TRUE;
}

HRESULT Text::CreateDXResource()
{
    if (FAILED(_pd2dRenderTarget->CreateSolidColorBrush({ 0, 0, 0, 1 }, &_pTextColor)))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Text::DeleteDXResource()
{
    return TRUE;
}

HRESULT Text::SetSurface(IDXGISurface1* pDXGISurface1)
{
    D2D1_RENDER_TARGET_PROPERTIES props;
    ZeroMemory(&props, sizeof(props));
    props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
    props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
    props.dpiX = 96;
    props.dpiY = 96;
    props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
    props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

    if (FAILED(_pd2dFactory->CreateDxgiSurfaceRenderTarget(pDXGISurface1, &props, _pd2dRenderTarget.GetAddressOf())))
    {
        return E_FAIL;
    }
    
    return TRUE;
}

HRESULT Text::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
    D2D1_RECT_F rect = { x, y, gClient.right, gClient.bottom };

    _pd2dRenderTarget->BeginDraw();

    _pTextColor->SetColor(color);
    _pTextColor->SetOpacity(1.0f);

    _pd2dRenderTarget->DrawText(text.c_str(), text.size(), _pTextFormat.Get(), rect, _pTextColor.Get());

    //_pTextLayout->SetFontSize(50, { 0, (UINT)_defaultText.size() });
    //_pTextLayout->SetFontStyle(DWRITE_FONT_STYLE_ITALIC, { 0, (UINT)_defaultText.size() });

   // _pd2dRenderTarget->DrawTextLayout({ 200, 250 }, _pTextLayout, _pTextColor);

    _pd2dRenderTarget->EndDraw();

    return TRUE;
}

void Text::SetText(std::wstring text)
{
    _text = text;
}

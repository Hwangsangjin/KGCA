#include "pch.h"
#include "Writer.h"
#include "Input.h"

HRESULT Writer::Init()
{
    HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pd2dFactory));
    HR(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&_pWriteFactory));
    HR(_pWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"en-us", &_pTextFormat));
    HR(_pWriteFactory->CreateTextLayout(_text.c_str(), _text.size(), _pTextFormat, gClient.right, gClient.bottom, &_pTextLayout));

    return TRUE;
}

HRESULT Writer::Frame()
{
    _point = INPUT->GetPosition();

    return TRUE;
}

HRESULT Writer::Render()
{
    Draw(0, 0, _text, { 1.0f, 1.0f, 1.0f, 1.0f });

    std::wstring point = L"(" + std::to_wstring(_point.x) + L", " + std::to_wstring(_point.y) + L")";

    if (INPUT->GetKey(VK_LBUTTON) == KEY_STATE::NONE)
    {
        Draw(_point.x, _point.y - 20, L"MOUSE" + point, { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
    {
        Draw(30, 140, L"Q", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('W') == KEY_STATE::HOLD)
    {
        Draw(50, 140, L"W", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('E') == KEY_STATE::HOLD)
    {
        Draw(70, 140, L"E", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('A') == KEY_STATE::HOLD)
    {
        Draw(30, 160, L"A", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('S') == KEY_STATE::HOLD)
    {
        Draw(50, 160, L"S", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('D') == KEY_STATE::HOLD)
    {
        Draw(70, 160, L"D", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey(VK_SHIFT) == KEY_STATE::HOLD)
    {
        Draw(30, 220, L"SHIFT", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
    {
        Draw(30, 280, L"SPACE", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    Draw(gClient.right - 120.0f, gClient.top + 0.0f, L"Top View", { 1.0f, 1.0f, 1.0f, 1.0f });
    Draw(gClient.right - 120.0f, gClient.top + 150.0f, L"Front View", { 1.0f, 1.0f, 1.0f, 1.0f });
    Draw(gClient.right - 120.0f, gClient.top + 300.0f, L"Side View", { 1.0f, 1.0f, 1.0f, 1.0f });
    Draw(gClient.right - 120.0f, gClient.top + 450.0f, L"User View", { 1.0f, 1.0f, 1.0f, 1.0f });

    return TRUE;
}

HRESULT Writer::Release()
{
    SAFE_RELEASE(_pTextColor);
    SAFE_RELEASE(_pTextLayout);
    SAFE_RELEASE(_pTextFormat);
    SAFE_RELEASE(_pd2dRenderTarget);
    SAFE_RELEASE(_pWriteFactory);
    SAFE_RELEASE(_pd2dFactory);

    return TRUE;
}

HRESULT Writer::CreateDXResource()
{
    HR(_pd2dRenderTarget->CreateSolidColorBrush({ 0, 0, 0, 1 }, &_pTextColor));

    return TRUE;
}

HRESULT Writer::DeleteDXResource()
{
    SAFE_RELEASE(_pTextColor);
    SAFE_RELEASE(_pd2dRenderTarget);

    return TRUE;
}

HRESULT Writer::SetSurface(IDXGISurface1* pDXGISurface1)
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
    
    CreateDXResource();

    return TRUE;
}

HRESULT Writer::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
    D2D1_RECT_F rect = { x, y, gClient.right, gClient.bottom };

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

void Writer::SetText(std::wstring text)
{
    _text = text;
}

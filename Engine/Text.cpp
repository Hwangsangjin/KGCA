#include "pch.h"
#include "Text.h"
#include "Input.h"

HRESULT Text::Init()
{
    // Direct2D 객체 생성
    assert(SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, d2d1_factory_.GetAddressOf())));

    // DirectWrite 객체 생성
    assert(SUCCEEDED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)dwrite_factory_.GetAddressOf())));

    // 텍스트 포맷 객체 생성
    assert(SUCCEEDED(dwrite_factory_->CreateTextFormat(L"Consolas", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"en-us", dwrite_text_format_.GetAddressOf())));

    // 텍스트 레이아웃 지정
    assert(SUCCEEDED(dwrite_factory_->CreateTextLayout(text_.c_str(), text_.size(), dwrite_text_format_.Get(), g_client_rect.right, g_client_rect.bottom, dwrite_text_layout_.GetAddressOf())));

    return TRUE;
}

HRESULT Text::Frame()
{
    return TRUE;
}

HRESULT Text::Render()
{
    Draw(0, 0, text_, { 1.0f, 1.0f, 1.0f, 1.0f });

    std::wstring point = L"(" + std::to_wstring(INPUT->GetPosition().x) + L", " + std::to_wstring(INPUT->GetPosition().y) + L")";

    if (INPUT->GetKey(VK_LBUTTON) == KEY_STATE::NONE)
    {
        TEXT->Draw(INPUT->GetPosition().x, INPUT->GetPosition().y - 20, L"MOUSE" + point, { 1, 1, 1, 1 });
    }

    if (INPUT->GetKey('Q') == KEY_STATE::HOLD)
    {
        TEXT->Draw(30.0f, 140.0f, L"Q", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('W') == KEY_STATE::HOLD)
    {
        TEXT->Draw(50.0f, 140.0f, L"W", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('E') == KEY_STATE::HOLD)
    {
        TEXT->Draw(70.0f, 140.0f, L"E", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('A') == KEY_STATE::HOLD)
    {
        TEXT->Draw(30.0f, 160.0f, L"A", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('S') == KEY_STATE::HOLD)
    {
        TEXT->Draw(50.0f, 160.0f, L"S", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey('D') == KEY_STATE::HOLD)
    {
        TEXT->Draw(70.0f, 160.0f, L"D", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey(VK_SHIFT) == KEY_STATE::HOLD)
    {
        TEXT->Draw(30.0f, 220.0f, L"SHIFT", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (INPUT->GetKey(VK_SPACE) == KEY_STATE::HOLD)
    {
        TEXT->Draw(30.0f, 280.0f, L"SPACE", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    return TRUE;
}

HRESULT Text::Release()
{
    return TRUE;
}

HRESULT Text::CreateResource()
{
    assert(SUCCEEDED(d2d1_render_target_->CreateSolidColorBrush({ 0, 0, 0, 1 }, text_color_.GetAddressOf())));

    return TRUE;
}

HRESULT Text::DeleteResource()
{
    if (text_color_)
    {
        text_color_->Release();
    }

    if (d2d1_render_target_)
    {
        d2d1_render_target_->Release();
    }

    return TRUE;
}

HRESULT Text::SetSurface(Microsoft::WRL::ComPtr<IDXGISurface1> DXGISurface1)
{
    D2D1_RENDER_TARGET_PROPERTIES props;
    ZeroMemory(&props, sizeof(props));
    props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
    props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
    props.dpiX = 96;
    props.dpiY = 96;
    props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
    props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

    assert(SUCCEEDED(d2d1_factory_->CreateDxgiSurfaceRenderTarget(DXGISurface1.Get(), &props, d2d1_render_target_.GetAddressOf())));

    CreateResource();

    return TRUE;
}

HRESULT Text::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
    D2D1_RECT_F rect = { x, y, g_client_rect.right, g_client_rect.bottom };

    d2d1_render_target_->BeginDraw();

    text_color_->SetColor(color);
    text_color_->SetOpacity(1.0f);

    d2d1_render_target_->DrawText(text.c_str(), text.size(), dwrite_text_format_.Get(), rect, text_color_.Get());

    assert(SUCCEEDED(d2d1_render_target_->EndDraw()));

    return TRUE;
}

void Text::SetText(std::wstring text)
{
    text_ = text;
}

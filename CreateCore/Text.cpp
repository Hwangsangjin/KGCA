#include "Text.h"
#include "Input.h"

extern RECT gClient;

HRESULT Text::Init()
{
    // Direct2D 객체 생성
    if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, _pd2dFactory.GetAddressOf())))
    {
        return E_FAIL;
    }

    // DirectWrite 객체 생성
    if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)_pWriteFactory.GetAddressOf())))
    {
        return E_FAIL;
    }

    // 텍스트 포맷 객체 생성
    if (FAILED(_pWriteFactory->CreateTextFormat(L"Consolas", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20, L"en-us", _pTextFormat.GetAddressOf())))
    {
        return E_FAIL;
    }

    // 텍스트 레이아웃 지정
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

    std::wstring point = L"(" + std::to_wstring(Input::GetInstance()->GetPosition().x) + L", " + std::to_wstring(Input::GetInstance()->GetPosition().y) + L")";

    if (Input::GetInstance()->GetKey(VK_LBUTTON) == KEY_STATE::NONE)
    {
        Text::GetInstance()->Draw(Input::GetInstance()->GetPosition().x, Input::GetInstance()->GetPosition().y - 20, L"MOUSE" + point, { 1, 1, 1, 1 });
    }

    if (Input::GetInstance()->GetKey('Q') == KEY_STATE::HOLD)
    {
        Text::GetInstance()->Draw(30.0f, 140.0f, L"Q", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (Input::GetInstance()->GetKey('W') == KEY_STATE::HOLD)
    {
        Text::GetInstance()->Draw(50.0f, 140.0f, L"W", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (Input::GetInstance()->GetKey('E') == KEY_STATE::HOLD)
    {
        Text::GetInstance()->Draw(70.0f, 140.0f, L"E", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (Input::GetInstance()->GetKey('A') == KEY_STATE::HOLD)
    {
        Text::GetInstance()->Draw(30.0f, 160.0f, L"A", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (Input::GetInstance()->GetKey('S') == KEY_STATE::HOLD)
    {
        Text::GetInstance()->Draw(50.0f, 160.0f, L"S", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (Input::GetInstance()->GetKey('D') == KEY_STATE::HOLD)
    {
        Text::GetInstance()->Draw(70.0f, 160.0f, L"D", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (Input::GetInstance()->GetKey(VK_SHIFT) == KEY_STATE::HOLD)
    {
        Text::GetInstance()->Draw(30.0f, 220.0f, L"SHIFT", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    if (Input::GetInstance()->GetKey(VK_SPACE) == KEY_STATE::HOLD)
    {
        Text::GetInstance()->Draw(30.0f, 280.0f, L"SPACE", { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    return TRUE;
}

HRESULT Text::Release()
{
    return TRUE;
}

HRESULT Text::CreateResource()
{
    if (FAILED(_pd2dRenderTarget->CreateSolidColorBrush({ 0, 0, 0, 1 }, _pTextColor.GetAddressOf())))
    {
        return E_FAIL;
    }

    return TRUE;
}

HRESULT Text::DeleteResource()
{
    if (_pTextColor)
    {
        _pTextColor->Release();
    }

    if (_pd2dRenderTarget)
    {
        _pd2dRenderTarget->Release();
    }

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

    CreateResource();
    
    return TRUE;
}

HRESULT Text::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
    D2D1_RECT_F rect = { x, y, gClient.right, gClient.bottom };

    _pd2dRenderTarget->BeginDraw();

    _pTextColor->SetColor(color);
    _pTextColor->SetOpacity(1.0f);

    _pd2dRenderTarget->DrawText(text.c_str(), text.size(), _pTextFormat.Get(), rect, _pTextColor.Get());

    _pd2dRenderTarget->EndDraw();

    return TRUE;
}

void Text::SetText(std::wstring text)
{
    _text = text;
}

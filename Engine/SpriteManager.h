#pragma once

class SpriteManager
{
	DECLARE_SINGLE(SpriteManager);

public:
    Microsoft::WRL::ComPtr<ID3D11Device> device_;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context_;
    std::vector<W_STR> sprite_files_;
    std::vector<UINT> sprite_types_;
    std::vector<W_STR> rect_names;
    std::vector<W_STR> texture_names_;
    std::vector<W_STR> mask_texture_names_;
    std::vector<W_STR> shader_names_;
    std::vector<std::vector<RECT>> sprite_rects_;
    std::vector<TCHAR_STRING_VECTOR> sprite_strings_;
    std::map<std::wstring, class Sprite*> sprites_;

    // �ʱ�ȭ
    HRESULT Init();
    // ������ ���
    HRESULT Frame();
    // ����
    HRESULT Render();
    // �޸� ����
    HRESULT Release();

    // ����̽� ����
    HRESULT SetDevice(ID3D11Device* device, ID3D11DeviceContext* device_context);

    HRESULT GameDataLoad(const TCHAR* sprite_file);
    HRESULT Load(std::wstring sprite_file);
    Sprite* Find(std::wstring sprite_file);

    Sprite& Get(W_STR str);
    Sprite* GetPtr(W_STR str);
};


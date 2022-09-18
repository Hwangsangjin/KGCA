#include "pch.h"
#include "Title.h"

HRESULT Title::Init()
{
	// 사운드
	SOUND->Init();
	SOUND->LoadAll(L"../../Resource/Pikachu/Sound/");
	_pBGM = SOUND->GetPtr(L"BGM.wav");
	_pBGM->PlayBGM(true);

	// 텍스처
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Title.png");

	// 배경
	for (size_t y = 0; y < 5; y++)
	{
		for (size_t x = 0; x < 5; x++)
		{
			_pBackground = new Background;
			_pBackground->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Title.png");
			_pBackground->SetRect({ 0, 0, 104, 104 });
			_pBackground->SetPosition({ x * 208.0f, y * 208.0f });
			_pBackground->SetScale(4.0f, 4.0f);
			_pBackground->SetSpeed(100.0f);
			_pBackground->SetUV();
			_pBackground->SetNormalize();
			_pBackground->SetVertexBuffer();
			AddObject(_pBackground);
		}
	}

    return TRUE;
}

HRESULT Title::Frame()
{
	for (auto& pObject : _pObjects)
	{
		pObject->Frame();
	}

	SOUND->Frame();

    return TRUE;
}

HRESULT Title::Render()
{
	for (auto& pObject : _pObjects)
	{
		pObject->Render();
	}

    return TRUE;
}

HRESULT Title::Release()
{
	for (auto& pObject : _pObjects)
	{
		SAFE_RELEASE(pObject);
	}

	SAFE_DELETE(_pMap);

    return TRUE;
}

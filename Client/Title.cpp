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

	// 맵
	_pMap = new Map;
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Title.png");
	_pMap->SetRect({ 0, 0, 800, 600 });
	_pMap->SetScale(2.0f, 2.0f);
	_pMap->SetPosition({ rtClient.right / 2.0f, rtClient.bottom / 2.0f });
	AddObject(_pMap);

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

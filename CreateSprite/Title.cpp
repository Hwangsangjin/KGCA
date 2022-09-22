#include "pch.h"
#include "Title.h"

HRESULT Title::Init()
{
	// 카메라
	_camera = { 0.0f, 0.0f };

	// 사운드
	SOUND->Init();
	SOUND->LoadAll(L"../../Resource/Pikachu/Sound/");
	_pBGM = SOUND->GetPtr(L"BGM.wav");
	_pBGM->PlayBGM(true);

	// 텍스처
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Sprite.png");
	Texture* pMaskTexture = TEXTURE->Load(L"../../Resource/Pikachu/Image/Mask.png");

	// 배경
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			_pBackground = new Background;
			_pBackground->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
			_pBackground->SetRect({ 280, 611, 104, 104 });
			_pBackground->SetSpeed(120.0f);
			_pBackground->SetScale(2.0f, 2.0f);
			_pBackground->SetCameraPosition(_camera);
			_pBackground->SetCameraViewSize({ 800.0f, 600.0f });
			_pBackground->SetPosition({ -400 + x * 208.0f, -300 + y * 208.0f });
			_pBackground->init = _pBackground->_position;
			AddObject(_pBackground);
		}
	}

	// 텍스트
	_pBattleText = new BattleText;
	_pBattleText->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pBattleText->SetMask(pMaskTexture);
	_pBattleText->SetRect({ 255, 725, 155, 155 });
	_pBattleText->SetSpeed(5.0f);
	_pBattleText->SetCameraPosition(_camera);
	_pBattleText->SetCameraViewSize({ 800.0f, 600.0f });
	_pBattleText->SetPosition({ -200.0f, -150.0f });
	AddObject(_pBattleText);

    return TRUE;
}

HRESULT Title::Frame()
{	
	for (auto& pObject : _pObjects)
	{
		_pImmediateContext->PSSetShaderResources(1, 1, &_pBattleText->_pMaskTexture->_pShaderResourceView);

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

	SAFE_DELETE(_pBackground);
	SAFE_DELETE(_pBattleText);

    return TRUE;
}

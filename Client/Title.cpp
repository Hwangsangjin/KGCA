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
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Sprite.png");
	Texture* pMaskTexture = TEXTURE->Load(L"../../Resource/Pikachu/Image/Mask.png");

	// 배경
	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			_pBackground = new Background;
			_pBackground->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
			_pBackground->SetMask(pMaskTexture);
			_pBackground->SetUV({ 280, 611, 104, 104 });
			_pBackground->SetRect({ 280, 611, 104, 104 });
			_pBackground->SetPosition({ x * 200.0f, y * 200.0f });
			_pBackground->SetScale(4.0f, 4.0f);
			_pBackground->SetSpeed(140.0f);
			_pBackground->SetNormalize();
			_pBackground->SetVertexBuffer();
			AddObject(_pBackground);
		}
	}

	// 텍스트
	_pBattleText = new BattleText;
	_pBattleText->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pBattleText->SetMask(pMaskTexture);
	_pBattleText->SetUV({ 255, 725, 155, 155 });
	_pBattleText->SetRect({ 255, 725, 155, 155 });
	_pBattleText->SetPosition({ 100.0f, 100.0f });
	_pBattleText->SetScale(2.0f, 2.0f);
	_pBattleText->SetSpeed(5.0f);
	_pBattleText->SetNormalize();
	_pBattleText->SetVertexBuffer();
	AddObject(_pBattleText);

    return TRUE;
}

HRESULT Title::Frame()
{
	for (auto& pObject : _pObjects)
	{
		_pImmediateContext->PSSetShaderResources(1, 1, &_pBackground->_pMaskTexture->_pShaderResourceView);
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

	SAFE_DELETE(_pMap);

    return TRUE;
}

#include "pch.h"
#include "Title.h"

HRESULT Title::Init()
{
	// 사운드
	SOUND->Init();
	SOUND->LoadAll(L"../../../Resource/Pikachu/Sound/");
	_pBGM = SOUND->GetPtr(L"BGM.wav");
	_pBGM->SetLoop(true);
	_pBGM->PlayBGM(true);
	_pEffect1 = SOUND->GetPtr(L"Effect1.wav");
	_pEffect2 = SOUND->GetPtr(L"Effect2.wav");

	// 텍스처
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Sprite1.png");
	Texture* pMaskTexture = TEXTURE->Load(L"../../../Resource/Pikachu/Image/Mask.png");

	// 배경
	for (size_t y = 0; y < 5; y++)
	{
		for (size_t x = 0; x < 6; x++)
		{
			_pBackground = new Background;
			_pBackground->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
			_pBackground->SetRect({ 280.0f, 611.0f, 104.0f, 104.0f });			
			_pBackground->SetSpeed(100.0f);
			_pBackground->SetScale(2.0f, 2.0f);
			_pBackground->SetDirection({ -1.0f, -1.0f });
			_pBackground->SetPosition({ x * 208.0f, y * 208.0f });
			_pBackground->init = _pBackground->_position;
			AddObject(_pBackground);
		}
	}

	// 대결 텍스트
	_pBattleText = new BattleText;
	_pBattleText->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pBattleText->SetMask(pMaskTexture);
	_pBattleText->SetRect({ 255.0f, 725.0f, 155.0f, 155.0f });
	_pBattleText->SetSpeed(5.0f);
	_pBattleText->SetPosition({ 200.0f, 150.0f });
	AddObject(_pBattleText);

	// 피카츄 배구 텍스트
	_pVolleyballText = new DynamicText;
	_pVolleyballText->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pVolleyballText->SetMask(pMaskTexture);
	_pVolleyballText->SetRect({ 53.0f, 628.0f, 162.0f, 34.0f });
	_pVolleyballText->SetScale(2.0f, 2.0f);
	_pVolleyballText->SetSpeed(300.0f);
	_pVolleyballText->SetDirection({ -1.0f, 0.0f });
	_pVolleyballText->SetPosition({ 962.0f, 240.0f });
	AddObject(_pVolleyballText);

	// 포켓몬스터 텍스트
	_pPokeMonText = new StaticText;
	_pPokeMonText->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPokeMonText->SetMask(pMaskTexture);
	_pPokeMonText->SetRect({ 60.0f, 131.0f, 77.0f, 22.0f });
	_pPokeMonText->SetScale(2.0f, 2.0f);
	_pPokeMonText->SetPosition({ 520.0f, 130.0f });
	AddObject(_pPokeMonText);

	// 회사 정보 텍스트
	_pCompanyText = new StaticText;
	_pCompanyText->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pCompanyText->SetMask(pMaskTexture);
	_pCompanyText->SetRect({ 2.0f, 22.0f, 362.0f, 20.0f });
	_pCompanyText->SetScale(1.8f, 1.8f);
	_pCompanyText->SetPosition({ 400.0f, 550.0f });
	AddObject(_pCompanyText);

	// 싱글 플레이 텍스트
	_pSinglePlayText = new SelectText;
	_pSinglePlayText->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pSinglePlayText->SetMask(pMaskTexture);
	_pSinglePlayText->SetRect({ 258.0f, 49.0f, 76.0f, 13.0f });
	_pSinglePlayText->SetScale(3.0f, 3.0f);
	_pSinglePlayText->SetPosition({ 400.0f, 380.0f });
	AddObject(_pSinglePlayText);

	// 멀티 플레이 텍스트
	_pMultiPlayText = new SelectText;
	_pMultiPlayText->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pMultiPlayText->SetMask(pMaskTexture);
	_pMultiPlayText->SetRect({ 14.0f, 68.0f, 61.0f, 12.0f });
	_pMultiPlayText->SetScale(2.0f, 2.0f);
	_pMultiPlayText->SetPosition({ 400.0f, 430.0f });
	AddObject(_pMultiPlayText);

    return TRUE;
}

HRESULT Title::Frame()
{	
	SOUND->Frame();

	for (auto& pObject : _pObjects)
	{
		_pImmediateContext->PSSetShaderResources(1, 1, &_pBattleText->_pMaskTexture->_pShaderResourceView);

		if (INPUT->GetKey('W') == KEY_STATE::DOWN || INPUT->GetKey(VK_UP) == KEY_STATE::DOWN)
		{
			_pEffect2->PlayEffect();
			_pSinglePlayText->SetScale(3.0f, 3.0f);
			_pMultiPlayText->SetScale(2.0f, 2.0f);
			_isSinglePlay = true;
			_isMultiPlay = false;

		}
		else if (INPUT->GetKey('S') == KEY_STATE::DOWN || INPUT->GetKey(VK_DOWN) == KEY_STATE::DOWN)
		{
			_pEffect2->PlayEffect();
			_pSinglePlayText->SetScale(2.0f, 2.0f);
			_pMultiPlayText->SetScale(3.0f, 3.0f);
			_isSinglePlay = false;
			_isMultiPlay = true;
		}
		else if (INPUT->GetKey(VK_RETURN) == KEY_STATE::DOWN)
		{
			_pEffect1->PlayEffect();
			_isInGame = true;
		}

		pObject->Frame();
	}

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
	SAFE_DELETE(_pVolleyballText);
	SAFE_DELETE(_pPokeMonText);
	SAFE_DELETE(_pCompanyText);
	SAFE_DELETE(_pSinglePlayText);
	SAFE_DELETE(_pMultiPlayText);

    return TRUE;
}

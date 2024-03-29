#include "pch.h"
#include "InGame.h"

HRESULT InGame::Init()
{
	// 사운드
	SOUND->Init();
	SOUND->LoadAll(L"../../Resource/Pikachu/Sound/");
	_pBGM = SOUND->GetPtr(L"BGM.wav");
	_pBGM->PlayBGM(true);

	// 스프라이트
	SPRITE->Load(L"../../Resource/Pikachu/Image/Sprite.txt");

	// 텍스처
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Map.png");
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Sprite.png");
	Texture* pMaskTexture = TEXTURE->Load(L"../../Resource/Pikachu/Image/Mask.png");

	// 맵
	_pMap = new Map;
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Map.png");
	_pMap->SetRect({ 0, 0, 800, 600 });
	_pMap->SetScale(1.0f, 1.0f);
	_pMap->SetPosition({ 400.0f, 300.0f });
	AddObject(_pMap);

	// 구름
	for (size_t i = 0; i < 10; i++)
	{
		_pCloud = new Cloud;
		_pCloud->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
		_pCloud->SetMask(pMaskTexture);
		_pCloud->SetRect({ 101, 90, 45, 20 });
		_pCloud->SetScale(RAND(1.5f, 2.0f), RAND(1.5f, 2.0f));
		_pCloud->SetPosition({ RAND(0, 800), RAND(0, 300) });
		AddObject(_pCloud);
	}

	// 파도
	for (size_t x = 0; x < 28; x++)
	{
		_pWave = new Wave;
		_pWave->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
		_pWave->SetMask(pMaskTexture);
		_pWave->SetRect({ 70, 160, 16, 30 });
		_pWave->SetScale(2.0f, 2.0f);
		_pWave->SetPosition({ x * 30.0f, 580.0f });
		AddObject(_pWave);
	}

	// 플레이어
	_pPlayer = new Player;
	_pPlayer->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pPlayer->SetMask(pMaskTexture);
	_pPlayer->SetRect({ 2, 265, 65, 65 });
	_pPlayer->SetSpeed(300.0f);
	_pPlayer->SetScale(2.0f , 2.0f);
	_pPlayer->SetPosition({ 65.0f, 480.0f });
	AddObject(_pPlayer);

	// 적
	_pEnemy = new Enemy;
	_pEnemy->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pEnemy->SetMask(pMaskTexture);
	_pEnemy->SetRect({ 2, 265, 65, 65 });
	_pEnemy->SetSpeed(300.0f);
	_pEnemy->SetScale(2.0f, 2.0f);
	_pEnemy->SetPosition({ 735.0f, 480.0f });
	AddObject(_pEnemy);

	// 공
	_pBall = new Ball;
	_pBall->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pBall->SetMask(pMaskTexture);
	_pBall->SetRect({ 88, 158, 40, 40 });
	_pBall->SetSpeed(200.0f);
	_pBall->SetScale(2.0f, 2.0f);
	_pBall->SetPosition({ 400.0f, 200.0f });
	AddObject(_pBall);

	return TRUE;
}

HRESULT InGame::Frame()
{
	for (auto& pObject : _pObjects)
	{
		pObject->Frame();
	}

	SOUND->Frame();

	return TRUE;
}

HRESULT InGame::Render()
{
	for (auto& pObject : _pObjects)
	{
		_pImmediateContext->PSSetShaderResources(1, 1, &_pCloud->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pPlayer->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pEnemy->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pBall->_pMaskTexture->_pShaderResourceView);

		pObject->Render();
	}

	return TRUE;
}

HRESULT InGame::Release()
{
	for (auto& pObject : _pObjects)
	{
		SAFE_RELEASE(pObject);
	}

	SAFE_DELETE(_pMap);
	SAFE_DELETE(_pSky);
	SAFE_DELETE(_pMountain);
	SAFE_DELETE(_pGround);
	SAFE_DELETE(_pNet);
	SAFE_DELETE(_pCloud);
	SAFE_DELETE(_pWave);
	SAFE_DELETE(_pPlayer);
	SAFE_DELETE(_pEnemy);
	SAFE_DELETE(_pBall);

	return TRUE;
}

#include "pch.h"
#include "InGame.h"

HRESULT InGame::Init()
{
	// 사운드
	SOUND->Init();
	SOUND->LoadAll(L"../../Resource/Pikachu/Sound/");
	_pBGM = SOUND->GetPtr(L"BGM.wav");
	_pBGM->PlayBGM(true);

	// 텍스처
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Map.png");
	TEXTURE->Load(L"../../Resource/Pikachu/Image/Sprite.png");
	Texture* pMaskTexture = TEXTURE->Load(L"../../Resource/Pikachu/Image/Mask.png");

	// 맵
	_pMap = new Map;
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Map.png");
	_pMap->SetUV({ 0, 0, 800, 600 });
	_pMap->SetRect({ 0, 0, 800, 600 });
	_pMap->SetPosition({ 0.0f, 0.0f });
	_pMap->SetScale(2.0f, 2.0f);
	_pMap->SetNormalize();
	_pMap->SetVertexBuffer();
	AddObject(_pMap);

	// 구름
	for (size_t i = 0; i < 10; i++)
	{
		_pCloud = new Cloud;
		_pCloud->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
		_pCloud->SetMask(pMaskTexture);
		_pCloud->SetUV({ 101, 90, 45, 20 });
		_pCloud->SetRect({ 101, 90, 45, 20 });
		_pCloud->SetPosition({ RAND(0, 800), RAND(0, 300) });
		_pCloud->SetScale(RAND(3.0f, 5.0f), RAND(3.0f, 5.0f));
		_pCloud->SetNormalize();
		_pCloud->SetVertexBuffer();
		AddObject(_pCloud);
	}

	// 파도
	for (size_t x = 0; x < 27; x++)
	{
		_pWave = new Wave;
		_pWave->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
		_pWave->SetMask(pMaskTexture);
		_pWave->SetUV({ 70, 160, 16, 30 });
		_pWave->SetRect({ 70, 160, 16, 30 });
		_pWave->SetPosition({ x * 30.0f, 560.0f });
		_pWave->SetScale(4.0f, 4.0f);
		_pWave->SetNormalize();
		_pWave->SetVertexBuffer();
		AddObject(_pWave);
	}

	// 플레이어
	_pPlayer = new Player;
	_pPlayer->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pPlayer->SetMask(pMaskTexture);
	_pPlayer->SetUV({ 2, 265, 65, 65 });
	_pPlayer->SetRect({ 2, 265, 65, 65 });
	_pPlayer->SetPosition({ 0.0f, 430.0f });
	_pPlayer->SetScale(3.5f, 3.5f);
	_pPlayer->SetSpeed(300.0f);
	_pPlayer->SetNormalize();
	_pPlayer->SetVertexBuffer();
	AddObject(_pPlayer);

	// 적
	_pEnemy = new Enemy;
	_pEnemy->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pEnemy->SetMask(pMaskTexture);
	_pEnemy->SetUV({ 67, 265, -65, 65 });
	_pEnemy->SetRect({ 2, 265, 65, 65 });
	_pEnemy->SetPosition({ 670.0f, 430.0f });
	_pEnemy->SetScale(3.5f, 3.5f);
	_pEnemy->SetSpeed(300.0f);
	_pEnemy->SetNormalize();
	_pEnemy->SetVertexBuffer();
	AddObject(_pEnemy);

	// 공
	_pBall = new Ball;
	_pBall->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pBall->SetMask(pMaskTexture);
	_pBall->SetUV({ 88, 158, 40, 40 });
	_pBall->SetRect({ 88, 158, 40, 40 });
	_pBall->SetPosition({ 370.0f, 200.0f });
	_pBall->SetScale(3.5f, 3.5f);
	_pBall->SetSpeed(200.0f);
	_pBall->SetNormalize();
	_pBall->SetVertexBuffer();
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

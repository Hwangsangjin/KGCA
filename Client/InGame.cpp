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
	_pMap->SetRect({ 0, 0, 800, 600 });
	_pMap->SetScale(2.0f, 2.0f);
	_pMap->SetPosition({ rtClient.left + 0.0f, rtClient.top + 0.0f });
	AddObject(_pMap);

	// 구름
	for (size_t i = 0; i < 10; i++)
	{
		_pCloud = new Cloud;
		_pCloud->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
		_pCloud->SetMask(pMaskTexture);
		_pCloud->SetRect({ 101, 90, 45, 20 });
		_pCloud->SetScale(RAND(3.0f, 5.0f), RAND(3.0f, 5.0f));
		_pCloud->SetPosition({ rtClient.left + RAND(0, 800), rtClient.top + RAND(0, 300) });
		AddObject(_pCloud);
	}

	//// 하늘
	//for (size_t y = 0; y < 12; y++)
	//{
	//	for (size_t x = 0; x < 25; x++)
	//	{
	//		_pSky = new Tile;
	//		_pSky->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	//		_pSky->SetUV({ 156, 2, 16, 16 });
	//		_pSky->SetScale(4.0f, 4.0f);
	//		_pSky->SetPosition({ rtClient.left - 0.0f + x * 32, rtClient.bottom - 600.0f + y * 32 });
	//		AddObject(_pSky);
	//	}
	//}

	//// 산
	//_pMountain = new Tile;
	//_pMountain->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	//_pMountain->SetUV({ 2, 200, 432, 64 });
	//_pMountain->SetScale(3.7f, 3.5f);
	//_pMountain->SetPosition({ rtClient.left - 0.0f, rtClient.bottom - 220.0f });
	//AddObject(_pMountain);

	//// 그라운드
	//for (size_t x = 0; x < 25; x++)
	//{
	//	_pGround = new Tile;
	//	_pGround->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	//	_pGround->SetUV({ 120, 2, 16, 16 });
	//	_pGround->SetScale(4.0f, 4.0f);
	//	_pGround->SetPosition({ rtClient.left - 0.0f + x * 32, rtClient.bottom - 110.0f });
	//	AddObject(_pGround);
	//}

	//for (size_t x = 0; x < 25; x++)
	//{
	//	_pGround = new Tile;
	//	_pGround->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");

	//	if (x == 0)
	//	{
	//		_pGround->SetUV({ 84, 2, 16, 16 });
	//		_pGround->SetScale(4.0f, 4.0f);
	//		_pGround->SetPosition({ rtClient.left - 0.0f, rtClient.bottom - 80.0f });
	//		AddObject(_pGround);
	//	}
	//	else if (x < 24)
	//	{
	//		_pGround->SetUV({ 66, 2, 16, 16 });
	//		_pGround->SetScale(4.0f, 4.0f);
	//		_pGround->SetPosition({ rtClient.left - 0.0f + x * 32, rtClient.bottom - 80.0f });
	//		AddObject(_pGround);
	//	}
	//	else
	//	{
	//		_pGround->SetUV({ 102, 2, 16, 16 });
	//		_pGround->SetScale(4.0f, 4.0f);
	//		_pGround->SetPosition({ rtClient.left - 0.0f + x * 32, rtClient.bottom - 80.0f });
	//		AddObject(_pGround);
	//	}
	//}

	//for (size_t y = 0; y < 15; y++)
	//{
	//	for (size_t x = 0; x < 27; x++)
	//	{
	//		_pGround = new Tile;
	//		_pGround->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	//		_pGround->SetUV({ 138, 2, 16, 16 });
	//		_pGround->SetScale(4.0f, 4.0f);
	//		_pGround->SetPosition({ rtClient.left - 0.0f + x * 30, rtClient.bottom - 48.0f + y * 30 });
	//		AddObject(_pGround);
	//	}
	//}

	//// 네트
	//for (size_t y = 0; y < 12; y++)
	//{
	//	_pNet = new Tile;
	//	_pNet->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Default.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");

	//	if (y == 0)
	//	{
	//		_pNet->SetUV({ 23, 2, 6, 8 });
	//		_pNet->SetScale(4.0f, 4.0f);
	//		_pNet->SetPosition({ rtClient.right / 2.0f, rtClient.bottom - 240.0f });
	//		AddObject(_pNet);
	//	}
	//	else
	//	{
	//		_pNet->SetUV({ 13, 2, 6, 8 });
	//		_pNet->SetScale(4.0f, 4.0f);
	//		_pNet->SetPosition({ rtClient.right / 2.0f, rtClient.bottom - 240.0f + y * 16 });
	//		AddObject(_pNet);
	//	}
	//	
	//}

	// 파도
	for (size_t x = 0; x < 27; x++)
	{
		_pWave = new Wave;
		_pWave->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
		_pWave->SetMask(pMaskTexture);
		_pWave->SetRect({ 70, 160, 16, 30 });
		_pWave->SetScale(4.0f, 4.0f);
		_pWave->SetPosition({ rtClient.left - 0.0f + x * 30, rtClient.bottom - 40.0f });
		AddObject(_pWave);
	}

	// 플레이어
	_pPlayer = new Player;
	_pPlayer->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pPlayer->SetMask(pMaskTexture);
	_pPlayer->SetRect({ 2, 265, 65, 65 });
	_pPlayer->SetPosition({ rtClient.left - 0.0f, rtClient.bottom - 170.0f });
	_pPlayer->SetScale(3.5f, 3.5f);
	_pPlayer->SetSpeed(300.0f);
	AddObject(_pPlayer);

	// 적
	_pEnemy = new Enemy;
	_pEnemy->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pEnemy->SetMask(pMaskTexture);
	_pEnemy->SetRect({ 2, 265, 65, 65 });
	_pEnemy->SetSpeed(300.0f);
	_pEnemy->SetScale(3.5f, 3.5f);
	_pEnemy->SetPosition({ rtClient.right - 130.0f, rtClient.bottom - 170.0f });
	AddObject(_pEnemy);

	// 공
	_pBall = new Ball;
	_pBall->CreateObject(_pd3dDevice, _pImmediateContext, L"../../Resource/Shader/Mask.hlsl", L"../../Resource/Pikachu/Image/Sprite.png");
	_pBall->SetMask(pMaskTexture);
	_pBall->SetRect({ 88, 158, 40, 40 });
	_pBall->SetSpeed(500.0f);
	_pBall->SetScale(3.5f, 3.5f);
	_pBall->SetPosition({ rtClient.left + 370.0f, rtClient.bottom - 400.0f });
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
		_pImmediateContext->PSSetShaderResources(1, 1, &_pPlayer->_pMaskTexture->_pShaderResourceView);

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

#include "pch.h"
#include "InGame.h"

HRESULT InGame::Init()
{
	// 사운드
	SOUND->Init();
	SOUND->LoadAll(L"../../../Resource/Pikachu/Sound/");
	_pBGM = SOUND->GetPtr(L"BGM.wav");
	_pBGM->PlayBGM(true);

	// 텍스처
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Map.png");
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Sprite1.png");
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Sprite2.png");
	Texture* pMaskTexture = TEXTURE->Load(L"../../../Resource/Pikachu/Image/Mask.png");

	// 스프라이트 정보
	SPRITE->Load(L"../../../Resource/Pikachu/Image/Sprite.txt");

	// 맵
	_pMap = new Map;
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Map.png");
	_pMap->SetRect({ 0.0f, 0.0f, 800.0f, 600.0f });
	_pMap->SetScale(1.0f, 1.0f);
	_pMap->SetPosition({ 400.0f, 300.0f });
	AddObject(_pMap);

	// 구름
	for (size_t i = 0; i < 10; i++)
	{
		_pCloud = new Cloud;
		_pCloud->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
		_pCloud->SetMask(pMaskTexture);
		_pCloud->SetRect({ 101, 90, 45, 20 });
		_pCloud->SetSpeed(RAND(40.0f, 50.0f));
		_pCloud->SetScale(2.0f, 2.0f);
		_pCloud->SetPosition({ RAND(0.0f, 800.0f), RAND(30.0f, 300.0f) });
		AddObject(_pCloud);
	}

	// 파도
	for (size_t x = 0; x < 26; x++)
	{
		_pWave = new Wave;
		_pWave->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
		_pWave->SetMask(pMaskTexture);
		_pWave->SetRect({ 70.0f, 160.0f, 16.0f, 30.0f });
		_pWave->SetSpeed(RAND(35.0f, 40.0f));
		_pWave->SetScale(2.0f, 2.0f);
		_pWave->SetPosition({ x * 32.0f, 630.0f });
		AddObject(_pWave);
	}

	// 플레이어 점수
	_pPlayerScore = new PlayerScore;
	_pPlayerScore->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayerScore->SetMask(pMaskTexture);
	_pPlayerScore->SetRect({ 205.0f, 125.0f, 30.0f, 30.0f });
	_pPlayerScore->SetScale(2.2f, 2.2f);
	_pPlayerScore->SetPosition({ 100.0f, 50.0f });
	AddObject(_pPlayerScore);

	// 플레이어 그림자
	_pPlayerShadow = new PlayerShadow;
	_pPlayerShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayerShadow->SetMask(pMaskTexture);
	_pPlayerShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pPlayerShadow->SetSpeed(300.0f);
	_pPlayerShadow->SetScale(2.0f, 2.0f);
	_pPlayerShadow->SetPosition({ 65.0f, 535.0f });
	AddObject(_pPlayerShadow);

	// 플레이어
	_pPlayer = new Player;
	_pPlayer->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayer->SetMask(pMaskTexture);
	_pPlayer->SetRect({ 2.0f, 265.0f, 65.0f, 65.0f });
	_pPlayer->SetSpeed(300.0f);
	_pPlayer->SetScale(2.0f, 2.0f);
	_pPlayer->SetPosition({ 65.0f, 480.0f });
	AddObject(_pPlayer);

	// 적 점수
	_pEnemyScore = new EnemyScore;
	_pEnemyScore->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pEnemyScore->SetMask(pMaskTexture);
	_pEnemyScore->SetRect({ 205.0f, 125.0f, 30.0f, 30.0f });
	_pEnemyScore->SetScale(2.2f, 2.2f);
	_pEnemyScore->SetPosition({ 700.0f, 50.0f });
	AddObject(_pEnemyScore);

	// 적 그림자
	_pEnemyShadow = new EnemyShadow;
	_pEnemyShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pEnemyShadow->SetMask(pMaskTexture);
	_pEnemyShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pEnemyShadow->SetSpeed(300.0f);
	_pEnemyShadow->SetScale(2.0f, 2.0f);
	_pEnemyShadow->SetPosition({ 735.0f, 535.0f });
	AddObject(_pEnemyShadow);

	// 적
	_pEnemy = new Enemy;
	_pEnemy->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite2.png");
	_pEnemy->SetMask(pMaskTexture);
	_pEnemy->SetRect({ 67.0f, 265.0f, -65.0f, 65.0f });
	_pEnemy->SetSpeed(300.0f);
	_pEnemy->SetScale(-2.0f, 2.0f);
	_pEnemy->SetPosition({ 735.0f, 480.0f });
	AddObject(_pEnemy);

	// 공 그림자
	_pBallShadow = new BallShadow;
	_pBallShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pBallShadow->SetMask(pMaskTexture);
	_pBallShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pBallShadow->SetSpeed(500.0f);
	_pBallShadow->SetScale(2.0f, 2.0f);
	_pBallShadow->SetPosition({ 400.0f, 535.0f });
	AddObject(_pBallShadow);

	// 공
	_pBall = new Ball;
	_pBall->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pBall->SetMask(pMaskTexture);
	_pBall->SetRect({ 88.0f, 158.0f, 40.0f, 40.0f });
	_pBall->SetSpeed(500.0f);
	_pBall->SetScale(2.0f, 2.0f);
	_pBall->SetPosition({ 400.0f, 200.0f });
	AddObject(_pBall);

	return TRUE;
}

HRESULT InGame::Frame()
{
	SOUND->Frame();

	for (auto& pObject : _pObjects)
	{
		_pPlayerShadow->_position.x = _pPlayer->_position.x;
		_pEnemyShadow->_position.x = _pEnemy->_position.x;
		_pBallShadow->_position.x = _pBall->_position.x;

		pObject->Frame();
	}

	if (INPUT->GetKey(VK_SPACE) == KEY_STATE::DOWN)
	{
		AddEffect();
	}

	for (auto iter = _pEffects.begin();
		iter != _pEffects.end(); )
	{
		Effect* pEffect = *iter;
		if (FAILED(pEffect->Update()))
		{
			delete pEffect;
			iter = _pEffects.erase(iter);
			continue;
		}

		iter++;
	}

	return TRUE;
}

HRESULT InGame::Render()
{
	for (auto& pObject : _pObjects)
	{
		_pImmediateContext->PSSetShaderResources(1, 1, &_pCloud->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pPlayer->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pPlayerScore->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pPlayerShadow->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pEnemy->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pEnemyScore->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pEnemyShadow->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pBall->_pMaskTexture->_pShaderResourceView);
		_pImmediateContext->PSSetShaderResources(1, 1, &_pBallShadow->_pMaskTexture->_pShaderResourceView);

		pObject->Render();
	}

	for (auto pEffect : _pEffects)
	{
		pEffect->_pSprite->PreRender();
		_pImmediateContext->PSSetShaderResources(1, 1,
			&pEffect->_pSprite->_pMaskTexture->_pShaderResourceView);
		pEffect->_pSprite->PostRender();
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
	SAFE_DELETE(_pCloud);
	SAFE_DELETE(_pWave);
	SAFE_DELETE(_pPlayer);
	SAFE_DELETE(_pPlayerScore);
	SAFE_DELETE(_pPlayerShadow);
	SAFE_DELETE(_pEnemy);
	SAFE_DELETE(_pEnemyScore);
	SAFE_DELETE(_pEnemyShadow);
	SAFE_DELETE(_pBall);
	SAFE_DELETE(_pBallShadow);

	return TRUE;
}

#include "pch.h"
#include "InGame.h"

HRESULT InGame::Init()
{
	// 타이머
	_netTimer1 = GetTickCount64();
	_netTimer2 = GetTickCount64();
	_netTimer3 = GetTickCount64();
	_netTimer4 = GetTickCount64();
	_playerTimer = GetTickCount64();
	_enemyTimer = GetTickCount64();

	// 사운드
	_pEffect3 = SOUND->GetPtr(L"Effect3.wav");
	_pEffect4 = SOUND->GetPtr(L"Effect4.wav");
	_pEffect5 = SOUND->GetPtr(L"Effect5.wav");
	_pEffect6 = SOUND->GetPtr(L"Effect6.wav");

	// 텍스처
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Map.png");
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Sprite1.png");
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Sprite2.png");
	Texture* pMaskTexture = TEXTURE->Load(L"../../../Resource/Pikachu/Image/Mask.png");

	// 스프라이트
	SPRITE->Load(L"../../../Resource/Pikachu/Image/Sprite.txt");

	// 네트
	_pNet1 = new Object2D;
	_pNet1->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pNet1->SetRect({ 0.0f, 0.0f, 20.0f, 50.0f });
	_pNet1->SetScale(1.0f, 1.0f);
	_pNet1->SetPosition({ 410.0f, 400.0f });
	AddObject(_pNet1);
	_pNet2 = new Object2D;
	_pNet2->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pNet2->SetRect({ 0.0f, 0.0f, 20.0f, 50.0f });
	_pNet2->SetScale(1.0f, 1.0f);
	_pNet2->SetPosition({ 410.0f, 430.0f });
	AddObject(_pNet2);
	_pNet3 = new Object2D;
	_pNet3->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pNet3->SetRect({ 0.0f, 0.0f, 20.0f, 50.0f });
	_pNet3->SetScale(1.0f, 1.0f);
	_pNet3->SetPosition({ 410.0f, 460.0f });
	AddObject(_pNet3);
	_pNet4 = new Object2D;
	_pNet4->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pNet4->SetRect({ 0.0f, 0.0f, 20.0f, 50.0f });
	_pNet4->SetScale(1.0f, 1.0f);
	_pNet4->SetPosition({ 410.0f, 490.0f });
	AddObject(_pNet4);

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
		_pCloud->SetDirection({ 1.0f, 0.0f });
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
		_pCloud->SetDirection({ 0.0f, -1.0f });
		_pWave->SetPosition({ x * 32.0f, 630.0f });
		AddObject(_pWave);
	}

	// 공 그림자
	_pBallShadow = new BallShadow;
	_pBallShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pBallShadow->SetMask(pMaskTexture);
	_pBallShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pBallShadow->SetSpeed(300.0f);
	_pBallShadow->SetScale(2.0f, 2.0f);
	_pBallShadow->SetPosition({ 400.0f, 535.0f });
	AddObject(_pBallShadow);

	// 플레이어 그림자
	_pPlayerShadow = new PlayerShadow;
	_pPlayerShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayerShadow->SetMask(pMaskTexture);
	_pPlayerShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pPlayerShadow->SetSpeed(400.0f);
	_pPlayerShadow->SetScale(2.0f, 2.0f);
	_pPlayerShadow->SetPosition({ 100.0f, 535.0f });
	AddObject(_pPlayerShadow);

	// 플레이어
	_pPlayer = new Player;
	_pPlayer->_pSprite = SPRITE->GetPtr(L"rtPlayerRun");
	_pPlayer->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayer->SetMask(pMaskTexture);
	_pPlayer->SetRect({ 8.0f, 272.0f, 54.0f, 56.0f });
	_pPlayer->SetSpeed(400.0f);
	_pPlayer->SetScale(2.0f, 2.0f);
	_pPlayer->SetPosition({ 100.0f, 485.0f });
	AddObject(_pPlayer);

	// 플레이어 점수
	_pPlayerScore = new PlayerScore;
	_pPlayerScore->_pSprite = SPRITE->GetPtr(L"rtPlayerScore");
	_pPlayerScore->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayerScore->SetMask(pMaskTexture);
	_pPlayerScore->SetRect({ 205.0f, 125.0f, 30.0f, 30.0f });
	_pPlayerScore->SetScale(2.2f, 2.2f);
	_pPlayerScore->SetPosition({ 100.0f, 50.0f });
	AddObject(_pPlayerScore);

	// 적 점수
	_pEnemyScore = new EnemyScore;
	_pEnemyScore->_pSprite = SPRITE->GetPtr(L"rtEnemyScore");
	_pEnemyScore->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pEnemyScore->SetMask(pMaskTexture);
	_pEnemyScore->SetRect({ 210.0f, 126.0f, 21.0f, 27.0f });
	_pEnemyScore->SetScale(2.2f, 2.2f);
	_pEnemyScore->SetPosition({ 700.0f, 50.0f });
	AddObject(_pEnemyScore);

	// 적 그림자
	_pEnemyShadow = new EnemyShadow;
	_pEnemyShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pEnemyShadow->SetMask(pMaskTexture);
	_pEnemyShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pEnemyShadow->SetSpeed(400.0f);
	_pEnemyShadow->SetScale(2.0f, 2.0f);
	_pEnemyShadow->SetPosition({ 735.0f, 535.0f });
	AddObject(_pEnemyShadow);

	// 적
	_pEnemy = new Enemy;
	_pEnemy->_pSprite = SPRITE->GetPtr(L"rtEnemyRun");
	_pEnemy->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite2.png");
	_pEnemy->SetMask(pMaskTexture);
	_pEnemy->SetRect({ 62.0f, 272.0f, -54.0f, 56.0f });
	_pEnemy->SetSpeed(400.0f);
	_pEnemy->SetScale(-2.0f, 2.0f);
	_pEnemy->SetPosition({ 735.0f, 485.0f });
	AddObject(_pEnemy);

	// 공
	_pBall = new Ball;
	_pBall->_pSprite = SPRITE->GetPtr(L"rtBall");
	_pBall->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pBall->SetMask(pMaskTexture);
	_pBall->SetRect({ 88.0f, 158.0f, 40.0f, 40.0f });
	_pBall->SetSpeed(300.0f);
	_pBall->SetScale(2.0f, 2.0f);
	_pBall->SetPosition({ 400.0f, 100.0f });
	AddObject(_pBall);

	return TRUE;
}

HRESULT InGame::Frame()
{
	SOUND->Frame();

	for (auto& pObject : _pObjects)
	{
		// 그림자
		_pPlayerShadow->_position.x = _pPlayer->_position.x;
		_pEnemyShadow->_position.x = _pEnemy->_position.x;
		_pBallShadow->_position.x = _pBall->_position.x;

		// 인공지능
		if (_isSinglePlay)
		{
			if (_pBall->_position.x >= RESOLUTION_X / HALF + _pBall->_rect.w)
			{
				_pEnemy->_position.x = _pBall->_position.x + _pBall->_rect.w;
			}
		}

		// 효과음
		if (INPUT->GetKey('W') == KEY_STATE::DOWN)
		{
			_pEffect3->PlayEffect();
		}
		else if (INPUT->GetKey(VK_UP) == KEY_STATE::DOWN)
		{
			_pEffect3->PlayEffect();
		}

		// 점수
		if (_pBall->_isPlayerBall)
		{
			_pPlayerScore->AddScore();
			_pBall->_isPlayerBall = false;
		}
		else if (_pBall->_isEnemyBall)
		{
			_pEnemyScore->AddScore();
			_pBall->_isEnemyBall = false;
		}

		if (_pPlayerScore->_isPlayerWin)
		{
			_pBall->_position = { (-100.0f, -100.0f) };
			_pPlayer->_isWin = true;
			_pEnemy->_isLose = true;
		}
		else if (_pEnemyScore->_isEnemyWin)
		{
			_pBall->_position = { (-100.0f, -100.0f) };
			_pEnemy->_isWin = true;
			_pPlayer->_isLose = true;
		}

		// 네트 충돌
		if (GetTickCount64() - _netTimer1 > 500 && _pBall->CheckCollision(*_pNet1))
		{
			_netTimer1 = GetTickCount64();
		}

		if (GetTickCount64() - _netTimer2 > 500 && _pBall->CheckCollision(*_pNet2))
		{
			_netTimer2 = GetTickCount64();
		}

		if (GetTickCount64() - _netTimer3 > 500 && _pBall->CheckCollision(*_pNet3))
		{
			_netTimer3 = GetTickCount64();
		}

		if (GetTickCount64() - _netTimer4 > 500 && _pBall->CheckCollision(*_pNet4))
		{
			_netTimer4 = GetTickCount64();
		}

		// 플레이어 충돌
		if (GetTickCount64() - _playerTimer > 500 && _pBall->CheckCollision(*_pPlayer) && _pPlayer->IsSpike())
		{
			_playerTimer = GetTickCount64();
			_pEffect4->PlayEffect();
			AddEffect(_pBall);
		}

		// 적 충돌
		if (GetTickCount64() - _enemyTimer > 500 && _pBall->CheckCollision(*_pEnemy) && _pEnemy->IsSpike())
		{
			_enemyTimer = GetTickCount64();
			_pEffect4->PlayEffect();
			AddEffect(_pBall);
		}

		// 그라운드 충돌
		if (_pBall->_position.y >= 470.0f)
		{
			AddEffect(_pBall);
		}

		pObject->Frame();
	}

	for (auto& pEffect : _pEffects)
	{
		pEffect->_pSprite->SetRect(pEffect->_rect);
		pEffect->_pSprite->SetScale(2.0f, 2.0f);
		pEffect->_pSprite->SetPosition(pEffect->_position);
	}

	for (auto iter = _pEffects.begin(); iter != _pEffects.end();)
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

	SAFE_DELETE(_pNet1);
	SAFE_DELETE(_pNet2);
	SAFE_DELETE(_pNet3);
	SAFE_DELETE(_pNet4);
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

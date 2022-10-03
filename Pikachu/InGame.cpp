#include "pch.h"
#include "InGame.h"

HRESULT InGame::Init()
{
	// Ÿ�̸�
	_netTimer1 = GetTickCount64();
	_netTimer2 = GetTickCount64();
	_netTimer3 = GetTickCount64();
	_playerTimer = GetTickCount64();
	_enemyTimer = GetTickCount64();

	// ����
	SOUND->Init();
	SOUND->LoadAll(L"../../../Resource/Pikachu/Sound/");
	_pEffect1 = SOUND->GetPtr(L"Effect1.wav");
	_pEffect2 = SOUND->GetPtr(L"Effect2.wav");
	_pEffect3 = SOUND->GetPtr(L"Effect3.wav");
	_pEffect4 = SOUND->GetPtr(L"Effect4.wav");
	_pEffect5 = SOUND->GetPtr(L"Effect5.wav");
	_pEffect6 = SOUND->GetPtr(L"Effect6.wav");

	// �ؽ�ó
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Map.png");
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Sprite1.png");
	TEXTURE->Load(L"../../../Resource/Pikachu/Image/Sprite2.png");
	Texture* pMaskTexture = TEXTURE->Load(L"../../../Resource/Pikachu/Image/Mask.png");

	// ��������Ʈ ����
	SPRITE->Load(L"../../../Resource/Pikachu/Image/Sprite.txt");

	// ��Ʈ
	_pNet1 = new Object2D;
	_pNet1->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pNet1->SetRect({ 0.0f, 0.0f, 12.0f, 192.0f });
	_pNet1->SetScale(1.0f, 1.0f);
	_pNet1->SetPosition({ 400.0f, 400.0f });
	AddObject(_pNet1);
	_pNet2 = new Object2D;
	_pNet2->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pNet2->SetRect({ 0.0f, 0.0f, 12.0f, 192.0f });
	_pNet2->SetScale(1.0f, 1.0f);
	_pNet2->SetPosition({ 400.0f, 450.0f });
	AddObject(_pNet2);
	_pNet3 = new Object2D;
	_pNet3->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pNet3->SetRect({ 0.0f, 0.0f, 12.0f, 192.0f });
	_pNet3->SetScale(1.0f, 1.0f);
	_pNet3->SetPosition({ 400.0f, 500.0f });
	AddObject(_pNet3);

	// ��
	_pMap = new Map;
	_pMap->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Default.hlsl", L"../../../Resource/Pikachu/Image/Map.png");
	_pMap->SetRect({ 0.0f, 0.0f, 800.0f, 600.0f });
	_pMap->SetScale(1.0f, 1.0f);
	_pMap->SetPosition({ 400.0f, 300.0f });
	AddObject(_pMap);

	// ����
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

	// �ĵ�
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

	// �÷��̾� ����
	_pPlayerScore = new PlayerScore;
	_pPlayerScore->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayerScore->SetMask(pMaskTexture);
	_pPlayerScore->SetRect({ 205.0f, 125.0f, 30.0f, 30.0f });
	_pPlayerScore->SetScale(2.2f, 2.2f);
	_pPlayerScore->SetPosition({ 100.0f, 50.0f });
	AddObject(_pPlayerScore);

	// �÷��̾� �׸���
	_pPlayerShadow = new PlayerShadow;
	_pPlayerShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayerShadow->SetMask(pMaskTexture);
	_pPlayerShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pPlayerShadow->SetSpeed(400.0f);
	_pPlayerShadow->SetScale(2.0f, 2.0f);
	_pPlayerShadow->SetPosition({ 65.0f, 535.0f });
	AddObject(_pPlayerShadow);

	// �÷��̾�
	_pPlayer = new Player;
	_pPlayer->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pPlayer->SetMask(pMaskTexture);
	_pPlayer->SetRect({ 2.0f, 265.0f, 65.0f, 65.0f });
	_pPlayer->SetSpeed(400.0f);
	_pPlayer->SetScale(2.0f, 2.0f);
	_pPlayer->SetPosition({ 65.0f, 480.0f });
	AddObject(_pPlayer);

	// �� ����
	_pEnemyScore = new EnemyScore;
	_pEnemyScore->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pEnemyScore->SetMask(pMaskTexture);
	_pEnemyScore->SetRect({ 205.0f, 125.0f, 30.0f, 30.0f });
	_pEnemyScore->SetScale(2.2f, 2.2f);
	_pEnemyScore->SetPosition({ 700.0f, 50.0f });
	AddObject(_pEnemyScore);

	// �� �׸���
	_pEnemyShadow = new EnemyShadow;
	_pEnemyShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pEnemyShadow->SetMask(pMaskTexture);
	_pEnemyShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pEnemyShadow->SetSpeed(400.0f);
	_pEnemyShadow->SetScale(2.0f, 2.0f);
	_pEnemyShadow->SetPosition({ 735.0f, 535.0f });
	AddObject(_pEnemyShadow);

	// ��
	_pEnemy = new Enemy;
	_pEnemy->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite2.png");
	_pEnemy->SetMask(pMaskTexture);
	_pEnemy->SetRect({ 67.0f, 265.0f, -65.0f, 65.0f });
	_pEnemy->SetSpeed(400.0f);
	_pEnemy->SetScale(-2.0f, 2.0f);
	_pEnemy->SetPosition({ 735.0f, 480.0f });
	AddObject(_pEnemy);

	// �� �׸���
	_pBallShadow = new BallShadow;
	_pBallShadow->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pBallShadow->SetMask(pMaskTexture);
	_pBallShadow->SetRect({ 32.0f, 2.0f, 32.0f, 7.0f });
	_pBallShadow->SetSpeed(300.0f);
	_pBallShadow->SetScale(2.0f, 2.0f);
	_pBallShadow->SetPosition({ 400.0f, 535.0f });
	AddObject(_pBallShadow);

	// ��
	_pBall = new Ball;
	_pBall->_pSprite = SPRITE->GetPtr(L"rtBall");

	_pBall->_index = 0;

	_pBall->_maxIndex = _pBall->_pSprite->_uvs.size();

	_pBall->CreateObject(_pd3dDevice, _pImmediateContext, L"../../../Resource/Shader/Mask.hlsl", L"../../../Resource/Pikachu/Image/Sprite1.png");
	_pBall->SetMask(pMaskTexture);
	_pBall->SetRect({ 88.0f, 158.0f, 40.0f, 40.0f });
	_pBall->SetSpeed(300.0f);
	_pBall->SetScale(2.0f, 2.0f);
	_pBall->SetPosition({ 65.0f, 200.0f });
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

		//if (_pBall->_position.x >= RESOLUTION_X / HALF + _pBall->_rect.w)
		//{
		//	_pEnemy->_position.x = _pBall->_position.x + _pBall->_rect.w;
		//}

		//if (_pBall->_position.x <= RESOLUTION_X / HALF - _pBall->_rect.w)
		//{
		//	_pPlayer->_position.x = _pBall->_position.x - _pBall->_rect.w;
		//}

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

		if (GetTickCount64() - _playerTimer > 500 && _pBall->CheckCollision(*_pPlayer))
		{
			_playerTimer = GetTickCount64();
		}

		if (_pBall->_isCollision)
		{
			AddEffect(_pBall);
		}

		if (GetTickCount64() - _enemyTimer > 500 && _pBall->CheckCollision(*_pEnemy))
		{
			_enemyTimer = GetTickCount64();
		}

		if (_pBall->_isCollision)
		{
			AddEffect(_pBall);
		}

		if (_pBall->_position.y >= 470.0f + _pBall->_rect.h && _pBall->_speed >= 0.1f)
		{
			AddEffect(_pBall);
		}

		//_pBall->Update();

		pObject->Frame();
	}

	for (auto iter = _pEffects.begin();
		iter != _pEffects.end();)
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

	for (auto pEffect : _pEffects)
	{
		pEffect->_pSprite->SetScale(1.5f, 1.5f);
		pEffect->_pSprite->SetRect(pEffect->_rect);
		pEffect->_pSprite->SetPosition(pEffect->_position);
	}

	return TRUE;
}

HRESULT InGame::Render()
{
	_pBall->Update();

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

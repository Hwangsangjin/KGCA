#pragma once

#include "Object2D.h"

class Sprite;

class Ball : public Object2D
{
public:
	Vector2 _force = { 0.0f, 0.0f };

	Sprite* _pSprite = nullptr;
	UINT _spriteIndex = 0;
	UINT _spriteMaxIndex = 1;
	float _spriteTimer = 0.0f;
	float _spriteStep = 1.0f;

	bool _isCollision = false;
	bool _isSpin = false;

	bool _isPlayerBall = false;
	bool _isEnemyBall = false;

	virtual HRESULT Frame() override;
	virtual bool CheckCollision(Object2D& object);
	void AddForce(Vector2 force);
	bool IsSpin();
};


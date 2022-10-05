#pragma once

#include "Object2D.h"

class Sprite;

class Enemy : public Object2D
{
public:
	Sprite* _pSprite = nullptr;
	UINT _spriteIndex = 0;
	UINT _spriteMaxIndex = 1;
	float _spriteTimer = 0.0f;
	float _spriteStep = 1.0f;
	Vector2 _velocity = { 0.0f, 0.0f };
	bool _isJump = false;
	bool _isSpike = false;
	bool _isDig = false;
	bool _isWin = false;
	bool _isLose = false;

	virtual HRESULT Frame() override;

	bool IsSpike();
	bool IsJump();
	bool IsDig();
};


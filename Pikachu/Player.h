#pragma once

#include "Object2D.h"

class Sprite;

class Player : public Object2D
{
public:
	enum PLAYER_STATE
	{
		RUN,
		TOSS,
		DIG,
		SPIKE,
		WIN,
		LOSE
	};

	Sprite* _pSprite = nullptr;
	UINT _spriteIndex = 0;
	UINT _spriteMaxIndex = 1;
	float _spriteTimer = 0.0f;
	float _spriteStep = 1.0f;
	Vector2 _velocity = { 0.0f, 0.0f };
	bool _isJump = false;
	bool _isDig = false;

	virtual HRESULT Frame() override;
};


#pragma once

#include "Object2D.h"

class Sprite;

class Ball : public Object2D
{
private:
	float _mass = 1.0f;
	Vector2 _force = { 0.0f, 0.0f };
	Vector2 _acc = { 0.0f, 0.0f };
	Vector2 _velocity = { 0.0f, 0.0f };

public:
	bool _isCollision = false;

	Sprite* _pSprite = nullptr;
	UINT _spriteIndex = 0;
	UINT _spriteMaxIndex = 1;
	float _spriteTimer = 0.0f;
	float _spriteStep = 1.0f;

	virtual HRESULT Frame() override;
	bool CheckCollision(Object2D& object);
};


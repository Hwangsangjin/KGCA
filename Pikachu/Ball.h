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

	UINT _index = 0;
	UINT _maxIndex = 1;
	float _effectTimer = 0.0f;
	float _step = 1.0f;
	Sprite* _pSprite = nullptr;

	virtual HRESULT Frame() override;
	bool CheckCollision(Object2D& object);

	HRESULT Update();
};


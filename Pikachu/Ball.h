#pragma once

#include "Object2D.h"

class Ball : public Object2D
{
private:
	float _mass = 1.0f;
	Vector2 _force = { 0.0f, 0.0f };
	Vector2 _acc = { 0.0f, 0.0f };
	Vector2 _velocity = { 0.0f, 0.0f };

public:
	bool _isCollision = false;

	virtual HRESULT Frame() override;
	bool CheckCollision(Object2D& object);
};


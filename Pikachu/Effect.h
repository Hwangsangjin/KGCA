#pragma once

#include "SpriteManager.h"
#include "Timer.h"

class Effect
{
public:
	Vector2 _position;
	Vector2 _direction = { 0.0f, 1.0f };
	float _lifeTime = 0.33f;
	float _speed = 300.0f;
	UINT _index = 0;
	UINT _maxIndex = 1;
	float _effectTimer = 0.0f;
	Rect _rect = { 0.0f, 0.0f, 0.0f, 0.0f };
	Vector2 _scale = { 1.0f, 1.0f };
	float _step = 1.0f;
	Rect _collision;
	Sprite* _pSprite = nullptr;

	Rect Convert(RECT rect);

	HRESULT Update();
};


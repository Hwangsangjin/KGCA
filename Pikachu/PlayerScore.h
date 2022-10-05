#pragma once

#include "Object2D.h"

class Sprite;

class PlayerScore : public Object2D
{
public:
	Sprite* _pSprite = nullptr;
	UINT _spriteIndex = 0;
	UINT _spriteMaxIndex = 1;
	float _spriteTimer = 0.0f;
	float _spriteStep = 1.0f;

	bool _isPlayerWin = false;

	virtual HRESULT Frame() override;
	void AddScore();
};


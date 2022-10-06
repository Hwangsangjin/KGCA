#pragma once

#include "Object2D.h"

class GameOverText : public Object2D
{
public:
	static float _x;
	static float _y;
	static float _timer;

	bool _isFull = false;

	virtual HRESULT Frame() override;
};


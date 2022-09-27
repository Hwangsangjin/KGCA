#pragma once

#include "Object2D.h"

class BattleText : public Object2D
{
private:
	static float _x;
	static float _y;
	static float _timer;
	
	bool _isFull = false;

public:
	virtual HRESULT Frame() override;
};


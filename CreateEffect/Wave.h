#pragma once

#include "Object2D.h"

class Wave : public Object2D
{
private:
	float _timer;

	bool _isFull = false;

public:
	virtual HRESULT Frame() override;
};


#pragma once

#include "Object2D.h"

class Ball : public Object2D
{
public:
	virtual HRESULT Frame() final;
};


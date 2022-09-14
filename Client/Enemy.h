#pragma once

#include "Object2D.h"

class Enemy : public Object2D
{
public:
	virtual HRESULT Frame() final;
};


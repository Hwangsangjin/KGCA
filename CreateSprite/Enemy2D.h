#pragma once

#include "Object2D.h"

class Enemy2D : public Object2D
{
public:
	virtual HRESULT Frame() final;
};


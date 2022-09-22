#pragma once

#include "Object2D.h"

class Background : public Object2D
{
public:
	Vector2 init;

	virtual HRESULT Frame() override;
};


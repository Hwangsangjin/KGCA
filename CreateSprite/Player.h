#pragma once

#include "Object2D.h"

class Player : public Object2D
{
public:
	virtual HRESULT Frame() override;
};


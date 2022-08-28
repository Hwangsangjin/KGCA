#pragma once

#include "Object.h"

class Enemy : public Object
{
public:
	void Frame(float fDeltaTime, float fGameTime) override;
};


#pragma once

#include "Object.h"

class Player : public Object
{
public:
	void Frame(float fDeltaTime, float fGameTime) override;
};


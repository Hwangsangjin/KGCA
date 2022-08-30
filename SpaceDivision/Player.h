#pragma once

#include "Object.h"

class Player : public Object
{
public:
	virtual void Init() override;
    virtual void Frame(float elapsedTime, float gameTime) override;
};


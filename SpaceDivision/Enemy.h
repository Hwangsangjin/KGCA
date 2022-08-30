#pragma once

#include "Object.h"

class Enemy : public Object
{
public:
	Enemy();
	Enemy(std::string name);

	virtual void Init() override;
	virtual void Frame(float elapsedTime, float gameTime) override;
};


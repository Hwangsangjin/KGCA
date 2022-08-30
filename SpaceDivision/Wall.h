#pragma once

#include "Object.h"

class Wall : public Object
{
public:
	Wall();
	Wall(std::string name);

	virtual void Init() override;
	virtual void Frame(float elapsedTime, float gameTime) override;
};


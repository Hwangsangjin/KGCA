#pragma once

#include "Rect.h"

class Object
{
public:
	Rect _rect;

	Object() = default;
	Object(Rect rect);

	void Create(Rect rect);
	void SetPosition(float x, float y);
};


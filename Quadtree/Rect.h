#pragma once

#include "Vector2D.h"
#include <vector>
#include <map>

class Rect
{
public:
	float _left;
	float _top;
	float _right;
	float _bottom;

	Rect() = default;
	Rect(float left, float top, float right, float bottom);
};


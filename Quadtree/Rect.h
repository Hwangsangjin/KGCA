#pragma once

#include "Vector2D.h"
#include <vector>
#include <map>

struct Rect
{
	float left;
	float top;
	float right;
	float bottom;

	Rect() = default;
	Rect(float left, float top, float right, float bottom);
};


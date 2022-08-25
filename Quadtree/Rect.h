#pragma once

#include "Vector2.h"
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


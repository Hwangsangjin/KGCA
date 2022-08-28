#pragma once

struct Rectangle
{
	Vector2 _vMin;
	Vector2 _vMax;

	Rectangle() = default;
	Rectangle(const Rectangle& rect);
};


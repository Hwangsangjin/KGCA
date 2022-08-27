#pragma once

class Rectangle
{
private:
	Vector2 _vMin;
	Vector2 _vMax;

public:
	Rectangle() = default;
	Rectangle(const Rectangle& rect);
};


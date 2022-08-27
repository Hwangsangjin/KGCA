#pragma once

class Circle
{
private:
	Vector2 _vCenter;
	float _radius;

public:
	Circle() = default;
	Circle(const Vector2& vCenter, float radius);
};


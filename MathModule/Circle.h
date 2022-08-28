#pragma once

struct Circle
{
	Vector2 _vCenter;
	float _radius;

	Circle() = default;
	Circle(const Vector2& vCenter, float radius);
};


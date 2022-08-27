#pragma once

class Box
{
private:
	Vector3 _vMin;
	Vector3 _vMax;

public:
	Box() = default;
	Box(const Box& box);
	Box(const Vector3& vMin, const Vector3& vMax);
};


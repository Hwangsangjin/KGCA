#pragma once

class Box
{
public:
	Vector3 _vMin;
	Vector3 _vMax;

	Box() = default;
	Box(const Box& box);
	Box(const Vector3& vMin, const Vector3& vMax);

	bool Intersect(const Box& box) const;
	bool IsInside(const Box& box) const;
	bool IsInside(const Vector3& vector) const;
};


#pragma once

struct Sphere
{
	Vector3 vCenter;
	float radius;

	Sphere() = default;
	Sphere(const Vector3& vCenter, float radius);
};


#pragma once

struct Sphere
{
	Vector3 _vCenter;
	float _radius;

	Sphere() = default;
	Sphere(const Vector3& vCenter, float radius);
};


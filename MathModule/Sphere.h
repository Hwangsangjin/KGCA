#pragma once

struct Sphere
{
	Vector3 vCenter;
	float radius;

	Sphere() = default;
	Sphere(Vector3 vC, float r);
};


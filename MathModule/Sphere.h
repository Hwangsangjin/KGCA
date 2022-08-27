#pragma once

class Sphere
{
private:
	Vector3 _vCenter;
	float _radius;

public:
	Sphere() = default;
	Sphere(const Vector3& vCenter, float radius);
};


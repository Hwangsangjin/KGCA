#pragma once

struct Box
{
	Vector3 _vMin;
	Vector3 _vMax;
	Vector3 _vCenter;
	Vector3 _vSize;

	Box() = default;
	Box(const Vector3& vPos, const Vector3& vSize);

	bool operator==(const Box& dest);

	void Set(const Vector3& vPos, const Vector3& vSize);
};


#pragma once

struct Box
{
	Vector3 vMin;
	Vector3 vMax;
	Vector3 vCenter;
	Vector3 vSize;

	Box() = default;
	Box(const Vector3& vPos, const Vector3& vSize);

	bool operator==(const Box& dest);

	void Set(const Vector3& vPos, const Vector3& vSize);
};


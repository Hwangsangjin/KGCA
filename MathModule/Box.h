#pragma once

struct Box
{
	Vector3 vMin;
	Vector3 vMax;
	Vector3 vCenter;
	Vector3 vSize;

	Box() = default;
	Box(Vector3 vPos, Vector3 vSize);

	bool operator==(Box& dest);

	void Set(Vector3 vPos, Vector3 vSize);
};


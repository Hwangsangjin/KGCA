#include "pch.h"
#include "Box.h"

Box::Box(const Box& box)
	: _vMin(box._vMin)
	, _vMax(box._vMax)
{
}

Box::Box(const Vector3& vMin, const Vector3& vMax)
	: _vMin(vMin)
	, _vMax(vMax)
{
}

bool Box::Intersect(const Box& box) const
{
	if ((_vMin._x> box._vMax._x) || (box._vMin._x > _vMax._x))
	{
		return false;
	}

	if ((_vMin._y > box._vMax._y) || (box._vMin._y > _vMax._y))
	{
		return false;
	}

	if ((_vMin._z > box._vMax._z) || (box._vMin._z > _vMax._z))
	{
		return false;
	}

	return true;
}

bool Box::IsInside(const Box& box) const
{
	return (IsInside(box._vMin) && IsInside(box._vMax));
}

bool Box::IsInside(const Vector3& vector) const
{
	return ((vector._x >= _vMin._x) && (vector._x <= _vMax._x) && (vector._y >= _vMin._y) && (vector._y <= _vMax._y) && (vector._z >= _vMin._z) && (vector._z <= _vMax._z));
}

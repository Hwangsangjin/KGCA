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

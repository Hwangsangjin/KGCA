#include "pch.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Rectangle& rect)
	: _vMin(rect._vMin)
	, _vMax(rect._vMax)
{
}

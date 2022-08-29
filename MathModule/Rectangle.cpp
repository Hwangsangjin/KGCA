#include "pch.h"
#include "Rectangle.h"

Rectangle::Rectangle(const Rectangle& rect)
	: vMin(rect.vMin)
	, vMax(rect.vMax)
{
}

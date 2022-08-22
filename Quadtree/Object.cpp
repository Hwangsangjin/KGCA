#include "Object.h"

Object::Object(Rect rect)
{
	_rect = rect;
}

void Object::Create(Rect rect)
{
	_rect = rect;
}

void Object::SetPosition(float x, float y)
{
	_rect._left = x;
	_rect._right = y;
}

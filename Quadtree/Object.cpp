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
	_rect.left = x;
	_rect.right = y;
}

#include "pch.h"
#include "Object2D.h"

Object2D::Object2D()
{
	Init();
}

Object2D::Object2D(std::string name)
{
	Init();
	_name = name;
}

void Object2D::Init()
{
}

void Object2D::Frame(float deltaTime)
{
}

void Object2D::AddForce(Vector2 vForce)
{
}

void Object2D::SetCircle(Vector2 p, Vector2 s)
{
}

void Object2D::SetPosition(Vector2 p, Vector2 s)
{
}

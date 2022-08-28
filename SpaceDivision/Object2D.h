#pragma once

#include "ObjectBase.h"

class Object2D : ObjectBase
{
public:
	Vector2 _vDirection;
	Vector2 _vAcceleration;
	Vector2 _vVelocity;
	Vector2 _vForce;

	Rectangle _rect;
	Circle _circle;

	Object2D();
	Object2D(std::string name);

	virtual void Init() override;
	virtual void Frame(float deltaTime) override;
	virtual void AddForce(Vector2 vforce);

	void   SetCircle(Vector2 p, Vector2 s);
	void   SetPosition(Vector2 p, Vector2 s);
};


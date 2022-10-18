#pragma once

#include "Object.h"

class Camera : public Object
{
public:
	virtual void CreateView(MyVector3 eye, MyVector3 at, MyVector3 up);
	virtual void CreateProjection(float fNear, float fFar, float fovY, float aspectRatio);
	virtual HRESULT Frame();

	MyVector3 _position;
	MyVector3 _target;
	MyVector3 _up;
	
	float _near;
	float _far;
	float _fovY;
	float _aspectRatio;
};


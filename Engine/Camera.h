#pragma once

#include "Object.h"

class Camera : public Object
{
public:
	virtual void CreateView(MyVector3 Eye, MyVector3 At, MyVector3 Up);
	virtual void CreateProjection(float Near, float Far, float FovY, float AspectRatio);
	virtual HRESULT Frame();

	MyVector3 _Position;
	MyVector3 _Target;
	MyVector3 _Up;
	
	float _Near;
	float _Far;
	float _FovY;
	float _AspectRatio;
};


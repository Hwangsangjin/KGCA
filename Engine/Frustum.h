#pragma once

#include "Object.h"
#include "TMath.h"

struct Plane
{
	void CreatePlane(MyVector3 v0, MyVector3 v1, MyVector3 v2);
	void CreatePlane(MyVector3 normal, MyVector3 v0);

	float _a, _b, _c, _d;
};

struct Sphere
{
	MyVector3 _center;
	float _radius;
};

struct Box
{
	MyVector3 _center;
	MyVector3 _position[8];

	// AABB
	MyVector3 _min;
	MyVector3 _max;

	// OBB
	MyVector3 _axis[3];
	float _extent[3];
};

class Frustum : public Object
{
public:
	void CreateFrustum(MyMatrix* pView, MyMatrix* pProjection);
	HRESULT ClassifyPoint(MyVector3 vector);
	HRESULT ClassifySphere(Sphere* pSphere);

	MyMatrix _view;
	MyMatrix _projection;
	TBASIS_EX::TVector3 _frustum[8];
	Plane _plane[6];
};


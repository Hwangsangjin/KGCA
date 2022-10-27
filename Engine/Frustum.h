#pragma once

#include "Object.h"
#include "TMath.h"

enum CULLING_POSITION
{
	BACK,
	FRONT,
	ONPLANE,
	SPANNING
};

struct Plane
{
	float _a, _b, _c, _d;

	void CreatePlane(MyVector3 v0, MyVector3 v1, MyVector3 v2);
	void CreatePlane(MyVector3 normal, MyVector3 v0);
};

class Frustum : public Object
{
public:
	MyMatrix _view;
	MyMatrix _projection;
	TBASIS_EX::TVector3 _frustum[8];
	Plane _plane[6];

	void CreateFrustum(MyMatrix* pView, MyMatrix* pProjection);
	CULLING_POSITION ClassifyPoint(MyVector3 vector);
	CULLING_POSITION ClassifySphere(MySphere* pSphere);
	CULLING_POSITION ClassifyAABB(CollisionAABB aabb);
	CULLING_POSITION ClassifyOBB(CollisionOBB obb);
	CULLING_POSITION ClassifyBOX(CollisionBOX box);
};


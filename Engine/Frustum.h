#pragma once

#include "Object.h"

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

	void CreatePlane(DxVector3 v0, DxVector3 v1, DxVector3 v2);
	void CreatePlane(DxVector3 normal, DxVector3 v0);
};

class Frustum : public Object
{
public:
	DxMatrix _view;
	DxMatrix _projection;
	DxVector3 _frustum[8];
	Plane _plane[6];

	void CreateFrustum(DxMatrix* pView, DxMatrix* pProjection);
	CULLING_POSITION ClassifyPoint(DxVector3 vector);
	CULLING_POSITION ClassifySphere(MySphere* pSphere);
	CULLING_POSITION ClassifyAABB(CollisionAABB aabb);
	CULLING_POSITION ClassifyOBB(CollisionOBB obb);
	CULLING_POSITION ClassifyBOX(CollisionBOX box);
};


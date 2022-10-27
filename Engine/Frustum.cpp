#include "pch.h"
#include "Frustum.h"
#include "Shape.h"
#include "Tmath.h"

void Plane::CreatePlane(MyVector3 v0, MyVector3 v1, MyVector3 v2)
{
	MyVector3 edge0 = v1 - v0;
	MyVector3 edge1 = v2 - v0;
	MyVector3 normal = edge0 ^ edge1;
	normal = normal.Normalize();
	_a = normal._x;
	_b = normal._y;
	_c = normal._z;
	_d = -(normal | v0);
	//_d = -(_a * v0._x + _b * v0._y, + _c * v0._z);
}

void Plane::CreatePlane(MyVector3 normal, MyVector3 v0)
{
	normal = normal.Normalize();
	_a = normal._x;
	_b = normal._y;
	_c = normal._z;
	_d = -(normal | v0);
	//_d = -(_a * v0._x + _b * v0._y, + _c * v0._z);
}

void Frustum::CreateFrustum(MyMatrix* pView, MyMatrix* pProjection)
{
	TBASIS_EX::TMatrix view = *(TBASIS_EX::TMatrix*)pView;
	TBASIS_EX::TMatrix projection = *(TBASIS_EX::TMatrix*)pProjection;
	TBASIS_EX::TMatrix inverseViewProjection = view * projection;
	TBASIS_EX::D3DXMatrixInverse(&inverseViewProjection, nullptr, &inverseViewProjection);

	_frustum[0] = TBASIS_EX::TVector3{ -1.0f, -1.0f, 0.0f };
	_frustum[1] = TBASIS_EX::TVector3{ -1.0f, 1.0f, 0.0f };
	_frustum[2] = TBASIS_EX::TVector3{ 1.0f, 1.0f, 0.0f };
	_frustum[3] = TBASIS_EX::TVector3{ 1.0f, -1.0f, 0.0f };
	_frustum[4] = TBASIS_EX::TVector3{ -1.0f, -1.0f, 1.0f };
	_frustum[5] = TBASIS_EX::TVector3{ -1.0f, 1.0f, 1.0f };
	_frustum[6] = TBASIS_EX::TVector3{ 1.0f, 1.0f, 1.0f };
	_frustum[7] = TBASIS_EX::TVector3{ 1.0f, -1.0f, 1.0f };

	for (size_t i = 0; i < 8; i++)
	{
		TBASIS_EX::D3DXVec3TransformCoord(&_frustum[i], &_frustum[i], &inverseViewProjection);
	}

	_plane[0].CreatePlane(*((MyVector3*)&_frustum[1]), *((MyVector3*)&_frustum[5]), *((MyVector3*)&_frustum[0]));
	_plane[1].CreatePlane(*((MyVector3*)&_frustum[3]), *((MyVector3*)&_frustum[6]), *((MyVector3*)&_frustum[2]));
	_plane[2].CreatePlane(*((MyVector3*)&_frustum[5]), *((MyVector3*)&_frustum[2]), *((MyVector3*)&_frustum[6]));
	_plane[3].CreatePlane(*((MyVector3*)&_frustum[0]), *((MyVector3*)&_frustum[7]), *((MyVector3*)&_frustum[3]));
	_plane[4].CreatePlane(*((MyVector3*)&_frustum[2]), *((MyVector3*)&_frustum[1]), *((MyVector3*)&_frustum[0]));
	_plane[5].CreatePlane(*((MyVector3*)&_frustum[5]), *((MyVector3*)&_frustum[6]), *((MyVector3*)&_frustum[4]));
}

CULLING_POSITION Frustum::ClassifyPoint(MyVector3 vector)
{
	for (size_t i = 0; i < 6; i++)
	{
		float distance = _plane[i]._a * vector._x + _plane[i]._b * vector._y + _plane[i]._c * vector._z + _plane[i]._d;

		if (distance == 0)
		{
			return CULLING_POSITION::ONPLANE;
		}
		if (distance < 0.0f)
		{
			return CULLING_POSITION::FRONT;
		}
	}

	return CULLING_POSITION::BACK;
}

CULLING_POSITION Frustum::ClassifySphere(MySphere* pSphere)
{
	for (size_t i = 0; i < 6; i++)
	{
		float distance = _plane[i]._a * pSphere->_center._x + _plane[i]._b * pSphere->_center._y + _plane[i]._c * pSphere->_center._z + _plane[i]._d;
		if (distance <= -pSphere->_radius)
		{
			return CULLING_POSITION::FRONT;
		}
	}

	return CULLING_POSITION::BACK;
}

CULLING_POSITION Frustum::ClassifyAABB(CollisionAABB aabb)
{
	return CULLING_POSITION::SPANNING;
}

CULLING_POSITION Frustum::ClassifyOBB(CollisionOBB obb)
{
	return CULLING_POSITION::SPANNING;
}

CULLING_POSITION Frustum::ClassifyBOX(CollisionBOX box)
{
	float planeToCenter = 0.0f;
	float distance = 0.0f;
	MyVector3 direction;
	CULLING_POSITION position = CULLING_POSITION::FRONT;

	for (int iPlane = 0; iPlane < 6; iPlane++)
	{
		direction = box._axis[0] * box._extent[0];
		distance = fabs(_plane[iPlane]._a * direction._x + _plane[iPlane]._b * direction._y + _plane[iPlane]._c * direction._z);
		direction = box._axis[1] * box._extent[1];
		distance += fabs(_plane[iPlane]._a * direction._x + _plane[iPlane]._b * direction._y + _plane[iPlane]._c * direction._z);
		direction = box._axis[2] * box._extent[2];
		distance += fabs(_plane[iPlane]._a * direction._x + _plane[iPlane]._b * direction._y + _plane[iPlane]._c * direction._z);
		
		planeToCenter = _plane[iPlane]._a * box._center._x + _plane[iPlane]._b * box._center._y + _plane[iPlane]._c * box._center._z + _plane[iPlane]._d;

		if (planeToCenter > 0.0f)
		{
			if (planeToCenter < distance)
			{
				position = CULLING_POSITION::SPANNING;
				break;
			}
		}
		else
			if (planeToCenter < 0)
			{
				position = CULLING_POSITION::BACK;

				if (planeToCenter > -distance)
				{
					position = CULLING_POSITION::SPANNING;
				}

				break;
			}
	}
	return position;
}

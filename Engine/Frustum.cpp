#include "pch.h"
#include "Frustum.h"
#include "Shape.h"

void Plane::CreatePlane(DxVector3 v0, DxVector3 v1, DxVector3 v2)
{
	DxVector3 edge0 = v1 - v0;
	DxVector3 edge1 = v2 - v0;
	DxVector3 normal;
	D3DXVec3Cross(&normal, &edge0, &edge1);
	D3DXVec3Normalize(&normal, &normal);
	_a = normal.x;
	_b = normal.y;
	_c = normal.z;
	_d = -D3DXVec3Dot(&normal, &v0);
}

void Plane::CreatePlane(DxVector3 normal, DxVector3 v0)
{
	D3DXVec3Normalize(&normal, &normal);
	_a = normal.x;
	_b = normal.y;
	_c = normal.z;
	_d = -D3DXVec3Dot(&normal, &v0);
}

void Frustum::CreateFrustum(DxMatrix* pView, DxMatrix* pProjection)
{
	DxMatrix view = *(DxMatrix*)pView;
	DxMatrix projection = *(DxMatrix*)pProjection;
	DxMatrix inverseViewProjection = view * projection;
	D3DXMatrixInverse(&inverseViewProjection, nullptr, &inverseViewProjection);

	_frustum[0] = DxVector3{ -1.0f, -1.0f, 0.0f };
	_frustum[1] = DxVector3{ -1.0f, 1.0f, 0.0f };
	_frustum[2] = DxVector3{ 1.0f, 1.0f, 0.0f };
	_frustum[3] = DxVector3{ 1.0f, -1.0f, 0.0f };
	_frustum[4] = DxVector3{ -1.0f, -1.0f, 1.0f };
	_frustum[5] = DxVector3{ -1.0f, 1.0f, 1.0f };
	_frustum[6] = DxVector3{ 1.0f, 1.0f, 1.0f };
	_frustum[7] = DxVector3{ 1.0f, -1.0f, 1.0f };

	for (size_t i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&_frustum[i], &_frustum[i], &inverseViewProjection);
	}

	_plane[0].CreatePlane(*((DxVector3*)&_frustum[1]), *((DxVector3*)&_frustum[5]), *((DxVector3*)&_frustum[0]));
	_plane[1].CreatePlane(*((DxVector3*)&_frustum[3]), *((DxVector3*)&_frustum[6]), *((DxVector3*)&_frustum[2]));
	_plane[2].CreatePlane(*((DxVector3*)&_frustum[5]), *((DxVector3*)&_frustum[2]), *((DxVector3*)&_frustum[6]));
	_plane[3].CreatePlane(*((DxVector3*)&_frustum[0]), *((DxVector3*)&_frustum[7]), *((DxVector3*)&_frustum[3]));
	_plane[4].CreatePlane(*((DxVector3*)&_frustum[2]), *((DxVector3*)&_frustum[1]), *((DxVector3*)&_frustum[0]));
	_plane[5].CreatePlane(*((DxVector3*)&_frustum[5]), *((DxVector3*)&_frustum[6]), *((DxVector3*)&_frustum[4]));
}

CULLING_POSITION Frustum::ClassifyPoint(DxVector3 vector)
{
	for (size_t i = 0; i < 6; i++)
	{
		float distance = _plane[i]._a * vector.x + _plane[i]._b * vector.y + _plane[i]._c * vector.z + _plane[i]._d;

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
		float distance = _plane[i]._a * pSphere->_center.x + _plane[i]._b * pSphere->_center.y + _plane[i]._c * pSphere->_center.z + _plane[i]._d;
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
	DxVector3 direction;
	CULLING_POSITION position = CULLING_POSITION::FRONT;

	for (int iPlane = 0; iPlane < 6; iPlane++)
	{
		direction = box._axis[0] * box._extent[0];
		distance = fabs(_plane[iPlane]._a * direction.x + _plane[iPlane]._b * direction.y + _plane[iPlane]._c * direction.z);
		direction = box._axis[1] * box._extent[1];
		distance += fabs(_plane[iPlane]._a * direction.x + _plane[iPlane]._b * direction.y + _plane[iPlane]._c * direction.z);
		direction = box._axis[2] * box._extent[2];
		distance += fabs(_plane[iPlane]._a * direction.x + _plane[iPlane]._b * direction.y + _plane[iPlane]._c * direction.z);
		
		planeToCenter = _plane[iPlane]._a * box._center.x + _plane[iPlane]._b * box._center.y + _plane[iPlane]._c * box._center.z + _plane[iPlane]._d;

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

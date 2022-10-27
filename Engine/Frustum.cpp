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

HRESULT Frustum::ClassifyPoint(MyVector3 vector)
{
	for (size_t i = 0; i < 6; i++)
	{
		float distance = _plane[i]._a * vector._x + _plane[i]._b * vector._y + _plane[i]._c * vector._z + _plane[i]._d;
		if (distance < 0.0f)
		{
			return E_FAIL;
		}
	}

	return TRUE;
}

HRESULT Frustum::ClassifySphere(Sphere* pSphere)
{
	for (size_t i = 0; i < 6; i++)
	{
		float distance = _plane[i]._a * pSphere->_center._x + _plane[i]._b * pSphere->_center._y + _plane[i]._c * pSphere->_center._z + _plane[i]._d;
		if (distance <= -pSphere->_radius)
		{
			return E_FAIL;
		}
	}

	return TRUE;
}

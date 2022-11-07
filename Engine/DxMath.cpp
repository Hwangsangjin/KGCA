#include "pch.h"
#include "DxMath.h"

//https://docs.microsoft.com/en-us/windows/win32/dxmath/pg-xnamath-migration-d3dx
namespace DX_MATH
{
	const DxVector2 DxVector2::Zero = { 0.f, 0.f };
	const DxVector2 DxVector2::One = { 1.f, 1.f };
	const DxVector2 DxVector2::UnitX = { 1.f, 0.f };
	const DxVector2 DxVector2::UnitY = { 0.f, 1.f };

	const DxVector3 DxVector3::Zero = { 0.f, 0.f, 0.f };
	const DxVector3 DxVector3::One = { 1.f, 1.f, 1.f };
	const DxVector3 DxVector3::UnitX = { 1.f, 0.f, 0.f };
	const DxVector3 DxVector3::UnitY = { 0.f, 1.f, 0.f };
	const DxVector3 DxVector3::UnitZ = { 0.f, 0.f, 1.f };
	const DxVector3 DxVector3::Up = { 0.f, 1.f, 0.f };
	const DxVector3 DxVector3::Down = { 0.f, -1.f, 0.f };
	const DxVector3 DxVector3::Right = { 1.f, 0.f, 0.f };
	const DxVector3 DxVector3::Left = { -1.f, 0.f, 0.f };
	const DxVector3 DxVector3::Forward = { 0.f, 0.f, -1.f };
	const DxVector3 DxVector3::Backward = { 0.f, 0.f, 1.f };

	const DxVector4 DxVector4::Zero = { 0.f, 0.f, 0.f, 0.f };
	const DxVector4 DxVector4::One = { 1.f, 1.f, 1.f, 1.f };
	const DxVector4 DxVector4::UnitX = { 1.f, 0.f, 0.f, 0.f };
	const DxVector4 DxVector4::UnitY = { 0.f, 1.f, 0.f, 0.f };
	const DxVector4 DxVector4::UnitZ = { 0.f, 0.f, 1.f, 0.f };
	const DxVector4 DxVector4::UnitW = { 0.f, 0.f, 0.f, 1.f };

	const DxMatrix DxMatrix::Identity = { 1.f, 0.f, 0.f, 0.f,
									  0.f, 1.f, 0.f, 0.f,
									  0.f, 0.f, 1.f, 0.f,
									  0.f, 0.f, 0.f, 1.f };

	const DxQuaternion DxQuaternion::Identity = { 0.f, 0.f, 0.f, 1.f };


	DxVector2 DxRectangle::Location() const
	{
		return DxVector2(float(x), float(y));
	}

	DxVector2 DxRectangle::Center() const
	{
		return DxVector2(float(x) + float(width / 2.f), float(y) + float(height / 2.f));
	}

	bool DxRectangle::Contains(const DxVector2& point) const
	{
		return (float(x) <= point.x) && (point.x < float(x + width)) && (float(y) <= point.y) && (point.y < float(y + height));
	}

	void DxRectangle::Inflate(long horizAmount, long vertAmount)
	{
		x -= horizAmount;
		y -= vertAmount;
		width += horizAmount;
		height += vertAmount;
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	DxRectangle DxRectangle::Intersect(const DxRectangle& ra, const DxRectangle& rb)
	{
		long righta = ra.x + ra.width;
		long rightb = rb.x + rb.width;

		long bottoma = ra.y + ra.height;
		long bottomb = rb.y + rb.height;

		long maxX = ra.x > rb.x ? ra.x : rb.x;
		long maxY = ra.y > rb.y ? ra.y : rb.y;

		long minRight = righta < rightb ? righta : rightb;
		long minBottom = bottoma < bottomb ? bottoma : bottomb;

		DxRectangle result;

		if ((minRight > maxX) && (minBottom > maxY))
		{
			result.x = maxX;
			result.y = maxY;
			result.width = minRight - maxX;
			result.height = minBottom - maxY;
		}
		else
		{
			result.x = 0;
			result.y = 0;
			result.width = 0;
			result.height = 0;
		}

		return result;
	}

	RECT DxRectangle::Intersect(const RECT& rcta, const RECT& rctb)
	{
		long maxX = rcta.left > rctb.left ? rcta.left : rctb.left;
		long maxY = rcta.top > rctb.top ? rcta.top : rctb.top;

		long minRight = rcta.right < rctb.right ? rcta.right : rctb.right;
		long minBottom = rcta.bottom < rctb.bottom ? rcta.bottom : rctb.bottom;

		RECT result;

		if ((minRight > maxX) && (minBottom > maxY))
		{
			result.left = maxX;
			result.top = maxY;
			result.right = minRight;
			result.bottom = minBottom;
		}
		else
		{
			result.left = 0;
			result.top = 0;
			result.right = 0;
			result.bottom = 0;
		}

		return result;
	}

	DxRectangle DxRectangle::Union(const DxRectangle& ra, const DxRectangle& rb)
	{
		long righta = ra.x + ra.width;
		long rightb = rb.x + rb.width;

		long bottoma = ra.y + ra.height;
		long bottomb = rb.y + rb.height;

		int minX = ra.x < rb.x ? ra.x : rb.x;
		int minY = ra.y < rb.y ? ra.y : rb.y;

		int maxRight = righta > rightb ? righta : rightb;
		int maxBottom = bottoma > bottomb ? bottoma : bottomb;

		DxRectangle result;
		result.x = minX;
		result.y = minY;
		result.width = maxRight - minX;
		result.height = maxBottom - minY;
		return result;
	}

	RECT DxRectangle::Union(const RECT& rcta, const RECT& rctb)
	{
		RECT result;
		result.left = rcta.left < rctb.left ? rcta.left : rctb.left;
		result.top = rcta.top < rctb.top ? rcta.top : rctb.top;
		result.right = rcta.right > rctb.right ? rcta.right : rctb.right;
		result.bottom = rcta.bottom > rctb.bottom ? rcta.bottom : rctb.bottom;
		return result;
	}


	/****************************************************************************
	*
	* DxVector2
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool DxVector2::operator == (const DxVector2& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		return XMVector2Equal(v1, v2);
	}

	bool DxVector2::operator != (const DxVector2& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		return XMVector2NotEqual(v1, v2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	DxVector2& DxVector2::operator+= (const DxVector2& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorAdd(v1, v2);
		XMStoreFloat2(this, X);
		return *this;
	}

	DxVector2& DxVector2::operator-= (const DxVector2& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		XMStoreFloat2(this, X);
		return *this;
	}

	DxVector2& DxVector2::operator*= (const DxVector2& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		XMStoreFloat2(this, X);
		return *this;
	}

	DxVector2& DxVector2::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVectorScale(v1, S);
		XMStoreFloat2(this, X);
		return *this;
	}

	DxVector2& DxVector2::operator/= (float S)
	{
		using namespace DirectX;
		assert(S != 0.0f);
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVectorScale(v1, 1.f / S);
		XMStoreFloat2(this, X);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	DxVector2 operator+ (const DxVector2& V1, const DxVector2& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V1);
		XMVECTOR v2 = XMLoadFloat2(&V2);
		XMVECTOR X = XMVectorAdd(v1, v2);
		DxVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	DxVector2 operator- (const DxVector2& V1, const DxVector2& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V1);
		XMVECTOR v2 = XMLoadFloat2(&V2);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		DxVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	DxVector2 operator* (const DxVector2& V1, const DxVector2& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V1);
		XMVECTOR v2 = XMLoadFloat2(&V2);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		DxVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	DxVector2 operator* (const DxVector2& V, float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		DxVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	DxVector2 operator/ (const DxVector2& V1, const DxVector2& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V1);
		XMVECTOR v2 = XMLoadFloat2(&V2);
		XMVECTOR X = XMVectorDivide(v1, v2);
		DxVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	DxVector2 operator* (float S, const DxVector2& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		DxVector2 R;
		XMStoreFloat2(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Vector operations
	//------------------------------------------------------------------------------

	bool DxVector2::InBounds(const DxVector2& Bounds) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&Bounds);
		return XMVector2InBounds(v1, v2);
	}

	float DxVector2::Length() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVector2Length(v1);
		return XMVectorGetX(X);
	}

	float DxVector2::LengthSquared() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVector2LengthSq(v1);
		return XMVectorGetX(X);
	}

	float DxVector2::Dot(const DxVector2& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR X = XMVector2Dot(v1, v2);
		return XMVectorGetX(X);
	}

	void DxVector2::Cross(const DxVector2& V, DxVector2& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR R = XMVector2Cross(v1, v2);
		XMStoreFloat2(&result, R);
	}

	DxVector2 DxVector2::Cross(const DxVector2& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&V);
		XMVECTOR R = XMVector2Cross(v1, v2);

		DxVector2 result;
		XMStoreFloat2(&result, R);
		return result;
	}

	void DxVector2::Normalize()
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVector2Normalize(v1);
		XMStoreFloat2(this, X);
	}

	void DxVector2::Normalize(DxVector2& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR X = XMVector2Normalize(v1);
		XMStoreFloat2(&result, X);
	}

	void DxVector2::Clamp(const DxVector2& vmin, const DxVector2& vmax)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&vmin);
		XMVECTOR v3 = XMLoadFloat2(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat2(this, X);
	}

	void DxVector2::Clamp(const DxVector2& vmin, const DxVector2& vmax, DxVector2& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(this);
		XMVECTOR v2 = XMLoadFloat2(&vmin);
		XMVECTOR v3 = XMLoadFloat2(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat2(&result, X);
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	float DxVector2::Distance(const DxVector2& v1, const DxVector2& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector2Length(V);
		return XMVectorGetX(X);
	}

	float DxVector2::DistanceSquared(const DxVector2& v1, const DxVector2& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector2LengthSq(V);
		return XMVectorGetX(X);
	}

	void DxVector2::Min(const DxVector2& v1, const DxVector2& v2, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Min(const DxVector2& v1, const DxVector2& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::Max(const DxVector2& v1, const DxVector2& v2, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Max(const DxVector2& v1, const DxVector2& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::Lerp(const DxVector2& v1, const DxVector2& v2, float t, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Lerp(const DxVector2& v1, const DxVector2& v2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::SmoothStep(const DxVector2& v1, const DxVector2& v2, float t, DxVector2& result)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t * (3.f - 2.f * t);
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::SmoothStep(const DxVector2& v1, const DxVector2& v2, float t)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t * (3.f - 2.f * t);
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::Barycentric(const DxVector2& v1, const DxVector2& v2, const DxVector2& v3, float f, float g, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR x3 = XMLoadFloat2(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Barycentric(const DxVector2& v1, const DxVector2& v2, const DxVector2& v3, float f, float g)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR x3 = XMLoadFloat2(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::CatmullRom(const DxVector2& v1, const DxVector2& v2, const DxVector2& v3, const DxVector2& v4, float t, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR x3 = XMLoadFloat2(&v3);
		XMVECTOR x4 = XMLoadFloat2(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::CatmullRom(const DxVector2& v1, const DxVector2& v2, const DxVector2& v3, const DxVector2& v4, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&v2);
		XMVECTOR x3 = XMLoadFloat2(&v3);
		XMVECTOR x4 = XMLoadFloat2(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::Hermite(const DxVector2& v1, const DxVector2& t1, const DxVector2& v2, const DxVector2& t2, float t, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&t1);
		XMVECTOR x3 = XMLoadFloat2(&v2);
		XMVECTOR x4 = XMLoadFloat2(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Hermite(const DxVector2& v1, const DxVector2& t1, const DxVector2& v2, const DxVector2& t2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat2(&v1);
		XMVECTOR x2 = XMLoadFloat2(&t1);
		XMVECTOR x3 = XMLoadFloat2(&v2);
		XMVECTOR x4 = XMLoadFloat2(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::Reflect(const DxVector2& ivec, const DxVector2& nvec, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat2(&ivec);
		XMVECTOR n = XMLoadFloat2(&nvec);
		XMVECTOR X = XMVector2Reflect(i, n);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Reflect(const DxVector2& ivec, const DxVector2& nvec)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat2(&ivec);
		XMVECTOR n = XMLoadFloat2(&nvec);
		XMVECTOR X = XMVector2Reflect(i, n);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::Refract(const DxVector2& ivec, const DxVector2& nvec, float refractionIndex, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat2(&ivec);
		XMVECTOR n = XMLoadFloat2(&nvec);
		XMVECTOR X = XMVector2Refract(i, n, refractionIndex);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Refract(const DxVector2& ivec, const DxVector2& nvec, float refractionIndex)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat2(&ivec);
		XMVECTOR n = XMLoadFloat2(&nvec);
		XMVECTOR X = XMVector2Refract(i, n, refractionIndex);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::Transform(const DxVector2& v, const DxQuaternion& quat, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMVECTOR q = XMLoadFloat4((DirectX::XMFLOAT4*)&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Transform(const DxVector2& v, const DxQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMVECTOR q = XMLoadFloat4((DirectX::XMFLOAT4*)&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	void DxVector2::Transform(const DxVector2& v, const DxMatrix& m, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector2TransformCoord(v1, M);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::Transform(const DxVector2& v, const DxMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector2TransformCoord(v1, M);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void DxVector2::Transform(const DxVector2* varray, size_t count, const DxMatrix& m, DxVector2* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVector2TransformCoordStream(resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M);
	}

	void DxVector2::Transform(const DxVector2& v, const DxMatrix& m, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector2Transform(v1, M);
		XMStoreFloat4((DirectX::XMFLOAT4*)&result, X);
	}

	_Use_decl_annotations_
		void DxVector2::Transform(const DxVector2* varray, size_t count, const DxMatrix& m, DxVector4* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVector2TransformStream((DirectX::XMFLOAT4*)resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT2), count, M);
	}

	void DxVector2::TransformNormal(const DxVector2& v, const DxMatrix& m, DxVector2& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector2TransformNormal(v1, M);
		XMStoreFloat2(&result, X);
	}

	DxVector2 DxVector2::TransformNormal(const DxVector2& v, const DxMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector2TransformNormal(v1, M);

		DxVector2 result;
		XMStoreFloat2(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void DxVector2::TransformNormal(const DxVector2* varray, size_t count, const DxMatrix& m, DxVector2* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((DirectX::XMFLOAT4X4*)&m);
		XMVector2TransformNormalStream(resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M);
	}


	/****************************************************************************
	*
	* DxVector3
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------
	bool DxVector3::operator == (const DxVector3& V) const
	{
		DirectX::XMVECTOR v1 = XMLoadFloat3(this);
		DirectX::XMVECTOR v2 = XMLoadFloat3(&V);
		return DirectX::XMVector3Equal(v1, v2);
	}

	bool DxVector3::operator != (const DxVector3& V) const
	{
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		return XMVector3NotEqual(v1, v2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	DxVector3& DxVector3::operator+= (const DxVector3& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorAdd(v1, v2);
		XMStoreFloat3(this, X);
		return *this;
	}

	DxVector3& DxVector3::operator-= (const DxVector3& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		XMStoreFloat3(this, X);
		return *this;
	}

	DxVector3& DxVector3::operator*= (const DxVector3& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		XMStoreFloat3(this, X);
		return *this;
	}

	DxVector3& DxVector3::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVectorScale(v1, S);
		XMStoreFloat3(this, X);
		return *this;
	}

	DxVector3& DxVector3::operator/= (float S)
	{
		using namespace DirectX;
		assert(S != 0.0f);
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVectorScale(v1, 1.f / S);
		XMStoreFloat3(this, X);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	DxVector3 DxVector3::operator- () const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVectorNegate(v1);
		DxVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	DxVector3 operator+ (const DxVector3& V1, const DxVector3& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V1);
		XMVECTOR v2 = XMLoadFloat3(&V2);
		XMVECTOR X = XMVectorAdd(v1, v2);
		DxVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	DxVector3 operator- (const DxVector3& V1, const DxVector3& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V1);
		XMVECTOR v2 = XMLoadFloat3(&V2);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		DxVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	DxVector3 operator* (const DxVector3& V1, const DxVector3& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V1);
		XMVECTOR v2 = XMLoadFloat3(&V2);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		DxVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	DxVector3 operator* (const DxVector3& V, float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		DxVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	DxVector3 operator/ (const DxVector3& V1, const DxVector3& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V1);
		XMVECTOR v2 = XMLoadFloat3(&V2);
		XMVECTOR X = XMVectorDivide(v1, v2);
		DxVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	DxVector3 operator* (float S, const DxVector3& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		DxVector3 R;
		XMStoreFloat3(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Vector operations
	//------------------------------------------------------------------------------

	bool DxVector3::InBounds(const DxVector3& Bounds) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&Bounds);
		return XMVector3InBounds(v1, v2);
	}

	float DxVector3::Length() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVector3Length(v1);
		return XMVectorGetX(X);
	}

	float DxVector3::LengthSquared() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVector3LengthSq(v1);
		return XMVectorGetX(X);
	}

	float DxVector3::Dot(const DxVector3& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR X = XMVector3Dot(v1, v2);
		return XMVectorGetX(X);
	}

	void DxVector3::Cross(const DxVector3& V, DxVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR R = XMVector3Cross(v1, v2);
		XMStoreFloat3(&result, R);
	}

	DxVector3 DxVector3::Cross(const DxVector3& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&V);
		XMVECTOR R = XMVector3Cross(v1, v2);

		DxVector3 result;
		XMStoreFloat3(&result, R);
		return result;
	}

	void DxVector3::Normalize()
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVector3Normalize(v1);
		XMStoreFloat3(this, X);
	}

	void DxVector3::Normalize(DxVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR X = XMVector3Normalize(v1);
		XMStoreFloat3(&result, X);
	}

	void DxVector3::Clamp(const DxVector3& vmin, const DxVector3& vmax)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&vmin);
		XMVECTOR v3 = XMLoadFloat3(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat3(this, X);
	}

	void DxVector3::Clamp(const DxVector3& vmin, const DxVector3& vmax, DxVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(this);
		XMVECTOR v2 = XMLoadFloat3(&vmin);
		XMVECTOR v3 = XMLoadFloat3(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat3(&result, X);
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------
	float DxVector3::Distance(const DxVector3& v1, const DxVector3& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector3Length(V);
		return XMVectorGetX(X);
	}

	float DxVector3::DistanceSquared(const DxVector3& v1, const DxVector3& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector3LengthSq(V);
		return XMVectorGetX(X);
	}

	void DxVector3::Min(const DxVector3& v1, const DxVector3& v2, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Min(const DxVector3& v1, const DxVector3& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::Max(const DxVector3& v1, const DxVector3& v2, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Max(const DxVector3& v1, const DxVector3& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::Lerp(const DxVector3& v1, const DxVector3& v2, float t, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Lerp(const DxVector3& v1, const DxVector3& v2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::SmoothStep(const DxVector3& v1, const DxVector3& v2, float t, DxVector3& result)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t * (3.f - 2.f * t);
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::SmoothStep(const DxVector3& v1, const DxVector3& v2, float t)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t * (3.f - 2.f * t);
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::Barycentric(const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, float f, float g, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR x3 = XMLoadFloat3(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Barycentric(const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, float f, float g)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR x3 = XMLoadFloat3(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::CatmullRom(const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, const DxVector3& v4, float t, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR x3 = XMLoadFloat3(&v3);
		XMVECTOR x4 = XMLoadFloat3(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::CatmullRom(const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, const DxVector3& v4, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&v2);
		XMVECTOR x3 = XMLoadFloat3(&v3);
		XMVECTOR x4 = XMLoadFloat3(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::Hermite(const DxVector3& v1, const DxVector3& t1, const DxVector3& v2, const DxVector3& t2, float t, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&t1);
		XMVECTOR x3 = XMLoadFloat3(&v2);
		XMVECTOR x4 = XMLoadFloat3(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Hermite(const DxVector3& v1, const DxVector3& t1, const DxVector3& v2, const DxVector3& t2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat3(&v1);
		XMVECTOR x2 = XMLoadFloat3(&t1);
		XMVECTOR x3 = XMLoadFloat3(&v2);
		XMVECTOR x4 = XMLoadFloat3(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::Reflect(const DxVector3& ivec, const DxVector3& nvec, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat3(&ivec);
		XMVECTOR n = XMLoadFloat3(&nvec);
		XMVECTOR X = XMVector3Reflect(i, n);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Reflect(const DxVector3& ivec, const DxVector3& nvec)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat3(&ivec);
		XMVECTOR n = XMLoadFloat3(&nvec);
		XMVECTOR X = XMVector3Reflect(i, n);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::Refract(const DxVector3& ivec, const DxVector3& nvec, float refractionIndex, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat3(&ivec);
		XMVECTOR n = XMLoadFloat3(&nvec);
		XMVECTOR X = XMVector3Refract(i, n, refractionIndex);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Refract(const DxVector3& ivec, const DxVector3& nvec, float refractionIndex)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat3(&ivec);
		XMVECTOR n = XMLoadFloat3(&nvec);
		XMVECTOR X = XMVector3Refract(i, n, refractionIndex);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::Transform(const DxVector3& v, const DxQuaternion& quat, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMVECTOR q = XMLoadFloat4((XMFLOAT4*)&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Transform(const DxVector3& v, const DxQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMVECTOR q = XMLoadFloat4((XMFLOAT4*)&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	void DxVector3::Transform(const DxVector3& v, const DxMatrix& m, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3TransformCoord(v1, M);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::Transform(const DxVector3& v, const DxMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3TransformCoord(v1, M);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void DxVector3::Transform(const DxVector3* varray, size_t count, const DxMatrix& m, DxVector3* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVector3TransformCoordStream(resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M);
	}

	void DxVector3::Transform(const DxVector3& v, const DxMatrix& m, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3Transform(v1, M);
		XMStoreFloat4(&result, X);
	}

	_Use_decl_annotations_
		void DxVector3::Transform(const DxVector3* varray, size_t count, const DxMatrix& m, DxVector4* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVector3TransformStream((XMFLOAT4*)resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT3), count, M);
	}

	void DxVector3::TransformNormal(const DxVector3& v, const DxMatrix& m, DxVector3& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3TransformNormal(v1, M);
		XMStoreFloat3(&result, X);
	}

	DxVector3 DxVector3::TransformNormal(const DxVector3& v, const DxMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector3TransformNormal(v1, M);

		DxVector3 result;
		XMStoreFloat3(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void DxVector3::TransformNormal(const DxVector3* varray, size_t count, const DxMatrix& m, DxVector3* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVector3TransformNormalStream(resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M);
	}


	///****************************************************************************
	//*
	//* DxVector4
	//*
	//****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool DxVector4::operator == (const DxVector4& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		return XMVector4Equal(v1, v2);
	}

	bool DxVector4::operator != (const DxVector4& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		return XMVector4NotEqual(v1, v2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	DxVector4& DxVector4::operator+= (const DxVector4& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorAdd(v1, v2);
		XMStoreFloat4(this, X);
		return *this;
	}

	DxVector4& DxVector4::operator-= (const DxVector4& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		XMStoreFloat4(this, X);
		return *this;
	}

	DxVector4& DxVector4::operator*= (const DxVector4& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		XMStoreFloat4(this, X);
		return *this;
	}

	DxVector4& DxVector4::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVectorScale(v1, S);
		XMStoreFloat4(this, X);
		return *this;
	}

	DxVector4& DxVector4::operator/= (float S)
	{
		using namespace DirectX;
		assert(S != 0.0f);
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVectorScale(v1, 1.f / S);
		XMStoreFloat4(this, X);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	DxVector4 DxVector4::operator- () const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVectorNegate(v1);
		DxVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	DxVector4 operator+ (const DxVector4& V1, const DxVector4& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V1);
		XMVECTOR v2 = XMLoadFloat4(&V2);
		XMVECTOR X = XMVectorAdd(v1, v2);
		DxVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	DxVector4 operator- (const DxVector4& V1, const DxVector4& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V1);
		XMVECTOR v2 = XMLoadFloat4(&V2);
		XMVECTOR X = XMVectorSubtract(v1, v2);
		DxVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	DxVector4 operator* (const DxVector4& V1, const DxVector4& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V1);
		XMVECTOR v2 = XMLoadFloat4(&V2);
		XMVECTOR X = XMVectorMultiply(v1, v2);
		DxVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	DxVector4 operator* (const DxVector4& V, float S)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		DxVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	DxVector4 operator/ (const DxVector4& V1, const DxVector4& V2)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V1);
		XMVECTOR v2 = XMLoadFloat4(&V2);
		XMVECTOR X = XMVectorDivide(v1, v2);
		DxVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	DxVector4 operator* (float S, const DxVector4& V)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&V);
		XMVECTOR X = XMVectorScale(v1, S);
		DxVector4 R;
		XMStoreFloat4(&R, X);
		return R;
	}

	//------------------------------------------------------------------------------
	// Vector operations
	//------------------------------------------------------------------------------

	bool DxVector4::InBounds(const DxVector4& Bounds) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&Bounds);
		return XMVector4InBounds(v1, v2);
	}

	float DxVector4::Length() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVector4Length(v1);
		return XMVectorGetX(X);
	}

	float DxVector4::LengthSquared() const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVector4LengthSq(v1);
		return XMVectorGetX(X);
	}

	float DxVector4::Dot(const DxVector4& V) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&V);
		XMVECTOR X = XMVector4Dot(v1, v2);
		return XMVectorGetX(X);
	}

	void DxVector4::Cross(const DxVector4& v1, const DxVector4& v2, DxVector4& result) const
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(this);
		XMVECTOR x2 = XMLoadFloat4(&v1);
		XMVECTOR x3 = XMLoadFloat4(&v2);
		XMVECTOR R = XMVector4Cross(x1, x2, x3);
		XMStoreFloat4(&result, R);
	}

	DxVector4 DxVector4::Cross(const DxVector4& v1, const DxVector4& v2) const
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(this);
		XMVECTOR x2 = XMLoadFloat4(&v1);
		XMVECTOR x3 = XMLoadFloat4(&v2);
		XMVECTOR R = XMVector4Cross(x1, x2, x3);

		DxVector4 result;
		XMStoreFloat4(&result, R);
		return result;
	}

	void DxVector4::Normalize()
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVector4Normalize(v1);
		XMStoreFloat4(this, X);
	}

	void DxVector4::Normalize(DxVector4& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR X = XMVector4Normalize(v1);
		XMStoreFloat4(&result, X);
	}

	void DxVector4::Clamp(const DxVector4& vmin, const DxVector4& vmax)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&vmin);
		XMVECTOR v3 = XMLoadFloat4(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat4(this, X);
	}

	void DxVector4::Clamp(const DxVector4& vmin, const DxVector4& vmax, DxVector4& result) const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(this);
		XMVECTOR v2 = XMLoadFloat4(&vmin);
		XMVECTOR v3 = XMLoadFloat4(&vmax);
		XMVECTOR X = XMVectorClamp(v1, v2, v3);
		XMStoreFloat4(&result, X);
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	float DxVector4::Distance(const DxVector4& v1, const DxVector4& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector4Length(V);
		return XMVectorGetX(X);
	}

	float DxVector4::DistanceSquared(const DxVector4& v1, const DxVector4& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR V = XMVectorSubtract(x2, x1);
		XMVECTOR X = XMVector4LengthSq(V);
		return XMVectorGetX(X);
	}

	void DxVector4::Min(const DxVector4& v1, const DxVector4& v2, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Min(const DxVector4& v1, const DxVector4& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorMin(x1, x2);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Max(const DxVector4& v1, const DxVector4& v2, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Max(const DxVector4& v1, const DxVector4& v2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorMax(x1, x2);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Lerp(const DxVector4& v1, const DxVector4& v2, float t, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Lerp(const DxVector4& v1, const DxVector4& v2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::SmoothStep(const DxVector4& v1, const DxVector4& v2, float t, DxVector4& result)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t * (3.f - 2.f * t);
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::SmoothStep(const DxVector4& v1, const DxVector4& v2, float t)
	{
		using namespace DirectX;
		t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
		t = t * t * (3.f - 2.f * t);
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR X = XMVectorLerp(x1, x2, t);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Barycentric(const DxVector4& v1, const DxVector4& v2, const DxVector4& v3, float f, float g, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR x3 = XMLoadFloat4(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Barycentric(const DxVector4& v1, const DxVector4& v2, const DxVector4& v3, float f, float g)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR x3 = XMLoadFloat4(&v3);
		XMVECTOR X = XMVectorBaryCentric(x1, x2, x3, f, g);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::CatmullRom(const DxVector4& v1, const DxVector4& v2, const DxVector4& v3, const DxVector4& v4, float t, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR x3 = XMLoadFloat4(&v3);
		XMVECTOR x4 = XMLoadFloat4(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::CatmullRom(const DxVector4& v1, const DxVector4& v2, const DxVector4& v3, const DxVector4& v4, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&v2);
		XMVECTOR x3 = XMLoadFloat4(&v3);
		XMVECTOR x4 = XMLoadFloat4(&v4);
		XMVECTOR X = XMVectorCatmullRom(x1, x2, x3, x4, t);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Hermite(const DxVector4& v1, const DxVector4& t1, const DxVector4& v2, const DxVector4& t2, float t, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&t1);
		XMVECTOR x3 = XMLoadFloat4(&v2);
		XMVECTOR x4 = XMLoadFloat4(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Hermite(const DxVector4& v1, const DxVector4& t1, const DxVector4& v2, const DxVector4& t2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(&v1);
		XMVECTOR x2 = XMLoadFloat4(&t1);
		XMVECTOR x3 = XMLoadFloat4(&v2);
		XMVECTOR x4 = XMLoadFloat4(&t2);
		XMVECTOR X = XMVectorHermite(x1, x2, x3, x4, t);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Reflect(const DxVector4& ivec, const DxVector4& nvec, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat4(&ivec);
		XMVECTOR n = XMLoadFloat4(&nvec);
		XMVECTOR X = XMVector4Reflect(i, n);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Reflect(const DxVector4& ivec, const DxVector4& nvec)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat4(&ivec);
		XMVECTOR n = XMLoadFloat4(&nvec);
		XMVECTOR X = XMVector4Reflect(i, n);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Refract(const DxVector4& ivec, const DxVector4& nvec, float refractionIndex, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat4(&ivec);
		XMVECTOR n = XMLoadFloat4(&nvec);
		XMVECTOR X = XMVector4Refract(i, n, refractionIndex);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Refract(const DxVector4& ivec, const DxVector4& nvec, float refractionIndex)
	{
		using namespace DirectX;
		XMVECTOR i = XMLoadFloat4(&ivec);
		XMVECTOR n = XMLoadFloat4(&nvec);
		XMVECTOR X = XMVector4Refract(i, n, refractionIndex);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Transform(const DxVector2& v, const DxQuaternion& quat, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Transform(const DxVector2& v, const DxQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat2(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Transform(const DxVector3& v, const DxQuaternion& quat, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Transform(const DxVector3& v, const DxQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(g_XMIdentityR3, X, g_XMSelect1110); // result.w = 1.f

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Transform(const DxVector4& v, const DxQuaternion& quat, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(v1, X, g_XMSelect1110); // result.w = v.w
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Transform(const DxVector4& v, const DxQuaternion& quat)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&v);
		XMVECTOR q = XMLoadFloat4(&quat);
		XMVECTOR X = XMVector3Rotate(v1, q);
		X = XMVectorSelect(v1, X, g_XMSelect1110); // result.w = v.w

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	void DxVector4::Transform(const DxVector4& v, const DxMatrix& m, DxVector4& result)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector4Transform(v1, M);
		XMStoreFloat4(&result, X);
	}

	DxVector4 DxVector4::Transform(const DxVector4& v, const DxMatrix& m)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(&v);
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVECTOR X = XMVector4Transform(v1, M);

		DxVector4 result;
		XMStoreFloat4(&result, X);
		return result;
	}

	_Use_decl_annotations_
		void DxVector4::Transform(const DxVector4* varray, size_t count, const DxMatrix& m, DxVector4* resultArray)
	{
		using namespace DirectX;
		XMMATRIX M = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMVector4TransformStream(resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT4), count, M);
	}


	/****************************************************************************
	*
	* DxMatrix
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool DxMatrix::operator == (const DxMatrix& M) const
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		return (XMVector4Equal(x1, y1)
			&& XMVector4Equal(x2, y2)
			&& XMVector4Equal(x3, y3)
			&& XMVector4Equal(x4, y4)) != 0;
	}

	bool DxMatrix::operator != (const DxMatrix& M) const
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		return (XMVector4NotEqual(x1, y1)
			|| XMVector4NotEqual(x2, y2)
			|| XMVector4NotEqual(x3, y3)
			|| XMVector4NotEqual(x4, y4)) != 0;
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	DxMatrix::DxMatrix(const XMFLOAT3X3& M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
	}

	DxMatrix::DxMatrix(const XMFLOAT4X3& M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
	}

	DxMatrix& DxMatrix::operator= (const XMFLOAT3X3& M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = 0.f;   _42 = 0.f;   _43 = 0.f;   _44 = 1.f;
		return *this;
	}

	DxMatrix& DxMatrix::operator= (const XMFLOAT4X3& M)
	{
		_11 = M._11; _12 = M._12; _13 = M._13; _14 = 0.f;
		_21 = M._21; _22 = M._22; _23 = M._23; _24 = 0.f;
		_31 = M._31; _32 = M._32; _33 = M._33; _34 = 0.f;
		_41 = M._41; _42 = M._42; _43 = M._43; _44 = 1.f;
		return *this;
	}

	DxMatrix& DxMatrix::operator+= (const DxMatrix& M)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	DxMatrix& DxMatrix::operator-= (const DxMatrix& M)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	DxMatrix& DxMatrix::operator*= (const DxMatrix& M)
	{
		using namespace DirectX;
		XMMATRIX M1 = XMLoadFloat4x4(this);
		XMMATRIX M2 = XMLoadFloat4x4((XMFLOAT4X4*)&m);
		XMMATRIX X = XMMatrixMultiply(M1, M2);
		XMStoreFloat4x4(this, X);
		return *this;
	}

	DxMatrix& DxMatrix::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		x1 = XMVectorScale(x1, S);
		x2 = XMVectorScale(x2, S);
		x3 = XMVectorScale(x3, S);
		x4 = XMVectorScale(x4, S);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	DxMatrix& DxMatrix::operator/= (float S)
	{
		using namespace DirectX;
		assert(S != 0.f);
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		float rs = 1.f / S;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	DxMatrix& DxMatrix::operator/= (const DxMatrix& M)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	DxMatrix DxMatrix::operator- () const
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		v1 = XMVectorNegate(v1);
		v2 = XMVectorNegate(v2);
		v3 = XMVectorNegate(v3);
		v4 = XMVectorNegate(v4);

		DxMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), v1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), v2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), v3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), v4);
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	DxMatrix operator+ (const DxMatrix& M1, const DxMatrix& M2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		DxMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	DxMatrix operator- (const DxMatrix& M1, const DxMatrix& M2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		DxMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	DxMatrix operator* (const DxMatrix& M1, const DxMatrix& M2)
	{
		using namespace DirectX;
		XMMATRIX m1 = XMLoadFloat4x4(&M1);
		XMMATRIX m2 = XMLoadFloat4x4((XMFLOAT4X4*)&M2);
		XMMATRIX X = XMMatrixMultiply(m1, m2);

		DxMatrix R;
		XMStoreFloat4x4(&R, X);
		return R;
	}

	DxMatrix operator* (const DxMatrix& M, float S)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorScale(x1, S);
		x2 = XMVectorScale(x2, S);
		x3 = XMVectorScale(x3, S);
		x4 = XMVectorScale(x4, S);

		DxMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	DxMatrix operator/ (const DxMatrix& M, float S)
	{
		using namespace DirectX;
		assert(S != 0.f);

		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		float rs = 1.f / S;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		DxMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	DxMatrix operator/ (const DxMatrix& M1, const DxMatrix& M2)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		DxMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	DxMatrix operator* (float S, const DxMatrix& M)
	{
		using namespace DirectX;

		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M._41));

		x1 = XMVectorScale(x1, S);
		x2 = XMVectorScale(x2, S);
		x3 = XMVectorScale(x3, S);
		x4 = XMVectorScale(x4, S);

		DxMatrix R;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&R._41), x4);
		return R;
	}

	//------------------------------------------------------------------------------
	// DxMatrix operations
	//------------------------------------------------------------------------------

	bool DxMatrix::Decompose(DxVector3& scale, DxQuaternion& rotation, DxVector3& translation)
	{
		using namespace DirectX;

		XMVECTOR s, r, t;

		if (!XMMatrixDecompose(&s, &r, &t, *(XMMATRIX*)this))
			return false;

		XMStoreFloat3(&scale, s);
		XMStoreFloat4(&rotation, r);
		XMStoreFloat3(&translation, t);

		return true;
	}

	DxMatrix DxMatrix::Transpose() const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixTranspose(M));
		return R;
	}

	void DxMatrix::Transpose(DxMatrix& result) const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		XMStoreFloat4x4(&result, XMMatrixTranspose(M));
	}

	DxMatrix DxMatrix::Invert() const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		DxMatrix R;
		XMVECTOR det;
		XMStoreFloat4x4(&R, XMMatrixInverse(&det, M));
		return R;
	}

	void DxMatrix::Invert(DxMatrix& result) const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		XMVECTOR det;
		XMStoreFloat4x4(&result, XMMatrixInverse(&det, M));
	}

	float DxMatrix::Determinant() const
	{
		using namespace DirectX;
		FXMMATRIX M = XMLoadFloat4x4(this);
		return XMVectorGetX(XMMatrixDeterminant(M));
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	_Use_decl_annotations_
		DxMatrix DxMatrix::CreateBillboard(const DxVector3& object, const DxVector3& cameraPosition, const DxVector3& cameraUp, const DxVector3* cameraForward)
	{
		using namespace DirectX;
		XMVECTOR O = XMLoadFloat3(&object);
		XMVECTOR C = XMLoadFloat3(&cameraPosition);
		XMVECTOR Z = XMVectorSubtract(O, C);

		XMVECTOR N = XMVector3LengthSq(Z);
		if (XMVector3Less(N, g_XMEpsilon))
		{
			if (cameraForward)
			{
				XMVECTOR F = XMLoadFloat3(cameraForward);
				Z = XMVectorNegate(F);
			}
			else
				Z = g_XMNegIdentityR2;
		}
		else
		{
			Z = XMVector3Normalize(Z);
		}

		XMVECTOR up = XMLoadFloat3(&cameraUp);
		XMVECTOR X = XMVector3Cross(up, Z);
		X = XMVector3Normalize(X);

		XMVECTOR Y = XMVector3Cross(Z, X);

		XMMATRIX M;
		M.r[0] = X;
		M.r[1] = Y;
		M.r[2] = Z;
		M.r[3] = XMVectorSetW(O, 1.f);

		DxMatrix R;
		XMStoreFloat4x4(&R, M);
		return R;
	}

	_Use_decl_annotations_
		DxMatrix DxMatrix::CreateConstrainedBillboard(const DxVector3& object, const DxVector3& cameraPosition, const DxVector3& rotateAxis,
			const DxVector3* cameraForward, const DxVector3* objectForward)
	{
		using namespace DirectX;

		static const XMVECTORF32 s_minAngle = { { { 0.99825467075f, 0.99825467075f, 0.99825467075f, 0.99825467075f } } }; // 1.0 - XMConvertToRadians( 0.1f );

		XMVECTOR O = XMLoadFloat3(&object);
		XMVECTOR C = XMLoadFloat3(&cameraPosition);
		XMVECTOR faceDir = XMVectorSubtract(O, C);

		XMVECTOR N = XMVector3LengthSq(faceDir);
		if (XMVector3Less(N, g_XMEpsilon))
		{
			if (cameraForward)
			{
				XMVECTOR F = XMLoadFloat3(cameraForward);
				faceDir = XMVectorNegate(F);
			}
			else
				faceDir = g_XMNegIdentityR2;
		}
		else
		{
			faceDir = XMVector3Normalize(faceDir);
		}

		XMVECTOR Y = XMLoadFloat3(&rotateAxis);
		XMVECTOR X, Z;

		XMVECTOR dot = XMVectorAbs(XMVector3Dot(Y, faceDir));
		if (XMVector3Greater(dot, s_minAngle))
		{
			if (objectForward)
			{
				Z = XMLoadFloat3(objectForward);
				dot = XMVectorAbs(XMVector3Dot(Y, Z));
				if (XMVector3Greater(dot, s_minAngle))
				{
					dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
					Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
				}
			}
			else
			{
				dot = XMVectorAbs(XMVector3Dot(Y, g_XMNegIdentityR2));
				Z = (XMVector3Greater(dot, s_minAngle)) ? g_XMIdentityR0 : g_XMNegIdentityR2;
			}

			X = XMVector3Cross(Y, Z);
			X = XMVector3Normalize(X);

			Z = XMVector3Cross(X, Y);
			Z = XMVector3Normalize(Z);
		}
		else
		{
			X = XMVector3Cross(Y, faceDir);
			X = XMVector3Normalize(X);

			Z = XMVector3Cross(X, Y);
			Z = XMVector3Normalize(Z);
		}

		XMMATRIX M;
		M.r[0] = X;
		M.r[1] = Y;
		M.r[2] = Z;
		M.r[3] = XMVectorSetW(O, 1.f);

		DxMatrix R;
		XMStoreFloat4x4(&R, M);
		return R;
	}

	DxMatrix DxMatrix::CreateTranslation(const DxVector3& position)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixTranslation(position.x, position.y, position.z));
		return R;
	}

	DxMatrix DxMatrix::CreateTranslation(float x, float y, float z)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixTranslation(x, y, z));
		return R;
	}

	DxMatrix DxMatrix::CreateScale(const DxVector3& scales)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixScaling(scales.x, scales.y, scales.z));
		return R;
	}

	DxMatrix DxMatrix::CreateScale(float xs, float ys, float zs)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixScaling(xs, ys, zs));
		return R;
	}

	DxMatrix DxMatrix::CreateScale(float scale)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixScaling(scale, scale, scale));
		return R;
	}

	DxMatrix DxMatrix::CreateRotationX(float radians)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixRotationX(radians));
		return R;
	}

	DxMatrix DxMatrix::CreateRotationY(float radians)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixRotationY(radians));
		return R;
	}

	DxMatrix DxMatrix::CreateRotationZ(float radians)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixRotationZ(radians));
		return R;
	}

	DxMatrix DxMatrix::CreateFromAxisAngle(const DxVector3& axis, float angle)
	{
		using namespace DirectX;
		DxMatrix R;
		XMVECTOR a = XMLoadFloat3(&axis);
		XMStoreFloat4x4(&R, XMMatrixRotationAxis(a, angle));
		return R;
	}

	DxMatrix DxMatrix::CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane));
		return R;
	}

	DxMatrix DxMatrix::CreatePerspective(float width, float height, float nearPlane, float farPlane)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixPerspectiveLH(width, height, nearPlane, farPlane));
		return R;
	}

	DxMatrix DxMatrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixPerspectiveOffCenterLH(left, right, bottom, top, nearPlane, farPlane));
		return R;
	}

	DxMatrix DxMatrix::CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixOrthographicLH(width, height, zNearPlane, zFarPlane));
		return R;
	}

	DxMatrix DxMatrix::CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixOrthographicOffCenterLH(left, right, bottom, top, zNearPlane, zFarPlane));
		return R;
	}

	DxMatrix DxMatrix::CreateLookAt(const DxVector3& eye, const DxVector3& target, const DxVector3& up)
	{
		using namespace DirectX;
		DxMatrix R;
		XMVECTOR eyev = XMLoadFloat3(&eye);
		XMVECTOR targetv = XMLoadFloat3(&target);
		XMVECTOR upv = XMLoadFloat3(&up);
		XMStoreFloat4x4(&R, XMMatrixLookAtLH(eyev, targetv, upv));
		return R;
	}

	DxMatrix DxMatrix::CreateWorld(const DxVector3& position, const DxVector3& forward, const DxVector3& up)
	{
		using namespace DirectX;
		XMVECTOR zaxis = XMVector3Normalize(XMVectorNegate(XMLoadFloat3(&forward)));
		XMVECTOR yaxis = XMLoadFloat3(&up);
		XMVECTOR xaxis = XMVector3Normalize(XMVector3Cross(yaxis, zaxis));
		yaxis = XMVector3Cross(zaxis, xaxis);

		DxMatrix R;
		XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._11), xaxis);
		XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._21), yaxis);
		XMStoreFloat3(reinterpret_cast<XMFLOAT3*>(&R._31), zaxis);
		R._14 = R._24 = R._34 = 0.f;
		R._41 = position.x; R._42 = position.y; R._43 = position.z;
		R._44 = 1.f;
		return R;
	}

	DxMatrix DxMatrix::CreateFromQuaternion(const DxQuaternion& rotation)
	{
		using namespace DirectX;
		DxMatrix R;
		XMVECTOR quatv = XMLoadFloat4(&rotation);
		XMStoreFloat4x4(&R, XMMatrixRotationQuaternion(quatv));
		return R;
	}

	DxMatrix DxMatrix::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		using namespace DirectX;
		DxMatrix R;
		XMStoreFloat4x4(&R, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
		return R;
	}

	DxMatrix DxMatrix::CreateShadow(const DxVector3& lightDir, const DxPlane& plane)
	{
		using namespace DirectX;
		DxMatrix R;
		XMVECTOR light = XMLoadFloat3(&lightDir);
		XMVECTOR planev = XMLoadFloat4(&plane);
		XMStoreFloat4x4(&R, XMMatrixShadow(planev, light));
		return R;
	}

	DxMatrix DxMatrix::CreateReflection(const DxPlane& plane)
	{
		using namespace DirectX;
		DxMatrix R;
		XMVECTOR planev = XMLoadFloat4(&plane);
		XMStoreFloat4x4(&R, XMMatrixReflect(planev));
		return R;
	}

	void DxMatrix::Lerp(const DxMatrix& M1, const DxMatrix& M2, float t, DxMatrix& result)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorLerp(x1, y1, t);
		x2 = XMVectorLerp(x2, y2, t);
		x3 = XMVectorLerp(x3, y3, t);
		x4 = XMVectorLerp(x4, y4, t);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
	}

	DxMatrix DxMatrix::Lerp(const DxMatrix& M1, const DxMatrix& M2, float t)
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M1._41));

		XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._11));
		XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._21));
		XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._31));
		XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&M2._41));

		x1 = XMVectorLerp(x1, y1, t);
		x2 = XMVectorLerp(x2, y2, t);
		x3 = XMVectorLerp(x3, y3, t);
		x4 = XMVectorLerp(x4, y4, t);

		DxMatrix result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	void DxMatrix::Transform(const DxMatrix& M, const DxQuaternion& rotation, DxMatrix& result)
	{
		using namespace DirectX;
		XMVECTOR quatv = XMLoadFloat4(&rotation);

		XMMATRIX M0 = XMLoadFloat4x4(&M);
		XMMATRIX M1 = XMMatrixRotationQuaternion(quatv);

		XMStoreFloat4x4(&result, XMMatrixMultiply(M0, M1));
	}

	DxMatrix DxMatrix::Transform(const DxMatrix& M, const DxQuaternion& rotation)
	{
		using namespace DirectX;
		XMVECTOR quatv = XMLoadFloat4(&rotation);

		XMMATRIX M0 = XMLoadFloat4x4(&M);
		XMMATRIX M1 = XMMatrixRotationQuaternion(quatv);

		DxMatrix result;
		XMStoreFloat4x4(&result, XMMatrixMultiply(M0, M1));
		return result;
	}


	/****************************************************************************
	*
	* DxPlane
	*
	****************************************************************************/

	DxPlane::DxPlane(const DxVector3& point1, const DxVector3& point2, const DxVector3& point3)
	{
		using namespace DirectX;
		XMVECTOR P0 = XMLoadFloat3(&point1);
		XMVECTOR P1 = XMLoadFloat3(&point2);
		XMVECTOR P2 = XMLoadFloat3(&point3);
		XMStoreFloat4(this, XMPlaneFromPoints(P0, P1, P2));
	}

	DxPlane::DxPlane(const DxVector3& point, const DxVector3& normal)
	{
		using namespace DirectX;
		XMVECTOR P = XMLoadFloat3(&point);
		XMVECTOR N = XMLoadFloat3(&normal);
		XMStoreFloat4(this, XMPlaneFromPointNormal(P, N));
	}

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool DxPlane::operator == (const DxPlane& p) const
	{
		using namespace DirectX;
		XMVECTOR p1 = XMLoadFloat4(this);
		XMVECTOR p2 = XMLoadFloat4(&p);
		return XMPlaneEqual(p1, p2);
	}

	bool DxPlane::operator != (const DxPlane& p) const
	{
		using namespace DirectX;
		XMVECTOR p1 = XMLoadFloat4(this);
		XMVECTOR p2 = XMLoadFloat4(&p);
		return XMPlaneNotEqual(p1, p2);
	}

	//------------------------------------------------------------------------------
	// DxPlane operations
	//------------------------------------------------------------------------------

	void DxPlane::Normalize()
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMStoreFloat4(this, XMPlaneNormalize(p));
	}

	void DxPlane::Normalize(DxPlane& result) const
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMPlaneNormalize(p));
	}

	float DxPlane::Dot(const DxVector4& v) const
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMVECTOR v0 = XMLoadFloat4(&v);
		return XMVectorGetX(XMPlaneDot(p, v0));
	}

	float DxPlane::DotCoordinate(const DxVector3& position) const
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMVECTOR v0 = XMLoadFloat3(&position);
		return XMVectorGetX(XMPlaneDotCoord(p, v0));
	}

	float DxPlane::DotNormal(const DxVector3& normal) const
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(this);
		XMVECTOR n0 = XMLoadFloat3(&normal);
		return XMVectorGetX(XMPlaneDotNormal(p, n0));
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	void DxPlane::Transform(const DxPlane& plane, const DxMatrix& M, DxPlane& result)
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(&plane);
		XMMATRIX m0 = XMLoadFloat4x4(&M);
		XMStoreFloat4(&result, XMPlaneTransform(p, m0));
	}

	DxPlane DxPlane::Transform(const DxPlane& plane, const DxMatrix& M)
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(&plane);
		XMMATRIX m0 = XMLoadFloat4x4(&M);

		DxPlane result;
		XMStoreFloat4(&result, XMPlaneTransform(p, m0));
		return result;
	}

	void DxPlane::Transform(const DxPlane& plane, const DxQuaternion& rotation, DxPlane& result)
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(&plane);
		XMVECTOR q = XMLoadFloat4(&rotation);
		XMVECTOR X = XMVector3Rotate(p, q);
		X = XMVectorSelect(p, X, g_XMSelect1110); // result.d = plane.d
		XMStoreFloat4(&result, X);
	}

	DxPlane DxPlane::Transform(const DxPlane& plane, const DxQuaternion& rotation)
	{
		using namespace DirectX;
		XMVECTOR p = XMLoadFloat4(&plane);
		XMVECTOR q = XMLoadFloat4(&rotation);
		XMVECTOR X = XMVector3Rotate(p, q);
		X = XMVectorSelect(p, X, g_XMSelect1110); // result.d = plane.d

		DxPlane result;
		XMStoreFloat4(&result, X);
		return result;
	}


	/****************************************************************************
	*
	* DxQuaternion
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool DxQuaternion::operator == (const DxQuaternion& q) const
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		return XMQuaternionEqual(q1, q2);
	}

	bool DxQuaternion::operator != (const DxQuaternion& q) const
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		return XMQuaternionNotEqual(q1, q2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	DxQuaternion& DxQuaternion::operator+= (const DxQuaternion& q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMVectorAdd(q1, q2));
		return *this;
	}

	DxQuaternion& DxQuaternion::operator-= (const DxQuaternion& q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMVectorSubtract(q1, q2));
		return *this;
	}

	DxQuaternion& DxQuaternion::operator*= (const DxQuaternion& q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
		return *this;
	}

	DxQuaternion& DxQuaternion::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorScale(q, S));
		return *this;
	}

	DxQuaternion& DxQuaternion::operator/= (const DxQuaternion& q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		q2 = XMQuaternionInverse(q2);
		XMStoreFloat4(this, XMQuaternionMultiply(q1, q2));
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	DxQuaternion DxQuaternion::operator- () const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);

		DxQuaternion R;
		XMStoreFloat4(&R, XMVectorNegate(q));
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	DxQuaternion operator+ (const DxQuaternion& Q1, const DxQuaternion& Q2)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2 = XMLoadFloat4(&Q2);

		DxQuaternion R;
		XMStoreFloat4(&R, XMVectorAdd(q1, q2));
		return R;
	}

	DxQuaternion operator- (const DxQuaternion& Q1, const DxQuaternion& Q2)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2 = XMLoadFloat4(&Q2);

		DxQuaternion R;
		XMStoreFloat4(&R, XMVectorSubtract(q1, q2));
		return R;
	}

	DxQuaternion operator* (const DxQuaternion& Q1, const DxQuaternion& Q2)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2 = XMLoadFloat4(&Q2);

		DxQuaternion R;
		XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
		return R;
	}

	DxQuaternion operator* (const DxQuaternion& Q, float S)
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(&Q);

		DxQuaternion R;
		XMStoreFloat4(&R, XMVectorScale(q, S));
		return R;
	}

	DxQuaternion operator/ (const DxQuaternion& Q1, const DxQuaternion& Q2)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q1);
		XMVECTOR q2 = XMLoadFloat4(&Q2);
		q2 = XMQuaternionInverse(q2);

		DxQuaternion R;
		XMStoreFloat4(&R, XMQuaternionMultiply(q1, q2));
		return R;
	}

	DxQuaternion operator* (float S, const DxQuaternion& Q)
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(&Q);

		DxQuaternion R;
		XMStoreFloat4(&R, XMVectorScale(q1, S));
		return R;
	}

	//------------------------------------------------------------------------------
	// DxQuaternion operations
	//------------------------------------------------------------------------------

	float DxQuaternion::Length() const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		return XMVectorGetX(XMQuaternionLength(q));
	}

	float DxQuaternion::LengthSquared() const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		return XMVectorGetX(XMQuaternionLengthSq(q));
	}

	void DxQuaternion::Normalize()
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMQuaternionNormalize(q));
	}

	void DxQuaternion::Normalize(DxQuaternion& result) const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMQuaternionNormalize(q));
	}

	void DxQuaternion::Conjugate()
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(this, XMQuaternionConjugate(q));
	}

	void DxQuaternion::Conjugate(DxQuaternion& result) const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMQuaternionConjugate(q));
	}

	void DxQuaternion::Inverse(DxQuaternion& result) const
	{
		using namespace DirectX;
		XMVECTOR q = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMQuaternionInverse(q));
	}

	float DxQuaternion::Dot(const DxQuaternion& q) const
	{
		using namespace DirectX;
		XMVECTOR q1 = XMLoadFloat4(this);
		XMVECTOR q2 = XMLoadFloat4(&q);
		return XMVectorGetX(XMQuaternionDot(q1, q2));
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	DxQuaternion DxQuaternion::CreateFromAxisAngle(const DxVector3& axis, float angle)
	{
		using namespace DirectX;
		XMVECTOR a = XMLoadFloat3(&axis);

		DxQuaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationAxis(a, angle));
		return R;
	}

	DxQuaternion DxQuaternion::CreateFromYawPitchRoll(float yaw, float pitch, float roll)
	{
		using namespace DirectX;
		DxQuaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationRollPitchYaw(pitch, yaw, roll));
		return R;
	}

	DxQuaternion DxQuaternion::CreateFromRotationMatrix(const DxMatrix& M)
	{
		using namespace DirectX;
		XMMATRIX M0 = XMLoadFloat4x4(&M);

		DxQuaternion R;
		XMStoreFloat4(&R, XMQuaternionRotationMatrix(M0));
		return R;
	}

	void DxQuaternion::Lerp(const DxQuaternion& q1, const DxQuaternion& q2, float t, DxQuaternion& result)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);

		XMVECTOR dot = XMVector4Dot(Q0, Q1);

		XMVECTOR R;
		if (XMVector4GreaterOrEqual(dot, XMVectorZero()))
		{
			R = XMVectorLerp(Q0, Q1, t);
		}
		else
		{
			XMVECTOR tv = XMVectorReplicate(t);
			XMVECTOR t1v = XMVectorReplicate(1.f - t);
			XMVECTOR X0 = XMVectorMultiply(Q0, t1v);
			XMVECTOR X1 = XMVectorMultiply(Q1, tv);
			R = XMVectorSubtract(X0, X1);
		}

		XMStoreFloat4(&result, XMQuaternionNormalize(R));
	}

	DxQuaternion DxQuaternion::Lerp(const DxQuaternion& q1, const DxQuaternion& q2, float t)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);

		XMVECTOR dot = XMVector4Dot(Q0, Q1);

		XMVECTOR R;
		if (XMVector4GreaterOrEqual(dot, XMVectorZero()))
		{
			R = XMVectorLerp(Q0, Q1, t);
		}
		else
		{
			XMVECTOR tv = XMVectorReplicate(t);
			XMVECTOR t1v = XMVectorReplicate(1.f - t);
			XMVECTOR X0 = XMVectorMultiply(Q0, t1v);
			XMVECTOR X1 = XMVectorMultiply(Q1, tv);
			R = XMVectorSubtract(X0, X1);
		}

		DxQuaternion result;
		XMStoreFloat4(&result, XMQuaternionNormalize(R));
		return result;
	}

	void DxQuaternion::Slerp(const DxQuaternion& q1, const DxQuaternion& q2, float t, DxQuaternion& result)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);
		XMStoreFloat4(&result, XMQuaternionSlerp(Q0, Q1, t));
	}

	DxQuaternion DxQuaternion::Slerp(const DxQuaternion& q1, const DxQuaternion& q2, float t)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);

		DxQuaternion result;
		XMStoreFloat4(&result, XMQuaternionSlerp(Q0, Q1, t));
		return result;
	}

	void DxQuaternion::Concatenate(const DxQuaternion& q1, const DxQuaternion& q2, DxQuaternion& result)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);
		XMStoreFloat4(&result, XMQuaternionMultiply(Q1, Q0));
	}

	DxQuaternion DxQuaternion::Concatenate(const DxQuaternion& q1, const DxQuaternion& q2)
	{
		using namespace DirectX;
		XMVECTOR Q0 = XMLoadFloat4(&q1);
		XMVECTOR Q1 = XMLoadFloat4(&q2);

		DxQuaternion result;
		XMStoreFloat4(&result, XMQuaternionMultiply(Q1, Q0));
		return result;
	}


	/****************************************************************************
	*
	* DxColor
	*
	****************************************************************************/

	DxColor::DxColor(const DirectX::PackedVector::XMCOLOR& Packed)
	{
		using namespace DirectX;
		XMStoreFloat4(this, PackedVector::XMLoadColor(&Packed));
	}

	DxColor::DxColor(const DirectX::PackedVector::XMUBYTEN4& Packed)
	{
		using namespace DirectX;
		XMStoreFloat4(this, PackedVector::XMLoadUByteN4(&Packed));
	}

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------
	bool DxColor::operator == (const DxColor& c) const
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		return XMColorEqual(c1, c2);
	}

	bool DxColor::operator != (const DxColor& c) const
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		return XMColorNotEqual(c1, c2);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	DxColor& DxColor::operator= (const DirectX::PackedVector::XMCOLOR& Packed)
	{
		using namespace DirectX;
		XMStoreFloat4(this, PackedVector::XMLoadColor(&Packed));
		return *this;
	}

	DxColor& DxColor::operator= (const DirectX::PackedVector::XMUBYTEN4& Packed)
	{
		using namespace DirectX;
		XMStoreFloat4(this, PackedVector::XMLoadUByteN4(&Packed));
		return *this;
	}

	DxColor& DxColor::operator+= (const DxColor& c)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorAdd(c1, c2));
		return *this;
	}

	DxColor& DxColor::operator-= (const DxColor& c)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorSubtract(c1, c2));
		return *this;
	}

	DxColor& DxColor::operator*= (const DxColor& c)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorMultiply(c1, c2));
		return *this;
	}

	DxColor& DxColor::operator*= (float S)
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorScale(c, S));
		return *this;
	}

	DxColor& DxColor::operator/= (const DxColor& c)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(this);
		XMVECTOR c2 = XMLoadFloat4(&c);
		XMStoreFloat4(this, XMVectorDivide(c1, c2));
		return *this;
	}

	//------------------------------------------------------------------------------
	// Urnary operators
	//------------------------------------------------------------------------------

	DxColor DxColor::operator- () const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		DxColor R;
		XMStoreFloat4(&R, XMVectorNegate(c));
		return R;
	}

	//------------------------------------------------------------------------------
	// Binary operators
	//------------------------------------------------------------------------------

	DxColor operator+ (const DxColor& C1, const DxColor& C2)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C1);
		XMVECTOR c2 = XMLoadFloat4(&C2);
		DxColor R;
		XMStoreFloat4(&R, XMVectorAdd(c1, c2));
		return R;
	}

	DxColor operator- (const DxColor& C1, const DxColor& C2)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C1);
		XMVECTOR c2 = XMLoadFloat4(&C2);
		DxColor R;
		XMStoreFloat4(&R, XMVectorSubtract(c1, c2));
		return R;
	}

	DxColor operator* (const DxColor& C1, const DxColor& C2)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C1);
		XMVECTOR c2 = XMLoadFloat4(&C2);
		DxColor R;
		XMStoreFloat4(&R, XMVectorMultiply(c1, c2));
		return R;
	}

	DxColor operator* (const DxColor& C, float S)
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(&C);
		DxColor R;
		XMStoreFloat4(&R, XMVectorScale(c, S));
		return R;
	}

	DxColor operator/ (const DxColor& C1, const DxColor& C2)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C1);
		XMVECTOR c2 = XMLoadFloat4(&C2);
		DxColor R;
		XMStoreFloat4(&R, XMVectorDivide(c1, c2));
		return R;
	}

	DxColor operator* (float S, const DxColor& C)
	{
		using namespace DirectX;
		XMVECTOR c1 = XMLoadFloat4(&C);
		DxColor R;
		XMStoreFloat4(&R, XMVectorScale(c1, S));
		return R;
	}

	//------------------------------------------------------------------------------
	// DxColor operations
	//------------------------------------------------------------------------------

	DirectX::PackedVector::XMCOLOR DxColor::BGRA() const
	{
		using namespace DirectX;
		XMVECTOR clr = XMLoadFloat4(this);
		PackedVector::XMCOLOR Packed;
		PackedVector::XMStoreColor(&Packed, clr);
		return Packed;
	}

	DirectX::PackedVector::XMUBYTEN4 DxColor::RGBA() const
	{
		using namespace DirectX;
		XMVECTOR clr = XMLoadFloat4(this);
		PackedVector::XMUBYTEN4 Packed;
		PackedVector::XMStoreUByteN4(&Packed, clr);
		return Packed;
	}

	DxVector3 DxColor::ToVector3() const
	{
		return DxVector3(x, y, z);
	}

	DxVector4 DxColor::ToVector4() const
	{
		return DxVector4(x, y, z, w);
	}

	void DxColor::Negate()
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMColorNegative(c));
	}

	void DxColor::Negate(DxColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMColorNegative(c));
	}

	void DxColor::Saturate()
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMVectorSaturate(c));
	}

	void DxColor::Saturate(DxColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMVectorSaturate(c));
	}

	void DxColor::Premultiply()
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMVECTOR a = XMVectorSplatW(c);
		a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
		XMStoreFloat4(this, XMVectorMultiply(c, a));
	}

	void DxColor::Premultiply(DxColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMVECTOR a = XMVectorSplatW(c);
		a = XMVectorSelect(g_XMIdentityR3, a, g_XMSelect1110);
		XMStoreFloat4(&result, XMVectorMultiply(c, a));
	}

	void DxColor::AdjustSaturation(float sat)
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMColorAdjustSaturation(c, sat));
	}

	void DxColor::AdjustSaturation(float sat, DxColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMColorAdjustSaturation(c, sat));
	}

	void DxColor::AdjustContrast(float contrast)
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(this, XMColorAdjustContrast(c, contrast));
	}

	void DxColor::AdjustContrast(float contrast, DxColor& result) const
	{
		using namespace DirectX;
		XMVECTOR c = XMLoadFloat4(this);
		XMStoreFloat4(&result, XMColorAdjustContrast(c, contrast));
	}

	//------------------------------------------------------------------------------
	// Static functions
	//------------------------------------------------------------------------------

	void DxColor::Modulate(const DxColor& c1, const DxColor& c2, DxColor& result)
	{
		using namespace DirectX;
		XMVECTOR C0 = XMLoadFloat4(&c1);
		XMVECTOR C1 = XMLoadFloat4(&c2);
		XMStoreFloat4(&result, XMColorModulate(C0, C1));
	}

	DxColor DxColor::Modulate(const DxColor& c1, const DxColor& c2)
	{
		using namespace DirectX;
		XMVECTOR C0 = XMLoadFloat4(&c1);
		XMVECTOR C1 = XMLoadFloat4(&c2);

		DxColor result;
		XMStoreFloat4(&result, XMColorModulate(C0, C1));
		return result;
	}

	void DxColor::Lerp(const DxColor& c1, const DxColor& c2, float t, DxColor& result)
	{
		using namespace DirectX;
		XMVECTOR C0 = XMLoadFloat4(&c1);
		XMVECTOR C1 = XMLoadFloat4(&c2);
		XMStoreFloat4(&result, XMVectorLerp(C0, C1, t));
	}

	DxColor DxColor::Lerp(const DxColor& c1, const DxColor& c2, float t)
	{
		using namespace DirectX;
		XMVECTOR C0 = XMLoadFloat4(&c1);
		XMVECTOR C1 = XMLoadFloat4(&c2);

		DxColor result;
		XMStoreFloat4(&result, XMVectorLerp(C0, C1, t));
		return result;
	}


	/****************************************************************************
	*
	* DxRay
	*
	****************************************************************************/

	//-----------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------
	bool DxRay::operator == (const DxRay& r) const
	{
		using namespace DirectX;
		XMVECTOR r1p = XMLoadFloat3(&position);
		XMVECTOR r2p = XMLoadFloat3(&r.position);
		XMVECTOR r1d = XMLoadFloat3(&direction);
		XMVECTOR r2d = XMLoadFloat3(&r.direction);
		return XMVector3Equal(r1p, r2p) && XMVector3Equal(r1d, r2d);
	}

	bool DxRay::operator != (const DxRay& r) const
	{
		using namespace DirectX;
		XMVECTOR r1p = XMLoadFloat3(&position);
		XMVECTOR r2p = XMLoadFloat3(&r.position);
		XMVECTOR r1d = XMLoadFloat3(&direction);
		XMVECTOR r2d = XMLoadFloat3(&r.direction);
		return XMVector3NotEqual(r1p, r2p) && XMVector3NotEqual(r1d, r2d);
	}

	//-----------------------------------------------------------------------------
	// DxRay operators
	//------------------------------------------------------------------------------

	bool DxRay::Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const
	{
		return sphere.Intersects(position, direction, Dist);
	}

	bool DxRay::Intersects(const BoundingBox& box, _Out_ float& Dist) const
	{
		return box.Intersects(position, direction, Dist);
	}

	bool DxRay::Intersects(const DxVector3& tri0, const DxVector3& tri1, const DxVector3& tri2, _Out_ float& Dist) const
	{
		return DirectX::TriangleTests::Intersects(position, direction, tri0, tri1, tri2, Dist);
	}

	bool DxRay::Intersects(const DxPlane& plane, _Out_ float& Dist) const
	{
		using namespace DirectX;

		XMVECTOR p = XMLoadFloat4(&plane);
		XMVECTOR dir = XMLoadFloat3(&direction);

		XMVECTOR nd = XMPlaneDotNormal(p, dir);

		if (XMVector3LessOrEqual(XMVectorAbs(nd), g_RayEpsilon))
		{
			Dist = 0.f;
			return false;
		}
		else
		{
			// t = -(dot(n,origin) + D) / dot(n,dir)
			XMVECTOR pos = XMLoadFloat3(&position);
			XMVECTOR v = XMPlaneDotNormal(p, pos);
			v = XMVectorAdd(v, XMVectorSplatW(p));
			v = XMVectorDivide(v, nd);
			float dist = -XMVectorGetX(v);
			if (dist < 0)
			{
				Dist = 0.f;
				return false;
			}
			else
			{
				Dist = dist;
				return true;
			}
		}
	}


	/****************************************************************************
	*
	* DxViewport
	*
	****************************************************************************/

	//------------------------------------------------------------------------------
	// Comparision operators
	//------------------------------------------------------------------------------

	bool DxViewport::operator == (const DxViewport& vp) const
	{
		return (x == vp.x && y == vp.y
			&& width == vp.width && height == vp.height
			&& minDepth == vp.minDepth && maxDepth == vp.maxDepth);
	}

	bool DxViewport::operator != (const DxViewport& vp) const
	{
		return (x != vp.x || y != vp.y
			|| width != vp.width || height != vp.height
			|| minDepth != vp.minDepth || maxDepth != vp.maxDepth);
	}

	//------------------------------------------------------------------------------
	// Assignment operators
	//------------------------------------------------------------------------------

	DxViewport& DxViewport::operator= (const RECT& rct)
	{
		x = float(rct.left); y = float(rct.top);
		width = float(rct.right - rct.left);
		height = float(rct.bottom - rct.top);
		minDepth = 0.f; maxDepth = 1.f;
		return *this;
	}

#if defined(__d3d11_h__) || defined(__d3d11_x_h__)
	DxViewport& DxViewport::operator= (const D3D11_VIEWPORT& vp)
	{
		x = vp.TopLeftX; y = vp.TopLeftY;
		width = vp.Width; height = vp.Height;
		minDepth = vp.MinDepth; maxDepth = vp.MaxDepth;
		return *this;
	}
#endif

#if defined(__d3d12_h__) || defined(__d3d12_x_h__)
	DxViewport& DxViewport::operator= (const D3D12_VIEWPORT& vp)
	{
		x = vp.TopLeftX; y = vp.TopLeftY;
		width = vp.Width; height = vp.Height;
		minDepth = vp.MinDepth; maxDepth = vp.MaxDepth;
		return *this;
	}
#endif

	//------------------------------------------------------------------------------
	// DxViewport operations
	//------------------------------------------------------------------------------

	float DxViewport::AspectRatio() const
	{
		if (width == 0.f || height == 0.f)
			return 0.f;

		return (width / height);
	}

	DxVector3 DxViewport::Project(const DxVector3& p, const DxMatrix& proj, const DxMatrix& view, const DxMatrix& world) const
	{
		using namespace DirectX;
		XMVECTOR v = XMLoadFloat3(&p);
		XMMATRIX projection = XMLoadFloat4x4(&proj);
		v = XMVector3Project(v, x, y, width, height, minDepth, maxDepth, projection,
			(CXMMATRIX)view, (CXMMATRIX)world);
		DxVector3 result;
		XMStoreFloat3(&result, v);
		return result;
	}

	void DxViewport::Project(const DxVector3& p, const DxMatrix& proj, const DxMatrix& view, const DxMatrix& world, DxVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v = XMLoadFloat3(&p);
		XMMATRIX projection = XMLoadFloat4x4(&proj);
		v = XMVector3Project(v, x, y, width, height, minDepth, maxDepth, projection, (CXMMATRIX)view, (CXMMATRIX)world);
		XMStoreFloat3(&result, v);
	}

	DxVector3 DxViewport::Unproject(const DxVector3& p, const DxMatrix& proj, const DxMatrix& view, const DxMatrix& world) const
	{
		using namespace DirectX;
		XMVECTOR v = XMLoadFloat3(&p);
		XMMATRIX projection = XMLoadFloat4x4(&proj);
		v = XMVector3Unproject(v, x, y, width, height, minDepth, maxDepth, projection, (CXMMATRIX)view, (CXMMATRIX)world);
		DxVector3 result;
		XMStoreFloat3(&result, v);
		return result;
	}

	void DxViewport::Unproject(const DxVector3& p, const DxMatrix& proj, const DxMatrix& view, const DxMatrix& world, DxVector3& result) const
	{
		using namespace DirectX;
		XMVECTOR v = XMLoadFloat3(&p);
		XMMATRIX projection = XMLoadFloat4x4(&proj);
		v = XMVector3Unproject(v, x, y, width, height, minDepth, maxDepth, projection, (CXMMATRIX)view, (CXMMATRIX)world);
		XMStoreFloat3(&result, v);
	}
}

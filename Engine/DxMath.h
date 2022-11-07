#pragma once
#include <d3d11_1.h> 
//#include <d3dx11.h> 
#if !defined(__d3d11_h__) && !defined(__d3d11_x_h__) && !defined(__d3d12_h__) && !defined(__d3d12_x_h__)
#error include d3d11.h or d3d12.h before including TMath.h
#endif

#if !defined(_XBOX_ONE) || !defined(_TITLE)
//#include <dxgi1_2.h>
#endif

#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#ifndef XM_CONSTEXPR
#define XM_CONSTEXPR
#endif

using namespace DirectX;
using namespace DirectX::PackedVector;

namespace DX_MATH
{
	struct DxVector2;
	struct DxVector3;
	struct DxVector4;
	struct DxMatrix;
	struct DxQuaternion;
	struct DxPlane;

	//------------------------------------------------------------------------------
	// 2D rectangle
	struct DxRectangle
	{
		long x;
		long y;
		long width;
		long height;

		// Creators
		DxRectangle() noexcept : x(0), y(0), width(0), height(0) {}
		XM_CONSTEXPR DxRectangle(long ix, long iy, long iw, long ih) : x(ix), y(iy), width(iw), height(ih) {}
		explicit DxRectangle(const RECT& rct) : x(rct.left), y(rct.top), width(rct.right - rct.left), height(rct.bottom - rct.top) {}

		DxRectangle(const DxRectangle&) = default;
		DxRectangle& operator=(const DxRectangle&) = default;

		DxRectangle(DxRectangle&&) = default;
		DxRectangle& operator=(DxRectangle&&) = default;

		operator RECT() { RECT rct; rct.left = x; rct.top = y; rct.right = (x + width); rct.bottom = (y + height); return rct; }
#ifdef __cplusplus_winrt
		operator Windows::Foundation::Rect() { return Windows::Foundation::Rect(float(x), float(y), float(width), float(height)); }
#endif

		// Comparison operators
		bool operator == (const DxRectangle& r) const { return (x == r.x) && (y == r.y) && (width == r.width) && (height == r.height); }
		bool operator == (const RECT& rct) const { return (x == rct.left) && (y == rct.top) && (width == (rct.right - rct.left)) && (height == (rct.bottom - rct.top)); }

		bool operator != (const DxRectangle& r) const { return (x != r.x) || (y != r.y) || (width != r.width) || (height != r.height); }
		bool operator != (const RECT& rct) const { return (x != rct.left) || (y != rct.top) || (width != (rct.right - rct.left)) || (height != (rct.bottom - rct.top)); }

		// Assignment operators
		DxRectangle& operator=(_In_ const RECT& rct) { x = rct.left; y = rct.top; width = (rct.right - rct.left); height = (rct.bottom - rct.top); return *this; }

		// DxRectangle operations
		DxVector2 Location() const;
		DxVector2 Center() const;

		bool IsEmpty() const { return (width == 0 && height == 0 && x == 0 && y == 0); }

		bool Contains(long ix, long iy) const { return (x <= ix) && (ix < (x + width)) && (y <= iy) && (iy < (y + height)); }
		bool Contains(const DxVector2& point) const;
		bool Contains(const DxRectangle& r) const { return (x <= r.x) && ((r.x + r.width) <= (x + width)) && (y <= r.y) && ((r.y + r.height) <= (y + height)); }
		bool Contains(const RECT& rct) const { return (x <= rct.left) && (rct.right <= (x + width)) && (y <= rct.top) && (rct.bottom <= (y + height)); }

		void Inflate(long horizAmount, long vertAmount);

		bool Intersects(const DxRectangle& r) const { return (r.x < (x + width)) && (x < (r.x + r.width)) && (r.y < (y + height)) && (y < (r.y + r.height)); }
		bool Intersects(const RECT& rct) const { return (rct.left < (x + width)) && (x < rct.right) && (rct.top < (y + height)) && (y < rct.bottom); }

		void Offset(long ox, long oy) { x += ox; y += oy; }

		// Static functions
		static DxRectangle Intersect(const DxRectangle& ra, const DxRectangle& rb);
		static RECT Intersect(const RECT& rcta, const RECT& rctb);

		static DxRectangle Union(const DxRectangle& ra, const DxRectangle& rb);
		static RECT Union(const RECT& rcta, const RECT& rctb);
	};

	//------------------------------------------------------------------------------
	// 2D vector
	struct DxVector2 : DirectX::XMFLOAT2
	{
		DxVector2() noexcept : XMFLOAT2(0.f, 0.f) {}
		XM_CONSTEXPR explicit DxVector2(float x) : XMFLOAT2(x, x) {}
		XM_CONSTEXPR DxVector2(float _x, float _y) : XMFLOAT2(_x, _y) {}
		explicit DxVector2(_In_reads_(2) const float* pArray) : XMFLOAT2(pArray) {}
		DxVector2(XMFLOAT2 V) { x = V.x; y = V.y; }
		DxVector2(const XMFLOAT2& V) { this->x = V.x; this->y = V.y; }
		explicit DxVector2(const DirectX::XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; }

		DxVector2(const DxVector2&) = default;
		DxVector2& operator=(const DxVector2&) = default;

		DxVector2(DxVector2&&) = default;
		DxVector2& operator=(DxVector2&&) = default;

		operator DirectX::XMVECTOR() const { return XMLoadFloat2(this); }

		// Comparison operators
		bool operator == (const DxVector2& V) const;
		bool operator != (const DxVector2& V) const;

		// Assignment operators
		DxVector2& operator= (const DirectX::XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; return *this; }
		DxVector2& operator+= (const DxVector2& V);
		DxVector2& operator-= (const DxVector2& V);
		DxVector2& operator*= (const DxVector2& V);
		DxVector2& operator*= (float S);
		DxVector2& operator/= (float S);

		// Unary operators
		DxVector2 operator+ () const { return *this; }
		DxVector2 operator- () const { return DxVector2(-x, -y); }

		// Vector operations
		bool InBounds(const DxVector2& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const DxVector2& V) const;
		void Cross(const DxVector2& V, DxVector2& result) const;
		DxVector2 Cross(const DxVector2& V) const;

		void Normalize();
		void Normalize(DxVector2& result) const;

		void Clamp(const DxVector2& vmin, const DxVector2& vmax);
		void Clamp(const DxVector2& vmin, const DxVector2& vmax, DxVector2& result) const;

		// Static functions
		static float Distance(const DxVector2& v1, const DxVector2& v2);
		static float DistanceSquared(const DxVector2& v1, const DxVector2& v2);

		static void Min(const DxVector2& v1, const DxVector2& v2, DxVector2& result);
		static DxVector2 Min(const DxVector2& v1, const DxVector2& v2);

		static void Max(const DxVector2& v1, const DxVector2& v2, DxVector2& result);
		static DxVector2 Max(const DxVector2& v1, const DxVector2& v2);

		static void Lerp(const DxVector2& v1, const DxVector2& v2, float t, DxVector2& result);
		static DxVector2 Lerp(const DxVector2& v1, const DxVector2& v2, float t);

		static void SmoothStep(const DxVector2& v1, const DxVector2& v2, float t, DxVector2& result);
		static DxVector2 SmoothStep(const DxVector2& v1, const DxVector2& v2, float t);

		static void Barycentric(const DxVector2& v1, const DxVector2& v2, const DxVector2& v3, float f, float g, DxVector2& result);
		static DxVector2 Barycentric(const DxVector2& v1, const DxVector2& v2, const DxVector2& v3, float f, float g);

		static void CatmullRom(const DxVector2& v1, const DxVector2& v2, const DxVector2& v3, const DxVector2& v4, float t, DxVector2& result);
		static DxVector2 CatmullRom(const DxVector2& v1, const DxVector2& v2, const DxVector2& v3, const DxVector2& v4, float t);

		static void Hermite(const DxVector2& v1, const DxVector2& t1, const DxVector2& v2, const DxVector2& t2, float t, DxVector2& result);
		static DxVector2 Hermite(const DxVector2& v1, const DxVector2& t1, const DxVector2& v2, const DxVector2& t2, float t);

		static void Reflect(const DxVector2& ivec, const DxVector2& nvec, DxVector2& result);
		static DxVector2 Reflect(const DxVector2& ivec, const DxVector2& nvec);

		static void Refract(const DxVector2& ivec, const DxVector2& nvec, float refractionIndex, DxVector2& result);
		static DxVector2 Refract(const DxVector2& ivec, const DxVector2& nvec, float refractionIndex);

		static void Transform(const DxVector2& v, const DxQuaternion& quat, DxVector2& result);
		static DxVector2 Transform(const DxVector2& v, const DxQuaternion& quat);

		static void Transform(const DxVector2& v, const DxMatrix& m, DxVector2& result);
		static DxVector2 Transform(const DxVector2& v, const DxMatrix& m);
		static void Transform(_In_reads_(count) const DxVector2* varray, size_t count, const DxMatrix& m, _Out_writes_(count) DxVector2* resultArray);

		static void Transform(const DxVector2& v, const DxMatrix& m, DxVector4& result);
		static void Transform(_In_reads_(count) const DxVector2* varray, size_t count, const DxMatrix& m, _Out_writes_(count) DxVector4* resultArray);

		static void TransformNormal(const DxVector2& v, const DxMatrix& m, DxVector2& result);
		static DxVector2 TransformNormal(const DxVector2& v, const DxMatrix& m);
		static void TransformNormal(_In_reads_(count) const DxVector2* varray, size_t count, const DxMatrix& m, _Out_writes_(count) DxVector2* resultArray);

		// Constants
		static const DxVector2 Zero;
		static const DxVector2 One;
		static const DxVector2 UnitX;
		static const DxVector2 UnitY;
	};

	// Binary operators
	DxVector2 operator+ (const DxVector2& V1, const DxVector2& V2);
	DxVector2 operator- (const DxVector2& V1, const DxVector2& V2);
	DxVector2 operator* (const DxVector2& V1, const DxVector2& V2);
	DxVector2 operator* (const DxVector2& V, float S);
	DxVector2 operator/ (const DxVector2& V1, const DxVector2& V2);
	DxVector2 operator* (float S, const DxVector2& V);

	//------------------------------------------------------------------------------
	// 3D vector
	struct DxVector3 : DirectX::XMFLOAT3
	{
		DxVector3() noexcept : DirectX::XMFLOAT3(0.f, 0.f, 0.f) {}
		XM_CONSTEXPR explicit DxVector3(float x) : DirectX::XMFLOAT3(x, x, x) {}
		XM_CONSTEXPR DxVector3(float _x, float _y, float _z) : DirectX::XMFLOAT3(_x, _y, _z) {}
		DxVector3(const float* pArray) : DirectX::XMFLOAT3(pArray) {}
		DxVector3(DirectX::XMFLOAT3 V) { x = V.x; y = V.y; z = V.z; }
		DxVector3(const DirectX::XMFLOAT3& V) { this->x = V.x; this->y = V.y; this->z = V.z; }
		explicit DxVector3(const DirectX::XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; }

		DxVector3(const DxVector3&) = default;
		DxVector3& operator=(const DxVector3&) = default;

		DxVector3(DxVector3&&) = default;
		DxVector3& operator=(DxVector3&&) = default;

		operator DirectX::XMVECTOR() const { return XMLoadFloat3(this); }

		float operator [](int i)
		{
			if (i == 0) return x;
			if (i == 1) return y;
			if (i == 2) return z;
			return 0.0f;
		}

		// Comparison operators
		bool operator == (const DxVector3& V) const;
		bool operator != (const DxVector3& V) const;

		// Assignment operators
		DxVector3& operator= (const DirectX::XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; return *this; }
		DxVector3& operator+= (const DxVector3& V);
		DxVector3& operator-= (const DxVector3& V);
		DxVector3& operator*= (const DxVector3& V);
		DxVector3& operator*= (float S);
		DxVector3& operator/= (float S);

		// Unary operators
		DxVector3 operator+ () const { return *this; }
		DxVector3 operator- () const;

		// Vector operations
		bool InBounds(const DxVector3& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const DxVector3& V) const;
		void Cross(const DxVector3& V, DxVector3& result) const;
		DxVector3 Cross(const DxVector3& V) const;

		void Normalize();
		void Normalize(DxVector3& result) const;

		void Clamp(const DxVector3& vmin, const DxVector3& vmax);
		void Clamp(const DxVector3& vmin, const DxVector3& vmax, DxVector3& result) const;

		// Static functions
		static float Distance(const DxVector3& v1, const DxVector3& v2);
		static float DistanceSquared(const DxVector3& v1, const DxVector3& v2);

		static void Min(const DxVector3& v1, const DxVector3& v2, DxVector3& result);
		static DxVector3 Min(const DxVector3& v1, const DxVector3& v2);

		static void Max(const DxVector3& v1, const DxVector3& v2, DxVector3& result);
		static DxVector3 Max(const DxVector3& v1, const DxVector3& v2);

		static void Lerp(const DxVector3& v1, const DxVector3& v2, float t, DxVector3& result);
		static DxVector3 Lerp(const DxVector3& v1, const DxVector3& v2, float t);

		static void SmoothStep(const DxVector3& v1, const DxVector3& v2, float t, DxVector3& result);
		static DxVector3 SmoothStep(const DxVector3& v1, const DxVector3& v2, float t);

		static void Barycentric(const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, float f, float g, DxVector3& result);
		static DxVector3 Barycentric(const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, float f, float g);

		static void CatmullRom(const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, const DxVector3& v4, float t, DxVector3& result);
		static DxVector3 CatmullRom(const DxVector3& v1, const DxVector3& v2, const DxVector3& v3, const DxVector3& v4, float t);

		static void Hermite(const DxVector3& v1, const DxVector3& t1, const DxVector3& v2, const DxVector3& t2, float t, DxVector3& result);
		static DxVector3 Hermite(const DxVector3& v1, const DxVector3& t1, const DxVector3& v2, const DxVector3& t2, float t);

		static void Reflect(const DxVector3& ivec, const DxVector3& nvec, DxVector3& result);
		static DxVector3 Reflect(const DxVector3& ivec, const DxVector3& nvec);

		static void Refract(const DxVector3& ivec, const DxVector3& nvec, float refractionIndex, DxVector3& result);
		static DxVector3 Refract(const DxVector3& ivec, const DxVector3& nvec, float refractionIndex);

		static void Transform(const DxVector3& v, const DxQuaternion& quat, DxVector3& result);
		static DxVector3 Transform(const DxVector3& v, const DxQuaternion& quat);

		static void Transform(const DxVector3& v, const DxMatrix& m, DxVector3& result);
		static DxVector3 Transform(const DxVector3& v, const DxMatrix& m);
		static void Transform(_In_reads_(count) const DxVector3* varray, size_t count, const DxMatrix& m, _Out_writes_(count) DxVector3* resultArray);

		static void Transform(const DxVector3& v, const DxMatrix& m, DxVector4& result);
		static void Transform(_In_reads_(count) const DxVector3* varray, size_t count, const DxMatrix& m, _Out_writes_(count) DxVector4* resultArray);

		static void TransformNormal(const DxVector3& v, const DxMatrix& m, DxVector3& result);
		static DxVector3 TransformNormal(const DxVector3& v, const DxMatrix& m);
		static void TransformNormal(_In_reads_(count) const DxVector3* varray, size_t count, const DxMatrix& m, _Out_writes_(count) DxVector3* resultArray);

		// Constants
		static const DxVector3 Zero;
		static const DxVector3 One;
		static const DxVector3 UnitX;
		static const DxVector3 UnitY;
		static const DxVector3 UnitZ;
		static const DxVector3 Up;
		static const DxVector3 Down;
		static const DxVector3 Right;
		static const DxVector3 Left;
		static const DxVector3 Forward;
		static const DxVector3 Backward;
	};

	// Binary operators
	DxVector3 operator+ (const DxVector3& V1, const DxVector3& V2);
	DxVector3 operator- (const DxVector3& V1, const DxVector3& V2);
	DxVector3 operator* (const DxVector3& V1, const DxVector3& V2);
	DxVector3 operator* (const DxVector3& V, float S);
	DxVector3 operator/ (const DxVector3& V1, const DxVector3& V2);
	DxVector3 operator* (float S, const DxVector3& V);

	//------------------------------------------------------------------------------
	// 4D vector
	struct DxVector4 : public XMFLOAT4
	{
		DxVector4() noexcept : XMFLOAT4(0.f, 0.f, 0.f, 0.f) {}
		XM_CONSTEXPR explicit DxVector4(float x) : XMFLOAT4(x, x, x, x) {}
		XM_CONSTEXPR DxVector4(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		explicit DxVector4(_In_reads_(4) const float* pArray) : XMFLOAT4(pArray) {}
		DxVector4(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		DxVector4(const XMFLOAT4& V) { this->x = V.x; this->y = V.y; this->z = V.z; this->w = V.w; }
		explicit DxVector4(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		DxVector4(const DxVector4&) = default;
		DxVector4& operator=(const DxVector4&) = default;

		DxVector4(DxVector4&&) = default;
		DxVector4& operator=(DxVector4&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const DxVector4& V) const;
		bool operator != (const DxVector4& V) const;

		// Assignment operators
		DxVector4& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		DxVector4& operator+= (const DxVector4& V);
		DxVector4& operator-= (const DxVector4& V);
		DxVector4& operator*= (const DxVector4& V);
		DxVector4& operator*= (float S);
		DxVector4& operator/= (float S);

		// Unary operators
		DxVector4 operator+ () const { return *this; }
		DxVector4 operator- () const;

		// Vector operations
		bool InBounds(const DxVector4& Bounds) const;

		float Length() const;
		float LengthSquared() const;

		float Dot(const DxVector4& V) const;
		void Cross(const DxVector4& v1, const DxVector4& v2, DxVector4& result) const;
		DxVector4 Cross(const DxVector4& v1, const DxVector4& v2) const;

		void Normalize();
		void Normalize(DxVector4& result) const;

		void Clamp(const DxVector4& vmin, const DxVector4& vmax);
		void Clamp(const DxVector4& vmin, const DxVector4& vmax, DxVector4& result) const;

		// Static functions
		static float Distance(const DxVector4& v1, const DxVector4& v2);
		static float DistanceSquared(const DxVector4& v1, const DxVector4& v2);

		static void Min(const DxVector4& v1, const DxVector4& v2, DxVector4& result);
		static DxVector4 Min(const DxVector4& v1, const DxVector4& v2);

		static void Max(const DxVector4& v1, const DxVector4& v2, DxVector4& result);
		static DxVector4 Max(const DxVector4& v1, const DxVector4& v2);

		static void Lerp(const DxVector4& v1, const DxVector4& v2, float t, DxVector4& result);
		static DxVector4 Lerp(const DxVector4& v1, const DxVector4& v2, float t);

		static void SmoothStep(const DxVector4& v1, const DxVector4& v2, float t, DxVector4& result);
		static DxVector4 SmoothStep(const DxVector4& v1, const DxVector4& v2, float t);

		static void Barycentric(const DxVector4& v1, const DxVector4& v2, const DxVector4& v3, float f, float g, DxVector4& result);
		static DxVector4 Barycentric(const DxVector4& v1, const DxVector4& v2, const DxVector4& v3, float f, float g);

		static void CatmullRom(const DxVector4& v1, const DxVector4& v2, const DxVector4& v3, const DxVector4& v4, float t, DxVector4& result);
		static DxVector4 CatmullRom(const DxVector4& v1, const DxVector4& v2, const DxVector4& v3, const DxVector4& v4, float t);

		static void Hermite(const DxVector4& v1, const DxVector4& t1, const DxVector4& v2, const DxVector4& t2, float t, DxVector4& result);
		static DxVector4 Hermite(const DxVector4& v1, const DxVector4& t1, const DxVector4& v2, const DxVector4& t2, float t);

		static void Reflect(const DxVector4& ivec, const DxVector4& nvec, DxVector4& result);
		static DxVector4 Reflect(const DxVector4& ivec, const DxVector4& nvec);

		static void Refract(const DxVector4& ivec, const DxVector4& nvec, float refractionIndex, DxVector4& result);
		static DxVector4 Refract(const DxVector4& ivec, const DxVector4& nvec, float refractionIndex);

		static void Transform(const DxVector2& v, const DxQuaternion& quat, DxVector4& result);
		static DxVector4 Transform(const DxVector2& v, const DxQuaternion& quat);

		static void Transform(const DxVector3& v, const DxQuaternion& quat, DxVector4& result);
		static DxVector4 Transform(const DxVector3& v, const DxQuaternion& quat);

		static void Transform(const DxVector4& v, const DxQuaternion& quat, DxVector4& result);
		static DxVector4 Transform(const DxVector4& v, const DxQuaternion& quat);

		static void Transform(const DxVector4& v, const DxMatrix& m, DxVector4& result);
		static DxVector4 Transform(const DxVector4& v, const DxMatrix& m);
		static void Transform(_In_reads_(count) const DxVector4* varray, size_t count, const DxMatrix& m, _Out_writes_(count) DxVector4* resultArray);

		// Constants
		static const DxVector4 Zero;
		static const DxVector4 One;
		static const DxVector4 UnitX;
		static const DxVector4 UnitY;
		static const DxVector4 UnitZ;
		static const DxVector4 UnitW;
	};

	// Binary operators
	DxVector4 operator+ (const DxVector4& V1, const DxVector4& V2);
	DxVector4 operator- (const DxVector4& V1, const DxVector4& V2);
	DxVector4 operator* (const DxVector4& V1, const DxVector4& V2);
	DxVector4 operator* (const DxVector4& V, float S);
	DxVector4 operator/ (const DxVector4& V1, const DxVector4& V2);
	DxVector4 operator* (float S, const DxVector4& V);

	//------------------------------------------------------------------------------
	// 4x4 DxMatrix (assumes right-handed cooordinates)
	struct DxMatrix : public XMFLOAT4X4
	{
		DxMatrix() noexcept
			: XMFLOAT4X4(1.f, 0, 0, 0,
				0, 1.f, 0, 0,
				0, 0, 1.f, 0,
				0, 0, 0, 1.f) {}
		XM_CONSTEXPR DxMatrix(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
			: XMFLOAT4X4(m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33) {}
		explicit DxMatrix(const DxVector3& r0, const DxVector3& r1, const DxVector3& r2)
			: XMFLOAT4X4(r0.x, r0.y, r0.z, 0,
				r1.x, r1.y, r1.z, 0,
				r2.x, r2.y, r2.z, 0,
				0, 0, 0, 1.f) {}
		explicit DxMatrix(const DxVector4& r0, const DxVector4& r1, const DxVector4& r2, const DxVector4& r3)
			: XMFLOAT4X4(r0.x, r0.y, r0.z, r0.w,
				r1.x, r1.y, r1.z, r1.w,
				r2.x, r2.y, r2.z, r2.w,
				r3.x, r3.y, r3.z, r3.w) {}
		DxMatrix(const XMFLOAT4X4& M) { memcpy_s(this, sizeof(float) * 16, &M, sizeof(XMFLOAT4X4)); }
		DxMatrix(const XMFLOAT3X3& M);
		DxMatrix(const XMFLOAT4X3& M);

		explicit DxMatrix(_In_reads_(16) const float* pArray) : XMFLOAT4X4(pArray) {}
		DxMatrix(CXMMATRIX M) { XMStoreFloat4x4(this, M); }

		DxMatrix(const DxMatrix&) = default;
		DxMatrix& operator=(const DxMatrix&) = default;

		DxMatrix(DxMatrix&&) = default;
		DxMatrix& operator=(DxMatrix&&) = default;

		operator XMFLOAT4X4() const { return *this; }

		// Comparison operators
		bool operator == (const DxMatrix& M) const;
		bool operator != (const DxMatrix& M) const;

		// Assignment operators
		DxMatrix& operator= (const XMFLOAT3X3& M);
		DxMatrix& operator= (const XMFLOAT4X3& M);
		DxMatrix& operator+= (const DxMatrix& M);
		DxMatrix& operator-= (const DxMatrix& M);
		DxMatrix& operator*= (const DxMatrix& M);
		DxMatrix& operator*= (float S);
		DxMatrix& operator/= (float S);

		DxMatrix& operator/= (const DxMatrix& M);
		// Element-wise divide

		// Unary operators
		DxMatrix operator+ () const { return *this; }
		DxMatrix operator- () const;

		// Properties
		DxVector3 Up() const { return DxVector3(_21, _22, _23); }
		void Up(const DxVector3& v) { _21 = v.x; _22 = v.y; _23 = v.z; }

		DxVector3 Down() const { return DxVector3(-_21, -_22, -_23); }
		void Down(const DxVector3& v) { _21 = -v.x; _22 = -v.y; _23 = -v.z; }

		DxVector3 Right() const { return DxVector3(_11, _12, _13); }
		void Right(const DxVector3& v) { _11 = v.x; _12 = v.y; _13 = v.z; }

		DxVector3 Left() const { return DxVector3(-_11, -_12, -_13); }
		void Left(const DxVector3& v) { _11 = -v.x; _12 = -v.y; _13 = -v.z; }

		DxVector3 Forward() const { return DxVector3(-_31, -_32, -_33); }
		void Forward(const DxVector3& v) { _31 = -v.x; _32 = -v.y; _33 = -v.z; }

		DxVector3 Backward() const { return DxVector3(_31, _32, _33); }
		void Backward(const DxVector3& v) { _31 = v.x; _32 = v.y; _33 = v.z; }

		DxVector3 Translation() const { return DxVector3(_41, _42, _43); }
		void Translation(const DxVector3& v) { _41 = v.x; _42 = v.y; _43 = v.z; }

		// DxMatrix operations
		bool Decompose(DxVector3& scale, DxQuaternion& rotation, DxVector3& translation);

		DxMatrix Transpose() const;
		void Transpose(DxMatrix& result) const;

		DxMatrix Invert() const;
		void Invert(DxMatrix& result) const;

		float Determinant() const;

		// Static functions
		static DxMatrix CreateBillboard(const DxVector3& object, const DxVector3& cameraPosition, const DxVector3& cameraUp, _In_opt_ const DxVector3* cameraForward = nullptr);

		static DxMatrix CreateConstrainedBillboard(const DxVector3& object, const DxVector3& cameraPosition, const DxVector3& rotateAxis,
			_In_opt_ const DxVector3* cameraForward = nullptr, _In_opt_ const DxVector3* objectForward = nullptr);

		static DxMatrix CreateTranslation(const DxVector3& position);
		static DxMatrix CreateTranslation(float x, float y, float z);

		static DxMatrix CreateScale(const DxVector3& scales);
		static DxMatrix CreateScale(float xs, float ys, float zs);
		static DxMatrix CreateScale(float scale);

		static DxMatrix CreateRotationX(float radians);
		static DxMatrix CreateRotationY(float radians);
		static DxMatrix CreateRotationZ(float radians);

		static DxMatrix CreateFromAxisAngle(const DxVector3& axis, float angle);

		static DxMatrix CreatePerspectiveFieldOfView(float fov, float aspectRatio, float nearPlane, float farPlane);
		static DxMatrix CreatePerspective(float width, float height, float nearPlane, float farPlane);
		static DxMatrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlane, float farPlane);
		static DxMatrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
		static DxMatrix CreateOrthographicOffCenter(float left, float right, float bottom, float top, float zNearPlane, float zFarPlane);

		static DxMatrix CreateLookAt(const DxVector3& position, const DxVector3& target, const DxVector3& up);
		static DxMatrix CreateWorld(const DxVector3& position, const DxVector3& forward, const DxVector3& up);

		static DxMatrix CreateFromQuaternion(const DxQuaternion& quat);

		static DxMatrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);

		static DxMatrix CreateShadow(const DxVector3& lightDir, const DxPlane& plane);

		static DxMatrix CreateReflection(const DxPlane& plane);

		static void Lerp(const DxMatrix& M1, const DxMatrix& M2, float t, DxMatrix& result);
		static DxMatrix Lerp(const DxMatrix& M1, const DxMatrix& M2, float t);

		static void Transform(const DxMatrix& M, const DxQuaternion& rotation, DxMatrix& result);
		static DxMatrix Transform(const DxMatrix& M, const DxQuaternion& rotation);

		// Constants
		static const DxMatrix Identity;
	};

	// Binary operators
	DxMatrix operator+ (const DxMatrix& M1, const DxMatrix& M2);
	DxMatrix operator- (const DxMatrix& M1, const DxMatrix& M2);
	DxMatrix operator* (const DxMatrix& M1, const DxMatrix& M2);
	DxMatrix operator* (const DxMatrix& M, float S);
	DxMatrix operator/ (const DxMatrix& M, float S);
	DxMatrix operator/ (const DxMatrix& M1, const DxMatrix& M2);
	// Element-wise divide
	DxMatrix operator* (float S, const DxMatrix& M);


	//-----------------------------------------------------------------------------
	// DxPlane
	struct DxPlane : public XMFLOAT4
	{
		DxPlane() noexcept : XMFLOAT4(0.f, 1.f, 0.f, 0.f) {}
		XM_CONSTEXPR DxPlane(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		DxPlane(const DxVector3& normal, float d) : XMFLOAT4(normal.x, normal.y, normal.z, d) {}
		DxPlane(const DxVector3& point1, const DxVector3& point2, const DxVector3& point3);
		DxPlane(const DxVector3& point, const DxVector3& normal);
		explicit DxPlane(const DxVector4& v) : XMFLOAT4(v.x, v.y, v.z, v.w) {}
		explicit DxPlane(_In_reads_(4) const float* pArray) : XMFLOAT4(pArray) {}
		DxPlane(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		DxPlane(const XMFLOAT4& p) { this->x = p.x; this->y = p.y; this->z = p.z; this->w = p.w; }
		explicit DxPlane(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		DxPlane(const DxPlane&) = default;
		DxPlane& operator=(const DxPlane&) = default;

		DxPlane(DxPlane&&) = default;
		DxPlane& operator=(DxPlane&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const DxPlane& p) const;
		bool operator != (const DxPlane& p) const;

		// Assignment operators
		DxPlane& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }

		// Properties
		DxVector3 Normal() const { return DxVector3(x, y, z); }
		void Normal(const DxVector3& normal) { x = normal.x; y = normal.y; z = normal.z; }

		float D() const { return w; }
		void D(float d) { w = d; }

		// DxPlane operations
		void Normalize();
		void Normalize(DxPlane& result) const;

		float Dot(const DxVector4& v) const;
		float DotCoordinate(const DxVector3& position) const;
		float DotNormal(const DxVector3& normal) const;

		// Static functions
		static void Transform(const DxPlane& plane, const DxMatrix& M, DxPlane& result);
		static DxPlane Transform(const DxPlane& plane, const DxMatrix& M);

		static void Transform(const DxPlane& plane, const DxQuaternion& rotation, DxPlane& result);
		static DxPlane Transform(const DxPlane& plane, const DxQuaternion& rotation);
		// Input quaternion must be the inverse transpose of the transformation
	};

	//------------------------------------------------------------------------------
	// DxQuaternion
	struct DxQuaternion : public XMFLOAT4
	{
		DxQuaternion() noexcept : XMFLOAT4(0, 0, 0, 1.f) {}
		XM_CONSTEXPR DxQuaternion(float _x, float _y, float _z, float _w) : XMFLOAT4(_x, _y, _z, _w) {}
		DxQuaternion(const DxVector3& v, float scalar) : XMFLOAT4(v.x, v.y, v.z, scalar) {}
		explicit DxQuaternion(const DxVector4& v) : XMFLOAT4(v.x, v.y, v.z, v.w) {}
		explicit DxQuaternion(_In_reads_(4) const float* pArray) : XMFLOAT4(pArray) {}
		DxQuaternion(XMFLOAT4 V) { x = V.x; y = V.y; z = V.z; w = V.w; }
		DxQuaternion(const XMFLOAT4& q) { this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w; }
		explicit DxQuaternion(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		DxQuaternion(const DxQuaternion&) = default;
		DxQuaternion& operator=(const DxQuaternion&) = default;

		DxQuaternion(DxQuaternion&&) = default;
		DxQuaternion& operator=(DxQuaternion&&) = default;

		//operator int () const { return 0; }
		//SampleClass f;
		//int i = f; //  f.operator int () 를 호출하고 초기화 및 반한됨.
		operator XMVECTOR() const { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator == (const DxQuaternion& q) const;
		bool operator != (const DxQuaternion& q) const;

		// Assignment operators
		DxQuaternion& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		DxQuaternion& operator+= (const DxQuaternion& q);
		DxQuaternion& operator-= (const DxQuaternion& q);
		DxQuaternion& operator*= (const DxQuaternion& q);
		DxQuaternion& operator*= (float S);
		DxQuaternion& operator/= (const DxQuaternion& q);

		// Unary operators
		DxQuaternion operator+ () const { return *this; }
		DxQuaternion operator- () const;

		// DxQuaternion operations
		float Length() const;
		float LengthSquared() const;

		void Normalize();
		void Normalize(DxQuaternion& result) const;

		void Conjugate();
		void Conjugate(DxQuaternion& result) const;

		void Inverse(DxQuaternion& result) const;

		float Dot(const DxQuaternion& Q) const;

		// Static functions
		static DxQuaternion CreateFromAxisAngle(const DxVector3& axis, float angle);
		static DxQuaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
		static DxQuaternion CreateFromRotationMatrix(const DxMatrix& M);

		static void Lerp(const DxQuaternion& q1, const DxQuaternion& q2, float t, DxQuaternion& result);
		static DxQuaternion Lerp(const DxQuaternion& q1, const DxQuaternion& q2, float t);

		static void Slerp(const DxQuaternion& q1, const DxQuaternion& q2, float t, DxQuaternion& result);
		static DxQuaternion Slerp(const DxQuaternion& q1, const DxQuaternion& q2, float t);

		static void Concatenate(const DxQuaternion& q1, const DxQuaternion& q2, DxQuaternion& result);
		static DxQuaternion Concatenate(const DxQuaternion& q1, const DxQuaternion& q2);

		// Constants
		static const DxQuaternion Identity;
	};

	// Binary operators
	DxQuaternion operator+ (const DxQuaternion& Q1, const DxQuaternion& Q2);
	DxQuaternion operator- (const DxQuaternion& Q1, const DxQuaternion& Q2);
	DxQuaternion operator* (const DxQuaternion& Q1, const DxQuaternion& Q2);
	DxQuaternion operator* (const DxQuaternion& Q, float S);
	DxQuaternion operator/ (const DxQuaternion& Q1, const DxQuaternion& Q2);
	DxQuaternion operator* (float S, const DxQuaternion& Q);

	//------------------------------------------------------------------------------
	// DxColor
	struct DxColor : public XMFLOAT4
	{
		DxColor() noexcept : XMFLOAT4(0, 0, 0, 1.f) {}
		XM_CONSTEXPR DxColor(float _r, float _g, float _b) : XMFLOAT4(_r, _g, _b, 1.f) {}
		XM_CONSTEXPR DxColor(float _r, float _g, float _b, float _a) : XMFLOAT4(_r, _g, _b, _a) {}
		explicit DxColor(const DxVector3& clr) : XMFLOAT4(clr.x, clr.y, clr.z, 1.f) {}
		explicit DxColor(const DxVector4& clr) : XMFLOAT4(clr.x, clr.y, clr.z, clr.w) {}
		explicit DxColor(_In_reads_(4) const float* pArray) : XMFLOAT4(pArray) {}
		DxColor(XMFLOAT3 V) { x = V.x; y = V.y; z = V.z; }
		DxColor(const XMFLOAT4& c) { this->x = c.x; this->y = c.y; this->z = c.z; this->w = c.w; }
		explicit DxColor(const XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; this->z = F.f[2]; this->w = F.f[3]; }

		explicit DxColor(const DirectX::PackedVector::XMCOLOR& Packed);
		// BGRA Direct3D 9 D3DCOLOR packed color

		explicit DxColor(const DirectX::PackedVector::XMUBYTEN4& Packed);
		// RGBA XNA Game Studio packed color

		DxColor(const DxColor&) = default;
		DxColor& operator=(const DxColor&) = default;

		DxColor(DxColor&&) = default;
		DxColor& operator=(DxColor&&) = default;

		operator XMVECTOR() const { return XMLoadFloat4(this); }
		operator const float* () const { return reinterpret_cast<const float*>(this); }

		// Comparison operators
		bool operator == (const DxColor& c) const;
		bool operator != (const DxColor& c) const;

		// Assignment operators
		DxColor& operator= (const XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; z = F.f[2]; w = F.f[3]; return *this; }
		DxColor& operator= (const DirectX::PackedVector::XMCOLOR& Packed);
		DxColor& operator= (const DirectX::PackedVector::XMUBYTEN4& Packed);
		DxColor& operator+= (const DxColor& c);
		DxColor& operator-= (const DxColor& c);
		DxColor& operator*= (const DxColor& c);
		DxColor& operator*= (float S);
		DxColor& operator/= (const DxColor& c);

		// Unary operators
		DxColor operator+ () const { return *this; }
		DxColor operator- () const;

		// Properties
		float R() const { return x; }
		void R(float r) { x = r; }

		float G() const { return y; }
		void G(float g) { y = g; }

		float B() const { return z; }
		void B(float b) { z = b; }

		float A() const { return w; }
		void A(float a) { w = a; }

		// DxColor operations
		DirectX::PackedVector::XMCOLOR BGRA() const;
		DirectX::PackedVector::XMUBYTEN4 RGBA() const;

		DxVector3 ToVector3() const;
		DxVector4 ToVector4() const;

		void Negate();
		void Negate(DxColor& result) const;

		void Saturate();
		void Saturate(DxColor& result) const;

		void Premultiply();
		void Premultiply(DxColor& result) const;

		void AdjustSaturation(float sat);
		void AdjustSaturation(float sat, DxColor& result) const;

		void AdjustContrast(float contrast);
		void AdjustContrast(float contrast, DxColor& result) const;

		// Static functions
		static void Modulate(const DxColor& c1, const DxColor& c2, DxColor& result);
		static DxColor Modulate(const DxColor& c1, const DxColor& c2);

		static void Lerp(const DxColor& c1, const DxColor& c2, float t, DxColor& result);
		static DxColor Lerp(const DxColor& c1, const DxColor& c2, float t);
	};

	// Binary operators
	DxColor operator+ (const DxColor& C1, const DxColor& C2);
	DxColor operator- (const DxColor& C1, const DxColor& C2);
	DxColor operator* (const DxColor& C1, const DxColor& C2);
	DxColor operator* (const DxColor& C, float S);
	DxColor operator/ (const DxColor& C1, const DxColor& C2);
	DxColor operator* (float S, const DxColor& C);

	//------------------------------------------------------------------------------
	// DxRay
	class DxRay
	{
	public:
		DxVector3 position;
		DxVector3 direction;

		DxRay() noexcept : position(0, 0, 0), direction(0, 0, 1) {}
		DxRay(const DxVector3& pos, const DxVector3& dir) : position(pos), direction(dir) {}

		DxRay(const DxRay&) = default;
		DxRay& operator=(const DxRay&) = default;

		DxRay(DxRay&&) = default;
		DxRay& operator=(DxRay&&) = default;

		// Comparison operators
		bool operator == (const DxRay& r) const;
		bool operator != (const DxRay& r) const;

		// DxRay operations
		bool Intersects(const BoundingSphere& sphere, _Out_ float& Dist) const;
		bool Intersects(const BoundingBox& box, _Out_ float& Dist) const;
		bool Intersects(const DxVector3& tri0, const DxVector3& tri1, const DxVector3& tri2, _Out_ float& Dist) const;
		bool Intersects(const DxPlane& plane, _Out_ float& Dist) const;
	};

	//------------------------------------------------------------------------------
	// DxViewport
	class DxViewport
	{
	public:
		float x;
		float y;
		float width;
		float height;
		float minDepth;
		float maxDepth;

		DxViewport() noexcept :
			x(0.f), y(0.f), width(0.f), height(0.f), minDepth(0.f), maxDepth(1.f) {}
		XM_CONSTEXPR DxViewport(float ix, float iy, float iw, float ih, float iminz = 0.f, float imaxz = 1.f) :
			x(ix), y(iy), width(iw), height(ih), minDepth(iminz), maxDepth(imaxz) {}
		explicit DxViewport(const RECT& rct) :
			x(float(rct.left)), y(float(rct.top)),
			width(float(rct.right - rct.left)),
			height(float(rct.bottom - rct.top)),
			minDepth(0.f), maxDepth(1.f) {}

#if defined(__d3d11_h__) || defined(__d3d11_x_h__)
		// Direct3D 11 interop
		explicit DxViewport(const D3D11_VIEWPORT& vp) :
			x(vp.TopLeftX), y(vp.TopLeftY),
			width(vp.Width), height(vp.Height),
			minDepth(vp.MinDepth), maxDepth(vp.MaxDepth) {}

		operator D3D11_VIEWPORT() { return *reinterpret_cast<const D3D11_VIEWPORT*>(this); }
		const D3D11_VIEWPORT* Get11() const { return reinterpret_cast<const D3D11_VIEWPORT*>(this); }
		DxViewport& operator= (const D3D11_VIEWPORT& vp);
#endif

#if defined(__d3d12_h__) || defined(__d3d12_x_h__)
		// Direct3D 12 interop
		explicit DxViewport(const D3D12_VIEWPORT& vp) :
			x(vp.TopLeftX), y(vp.TopLeftY),
			width(vp.Width), height(vp.Height),
			minDepth(vp.MinDepth), maxDepth(vp.MaxDepth) {}

		operator D3D12_VIEWPORT() { return *reinterpret_cast<const D3D12_VIEWPORT*>(this); }
		const D3D12_VIEWPORT* Get12() const { return reinterpret_cast<const D3D12_VIEWPORT*>(this); }
		DxViewport& operator= (const D3D12_VIEWPORT& vp);
#endif

		DxViewport(const DxViewport&) = default;
		DxViewport& operator=(const DxViewport&) = default;

		DxViewport(DxViewport&&) = default;
		DxViewport& operator=(DxViewport&&) = default;

		// Comparison operators
		bool operator == (const DxViewport& vp) const;
		bool operator != (const DxViewport& vp) const;

		// Assignment operators
		DxViewport& operator= (const RECT& rct);

		// DxViewport operations
		float AspectRatio() const;

		DxVector3 Project(const DxVector3& p, const DxMatrix& proj, const DxMatrix& view, const DxMatrix& world) const;
		void Project(const DxVector3& p, const DxMatrix& proj, const DxMatrix& view, const DxMatrix& world, DxVector3& result) const;

		DxVector3 Unproject(const DxVector3& p, const DxMatrix& proj, const DxMatrix& view, const DxMatrix& world) const;
		void Unproject(const DxVector3& p, const DxMatrix& proj, const DxMatrix& view, const DxMatrix& world, DxVector3& result) const;

		// Static methods
		static RECT __cdecl ComputeDisplayArea(DXGI_SCALING scaling, UINT backBufferWidth, UINT backBufferHeight, int outputWidth, int outputHeight);
		static RECT __cdecl ComputeTitleSafeArea(UINT backBufferWidth, UINT backBufferHeight);
	};


	///////////////////////////////////////// static ///////////////////////////////////////////
	//https://docs.microsoft.com/en-us/windows/win32/dxmath/pg-xnamath-migration-d3dx
	//--------------------------
	// 2D Vector
	//--------------------------

	static float D3DXVec2Length(CONST DxVector2* pV)
	{
		return pV->Length();
	}

	static float D3DXVec2LengthSq(CONST DxVector2* pV)
	{
		return 0.0f;
	}

	static float D3DXVec2Dot(CONST DxVector2* pV1, CONST DxVector2* pV2)
	{
		return 0.0f;
	}

	// Z component of ((x1,y1,0) cross (x2,y2,0))
	static float D3DXVec2CCW(CONST DxVector2* pV1, CONST DxVector2* pV2)
	{
		return 0.0f;
	}

	static DxVector2* D3DXVec2Add(DxVector2* pOut, CONST DxVector2* pV1, CONST DxVector2* pV2)
	{
		return pOut;
	}

	static DxVector2* D3DXVec2Subtract(DxVector2* pOut, CONST DxVector2* pV1, CONST DxVector2* pV2)
	{
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
	static DxVector2* D3DXVec2Minimize(DxVector2* pOut, CONST DxVector2* pV1, CONST DxVector2* pV2)
	{
		return pOut;
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
	static DxVector2* D3DXVec2Maximize(DxVector2* pOut, CONST DxVector2* pV1, CONST DxVector2* pV2)
	{
		return pOut;
	}

	static DxVector2* D3DXVec2Scale(DxVector2* pOut, CONST DxVector2* pV, float s)
	{
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static DxVector2* D3DXVec2Lerp(DxVector2* pOut, CONST DxVector2* pV1, CONST DxVector2* pV2,
		float s)
	{
		*pOut = DxVector2::Lerp(*pV1, *pV2, s);
		return pOut;
	}
	static DxVector2* D3DXVec2Normalize(DxVector2* pOut, CONST DxVector2* pV)
	{
		return pOut;
	}

	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static DxVector2* D3DXVec2Hermite(DxVector2* pOut, CONST DxVector2* pV1, CONST DxVector2* pT1,
		CONST DxVector2* pV2, CONST DxVector2* pT2, float s)
	{
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static DxVector2* D3DXVec2CatmullRom(DxVector2* pOut, CONST DxVector2* pV0, CONST DxVector2* pV1,
		CONST DxVector2* pV2, CONST DxVector2* pV3, float s)
	{
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static DxVector2* D3DXVec2BaryCentric(DxVector2* pOut, CONST DxVector2* pV1, CONST DxVector2* pV2,
		CONST DxVector2* pV3, float f, float g)
	{
		return pOut;
	}

	// Transform (x, y, 0, 1) by matrix.
	static DxVector4* D3DXVec2Transform(DxVector4* pOut, CONST DxVector2* pV, CONST DxMatrix* pM)
	{
		return pOut;
	}

	// Transform (x, y, 0, 1) by matrix, project result back into w=1.
	static DxVector2* D3DXVec2TransformCoord(DxVector2* pOut, CONST DxVector2* pV, CONST DxMatrix* pM)
	{
		return pOut;
	}

	// Transform (x, y, 0, 0) by matrix.
	static DxVector2* D3DXVec2TransformNormal(DxVector2* pOut, CONST DxVector2* pV, CONST DxMatrix* pM)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 1) by matrix.
	static DxVector4* D3DXVec2TransformArray(DxVector4* pOut, UINT OutStride, CONST DxVector2* pV, UINT VStride, CONST DxMatrix* pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 1) by matrix, project result back into w=1.
	static DxVector2* D3DXVec2TransformCoordArray(DxVector2* pOut, UINT OutStride, CONST DxVector2* pV, UINT VStride, CONST DxMatrix* pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, 0, 0) by matrix.
	static DxVector2* D3DXVec2TransformNormalArray(DxVector2* pOut, UINT OutStride, CONST DxVector2* pV, UINT VStride, CONST DxMatrix* pM, UINT n)
	{
		return pOut;
	}
	//--------------------------
	// 3D Vector
	//--------------------------

	static  float D3DXVec3Dot(CONST DxVector3* pV1, CONST DxVector3* pV2)
	{
		return pV1->Dot(*pV2);
	}
	static DxVector3* D3DXVec3Cross(DxVector3* pOut, CONST DxVector3* pV1, CONST DxVector3* pV2)
	{
		*pOut = pV1->Cross(*pV2);
		return pOut;
	}
	static DxVector3* D3DXVec3Normalize(DxVector3* pOut, CONST DxVector3* pV)
	{
		pV->Normalize(*pOut);
		return pOut;
	}
	static DxVector3* D3DXVec3TransformCoord(DxVector3* pOut, CONST DxVector3* pV, CONST DxMatrix* pM)
	{
		*pOut = DxVector3::Transform(*pV, *pM);
		return pOut;
	}
	static float D3DXVec3Length(CONST DxVector3* pV)
	{
		return pV->Length();
	}



	static float D3DXVec3LengthSq(CONST DxVector3* pV)
	{
		return pV->LengthSquared();
	}


	static DxVector3* D3DXVec3Add(DxVector3* pOut, CONST DxVector3* pV1, CONST DxVector3* pV2)
	{
		*pOut = *pV1 + *pV2;
		return pOut;
	}

	static DxVector3* D3DXVec3Subtract(DxVector3* pOut, CONST DxVector3* pV1, CONST DxVector3* pV2)
	{
		*pOut = *pV1 - *pV2;
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
	static DxVector3* D3DXVec3Minimize(DxVector3* pOut, CONST DxVector3* pV1, CONST DxVector3* pV2) {
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
	static DxVector3* D3DXVec3Maximize(DxVector3* pOut, CONST DxVector3* pV1, CONST DxVector3* pV2)
	{
		return pOut;
	}

	static DxVector3* D3DXVec3Scale(DxVector3* pOut, CONST DxVector3* pV, float s)
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat3(pV);
		XMVECTOR X = XMVectorScale(v1, s);
		DxVector3 R;
		XMStoreFloat3(&R, X);
		*pOut = R;
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static DxVector3* D3DXVec3Lerp(DxVector3* pOut, CONST DxVector3* pV1, CONST DxVector3* pV2, float s)
	{
		*pOut = DxVector3::Lerp(*pV1, *pV2, s);
		return pOut;
	}


	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static DxVector3* D3DXVec3Hermite(DxVector3* pOut, CONST DxVector3* pV1, CONST DxVector3* pT1,
		CONST DxVector3* pV2, CONST DxVector3* pT2, float s)
	{
		*pOut = DxVector3::Hermite(*pV1, *pT1, *pV2, *pT2, s);
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static DxVector3* D3DXVec3CatmullRom(DxVector3* pOut, CONST DxVector3* pV0, CONST DxVector3* pV1,
		CONST DxVector3* pV2, CONST DxVector3* pV3, float s)
	{
		*pOut = DxVector3::CatmullRom(*pV0, *pV1, *pV2, *pV3, s);
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static DxVector3* D3DXVec3BaryCentric(DxVector3* pOut, CONST DxVector3* pV1, CONST DxVector3* pV2,
		CONST DxVector3* pV3, float f, float g)
	{
		*pOut = DxVector3::Barycentric(*pV1, *pV2, *pV3, f, g);
		return pOut;
	}

	// Transform (x, y, z, 1) by matrix.
	static DxVector4* D3DXVec3Transform(DxVector4* pOut, CONST DxVector3* pV, CONST DxMatrix* pM)
	{
		return pOut;
	}

	// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
	// non-affine matrix, the matrix you pass to this function should be the 
	// transpose of the inverse of the matrix you would use to transform a coord.
	static DxVector3* D3DXVec3TransformNormal(DxVector3* pOut, CONST DxVector3* pV, CONST DxMatrix* pM)
	{
		*pOut = DxVector3::TransformNormal(*pV, *pM);
		return pOut;
	}


	// Transform Array (x, y, z, 1) by matrix. 
	static DxVector4* D3DXVec3TransformArray(DxVector4* pOut, UINT OutStride, CONST DxVector3* pV, UINT VStride, CONST DxMatrix* pM, UINT n)
	{
		return pOut;
	}

	// Transform Array (x, y, z, 1) by matrix, project result back into w=1.
	static DxVector3* D3DXVec3TransformCoordArray(DxVector3* pOut, UINT OutStride, CONST DxVector3* pV, UINT VStride, CONST DxMatrix* pM, UINT n)
	{
		return pOut;
	}

	// Transform (x, y, z, 0) by matrix.  If you transforming a normal by a 
	// non-affine matrix, the matrix you pass to this function should be the 
	// transpose of the inverse of the matrix you would use to transform a coord.
	static DxVector3* D3DXVec3TransformNormalArray(DxVector3* pOut, UINT OutStride, CONST DxVector3* pV, UINT VStride, CONST DxMatrix* pM, UINT n)
	{
		return pOut;
	}

	// Project vector from object space into screen space
	static DxVector3* D3DXVec3Project(DxVector3* pOut, CONST DxVector3* pV, CONST D3D10_VIEWPORT* pViewport,
		CONST DxMatrix* pProjection, CONST DxMatrix* pView, CONST DxMatrix* pWorld)
	{
		//*pOut = DxViewport::Project();
		return pOut;
	}

	// Project vector from screen space into object space
	static DxVector3* D3DXVec3Unproject(DxVector3* pOut, CONST DxVector3* pV, CONST D3D10_VIEWPORT* pViewport,
		CONST DxMatrix* pProjection, CONST DxMatrix* pView, CONST DxMatrix* pWorld)
	{
		//*pOut = DxViewport::Unproject();
		return pOut;
	}

	// Project vector Array from object space into screen space
	static DxVector3* D3DXVec3ProjectArray(DxVector3* pOut, UINT OutStride, CONST DxVector3* pV, UINT VStride, CONST D3D10_VIEWPORT* pViewport,
		CONST DxMatrix* pProjection, CONST DxMatrix* pView, CONST DxMatrix* pWorld, UINT n)
	{
		return pOut;
	}

	// Project vector Array from screen space into object space
	static DxVector3* D3DXVec3UnprojectArray(DxVector3* pOut, UINT OutStride, CONST DxVector3* pV, UINT VStride, CONST D3D10_VIEWPORT* pViewport,
		CONST DxMatrix* pProjection, CONST DxMatrix* pView, CONST DxMatrix* pWorld, UINT n)
	{
		return pOut;
	}

	//--------------------------
	// 4D Vector
	//--------------------------

	static float D3DXVec4Length(CONST DxVector4* pV)
	{
		return pV->Length();
	}


	static float D3DXVec4LengthSq(CONST DxVector4* pV)
	{
		return 0.0f;
	}

	static float D3DXVec4Dot(CONST DxVector4* pV1, CONST DxVector4* pV2)
	{
		return 0.0f;
	}
	static DxVector4* D3DXVec4Add(DxVector4* pOut, CONST DxVector4* pV1, CONST DxVector4* pV2)
	{
		return pOut;
	}

	static DxVector4* D3DXVec4Subtract(DxVector4* pOut, CONST DxVector4* pV1, CONST DxVector4* pV2)
	{
		return pOut;
	}

	// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
	static DxVector4* D3DXVec4Minimize(DxVector4* pOut, CONST DxVector4* pV1, CONST DxVector4* pV2)
	{
		return pOut;
	}

	// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
	static DxVector4* D3DXVec4Maximize(DxVector4* pOut, CONST DxVector4* pV1, CONST DxVector4* pV2)
	{
		return pOut;
	}
	static DxVector4* D3DXVec4Scale(DxVector4* pOut, CONST DxVector4* pV, float s) {
		return pOut;
	}

	// Linear interpolation. V1 + s(V2-V1)
	static DxVector4* D3DXVec4Lerp(DxVector4* pOut, CONST DxVector4* pV1, CONST DxVector4* pV2, float s)
	{
		*pOut = DxVector4::Lerp(*pV1, *pV2, s);
		return pOut;
	}

	// Cross-product in 4 dimensions.
	static DxVector4* D3DXVec4Cross(DxVector4* pOut, CONST DxVector4* pV1, CONST DxVector4* pV2,
		CONST DxVector4* pV3)
	{
		return pOut;
	}

	static DxVector4* D3DXVec4Normalize(DxVector4* pOut, CONST DxVector4* pV)
	{
		return pOut;
	}

	// Hermite interpolation between position V1, tangent T1 (when s == 0)
	// and position V2, tangent T2 (when s == 1).
	static DxVector4* D3DXVec4Hermite(DxVector4* pOut, CONST DxVector4* pV1, CONST DxVector4* pT1,
		CONST DxVector4* pV2, CONST DxVector4* pT2, float s)
	{
		return pOut;
	}

	// CatmullRom interpolation between V1 (when s == 0) and V2 (when s == 1)
	static DxVector4* D3DXVec4CatmullRom(DxVector4* pOut, CONST DxVector4* pV0, CONST DxVector4* pV1,
		CONST DxVector4* pV2, CONST DxVector4* pV3, float s)
	{
		return pOut;
	}

	// Barycentric coordinates.  V1 + f(V2-V1) + g(V3-V1)
	static DxVector4* D3DXVec4BaryCentric(DxVector4* pOut, CONST DxVector4* pV1, CONST DxVector4* pV2,
		CONST DxVector4* pV3, float f, float g)
	{
		return pOut;
	}

	// Transform vector by matrix.
	static DxVector4* D3DXVec4Transform(DxVector4* pOut, CONST DxVector4* pV, CONST DxMatrix* pM)
	{
		return pOut;
	}

	// Transform vector array by matrix.
	static DxVector4* D3DXVec4TransformArray(DxVector4* pOut, UINT OutStride, CONST DxVector4* pV, UINT VStride, CONST DxMatrix* pM, UINT n)
	{
		return pOut;
	}


	static DxMatrix* D3DXMatrixIdentity(DxMatrix* pOut)
	{
		XMStoreFloat4x4(pOut, XMMatrixIdentity());
		return pOut;
	}
	static DxMatrix* D3DXMatrixRotationQuaternion(DxMatrix* pOut, CONST DxQuaternion* pQ)
	{
		*pOut = DxMatrix::CreateFromQuaternion(*pQ);
		return pOut;
	}
	static DxQuaternion* D3DXQuaternionRotationMatrix(DxQuaternion* pOut, CONST DxMatrix* pM)
	{
		*pOut = DxQuaternion::CreateFromRotationMatrix(*pM);
		return pOut;
	}

	static float D3DXMatrixDeterminant(CONST DxMatrix* pM) {
		return pM->Determinant();
	}

	static HRESULT D3DXMatrixDecompose(DxVector3* pOutScale, DxQuaternion* pOutRotation,
		DxVector3* pOutTranslation, DxMatrix* pM)
	{
		if (pM->Decompose(*pOutScale, *pOutRotation, *pOutTranslation) == false)
		{
			return S_FALSE;
		}
		return S_OK;
	}

	static DxMatrix* D3DXMatrixTranspose(DxMatrix* pOut, CONST DxMatrix* pM) {

		*pOut = pM->Transpose();
		return pOut;
	}

	// Matrix multiplication.  The result represents the transformation M2
	// followed by the transformation M1.  (Out = M1 * M2)
	static DxMatrix* D3DXMatrixMultiply(DxMatrix* pOut, CONST DxMatrix* pM1, CONST DxMatrix* pM2) {
		*pOut = (*pM1) * (*pM2);
		return pOut;
	}

	// Matrix multiplication, followed by a transpose. (Out = T(M1 * M2))
	static DxMatrix* D3DXMatrixMultiplyTranspose(DxMatrix* pOut, CONST DxMatrix* pM1, CONST DxMatrix* pM2) {

		*pOut = (*pM1) * (*pM2);
		pOut->Transpose();
		return pOut;
	}

	// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
	// be returned.  The determinant of pM is also returned it pfDeterminant
	// is non-NULL.
	static DxMatrix* D3DXMatrixInverse(DxMatrix* pOut, float* pDeterminant, CONST DxMatrix* pM) {
		pM->Invert(*pOut);
		if (pDeterminant != nullptr)
		{
			*pDeterminant = pM->Determinant();
		}
		return pOut;
	}

	// Build a matrix which scales by (sx, sy, sz)
	static DxMatrix* D3DXMatrixScaling(DxMatrix* pOut, float sx, float sy, float sz) {
		*pOut = DxMatrix::CreateScale(sx, sy, sz);
		return pOut;
	}

	// Build a matrix which translates by (x, y, z)
	static DxMatrix* D3DXMatrixTranslation(DxMatrix* pOut, float x, float y, float z) {
		*pOut = DxMatrix::CreateTranslation(x, y, z);
		return pOut;
	}

	// Build a matrix which rotates around the X axis
	static DxMatrix* D3DXMatrixRotationX(DxMatrix* pOut, float Angle) {
		*pOut = DxMatrix::CreateRotationX(Angle);
		return pOut;
	}

	// Build a matrix which rotates around the Y axis
	static DxMatrix* D3DXMatrixRotationY(DxMatrix* pOut, float Angle) {
		*pOut = DxMatrix::CreateRotationY(Angle);
		return pOut;
	}

	// Build a matrix which rotates around the Z axis
	static DxMatrix* D3DXMatrixRotationZ(DxMatrix* pOut, float Angle) {
		*pOut = DxMatrix::CreateRotationZ(Angle);
		return pOut;
	}

	// Build a matrix which rotates around an arbitrary axis
	static DxMatrix* D3DXMatrixRotationAxis(DxMatrix* pOut, CONST DxVector3* pV, float Angle) {
		*pOut = DxMatrix::CreateFromAxisAngle(*pV, Angle);
		return pOut;
	}

	// Yaw around the Y axis, a pitch around the X axis,
	// and a roll around the Z axis.
	static DxMatrix* D3DXMatrixRotationYawPitchRoll(DxMatrix* pOut, float Yaw, float Pitch, float Roll) {
		*pOut = DxMatrix::CreateFromYawPitchRoll(Yaw, Pitch, Roll);
		return pOut;
	}

	// Build transformation matrix.  NULL arguments are treated as identity.
	// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
	static DxMatrix* D3DXMatrixTransformation(DxMatrix* pOut, CONST DxVector3* pScalingCenter,
		CONST DxQuaternion* pScalingRotation, CONST DxVector3* pScaling,
		CONST DxVector3* pRotationCenter, CONST DxQuaternion* pRotation,
		CONST DxVector3* pTranslation)
	{
		return pOut;
	}

	// Build 2D transformation matrix in XY plane.  NULL arguments are treated as identity.
	// Mout = Msc-1 * Msr-1 * Ms * Msr * Msc * Mrc-1 * Mr * Mrc * Mt
	static DxMatrix* D3DXMatrixTransformation2D(DxMatrix* pOut, CONST DxVector2* pScalingCenter,
		float ScalingRotation, CONST DxVector2* pScaling,
		CONST DxVector2* pRotationCenter, float Rotation,
		CONST DxVector2* pTranslation) {
		return pOut;
	}

	// Build affine transformation matrix.  NULL arguments are treated as identity.
	// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
	static DxMatrix* D3DXMatrixAffineTransformation(DxMatrix* pOut, float Scaling, CONST DxVector3* pRotationCenter,
		CONST DxQuaternion* pRotation, CONST DxVector3* pTranslation)
	{
		XMVECTOR S = XMVectorReplicate(Scaling);//XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		XMVECTOR O = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		if (pRotationCenter != NULL)
		{
			O = DirectX::XMLoadFloat3(pRotationCenter);
		}
		XMVECTOR P = DirectX::XMLoadFloat3(pTranslation);
		XMVECTOR Q = DirectX::XMLoadFloat4(pRotation);
		*pOut = DirectX::XMMatrixAffineTransformation(S, O, Q, P);
		return pOut;
	}

	// Build 2D affine transformation matrix in XY plane.  NULL arguments are treated as identity.
	// Mout = Ms * Mrc-1 * Mr * Mrc * Mt
	static DxMatrix* D3DXMatrixAffineTransformation2D(DxMatrix* pOut, float Scaling, CONST DxVector2* pRotationCenter,
		float Rotation, CONST DxVector2* pTranslation) {
		return pOut;
	}

	// Build a lookat matrix. (right-handed)
	static DxMatrix* D3DXMatrixLookAtRH(DxMatrix* pOut, CONST DxVector3* pEye, CONST DxVector3* pAt, CONST DxVector3* pUp) {
		return pOut;
	}

	// Build a lookat matrix. (left-handed)
	static DxMatrix* D3DXMatrixLookAtLH(DxMatrix* pOut, CONST DxVector3* pEye, CONST DxVector3* pAt, CONST DxVector3* pUp) {
		*pOut = DxMatrix::CreateLookAt(*pEye, *pAt, *pUp);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static DxMatrix* D3DXMatrixPerspectiveRH(DxMatrix* pOut, float w, float h, float zn, float zf) {
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static DxMatrix* D3DXMatrixPerspectiveLH(DxMatrix* pOut, float w, float h, float zn, float zf) {
		*pOut = DxMatrix::CreatePerspective(w, h, zn, zf);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static DxMatrix* D3DXMatrixPerspectiveFovRH(DxMatrix* pOut, float fovy, float Aspect, float zn, float zf)
	{
		using namespace DirectX;
		XMStoreFloat4x4(pOut, XMMatrixPerspectiveFovRH(fovy, Aspect, zn, zf));
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static DxMatrix* D3DXMatrixPerspectiveFovLH(DxMatrix* pOut, float fovy, float Aspect, float zn, float zf)
	{
		using namespace DirectX;
		*pOut = DxMatrix::CreatePerspectiveFieldOfView(fovy, Aspect, zn, zf);
		return pOut;
	}

	// Build a perspective projection matrix. (right-handed)
	static DxMatrix* D3DXMatrixPerspectiveOffCenterRH(DxMatrix* pOut, float l, float r, float b, float t, float zn, float zf) {
		return pOut;
	}

	// Build a perspective projection matrix. (left-handed)
	static DxMatrix* D3DXMatrixPerspectiveOffCenterLH(DxMatrix* pOut, float l, float r, float b, float t, float zn, float zf) {
		*pOut = DxMatrix::CreatePerspectiveOffCenter(l, r, b, t, zn, zf);
		return pOut;
	}

	// Build an ortho projection matrix. (right-handed)
	static DxMatrix* D3DXMatrixOrthoRH(DxMatrix* pOut, float w, float h, float zn, float zf) {
		return pOut;
	}

	// Build an ortho projection matrix. (left-handed)
	static DxMatrix* D3DXMatrixOrthoLH(DxMatrix* pOut, float w, float h, float zn, float zf) {
		*pOut = DxMatrix::CreateOrthographic(w, h, zn, zf);
		return pOut;
	}

	// Build an ortho projection matrix. (right-handed)
	static DxMatrix* D3DXMatrixOrthoOffCenterRH(DxMatrix* pOut, float l, float r, float b, float t, float zn, float zf) {
		return pOut;
	}

	// Build an ortho projection matrix. (left-handed)
	static DxMatrix* D3DXMatrixOrthoOffCenterLH(DxMatrix* pOut, float l, float r, float b, float t, float zn, float zf) {
		*pOut = DxMatrix::CreateOrthographicOffCenter(l, r, b, t, zn, zf);
		return pOut;
	}

	// Build a matrix which flattens geometry into a plane, as if casting
	// a shadow from a light.
	static DxMatrix* D3DXMatrixShadow(DxMatrix* pOut, CONST DxVector4* pLight, CONST DxPlane* pPlane)
	{
		CONST DxVector3 pLightLight = DxVector3(pLight->x, pLight->y, pLight->z);
		*pOut = DxMatrix::CreateShadow(pLightLight, *pPlane);
		return pOut;
	}

	// Build a matrix which reflects the coordinate system about a plane
	static DxMatrix* D3DXMatrixReflect(DxMatrix* pOut, CONST DxPlane* pPlane) {
		*pOut = DxMatrix::CreateReflection(*pPlane);
		return pOut;
	}

	//--------------------------
	// Quaternion
	//--------------------------

	// inline

	static float D3DXQuaternionLength(CONST DxQuaternion* pQ)
	{
		return pQ->Length();
	};

	// Length squared, or "norm"
	static float D3DXQuaternionLengthSq(CONST DxQuaternion* pQ)
	{
		return pQ->LengthSquared();
	};

	static float D3DXQuaternionDot(CONST DxQuaternion* pQ1, CONST DxQuaternion* pQ2)
	{
		return pQ1->Dot(*pQ2);;
	};

	// (0, 0, 0, 1)
	static DxQuaternion* D3DXQuaternionIdentity(DxQuaternion* pOut) {
		//*pOut = DxQuaternion::Identity;
		XMStoreFloat4(pOut, XMQuaternionIdentity());
		return pOut;
	};

	static BOOL D3DXQuaternionIsIdentity(CONST DxQuaternion* pQ) {
		return TRUE;
	};

	// (-x, -y, -z, w)
	static DxQuaternion* D3DXQuaternionConjugate(DxQuaternion* pOut, CONST DxQuaternion* pQ) {
		return pOut;
	};


	// Compute a quaternin's axis and angle of rotation. Expects unit quaternions.
	static void D3DXQuaternionToAxisAngle(CONST DxQuaternion* pQ, DxVector3* pAxis, float* pAngle)
	{

	};

	static DxQuaternion* D3DXQuaternionRotationAxis(DxQuaternion* pOut, CONST DxVector3* pV, FLOAT Angle)
	{
		*pOut = DxQuaternion::CreateFromAxisAngle(*pV, Angle);
		return pOut;
	}

	// Yaw around the Y axis, a pitch around the X axis,
	// and a roll around the Z axis.
	static DxQuaternion* D3DXQuaternionRotationYawPitchRoll(DxQuaternion* pOut, float Yaw, float Pitch, float Roll)
	{
		*pOut = DxQuaternion::CreateFromYawPitchRoll(Yaw, Pitch, Roll);
		return pOut;
	};

	// Quaternion multiplication.  The result represents the rotation Q2
	// followed by the rotation Q1.  (Out = Q2 * Q1)
	static DxQuaternion* D3DXQuaternionMultiply(DxQuaternion* pOut, CONST DxQuaternion* pQ1,
		CONST DxQuaternion* pQ2)
	{
		*pOut = *pQ1 * *pQ2;
		return pOut;
	};

	static DxQuaternion* D3DXQuaternionNormalize(DxQuaternion* pOut, CONST DxQuaternion* pQ)
	{
		*pOut = *pQ;
		pOut->Normalize();
		return pOut;
	};

	// Conjugate and re-norm
	static DxQuaternion* D3DXQuaternionInverse(DxQuaternion* pOut, CONST DxQuaternion* pQ)
	{
		DxQuaternion qRet = *pQ;
		pQ->Inverse(qRet);
		*pOut = qRet;
		return pOut;
	};

	// Expects unit quaternions.
	// if q = (cos(theta), sin(theta) * v); ln(q) = (0, theta * v)
	static DxQuaternion* D3DXQuaternionLn(DxQuaternion* pOut, CONST DxQuaternion* pQ) {
		return pOut;
	};

	// Expects pure quaternions. (w == 0)  w is ignored in calculation.
	// if q = (0, theta * v); exp(q) = (cos(theta), sin(theta) * v)
	static DxQuaternion* D3DXQuaternionExp(DxQuaternion* pOut, CONST DxQuaternion* pQ) {
		return pOut;
	};

	// Spherical linear interpolation between Q1 (t == 0) and Q2 (t == 1).
	// Expects unit quaternions.
	static DxQuaternion* D3DXQuaternionSlerp(DxQuaternion* pOut, CONST DxQuaternion* pQ1, CONST DxQuaternion* pQ2, float t)
	{
		*pOut = DxQuaternion::Slerp(*pQ1, *pQ2, t);
		return pOut;
	};

	// Spherical quadrangle interpolation.
	// Slerp(Slerp(Q1, C, t), Slerp(A, B, t), 2t(1-t))
	static DxQuaternion* D3DXQuaternionSquad(DxQuaternion* pOut, CONST DxQuaternion* pQ1,
		CONST DxQuaternion* pA, CONST DxQuaternion* pB,
		CONST DxQuaternion* pC, float t) {
		return pOut;
	};

	// Setup control points for spherical quadrangle interpolation
	// from Q1 to Q2.  The control points are chosen in such a way 
	// to ensure the continuity of tangents with adjacent segments.
	static void D3DXQuaternionSquadSetup(DxQuaternion* pAOut, DxQuaternion* pBOut, DxQuaternion* pCOut,
		CONST DxQuaternion* pQ0, CONST DxQuaternion* pQ1,
		CONST DxQuaternion* pQ2, CONST DxQuaternion* pQ3) {
	};

	// Barycentric interpolation.
	// Slerp(Slerp(Q1, Q2, f+g), Slerp(Q1, Q3, f+g), g/(f+g))
	static DxQuaternion* D3DXQuaternionBaryCentric(DxQuaternion* pOut, CONST DxQuaternion* pQ1,
		CONST DxQuaternion* pQ2, CONST DxQuaternion* pQ3,
		float f, float g) {
		return pOut;
	};


	//--------------------------
	// Plane
	//--------------------------

	// inline

	// ax + by + cz + dw
	static float D3DXPlaneDot(CONST DxPlane* pP, CONST DxVector4* pV) {
		return 0.0f;
	};
	// ax + by + cz + d
	static float D3DXPlaneDotCoord(CONST DxPlane* pP, CONST DxVector3* pV) {
		return 0.0f;
	};
	// ax + by + cz
	static float D3DXPlaneDotNormal(CONST DxPlane* pP, CONST DxVector3* pV) {
		return 0.0f;
	};
	static DxPlane* D3DXPlaneScale(DxPlane* pOut, CONST DxPlane* pP, float s) {
		return pOut;
	};


	// Normalize plane (so that |a,b,c| == 1)
	static DxPlane* D3DXPlaneNormalize(DxPlane* pOut, CONST DxPlane* pP) {
		return pOut;
	};

	// Find the intersection between a plane and a line.  If the line is
	// parallel to the plane, NULL is returned.
	static DxVector3* D3DXPlaneIntersectLine(DxVector3* pOut, CONST DxPlane* pP, CONST DxVector3* pV1,
		CONST DxVector3* pV2) {
		return pOut;
	};

	// Construct a plane from a point and a normal
	static DxPlane* D3DXPlaneFromPointNormal(DxPlane* pOut, CONST DxVector3* pPoint, CONST DxVector3* pNormal) {
		return pOut;
	};

	// Construct a plane from 3 points
	static DxPlane* D3DXPlaneFromPoints(DxPlane* pOut, CONST DxVector3* pV1, CONST DxVector3* pV2,
		CONST DxVector3* pV3) {
		return pOut;
	};

	// Transform a plane by a matrix.  The vector (a,b,c) must be normal.
	// M should be the inverse transpose of the transformation desired.
	static DxPlane* D3DXPlaneTransform(DxPlane* pOut, CONST DxPlane* pP, CONST DxMatrix* pM) {
		return pOut;
	};
	// Transform an array of planes by a matrix.  The vectors (a,b,c) must be normal.
// M should be the inverse transpose of the transformation desired.
	static DxPlane* D3DXPlaneTransformArray(DxPlane* pOut, UINT OutStride, CONST DxPlane* pP, UINT PStride, CONST DxMatrix* pM, UINT n) {
		return pOut;
	};



	//--------------------------
	// Color
	//--------------------------

	// inline

	// (1-r, 1-g, 1-b, a)
	static DxColor* D3DXColorNegative(DxColor* pOut, CONST DxColor* pC) {
		return pOut;
	};

	static DxColor* D3DXColorAdd(DxColor* pOut, CONST DxColor* pC1, CONST DxColor* pC2) {
		return pOut;
	};

	static DxColor* D3DXColorSubtract(DxColor* pOut, CONST DxColor* pC1, CONST DxColor* pC2) {
		return pOut;
	};

	static DxColor* D3DXColorScale(DxColor* pOut, CONST DxColor* pC, float s) {
		return pOut;
	};

	// (r1*r2, g1*g2, b1*b2, a1*a2)
	static DxColor* D3DXColorModulate(DxColor* pOut, CONST DxColor* pC1, CONST DxColor* pC2) {
		return pOut;
	};

	// Linear interpolation of r,g,b, and a. C1 + s(C2-C1)
	static DxColor* D3DXColorLerp(DxColor* pOut, CONST DxColor* pC1, CONST DxColor* pC2, float s) {
		return pOut;
	};


	// Interpolate r,g,b between desaturated color and color.
	// DesaturatedColor + s(Color - DesaturatedColor)
	static DxColor* D3DXColorAdjustSaturation(DxColor* pOut, CONST DxColor* pC, float s) {
		return pOut;
	};
	// Interpolate r,g,b between 50% grey and color.  Grey + s(Color - Grey)
	static DxColor* D3DXColorAdjustContrast(DxColor* pOut, CONST DxColor* pC, float c) {
		return pOut;
	};





	//--------------------------
	// Misc
	//--------------------------
		// Calculate Fresnel term given the cosine of theta (likely obtained by
		// taking the dot of two normals), and the refraction index of the material.
	static float D3DXFresnelTerm(float CosTheta, float RefractionIndex)
	{
		return 0.0f;
	};
}

//  ------------------------------------------------------------------------------
// Support for TMath and Standard C++ Library containers
namespace std
{
	template<> struct less<DX_MATH::DxRectangle>
	{
		bool operator()(const DX_MATH::DxRectangle& r1, const DX_MATH::DxRectangle& r2) const
		{
			return ((r1.x < r2.x)
				|| ((r1.x == r2.x) && (r1.y < r2.y))
				|| ((r1.x == r2.x) && (r1.y == r2.y) && (r1.width < r2.width))
				|| ((r1.x == r2.x) && (r1.y == r2.y) && (r1.width == r2.width) && (r1.height < r2.height)));
		}
	};

	template<> struct less<DX_MATH::DxVector2>
	{
		bool operator()(const DX_MATH::DxVector2& V1, const DX_MATH::DxVector2& V2) const
		{
			return ((V1.x < V2.x) || ((V1.x == V2.x) && (V1.y < V2.y)));
		}
	};

	template<> struct less<DX_MATH::DxVector3>
	{
		bool operator()(const DX_MATH::DxVector3& V1, const DX_MATH::DxVector3& V2) const
		{
			return ((V1.x < V2.x)
				|| ((V1.x == V2.x) && (V1.y < V2.y))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z)));
		}
	};

	template<> struct less<DX_MATH::DxVector4>
	{
		bool operator()(const DX_MATH::DxVector4& V1, const DX_MATH::DxVector4& V2) const
		{
			return ((V1.x < V2.x)
				|| ((V1.x == V2.x) && (V1.y < V2.y))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z < V2.z))
				|| ((V1.x == V2.x) && (V1.y == V2.y) && (V1.z == V2.z) && (V1.w < V2.w)));
		}
	};

	template<> struct less<DX_MATH::DxMatrix>
	{
		bool operator()(const DX_MATH::DxMatrix& M1, const DX_MATH::DxMatrix& M2) const
		{
			if (M1._11 != M2._11) return M1._11 < M2._11;
			if (M1._12 != M2._12) return M1._12 < M2._12;
			if (M1._13 != M2._13) return M1._13 < M2._13;
			if (M1._14 != M2._14) return M1._14 < M2._14;
			if (M1._21 != M2._21) return M1._21 < M2._21;
			if (M1._22 != M2._22) return M1._22 < M2._22;
			if (M1._23 != M2._23) return M1._23 < M2._23;
			if (M1._24 != M2._24) return M1._24 < M2._24;
			if (M1._31 != M2._31) return M1._31 < M2._31;
			if (M1._32 != M2._32) return M1._32 < M2._32;
			if (M1._33 != M2._33) return M1._33 < M2._33;
			if (M1._34 != M2._34) return M1._34 < M2._34;
			if (M1._41 != M2._41) return M1._41 < M2._41;
			if (M1._42 != M2._42) return M1._42 < M2._42;
			if (M1._43 != M2._43) return M1._43 < M2._43;
			if (M1._44 != M2._44) return M1._44 < M2._44;

			return false;
		}
	};

	template<> struct less<DX_MATH::DxPlane>
	{
		bool operator()(const DX_MATH::DxPlane& P1, const DX_MATH::DxPlane& P2) const
		{
			return ((P1.x < P2.x)
				|| ((P1.x == P2.x) && (P1.y < P2.y))
				|| ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z < P2.z))
				|| ((P1.x == P2.x) && (P1.y == P2.y) && (P1.z == P2.z) && (P1.w < P2.w)));
		}
	};

	template<> struct less<DX_MATH::DxQuaternion>
	{
		bool operator()(const DX_MATH::DxQuaternion& Q1, const DX_MATH::DxQuaternion& Q2) const
		{
			return ((Q1.x < Q2.x)
				|| ((Q1.x == Q2.x) && (Q1.y < Q2.y))
				|| ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z < Q2.z))
				|| ((Q1.x == Q2.x) && (Q1.y == Q2.y) && (Q1.z == Q2.z) && (Q1.w < Q2.w)));
		}
	};

	template<> struct less<DX_MATH::DxColor>
	{
		bool operator()(const DX_MATH::DxColor& C1, const DX_MATH::DxColor& C2) const
		{
			return ((C1.x < C2.x)
				|| ((C1.x == C2.x) && (C1.y < C2.y))
				|| ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z < C2.z))
				|| ((C1.x == C2.x) && (C1.y == C2.y) && (C1.z == C2.z) && (C1.w < C2.w)));
		}
	};

	template<> struct less<DX_MATH::DxRay>
	{
		bool operator()(const DX_MATH::DxRay& R1, const DX_MATH::DxRay& R2) const
		{
			if (R1.position.x != R2.position.x) return R1.position.x < R2.position.x;
			if (R1.position.y != R2.position.y) return R1.position.y < R2.position.y;
			if (R1.position.z != R2.position.z) return R1.position.z < R2.position.z;

			if (R1.direction.x != R2.direction.x) return R1.direction.x < R2.direction.x;
			if (R1.direction.y != R2.direction.y) return R1.direction.y < R2.direction.y;
			if (R1.direction.z != R2.direction.z) return R1.direction.z < R2.direction.z;

			return false;
		}
	};

	template<> struct less<DX_MATH::DxViewport>
	{
		bool operator()(const DX_MATH::DxViewport& vp1, const DX_MATH::DxViewport& vp2) const
		{
			if (vp1.x != vp2.x) return (vp1.x < vp2.x);
			if (vp1.y != vp2.y) return (vp1.y < vp2.y);

			if (vp1.width != vp2.width) return (vp1.width < vp2.width);
			if (vp1.height != vp2.height) return (vp1.height < vp2.height);

			if (vp1.minDepth != vp2.minDepth) return (vp1.minDepth < vp2.minDepth);
			if (vp1.maxDepth != vp2.maxDepth) return (vp1.maxDepth < vp2.maxDepth);

			return false;
		}
	};
};
using namespace DX_MATH;


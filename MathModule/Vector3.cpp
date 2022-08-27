#include "pch.h"
#include "Vector3.h"

const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);

constexpr Vector3::Vector3(float x, float y, float z)
	: _x(x)
	, _y(y)
	, _z(z)
{
}

constexpr Vector3::Vector3(const Vector3& vector)
	: _x(vector._x)
	, _y(vector._y)
	, _z(vector._z)
{
}

constexpr Vector3& Vector3::operator+=(const Vector3& other)
{
	return *this = *this + other;
}

constexpr Vector3& Vector3::operator-=(const Vector3& other)
{
	return *this = *this - other;
}

constexpr Vector3& Vector3::operator*=(float scalar)
{
	return *this = *this * scalar;
}

constexpr Vector3& Vector3::operator/=(float scalar)
{
	return *this = *this / scalar;
}

constexpr Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(_x + other._x, _y + other._y, other._z);
}

constexpr Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(_x - other._x, _y - other._y, _z - other._z);
}

constexpr Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(_x * scalar, _y * scalar, _z * scalar);
}

constexpr Vector3 Vector3::operator/(float scalar) const
{
	return Vector3(_x / scalar, _y / scalar, _z / scalar);
}

constexpr Vector3 Vector3::operator-() const
{
	return Vector3();
}



constexpr bool Vector3::operator==(const Vector3& other) const
{
	return (_x == other._x) && (_y == other._y) && (_z == other._z);
}

constexpr bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

constexpr bool Vector3::operator<(const Vector3& other) const
{
	if (_x != other._x) return _x < other._x;
	if (_y != other._y) return _y < other._y;
	if (_z != other._z) return _z < other._z;

	return false;
}

float Vector3::Dot(const Vector3& other) const
{
	return (_x * other._x) + (_y * other._y) + (_z * other._z);
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(_y * other._z - _z * other._y, _z * other._x - _x * other._z, _x * other._y - _y * other._x);
}

float Vector3::Size() const
{
	return std::sqrtf(SizeSquared());
}

float Vector3::SizeSquared() const
{
	return (_x * _x + _y * _y + _z * _z);
}

void Vector3::Normalize()
{
	*this = GetNormalize();
}

Vector3 Vector3::GetNormalize() const
{
	const float magitude = SizeSquared();
	if (magitude == 1.0f)
	{
		return *this;
	}
	else if (magitude < FLT_EPSILON)
	{
		return Vector3::Zero;
	}

	return *this / magitude;
}

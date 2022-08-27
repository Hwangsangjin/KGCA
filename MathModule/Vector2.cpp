#include "pch.h"
#include "Vector2.h"

const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);
const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::One(1.0f, 1.0f);

constexpr Vector2::Vector2(float x, float y)
	: _x(x)
	, _y(y)
{
}

constexpr Vector2::Vector2(const Vector2& vector)
	: _x(vector._x)
	, _y(vector._y)
{
}

constexpr Vector2& Vector2::operator+=(const Vector2& other)
{
	return *this = *this + other;
}

constexpr Vector2& Vector2::operator-=(const Vector2& other)
{
	return *this = *this - other;
}

constexpr Vector2& Vector2::operator*=(float scalar)
{
	return *this = *this * scalar;
}

constexpr Vector2& Vector2::operator/=(float scalar)
{
	return *this = *this / scalar;
}

constexpr Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(_x + other._x, _y + other._y);
}

constexpr Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(_x - other._x, _y - other._y);
}

constexpr Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(_x * scalar, _y * scalar);
}

constexpr Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(_x / scalar, _y / scalar);
}

constexpr Vector2 Vector2::operator-() const
{
	return Vector2(-_x, -_y);
}

constexpr bool Vector2::operator==(const Vector2& other) const
{
	return (_x == other._x) && (_y == other._y);
}

constexpr bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

constexpr bool Vector2::operator<(const Vector2& other) const
{
	if (_x != other._x) return _x < other._x;
	if (_y != other._y) return _y < other._y;

	return false;
}

constexpr float Vector2::Dot(const Vector2& other) const
{
	return (_x * other._x) + (_y * other._y);
}

float Vector2::Size() const
{
	return std::sqrtf(SizeSquared());
}

constexpr float Vector2::SizeSquared() const
{
	return (_x * _x + _y * _y);
}

void Vector2::Normalize()
{
	*this = GetNormalize();
}

Vector2 Vector2::GetNormalize() const
{
	const float magitude = SizeSquared();
	if (magitude == 1.0f)
	{
		return *this;
	}
	else if (magitude < FLT_EPSILON)
	{
		return Vector2::Zero;
	}

	return *this / magitude;
}

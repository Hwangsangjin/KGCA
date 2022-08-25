#include "Vector2.h"

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::LEFT(-1.0f, 0.0f);
const Vector2 Vector2::RIGHT(1.0f, 0.0f);
const Vector2 Vector2::UP(0.0f, -1.0f);
const Vector2 Vector2::DOWN(0.0f, 1.0f);

Vector2::Vector2(float x, float y)
{
	_x = x;
	_y = y;
}

Vector2::Vector2(const Vector2& other)
{
	_x = other._x;
	_y = other._y;
}

float Vector2::Dot(const Vector2& other) const
{
	return (_x * other._x) + (_y * other._y);
}

float Vector2::Length() const
{
	return std::sqrt(LenghtSquared());
}

float Vector2::LenghtSquared() const
{
	return (_x * _x + _y * _y);
}

float Vector2::distance(const Vector2& other) const
{
	return (*this - other).Length();
}

Vector2 Vector2::Normalize() const
{
	const float length = Length();
	if (length < FLT_EPSILON)
	{
		return Vector2::ZERO;
	}

	return *this / length;
}

bool Vector2::IsZero() const
{
	return *this == Vector2::ZERO;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	return *this = *this + other;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	return *this = *this - other;
}

Vector2& Vector2::operator*=(float scalar)
{
	return *this = *this * scalar;
}

Vector2& Vector2::operator/=(float scalar)
{
	return *this = *this / scalar;
}

const Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(_x + other._x, _y + other._y);
}

const Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(_x - other._x, _y - other._y);
}

const Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(_x * scalar, _y * scalar);
}

const Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(_x / scalar, _y / scalar);
}

const Vector2 Vector2::operator-() const
{
	return Vector2(-_x, -_y);
}

bool Vector2::operator==(const Vector2& other) const
{
	return (_x == other._x) && (_y == other._y);
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

bool Vector2::operator<(const Vector2& other) const
{
	if (_x != other._x) return _x < other._x;
	if (_y != other._y) return _y < other._y;

	return false;
}

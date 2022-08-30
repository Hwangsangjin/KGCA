#include "pch.h"
#include "Vector2.h"

const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);
const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::One(1.0f, 1.0f);

Vector2::Vector2(float x, float y)
	: x(x)
	, y(y)
{
}

Vector2::Vector2(const Vector2& vector)
	: x(vector.x)
	, y(vector.y)
{
}

const Vector2& Vector2::operator+=(const Vector2& other)
{
	return *this = *this + other;
}

const Vector2& Vector2::operator-=(const Vector2& other)
{
	return *this = *this - other;
}

const Vector2& Vector2::operator*=(float scalar)
{
	return *this = *this * scalar;
}

const Vector2& Vector2::operator/=(float scalar)
{
	return *this = *this / scalar;
}

const Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

const Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

const Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

const Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

const Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

const bool Vector2::operator==(const Vector2& other) const
{
	return (x == other.x) && (y == other.y);
}

const bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

const bool Vector2::operator<(const Vector2& other) const
{
	if (x != other.x) return x < other.x;
	if (y != other.y) return y < other.y;

	return false;
}

float Vector2::Dot(const Vector2& other) const
{
	return (x * other.x) + (y * other.y);
}

float Vector2::Angle(const Vector2& other) const
{
	float cos = Dot(other);
	cos /= (Length() * other.Length());
	float radian = acos(cos);
	float degree = RadianToDegree(radian);
	return degree;
}

float Vector2::Length() const
{
	return std::sqrtf(LengthSquared());
}

float Vector2::LengthSquared() const
{
	return (x * x + y * y);
}

float Vector2::Distance(const Vector2& other) const
{
	return (*this - other).Length();
}

void Vector2::Normalize()
{
	*this = Identity();
}

Vector2 Vector2::Identity() const
{
	const float magnitude = LengthSquared();
	if (magnitude == 1.0f)
	{
		return *this;
	}
	else if (magnitude < FLT_EPSILON)
	{
		return Vector2::Zero;
	}

	return *this / magnitude;
}

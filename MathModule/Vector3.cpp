#include "pch.h"
#include "Vector3.h"

const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);

Vector3::Vector3(float x, float y, float z)
	: x(x)
	, y(y)
	, z(z)
{
}

Vector3::Vector3(const Vector3& vector)
	: x(vector.x)
	, y(vector.y)
	, z(vector.z)
{
}

const Vector3& Vector3::operator+=(const Vector3& other)
{
	return *this = *this + other;
}

const Vector3& Vector3::operator-=(const Vector3& other)
{
	return *this = *this - other;

}

const Vector3& Vector3::operator*=(float scalar)
{
	return *this = *this * scalar;
}

const Vector3& Vector3::operator/=(float scalar)
{
	return *this = *this / scalar;
}

const Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

const Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

const Vector3 Vector3::operator*(float scalar) const
{
	return Vector3(x * scalar, y * scalar, z * scalar);
}

const Vector3 Vector3::operator/(float scalar) const
{
	return Vector3(x / scalar, y / scalar, z / scalar);
}

const Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

const bool Vector3::operator==(const Vector3& other) const
{
	return (x == other.x) && (y == other.y) && (z == other.z);
}

const bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

const bool Vector3::operator<(const Vector3& other) const
{
	if (x != other.x) return x < other.x;
	if (y != other.y) return y < other.y;
	if (z != other.z) return z < other.z;

	return false;
}

const bool Vector3::operator<=(const Vector3& other) const
{
	if (fabs(x - other.x) <= FLT_EPSILON)
	{
		if (fabs(y - other.y) <= FLT_EPSILON)
		{
			if (fabs(z - other.z) <= FLT_EPSILON)
			{
				return true;
			}
		}
	}

	return false;
}

const bool Vector3::operator>=(const Vector3& other) const
{
	if (fabs(x - other.x) >= FLT_EPSILON)
	{
		if (fabs(y - other.y) >= FLT_EPSILON)
		{
			if (fabs(z - other.z) >= FLT_EPSILON)
			{
				return true;
			}
		}
	}

	return false;
}

float Vector3::Dot(const Vector3& other) const
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}

float Vector3::Angle(const Vector3& other) const
{
	float cos = Dot(other);
	cos /= (Length() * other.Length());
	float radian = acos(cos);
	float degree = RadianToDegree(radian);
	return degree;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float Vector3::Length() const
{
	return std::sqrtf(LengthSquared());
}

float Vector3::LengthSquared() const
{
	return (x * x + y * y + z * z);
}

float Vector3::Distance(const Vector3& other) const
{
	return (*this - other).Length();
}

void Vector3::Normalize()
{
	*this = Identity();
}

Vector3 Vector3::Identity() const
{
	const float magnitude = LengthSquared();
	if (magnitude == 1.0f)
	{
		return *this;
	}
	else if (magnitude < FLT_EPSILON)
	{
		return Vector3::Zero;
	}

	return *this / magnitude;
}

#include "pch.h"
#include "Vector3.h"

Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector3::Vector3(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
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
	return Vector3(x + other.x, y + other.y, other.z);
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
	return Vector3();
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

Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float Vector3::Size() const
{
	return std::sqrtf(SizeSquared());
}

float Vector3::SizeSquared() const
{
	return (x * x + y * y + z * z);
}

void Vector3::Normalize()
{
	*this = GetNormalize();
}

Vector3 Vector3::GetNormalize() const
{
	Vector3 ret = *this;
	float fInvertLength = 1.0f / Size();
	ret.x = ret.x * fInvertLength;
	ret.y = ret.y * fInvertLength;
	ret.z = ret.z * fInvertLength;
	return ret;
}

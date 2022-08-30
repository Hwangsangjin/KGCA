#include "pch.h"
#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w)
    : x(x)
    , y(y)
    , z(z)
    , w(w)
{
}

Vector4::Vector4(const Vector4& vector)
    : x(vector.x)
    , y(vector.y)
    , z(vector.z)
    , w(vector.w)
{
}

const Vector4& Vector4::operator+=(const Vector4& other)
{
    return *this = *this + other;
}

const Vector4& Vector4::operator-=(const Vector4& other)
{
    return *this = *this - other;
}

const Vector4& Vector4::operator*=(float scalar)
{
    return *this = *this * scalar;
}

const Vector4& Vector4::operator/=(float scalar)
{
    return *this = *this / scalar;
}

const Vector4 Vector4::operator+(const Vector4& other) const
{
    return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}

const Vector4 Vector4::operator-(const Vector4& other) const
{
    return Vector4(x - other.x, y - other.y, z - other.z, w - other.z);
}

const Vector4 Vector4::operator*(float scalar) const
{
    return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
}

const Vector4 Vector4::operator/(float scalar) const
{
    return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
}

const Vector4 Vector4::operator-() const
{
    return Vector4(-x, -y, -z, -w);
}

const bool Vector4::operator==(const Vector4& other) const
{
    return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
}

const bool Vector4::operator!=(const Vector4& other) const
{
    return !(*this == other);
}

const bool Vector4::operator<=(const Vector4& other) const
{
    if (fabs(x - other.x) <= FLT_EPSILON)
    {
        if (fabs(y - other.y) <= FLT_EPSILON)
        {
            if (fabs(z - other.z) <= FLT_EPSILON)
            {
                if (fabs(w - other.w) <= FLT_EPSILON)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

const bool Vector4::operator>=(const Vector4& other) const
{
    if (fabs(x - other.x) >= FLT_EPSILON)
    {
        if (fabs(y - other.y) >= FLT_EPSILON)
        {
            if (fabs(z - other.z) >= FLT_EPSILON)
            {
                if (fabs(w - other.w) >= FLT_EPSILON)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

float Vector4::Dot(const Vector4& other) const
{
    return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

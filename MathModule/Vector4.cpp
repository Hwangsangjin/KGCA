#include "pch.h"
#include "Vector4.h"

const Vector4 Vector4::UnitX(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitY(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UnitZ(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UnitW(0.0f, 0.0f, 0.0f, 1.0f);
const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::One(1.0f, 1.0f, 1.0f, 1.0f);

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

float Vector4::Angle(const Vector4& other) const
{
    float cos = Dot(other);
    cos /= (Length() * other.Length());
    float radian = acos(cos);
    float degree = RadianToDegree(radian);
    return degree;
}

float Vector4::Length() const
{
    return std::sqrtf(LengthSquared());
}

float Vector4::LengthSquared() const
{
    return (x * x + y * y + z * z);
}

float Vector4::Distance(const Vector4& other) const
{
    return (*this - other).Length();
}

void Vector4::Normalize()
{
    *this = Identity();
}

Vector4 Vector4::Identity() const
{
    const float magnitude = LengthSquared();
    if (magnitude == 1.0f)
    {
        return *this;
    }
    else if (magnitude < FLT_EPSILON)
    {
        return Vector4::Zero;
    }

    return *this / magnitude;
}

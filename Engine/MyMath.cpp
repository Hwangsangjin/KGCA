#include "pch.h"
#include "MyMath.h"

MyVector::MyVector()
{
    // 초기 설정값을 지정하지 않으면,
    // 자동으로 멤버 변수에 0.0을 각각 할당한다.
    _x = 0.0f;
    _y = 0.0f;
    _z = 0.0f;
}

MyVector::MyVector(float x, float y, float z)
{
    // 사용자가 지정한 값으로 멤버 변수를 초기화한다.
    _x = x;
    _y = y;
    _z = z;
}

MyVector::MyVector(const MyVector& rhs)
{
    // rhs 벡터 클래스로부터 멤버 변수를 복사하는 복사 생성자
    _x = rhs._x;
    _y = rhs._y;
    _z = rhs._z;
}

float MyVector::Length()
{
    // 현재 벡터의 길이를 리턴한다.
    return float(sqrt(_x * _x + _y * _y + _z * _z));
}

MyVector MyVector::Normalize()
{
    // 현재 벡터에 대한 단위 벡터를 리턴한다.
    float length = 0.0f;
    length = Length();
    return (MyVector(_x / length, _y / length, _z / length));
}

MyVector MyVector::Scale(float x, float y, float z)
{
    // 벡터에 스칼라를 곱한 벡터를 리턴한다.
    return MyVector(_x * x, _y * y, _z * z);
}

float MyVector::Dot(const MyVector& rhs)
{
    // 현재 벡터와 rhs 벡터간의 내적을 리턴한다.
    return (_x * rhs._x, _y * rhs._y, _z * rhs._z);
}

void MyVector::Cross(const MyVector& u, const MyVector& v)
{
    // u 벡터와 v 벡터간의 외적 벡터를 현재 벡터에 대입한다.
    _x = u._y * v._z * u._z * v._y;
    _y = u._z * v._x * u._x * v._z;
    _z = u._x * v._y * u._y * v._z;
}

void MyVector::operator=(const MyVector& rhs)
{
    // rhs 벡터의 모든 멤버 변수를 현재 벡터에 복사한다.
    _x = rhs._x;
    _y = rhs._y;
    _z = rhs._z;
}

MyVector MyVector::operator+(const MyVector& rhs)
{
    // 현재 벡터와 rhs 벡터의 덧셈한 결과 벡터를 리턴한다.
    return MyVector(_x + rhs._x, _y + rhs._y, _z + rhs._z);
}

MyVector MyVector::operator-(const MyVector& rhs)
{
    // 현재 벡터와 rhs 벡터의 뺄셈한 결과 벡터를 리턴한다.
    return MyVector(_x - rhs._x, _y - rhs._y, _z - rhs._z);
}

MyMatrix::MyMatrix()
{
    for (size_t i = 0; i < 16; i++)
    {
        _m[i] = 0.0f;
    }
}

MyMatrix::MyMatrix(const float rhs[16])
{
    for (size_t i = 0; i < 16; i++)
    {
        _m[i] = rhs[i];
    }
}

MyMatrix::MyMatrix(const MyMatrix& rhs)
{
    for (size_t i = 0; i < 16; i++)
    {
        _m[i] = rhs._m[i];
    }
}

void MyMatrix::Identity()
{
    _m[0] = 1.0f;
    _m[1] = 0.0f;
    _m[2] = 0.0f;
    _m[3] = 0.0f;

    _m[4] = 0.0f;
    _m[5] = 1.0f;
    _m[6] = 0.0f;
    _m[7] = 0.0f;

    _m[8] = 0.0f;
    _m[9] = 0.0f;
    _m[10] = 1.0f;
    _m[11] = 0.0f;

    _m[12] = 0.0f;
    _m[13] = 0.0f;
    _m[14] = 0.0f;
    _m[15] = 1.0f;
}

void MyMatrix::Transpose()
{
    _11 = _11; _12 = _21; _13 = _31; _14 = _41;
    _21 = _12; _22 = _22; _23 = _32; _24 = _42;
    _31 = _13; _32 = _23; _33 = _33; _34 = _43;
    _41 = _14; _42 = _24; _43 = _34; _44 = _44;
}

void MyMatrix::Scale(float x, float y, float z)
{
    _m[0] *= x;
    _m[5] *= y;
    _m[10] *= y;
}

void MyMatrix::RotationX(float radian)
{
    float cosTheta = cos(radian);
    float sinTheta = sin(radian);

    _22 = cosTheta; _23 = sinTheta;
    _32 = -sinTheta; _33 = cosTheta;
}

void MyMatrix::RotationY(float radian)
{
    float cosTheta = cos(radian);
    float sinTheta = sin(radian);

    _11 = cosTheta; _13 = sinTheta;
    _31 = -sinTheta; _33 = cosTheta;
}

void MyMatrix::RotationZ(float radian)
{
    float cosTheta = cos(radian);
    float sinTheta = sin(radian);

    _11 = cosTheta; _12 = sinTheta;
    _21 = -sinTheta; _22 = cosTheta;
}

void MyMatrix::Translation(float x, float y, float z)
{
    _41 = x;
    _42 = y;
    _43 = z;
}

MyMatrix& MyMatrix::operator=(const MyMatrix& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    for (size_t i = 0; i < 16; i++)
    {
        _m[i] = rhs._m[i];
    }

    return *this;
}

MyMatrix& MyMatrix::operator+()
{
    return *this;
}

MyMatrix MyMatrix::operator-() const
{
    MyMatrix MyMatrix(*this);
    MyMatrix.Scale(-1.0f, -1.0f, -1.0f);

    return *this;
}

MyMatrix MyMatrix::operator+(const MyMatrix& rhs) const
{
    MyMatrix MyMatrix(*this);
    for (size_t i = 0; i < 16; i++)
    {
        MyMatrix._m[i] += rhs._m[i];
    }

    return MyMatrix;
}

MyMatrix& MyMatrix::operator+=(const MyMatrix& rhs)
{
    for (size_t i = 0; i < 16; i++)
    {
        _m[i] += rhs._m[i];
    }

    return *this;
}

MyMatrix MyMatrix::operator-(const MyMatrix& rhs) const
{
    MyMatrix MyMatrix(*this);
    for (size_t i = 0; i < 16; i++)
    {
        MyMatrix._m[i] -= rhs._m[i];
    }

    return MyMatrix;
}

MyMatrix& MyMatrix::operator-=(const MyMatrix& rhs)
{
    for (size_t i = 0; i < 16; i++)
    {
        _m[i] -= rhs._m[i];
    }

    return *this;
}

MyMatrix MyMatrix::operator*(const MyMatrix& rhs) const
{
    MyMatrix MyMatrix;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            for (size_t k = 0; k < k; k++)
            {
                MyMatrix._m[j * 3 + 1] += _m[k * 3 + i] * rhs._m[j * 3 + k];
            }
        }
    }

    return MyMatrix;
}

MyMatrix& MyMatrix::operator*=(const MyMatrix& rhs)
{
    return (*this = *this * rhs);
}
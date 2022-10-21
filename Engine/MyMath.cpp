#include "pch.h"
#include "MyMath.h"

MyVector2::MyVector2()
{
    // 초기 설정값을 지정하지 않으면,
    // 자동으로 멤버 변수에 0.0을 각각 할당한다.
    _x = 0.0f;
    _y = 0.0f;
}

MyVector2::MyVector2(float x, float y)
{
    // 사용자가 지정한 값으로 멤버 변수를 초기화한다.
    _x = x;
    _y = y;
}

MyVector2::MyVector2(const MyVector2& rhs)
{
    // rhs 벡터 클래스로부터 멤버 변수를 복사하는 복사 생성자
    _x = rhs._x;
    _y = rhs._y;
}

float MyVector2::Length()
{
    // 현재 벡터의 길이를 리턴한다.
    return float(sqrt(_x * _x + _y * _y));
}

MyVector2 MyVector2::Normalize()
{
    // 현재 벡터에 대한 단위 벡터를 리턴한다.
    float length = 0.0f;
    length = Length();
    return (MyVector2(_x / length, _y / length));
}

MyVector2 MyVector2::Scale(float x, float y)
{
    // 벡터에 스칼라를 곱한 벡터를 리턴한다.
    return MyVector2(_x * x, _y * y);
}

float MyVector2::Dot(const MyVector2& rhs)
{
    // 현재 벡터와 rhs 벡터간의 내적을 리턴한다.
    return (_x * rhs._x, _y * rhs._y);
}

void MyVector2::operator=(const MyVector2& rhs)
{
    // rhs 벡터의 모든 멤버 변수를 현재 벡터에 복사한다.
    _x = rhs._x;
    _y = rhs._y;
}

MyVector2 MyVector2::operator+(const MyVector2& rhs)
{
    // 현재 벡터와 rhs 벡터의 덧셈한 결과 벡터를 리턴한다.
    return MyVector2(_x + rhs._x, _y + rhs._y);
}

MyVector2 MyVector2::operator-(const MyVector2& rhs)
{
    // 현재 벡터와 rhs 벡터의 뺄셈한 결과 벡터를 리턴한다.
    return MyVector2(_x - rhs._x, _y - rhs._y);
}

MyVector3::MyVector3()
{
    // 초기 설정값을 지정하지 않으면,
    // 자동으로 멤버 변수에 0.0을 각각 할당한다.
    _x = 0.0f;
    _y = 0.0f;
    _z = 0.0f;
}

MyVector3::MyVector3(float x, float y, float z)
{
    // 사용자가 지정한 값으로 멤버 변수를 초기화한다.
    _x = x;
    _y = y;
    _z = z;
}

MyVector3::MyVector3(const MyVector3& rhs)
{
    // rhs 벡터 클래스로부터 멤버 변수를 복사하는 복사 생성자
    _x = rhs._x;
    _y = rhs._y;
    _z = rhs._z;
}

float MyVector3::Length()
{
    // 현재 벡터의 길이를 리턴한다.
    return float(sqrt(_x * _x + _y * _y + _z * _z));
}

MyVector3 MyVector3::Normalize()
{
    // 현재 벡터에 대한 단위 벡터를 리턴한다.
    float length = 0.0f;
    length = Length();
    return (MyVector3(_x / length, _y / length, _z / length));
}

MyVector3 MyVector3::Scale(float x, float y, float z)
{
    // 벡터에 스칼라를 곱한 벡터를 리턴한다.
    return MyVector3(_x * x, _y * y, _z * z);
}

float MyVector3::Dot(const MyVector3& rhs)
{
    // 현재 벡터와 rhs 벡터간의 내적을 리턴한다.
    return (_x * rhs._x, _y * rhs._y, _z * rhs._z);
}

void MyVector3::Cross(const MyVector3& u, const MyVector3& v)
{
    // u 벡터와 v 벡터간의 외적 벡터를 현재 벡터에 대입한다.
    _x = u._y * v._z * u._z * v._y;
    _y = u._z * v._x * u._x * v._z;
    _z = u._x * v._y * u._y * v._z;
}

void MyVector3::operator=(const MyVector3& rhs)
{
    // rhs 벡터의 모든 멤버 변수를 현재 벡터에 복사한다.
    _x = rhs._x;
    _y = rhs._y;
    _z = rhs._z;
}

MyVector3 MyVector3::operator+(const MyVector3& rhs)
{
    // 현재 벡터와 rhs 벡터의 덧셈한 결과 벡터를 리턴한다.
    return MyVector3(_x + rhs._x, _y + rhs._y, _z + rhs._z);
}

MyVector3 MyVector3::operator-(const MyVector3& rhs)
{
    // 현재 벡터와 rhs 벡터의 뺄셈한 결과 벡터를 리턴한다.
    return MyVector3(_x - rhs._x, _y - rhs._y, _z - rhs._z);
}

const MyVector3& MyVector3::operator+=(const MyVector3& rhs)
{
    _x += rhs._x;
    _y += rhs._y;
    _z += rhs._z;

    return *this;
}

const MyVector3& MyVector3::operator-=(const MyVector3& rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;
    _z -= rhs._z;

    return *this;
}

MyVector3 MyVector3::operator*(float scala)
{
    return MyVector3(_x * scala, _y * scala, _z * scala);
}

MyVector3 MyVector3::operator*=(float scala)
{
    _x *= scala;
    _y *= scala;
    _z *= scala;
    return *this;
}

MyVector3 MyVector3::operator*(class MyMatrix& m)
{
    MyVector3 v;
    v._x = _x * m._11 + _y * m._21 + _z * m._31 + 1.0f * m._41;
    v._y = _x * m._12 + _y * m._22 + _z * m._32 + 1.0f * m._42;
    v._z = _x * m._13 + _y * m._23 + _z * m._33 + 1.0f * m._43;
    return v;
}

MyMatrix::MyMatrix()
{
    Identity();
}

void MyMatrix::Identity()
{
    _12 = _13 = _14 = 0.0f;
    _21 = _23 = _24 = 0.0f;
    _31 = _32 = _34 = 0.0f;
    _41 = _42 = _43 = 0.0f;
    _11 = _22 = _33 = _44 = 1.0f;
}

MyMatrix MyMatrix::Transpose()
{
    MyMatrix m;

    m._11 = _11; m._12 = _21; m._13 = _31; m._14 = _41;
    m._21 = _12; m._22 = _22; m._23 = _32; m._24 = _42;
    m._31 = _13; m._32 = _23; m._33 = _33; m._34 = _43;
    m._41 = _14; m._42 = _24; m._43 = _34; m._44 = _44;

    return m;
}

void MyMatrix::Scale(float x, float y, float z)
{
    //Identity();

    _11 = x;
    _22 = y;
    _33 = z;
}

void MyMatrix::RotationX(float radian)
{
    //Identity();

    float cosTheta = cos(radian);
    float sinTheta = sin(radian);

    _22 = cosTheta; _23 = sinTheta;
    _32 = -sinTheta; _33 = cosTheta;
}

void MyMatrix::RotationY(float radian)
{
    //Identity();

    float cosTheta = cos(radian);
    float sinTheta = sin(radian);

    _11 = cosTheta; _13 = sinTheta;
    _31 = -sinTheta; _33 = cosTheta;
}

void MyMatrix::RotationZ(float radian)
{
    //Identity();

    float cosTheta = cos(radian);
    float sinTheta = sin(radian);

    _11 = cosTheta; _12 = sinTheta;
    _21 = -sinTheta; _22 = cosTheta;
}

void MyMatrix::Translation(float x, float y, float z)
{
    //Identity();

    _41 = x;
    _42 = y;
    _43 = z;
}

MyMatrix MyMatrix::operator*(const MyMatrix& rhs) const
{
    MyMatrix m;

    for (int column = 0; column < 4; column++)
    {
        for (int row = 0; row < 4; row++)
        {
            m._m[row][column] =
                _m[row][0] * rhs._m[0][column] +
                _m[row][1] * rhs._m[1][column] +
                _m[row][2] * rhs._m[2][column] +
                _m[row][3] * rhs._m[3][column];
        }
    }

    return m;
}

float MyVector3::operator|(const MyVector3 & v0)
{
    return _x * v0._x + _y * v0._y + _z * v0._z;
}

MyVector3 MyVector3::operator^(const MyVector3& v0)
{
    return MyVector3((_y * v0._z - _z * v0._y), (_z * v0._x - _x * v0._z), (_x * v0._y - _y * v0._x));
}

void MyMatrix::ObjectLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp)
{
    MyVector3 vDirection = vTarget - vPosition;
    vDirection = vDirection.Normalize();
    float fDot = vUp | vDirection;
    MyVector3 vC = vDirection * fDot;
    MyVector3 vD = (vDirection * fDot);
    MyVector3 vUpVector = vUp - vD;
    vUpVector = vUpVector.Normalize();
    MyVector3 vRightVector = vUpVector ^ vDirection;

    _11 = vRightVector._x;	_12 = vRightVector._y;	_13 = vRightVector._z;
    _21 = vUpVector._x;		_22 = vUpVector._y;		_23 = vUpVector._z;
    _31 = vDirection._x;	_32 = vDirection._y;	_33 = vDirection._z;
    _41 = vPosition._x;
    _42 = vPosition._y;
    _43 = vPosition._z;
}

MyMatrix MyMatrix::ViewLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp)
{
    MyMatrix matrix;
    MyVector3 vDirection = (vTarget - vPosition).Normalize();
    MyVector3 vRightVector = (vUp ^ vDirection).Normalize();
    MyVector3 vUpVector = (vDirection ^ vRightVector).Normalize();

    _11 = vRightVector._x;	_12 = vUpVector._x;	_13 = vDirection._x;
    _21 = vRightVector._y;	_22 = vUpVector._y;	_23 = vDirection._y;
    _31 = vRightVector._z;	_32 = vUpVector._z;	_33 = vDirection._z;

    _41 = -(vPosition._x * _11 + vPosition._y * _21 + vPosition._z * _31);
    _42 = -(vPosition._x * _12 + vPosition._y * _22 + vPosition._z * _32);
    _43 = -(vPosition._x * _13 + vPosition._y * _23 + vPosition._z * _33);

    memcpy(&matrix, this, 16 * sizeof(float));
    return matrix;
}

MyMatrix MyMatrix::OrthoLH(float w, float h, float n, float f)
{
    Identity();

    _11 = 2.0f / w;
    _22 = 2.0f / h;
    _33 = 1.0f / (f - n);
    _43 = -n / (f - n);

    return *this;
}

MyMatrix MyMatrix::OrthoOffCenterLH(float l, float r, float b, float t, float n, float f)
{
    Identity();

    _11 = 2.0f / (r - l);
    _22 = 2.0f / (t - b);
    _33 = 1.0f / (f - n);
    _43 = -n / (f - n);
    _41 - (l + r) / (l - r);
    _42 - (t + b) / (b - t);

    return *this;
}

MyMatrix MyMatrix::PerspectiveFovLH(float NearPlane, float FarPlane, float FovY, float AspectRatio)
{
    float h, w, Q;

    h = 1 / tan(FovY * 0.5f);  // 1/tans(x) = cot(x)
    w = h / AspectRatio;

    Q = FarPlane / (FarPlane - NearPlane);

    MyMatrix temp;
    ZeroMemory(this, sizeof(MyMatrix));

    _11 = w;
    _22 = h;
    _33 = Q;
    _43 = -Q * NearPlane;
    _34 = 1;
    _44 = 0.0f;

    memcpy((void*)&temp, this, 16 * sizeof(float));
    return temp;
}

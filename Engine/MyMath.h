#pragma once

#include <math.h>

class MyVector2
{
public:
	// ������ - ��� ������ �ʱ�ȭ
	MyVector2();
	// x, y, z�� �ʱⰪ�� �Է����� �ϴ� ������
	MyVector2(float x, float y);
	// ���� ������
	MyVector2(const MyVector2& rhs);

	// �Ҹ���
	~MyVector2() {}

	// ���� ������ ���� ����
	float Length();

	// ���� ������ ���� ���� ����
	MyVector2 Normalize();

	// ���Ϳ� ��Į�� ���� ���� ����
	MyVector2 Scale(float x, float y);

	// ������ ���� - ���� ���Ϳ� rhs ���Ͱ��� ���� ����
	float Dot(const MyVector2& rhs);

	// rhs ������ ��� ��� ������ ���� ���Ϳ� ����
	void operator=(const MyVector2& rhs);
	// ���� ���Ϳ� rhs ������ ������ ��� ���� ����
	MyVector2 operator+(const MyVector2& rhs);
	// ���� ���Ϳ� rhs ������ ������ ��� ���� ����
	MyVector2 operator-(const MyVector2& rhs);

	// 2���� ������ ��� ���� x, y
	// ���� ������ ���� �׼����� �� �ֵ��� public ����
	union
	{
		struct
		{
			float _x;
			float _y;
		};

		float _v[2];
	};
};

class MyVector3
{
public:
	// ������ - ��� ������ �ʱ�ȭ
	MyVector3();
	// x, y, z�� �ʱⰪ�� �Է����� �ϴ� ������
	MyVector3(float x, float y, float z);
	// ���� ������
	MyVector3(const MyVector3& rhs);

	// �Ҹ���
	~MyVector3() {}

	// ���� ������ ���� ����
	float Length();

	// ���� ������ ���� ���� ����
	MyVector3 Normalize();

	// ���Ϳ� ��Į�� ���� ���� ����
	MyVector3 Scale(float x, float y, float z);

	// ������ ���� - ���� ���Ϳ� rhs ���Ͱ��� ���� ����
	float Dot(const MyVector3& rhs);

	// ������ ���� - u ���Ϳ� v ���Ͱ��� ���� ���͸� ���� ���Ϳ� ����
	void Cross(const MyVector3& u, const MyVector3& v);

	// rhs ������ ��� ��� ������ ���� ���Ϳ� ����
	void operator=(const MyVector3& rhs);
	// ���� ���Ϳ� rhs ������ ������ ��� ���� ����
	MyVector3 operator+(const MyVector3& rhs);
	// ���� ���Ϳ� rhs ������ ������ ��� ���� ����
	MyVector3 operator-(const MyVector3& rhs);

	//
	MyVector3 operator*(float scala);
	MyVector3 operator*=(float scala);
	MyVector3 operator*(class MyMatrix& m);

	// Dot Product
	float operator|(const MyVector3& v0);
	// Cross Product
	MyVector3 operator^(const MyVector3& v0);

	// 3���� ������ ��� ���� x, y, z
	// ���� ������ ���� �׼����� �� �ֵ��� public ����
	union
	{
		struct
		{
			float _x;
			float _y;
			float _z;
		};

		float _v[3];
	};
};

class MyMatrix
{
public:
	// ������
	MyMatrix();
	// �Ҹ���
	~MyMatrix() {}

	// ���� ���
	void Identity();
	// ��ġ ���
	MyMatrix Transpose();

	// ����
	MyMatrix Scale(float x, float y, float z);
	// ȸ��
	MyMatrix RotationX(float radian);
	MyMatrix RotationY(float radian);
	MyMatrix RotationZ(float radian);
	// �̵�
	MyMatrix Translation(float x, float y, float z);

	//// ���� ������
	//MyMatrix& operator=(const MyMatrix& rhs);
	//// + ���� ������
	//MyMatrix& operator+();
	//// - ���� ������
	//MyMatrix operator-() const;

	//// ����� ����
	//MyMatrix operator+(const MyMatrix& rhs) const;
	//MyMatrix& operator+=(const MyMatrix& rhs);
	//// ����� ����
	//MyMatrix operator-(const MyMatrix& rhs) const;
	//MyMatrix& operator-=(const MyMatrix& rhs);
	// ����� ����
	MyMatrix operator*(const MyMatrix& rhs) const;
	/*MyMatrix& operator*=(const MyMatrix& rhs);*/

	// ����� ����
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};

		float _m[4][4];
	};

	// ī�޶� ����
	void ObjectLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp);
	MyMatrix ViewLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp);
	MyMatrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect);
};


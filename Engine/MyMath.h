#pragma once

#include <math.h>

class MyVector
{
public:
	// ������ - ��� ������ �ʱ�ȭ
	MyVector();
	// x, y, z�� �ʱⰪ�� �Է����� �ϴ� ������
	MyVector(float x, float y, float z);
	// ���� ������
	MyVector(const MyVector& rhs);

	// �Ҹ���
	~MyVector() {}

	// ���� ������ ���� ����
	float Length();

	// ���� ������ ���� ���� ����
	MyVector Normalize();

	// ���Ϳ� ��Į�� ���� ���� ����
	MyVector Scale(float x, float y, float z);

	// ������ ���� - ���� ���Ϳ� rhs ���Ͱ��� ���� ����
	float Dot(const MyVector& rhs);

	// ������ ���� - u ���Ϳ� v ���Ͱ��� ���� ���͸� ���� ���Ϳ� ����
	void Cross(const MyVector& u, const MyVector& v);

	// rhs ������ ��� ��� ������ ���� ���Ϳ� ����
	void operator=(const MyVector& rhs);
	// ���� ���Ϳ� rhs ������ ������ ��� ���� ����
	MyVector operator+(const MyVector& rhs);
	// ���� ���Ϳ� rhs ������ ������ ��� ���� ����
	MyVector operator-(const MyVector& rhs);

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
	MyMatrix(const float rhs[16]);
	MyMatrix(const MyMatrix& rhs);

	// �Ҹ���
	~MyMatrix() {}

	// ���� ���
	void Identity();
	// ��ġ ���
	void Transpose();

	// ����
	void Scale(float x, float y, float z);
	// ȸ��
	void RotationX(float radian);
	void RotationY(float radian);
	void RotationZ(float radian);
	// �̵�
	void Translation(float x, float y, float z);

	// ���� ������
	MyMatrix& operator=(const MyMatrix& rhs);
	// + ���� ������
	MyMatrix& operator+();
	// - ���� ������
	MyMatrix operator-() const;

	// ����� ����
	MyMatrix operator+(const MyMatrix& rhs) const;
	MyMatrix& operator+=(const MyMatrix& rhs);
	// ����� ����
	MyMatrix operator-(const MyMatrix& rhs) const;
	MyMatrix& operator-=(const MyMatrix& rhs);
	// ����� ����
	MyMatrix operator*(const MyMatrix& rhs) const;
	MyMatrix& operator*=(const MyMatrix& rhs);

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

		float _m[16];
	};
};


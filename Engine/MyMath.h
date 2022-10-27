#pragma once

class MyVector2
{
public:
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
};

class MyVector3
{
public:
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

	// operator
	bool operator==(MyVector3& rhs);

	MyVector3 operator+() const;
	MyVector3 operator-() const;

	const MyVector3& operator+=(const MyVector3& rhs);
	const MyVector3& operator-=(const MyVector3& rhs);

	MyVector3 operator*(float scala);
	MyVector3 operator*=(float scala);
	MyVector3 operator*(class MyMatrix& m);

	// Dot Product
	float operator|(const MyVector3& v0);
	// Cross Product
	MyVector3 operator^(const MyVector3& v0);
};

class MyMatrix
{
public:
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

	// ������
	MyMatrix();
	// �Ҹ���
	~MyMatrix() {}

	// ���� ���
	void Identity();
	// ��ġ ���
	MyMatrix Transpose();

	// ����
	void Scale(float x, float y, float z);
	// ȸ��
	void RotationX(float radian);
	void RotationY(float radian);
	void RotationZ(float radian);
	// �̵�
	void Translation(float x, float y, float z);

	// ����� ����
	MyMatrix operator*(const MyMatrix& rhs) const;

	// ��
	void ObjectLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp);
	MyMatrix ViewLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp);

	// ����
	MyMatrix OrthoLH(float w, float h, float n, float f);
	MyMatrix OrthoOffCenterLH(float l, float r, float b, float t, float n, float f);
	MyMatrix PerspectiveFovLH(float NearPlane, float FarPlane, float FovY, float AspectRatio);
};

namespace StaticMatrix
{
	// ����
	static MyMatrix Scale(float x, float y, float z)
	{
		MyMatrix m;
		m._11 = x;
		m._22 = y;
		m._33 = z;

		return m;
	}

	// ȸ��
	static MyMatrix RotationX(float radian)
	{
		float cosTheta = cos(radian);
		float sinTheta = sin(radian);

		MyMatrix m;
		m._22 = cosTheta; m._23 = sinTheta;
		m._32 = -sinTheta; m._33 = cosTheta;

		return m;
	}

	static MyMatrix RotationY(float radian)
	{
		float cosTheta = cos(radian);
		float sinTheta = sin(radian);

		MyMatrix m;
		m._11 = cosTheta; m._13 = sinTheta;
		m._31 = -sinTheta; m._33 = cosTheta;

		return m;
	}

	static MyMatrix RotationZ(float radian)
	{
		float cosTheta = cos(radian);
		float sinTheta = sin(radian);

		MyMatrix m;
		m._11 = cosTheta; m._12 = sinTheta;
		m._21 = -sinTheta; m._22 = cosTheta;

		return m;
	}

	// �̵�
	static MyMatrix Translation(float x, float y, float z)
	{
		MyMatrix m;
		m._41 = x;
		m._42 = y;
		m._43 = z;

		return m;
	}

	// ����
	static MyMatrix OrthoLH(float w, float h, float n, float f)
	{
		MyMatrix m;

		m._11 = 2.0f / w;
		m._22 = 2.0f / h;
		m._33 = 1.0f / (f - n);
		m._43 = -n / (f - n);

		return m;
	}

	static MyMatrix OrthoOffCenterLH(float l, float r, float b, float t, float n, float f)
	{
		MyMatrix m;

		m._11 = 2.0f / (r - l);
		m._22 = 2.0f / (t - b);
		m._33 = 1.0f / (f - n);
		m._43 = -n / (f - n);
		m._41 - (l + r) / (l - r);
		m._42 - (t + b) / (b - t);

		return m;
	}

	// ����
	static MyMatrix OrthoLH(MyMatrix m, float w, float h, float n, float f)
	{
		m.Identity();

		m._11 = 2.0f / w;
		m._22 = 2.0f / h;
		m._33 = 1.0f / (f - n);
		m._43 = -n / (f - n);

		return m;
	}

	static MyMatrix OrthoOffCenterLH(MyMatrix m, float l, float r, float b, float t, float n, float f)
	{
		m.Identity();

		m._11 = 2.0f / (r - l);
		m._22 = 2.0f / (t - b);
		m._33 = 1.0f / (f - n);
		m._43 = -n / (f - n);
		m._41 - (l + r) / (l - r);
		m._42 - (t + b) / (b - t);

		return m;
	}

	static MyMatrix PerspectiveFovLH(MyMatrix m, float NearPlane, float FarPlane, float FovY, float AspectRatio)
	{
		float h, w, Q;

		h = 1 / tan(FovY * 0.5f);  // 1/tans(x) = cot(x)
		w = h / AspectRatio;

		Q = FarPlane / (FarPlane - NearPlane);

		m._11 = w;
		m._22 = h;
		m._33 = Q;
		m._43 = -Q * NearPlane;
		m._34 = 1;
		m._44 = 0.0f;

		return m;
	}
}

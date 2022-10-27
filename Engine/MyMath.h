#pragma once

class MyVector2
{
public:
	// 2차원 벡터의 멤버 변수 x, y
	// 벡터 성분을 직접 액세스할 수 있도록 public 설정
	union
	{
		struct
		{
			float _x;
			float _y;
		};

		float _v[2];
	};

	// 생성자 - 멤버 변수를 초기화
	MyVector2();
	// x, y, z의 초기값을 입력으로 하는 생성자
	MyVector2(float x, float y);
	// 복사 생성자
	MyVector2(const MyVector2& rhs);

	// 소멸자
	~MyVector2() {}

	// 현재 벡터의 길이 리턴
	float Length();

	// 현재 벡터의 단위 벡터 리턴
	MyVector2 Normalize();

	// 벡터에 스칼라를 곱한 벡터 리턴
	MyVector2 Scale(float x, float y);

	// 벡터의 내적 - 현재 벡터와 rhs 벡터간의 내적 리턴
	float Dot(const MyVector2& rhs);

	// rhs 벡터의 모든 멤버 변수를 현재 벡터에 복사
	void operator=(const MyVector2& rhs);
	// 현재 벡터와 rhs 벡터의 덧셈한 결과 벡터 리턴
	MyVector2 operator+(const MyVector2& rhs);
	// 현재 벡터와 rhs 벡터의 뺄셈한 결과 벡터 리턴
	MyVector2 operator-(const MyVector2& rhs);
};

class MyVector3
{
public:
	// 3차원 벡터의 멤버 변수 x, y, z
	// 벡터 성분을 직접 액세스할 수 있도록 public 설정
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

	// 생성자 - 멤버 변수를 초기화
	MyVector3();
	// x, y, z의 초기값을 입력으로 하는 생성자
	MyVector3(float x, float y, float z);
	// 복사 생성자
	MyVector3(const MyVector3& rhs);

	// 소멸자
	~MyVector3() {}

	// 현재 벡터의 길이 리턴
	float Length();

	// 현재 벡터의 단위 벡터 리턴
	MyVector3 Normalize();

	// 벡터에 스칼라를 곱한 벡터 리턴
	MyVector3 Scale(float x, float y, float z);

	// 벡터의 내적 - 현재 벡터와 rhs 벡터간의 내적 리턴
	float Dot(const MyVector3& rhs);

	// 벡터의 외적 - u 벡터와 v 벡터간의 외적 벡터를 현재 벡터에 대입
	void Cross(const MyVector3& u, const MyVector3& v);

	// rhs 벡터의 모든 멤버 변수를 현재 벡터에 복사
	void operator=(const MyVector3& rhs);
	// 현재 벡터와 rhs 벡터의 덧셈한 결과 벡터 리턴
	MyVector3 operator+(const MyVector3& rhs);
	// 현재 벡터와 rhs 벡터의 뺄셈한 결과 벡터 리턴
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
	// 행렬의 원소
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

	// 생성자
	MyMatrix();
	// 소멸자
	~MyMatrix() {}

	// 단위 행렬
	void Identity();
	// 전치 행렬
	MyMatrix Transpose();

	// 신축
	void Scale(float x, float y, float z);
	// 회전
	void RotationX(float radian);
	void RotationY(float radian);
	void RotationZ(float radian);
	// 이동
	void Translation(float x, float y, float z);

	// 행렬의 곱셈
	MyMatrix operator*(const MyMatrix& rhs) const;

	// 뷰
	void ObjectLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp);
	MyMatrix ViewLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp);

	// 투영
	MyMatrix OrthoLH(float w, float h, float n, float f);
	MyMatrix OrthoOffCenterLH(float l, float r, float b, float t, float n, float f);
	MyMatrix PerspectiveFovLH(float NearPlane, float FarPlane, float FovY, float AspectRatio);
};

namespace StaticMatrix
{
	// 신축
	static MyMatrix Scale(float x, float y, float z)
	{
		MyMatrix m;
		m._11 = x;
		m._22 = y;
		m._33 = z;

		return m;
	}

	// 회전
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

	// 이동
	static MyMatrix Translation(float x, float y, float z)
	{
		MyMatrix m;
		m._41 = x;
		m._42 = y;
		m._43 = z;

		return m;
	}

	// 투영
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

	// 투영
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

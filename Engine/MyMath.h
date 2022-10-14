#pragma once

#include <math.h>

class MyVector2
{
public:
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
};

class MyVector3
{
public:
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

	//
	MyVector3 operator*(float scala);
	MyVector3 operator*=(float scala);
	MyVector3 operator*(class MyMatrix& m);

	// Dot Product
	float operator|(const MyVector3& v0);
	// Cross Product
	MyVector3 operator^(const MyVector3& v0);

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
};

class MyMatrix
{
public:
	// 생성자
	MyMatrix();
	// 소멸자
	~MyMatrix() {}

	// 단위 행렬
	void Identity();
	// 전치 행렬
	MyMatrix Transpose();

	// 신축
	MyMatrix Scale(float x, float y, float z);
	// 회전
	MyMatrix RotationX(float radian);
	MyMatrix RotationY(float radian);
	MyMatrix RotationZ(float radian);
	// 이동
	MyMatrix Translation(float x, float y, float z);

	//// 대입 연산자
	//MyMatrix& operator=(const MyMatrix& rhs);
	//// + 단항 연산자
	//MyMatrix& operator+();
	//// - 단항 연산자
	//MyMatrix operator-() const;

	//// 행렬의 덧셈
	//MyMatrix operator+(const MyMatrix& rhs) const;
	//MyMatrix& operator+=(const MyMatrix& rhs);
	//// 행렬의 뺄셈
	//MyMatrix operator-(const MyMatrix& rhs) const;
	//MyMatrix& operator-=(const MyMatrix& rhs);
	// 행렬의 곱셈
	MyMatrix operator*(const MyMatrix& rhs) const;
	/*MyMatrix& operator*=(const MyMatrix& rhs);*/

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

	// 카메라 관련
	void ObjectLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp);
	MyMatrix ViewLookAt(MyVector3& vPosition, MyVector3& vTarget, MyVector3& vUp);
	MyMatrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect);
};


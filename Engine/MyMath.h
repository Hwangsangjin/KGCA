#pragma once

#include <math.h>

class MyVector
{
public:
	// 생성자 - 멤버 변수를 초기화
	MyVector();
	// x, y, z의 초기값을 입력으로 하는 생성자
	MyVector(float x, float y, float z);
	// 복사 생성자
	MyVector(const MyVector& rhs);

	// 소멸자
	~MyVector() {}

	// 현재 벡터의 길이 리턴
	float Length();

	// 현재 벡터의 단위 벡터 리턴
	MyVector Normalize();

	// 벡터에 스칼라를 곱한 벡터 리턴
	MyVector Scale(float x, float y, float z);

	// 벡터의 내적 - 현재 벡터와 rhs 벡터간의 내적 리턴
	float Dot(const MyVector& rhs);

	// 벡터의 외적 - u 벡터와 v 벡터간의 외적 벡터를 현재 벡터에 대입
	void Cross(const MyVector& u, const MyVector& v);

	// rhs 벡터의 모든 멤버 변수를 현재 벡터에 복사
	void operator=(const MyVector& rhs);
	// 현재 벡터와 rhs 벡터의 덧셈한 결과 벡터 리턴
	MyVector operator+(const MyVector& rhs);
	// 현재 벡터와 rhs 벡터의 뺄셈한 결과 벡터 리턴
	MyVector operator-(const MyVector& rhs);

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
	MyMatrix(const float rhs[16]);
	MyMatrix(const MyMatrix& rhs);

	// 소멸자
	~MyMatrix() {}

	// 단위 행렬
	void Identity();
	// 전치 행렬
	void Transpose();

	// 신축
	void Scale(float x, float y, float z);
	// 회전
	void RotationX(float radian);
	void RotationY(float radian);
	void RotationZ(float radian);
	// 이동
	void Translation(float x, float y, float z);

	// 대입 연산자
	MyMatrix& operator=(const MyMatrix& rhs);
	// + 단항 연산자
	MyMatrix& operator+();
	// - 단항 연산자
	MyMatrix operator-() const;

	// 행렬의 덧셈
	MyMatrix operator+(const MyMatrix& rhs) const;
	MyMatrix& operator+=(const MyMatrix& rhs);
	// 행렬의 뺄셈
	MyMatrix operator-(const MyMatrix& rhs) const;
	MyMatrix& operator-=(const MyMatrix& rhs);
	// 행렬의 곱셈
	MyMatrix operator*(const MyMatrix& rhs) const;
	MyMatrix& operator*=(const MyMatrix& rhs);

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

		float _m[16];
	};
};


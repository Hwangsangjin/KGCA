#pragma once

#include <math.h>
#include <iostream>

class Vector2
{
public:
	// 구조체와 배열을 같이 사용하기 위한 공용체
	union
	{
		struct { float _x, _y; };
		float _v[2] = { 0 };
	};

	// 상수
	static const Vector2 ZERO;	// 제로 벡터
	static const Vector2 LEFT;	// 왼쪽
	static const Vector2 RIGHT;	// 오른쪽
	static const Vector2 UP;	// 위
	static const Vector2 DOWN;	// 아래

	// 생성자
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y);
	Vector2(const Vector2& v);

	// 내적 계산
	float Dot(const Vector2& other) const;

	// 길이 계산
	float Length() const;
	float LenghtSquared() const;

	// 거리 계산
	float distance(const Vector2& other) const;

	// 정규화
	Vector2 Normalize() const;

	// 제로 벡터 확인
	bool IsZero() const;

	// 연산자 오버로드
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float scalar);
	Vector2& operator/=(float scalar);
	const Vector2 operator+(const Vector2& other) const;
	const Vector2 operator-(const Vector2& other) const;
	const Vector2 operator*(float scalar) const;
	const Vector2 operator/(float scalar) const;
	const Vector2 operator-() const;
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;
	bool operator<(const Vector2& other) const;

	//friend Vector2 operator*(float scalar, const Vector2& vec);

	Vector2 Normalize()
	{
		float magnitude = sqrtf(_x * _x + _y * _y);
		
		return (*this) / magnitude;
	}
};


#pragma once

#include <math.h>
#include <iostream>

class Vector2
{
public:
	// ����ü�� �迭�� ���� ����ϱ� ���� ����ü
	union
	{
		struct { float _x, _y; };
		float _v[2] = { 0 };
	};

	// ���
	static const Vector2 ZERO;	// ���� ����
	static const Vector2 LEFT;	// ����
	static const Vector2 RIGHT;	// ������
	static const Vector2 UP;	// ��
	static const Vector2 DOWN;	// �Ʒ�

	// ������
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y);
	Vector2(const Vector2& v);

	// ���� ���
	float Dot(const Vector2& other) const;

	// ���� ���
	float Length() const;
	float LenghtSquared() const;

	// �Ÿ� ���
	float distance(const Vector2& other) const;

	// ����ȭ
	Vector2 Normalize() const;

	// ���� ���� Ȯ��
	bool IsZero() const;

	// ������ �����ε�
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


#pragma once

struct Vector2
{
	// 정적 멤버변수 
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 UnitZ;
	static const Vector2 One;
	static const Vector2 Zero;
	static const unsigned char Dimension = 2;

	// 멤버 변수
	union
	{
		struct
		{
			struct { float _x, _y; };
		};

		std::array<float, Dimension> _scalars = { 0.0f, 0.0f };
	};

	// 생성자
	Vector2() = default;
	Vector2(float x, float y);
	Vector2(const Vector2& vector);

	// 연산자
	const Vector2& operator+=(const Vector2& other);
	const Vector2& operator-=(const Vector2& other);
	const Vector2& operator*=(float scalar);
	const Vector2& operator/=(float scalar);
	const Vector2 operator+(const Vector2& other) const;
	const Vector2 operator-(const Vector2& other) const;
	const Vector2 operator*(float scalar) const;
	const Vector2 operator/(float scalar) const;
	const Vector2 operator-() const;
	const bool operator==(const Vector2& other) const;
	const bool operator!=(const Vector2& other) const;
	const bool operator<(const Vector2& other) const;

	// 내적 계산
	float Dot(const Vector2& other) const;

	// 길이 계산
	float Size() const;
	float SizeSquared() const;

	// 정규화
	void Normalize();
	Vector2 GetNormalize() const;
};


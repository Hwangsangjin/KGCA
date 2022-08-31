#pragma once

struct Vector4
{
	// 정적멤버변수
	static const Vector4 UnitX;
	static const Vector4 UnitY;
	static const Vector4 UnitZ;
	static const Vector4 UnitW;
	static const Vector4 One;
	static const Vector4 Zero;
	static const unsigned char Dimension = 4;

	// 멤버변수
	union
	{
		struct { float x, y, z, w; };

		std::array<float, Dimension> scalars = { 0.0f, 0.0f, 0.0f, 0.0f };
	};

	// 생성자
	Vector4() = default;
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4& vector);

	// 연산자
	const Vector4& operator+=(const Vector4& other);
	const Vector4& operator-=(const Vector4& other);
	const Vector4& operator*=(float scalar);
	const Vector4& operator/=(float scalar);
	const Vector4 operator+(const Vector4& other) const;
	const Vector4 operator-(const Vector4& other) const;
	const Vector4 operator*(float scalar) const;
	const Vector4 operator/(float scalar) const;
	const Vector4 operator-() const;
	const bool operator==(const Vector4& other) const;
	const bool operator!=(const Vector4& other) const;
	const bool operator<=(const Vector4& other) const;
	const bool operator>=(const Vector4& other) const;

	// 내적 계산
	float Dot(const Vector4& other) const;

	// 각도 계산
	float Angle(const Vector4& other) const;

	// 길이 계산
	float Length() const;
	float LengthSquared() const;

	// 거리 계산
	float Distance(const Vector4& other) const;

	// 정규화
	void Normalize();
	Vector4 Identity() const;
};

